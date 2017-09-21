""" Scalar renaming try to rename variable to avoid false polymorphism."""

from pythran.passmanager import Transformation
from pythran.analyses import UseDefChain, UseOMP, Identifiers

import networkx as nx
import gast as ast


class ScalarRenaming(Transformation):

    """
    Rename variable when possible to avoid false polymorphism.

    >>> import gast as ast
    >>> from pythran import passmanager, backend
    >>> node = ast.parse("def foo(): a = 12; a = 'babar'")
    >>> pm = passmanager.PassManager("test")
    >>> _, node = pm.apply(ScalarRenaming, node)
    >>> print pm.dump(backend.Python, node)
    def foo():
        a = 12
        a_ = 'babar'
    """

    def __init__(self):
        super(ScalarRenaming, self).__init__(UseDefChain, UseOMP)

    def visit_FunctionDef(self, node):
        # function using openmp are ignored
        if not self.use_omp:
            identifiers = self.passmanager.gather(Identifiers, node, self.ctx)
            for name, udgraph_ in self.use_def_chain.items():
                udgraph = nx.DiGraph(udgraph_)  # Shallow copy
                group_variable = list()
                # changing the result of an analyse disturbs caching -> COPY
                while udgraph:
                    e = next(udgraph.nodes_iter())
                    to_change = set()
                    to_analyse_pred = set([e])
                    to_analyse_succ = set()
                    while to_analyse_pred or to_analyse_succ:
                        if to_analyse_pred:
                            n = to_analyse_pred.pop()
                            to_change.add(n)
                            to_analyse_succ.update(udgraph.successors(n))
                            to_analyse_succ -= to_change
                        else:
                            n = to_analyse_succ.pop()
                            if (udgraph.node[n]['action'] == 'U' or
                                    udgraph.node[n]['action'] == 'UD'):
                                to_change.add(n)
                                to_analyse_succ.update(udgraph.successors(n))
                                to_analyse_succ -= to_change
                        if (udgraph.node[n]['action'] == 'U' or
                                udgraph.node[n]['action'] == 'UD'):
                            to_analyse_pred.update(udgraph.predecessors(n))
                            to_analyse_pred -= to_change
                    nodes_to_change = [udgraph.node[k]['name']
                                       for k in to_change]
                    group_variable.append(nodes_to_change)
                    udgraph.remove_nodes_from(to_change)
                if len(group_variable) > 1:
                    identifiers.remove(name)
                    for group in group_variable:
                        while name in identifiers:
                            name += "_"
                        for var in group:
                            self.update |= var.id != name
                            var.id = name
                        identifiers.add(name)
            self.identifiers = identifiers
        return self.generic_visit(node)


class PhiInsertion(Transformation):
    """
    Insert phi-function equivalent

    >>> import gast as ast
    >>> from pythran import passmanager, backend
    >>> node = ast.parse("def foo(a):\n if a\n  a = 2\n else:\n  a = 1\n a")
    >>> pm = passmanager.PassManager("test")
    >>> _, node = pm.apply(FalsePolymorphism, node)
    >>> print pm.dump(backend.Python, node)
    def foo(a):
        if a:
            a_ = 2
        else:
            a_ = 1
        a_
    """

    def visit_Module(self, node):
        self.identifiers = self.passmanager.gather(Identifiers, node, self.ctx)
        return self.generic_visit(node)

    def visit_If(self, node):
        self.generic_visit(node)

        def isLoad(n):
            if isinstance(n, ast.Assign):
                return hasattr(n.targets[0], 'id')
            return False

        def getLoads(stmts):
            defs = dict()
            for i, stmt in reversed(list(enumerate(stmts))):
                if isinstance(stmt, ast.Expr):
                    continue
                elif isLoad(stmt):
                    if hasattr(stmt, 'target'):
                        defs[stmt.target.id] = i
                    else:
                        defs[stmt.targets[0].id] = i
                else:
                    break
            return defs
        body_defs = getLoads(node.body)
        orelse_defs = getLoads(node.orelse)
        new_defs = set(body_defs.keys()).intersection(orelse_defs.keys())

        renamed_new_defs = []
        for d in new_defs:
            new_d = d + '_'
            while new_d in self.identifiers:
                new_d += '_'
            renamed_new_defs.append(new_d)

            renamer = Renamer(d, new_d)
            for i in range(body_defs[d], len(body_defs)):
                node.body[i] = renamer.visit(node.body[i])
            for i in range(orelse_defs[d], len(orelse_defs)):
                node.orelse[i] = renamer.visit(node.orelse[i])

            self.update = True

        return [node] + [ast.Assign([ast.Name(d, ast.Store(), None)],
                                    ast.Name(new_d, ast.Load(), None))
                         for d, new_d in zip(new_defs, renamed_new_defs)]


class Renamer(ast.NodeTransformer):
    '''Helper class to perform renaming in PhiInsertion'''

    def __init__(self, old, new):
        self.renamings = {old: new}

    def visit_Name(self, node):
        node.id = self.renamings.get(node.id, node.id)
        return node
