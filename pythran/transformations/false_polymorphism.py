"""
FalsePolymorphism rename variable if possible to avoid false polymorphism
"""
import ast
from pythran.passmanager import Transformation
from pythran.analyses import UseDefChain, UseOMP, Globals, Identifiers


class FalsePolymorphism(Transformation):
    """
    Rename variable when possible to avoid false polymorphism.
    >>> import ast, passmanager, backend
    >>> node = ast.parse("def foo(): a = 12; a = 'babar'")
    >>> pm = passmanager.PassManager("test")
    >>> node = pm.apply(FalsePolymorphism, node)
    >>> print pm.dump(backend.Python, node)
    def foo():
        a = 12
        a_ = 'babar'
    """
    def __init__(self):
        super(FalsePolymorphism, self).__init__(UseDefChain, UseOMP)

    def visit_FunctionDef(self, node):
        #function using openmp are ignored
        if not self.use_omp:
            self.identifiers = self.passmanager.gather(Identifiers, node,
                                                       self.ctx)
            for name, udgraph in self.use_def_chain.iteritems():
                group_variable = list()
                while udgraph:
                    e = udgraph.nodes_iter().next()
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
                    self.identifiers.remove(name)
                    for group in group_variable:
                        while name in self.identifiers:
                            name += "_"
                        for var in group:
                            var.id = name
                        self.identifiers.add(name)
        return node
