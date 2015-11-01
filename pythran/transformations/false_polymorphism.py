""" FalsePolymorphism try to rename variable to avoid false polymorphism."""

from pythran.passmanager import Transformation
from pythran.analyses import UseDefChain, UseOMP, Identifiers

import networkx as nx


class FalsePolymorphism(Transformation):

    """
    Rename variable when possible to avoid false polymorphism.

    >>> import ast
    >>> from pythran import passmanager, backend
    >>> node = ast.parse("def foo(): a = 12; a = 'babar'")
    >>> pm = passmanager.PassManager("test")
    >>> _, node = pm.apply(FalsePolymorphism, node)
    >>> print pm.dump(backend.Python, node)
    def foo():
        a = 12
        a_ = 'babar'
    """

    def __init__(self):
        super(FalsePolymorphism, self).__init__(UseDefChain, UseOMP)

    def visit_FunctionDef(self, node):
        # function using openmp are ignored
        if not self.use_omp:
            identifiers = self.passmanager.gather(Identifiers, node, self.ctx)
            for name, udgraph_ in self.use_def_chain.iteritems():
                udgraph = nx.DiGraph(udgraph_)  # Shallow copy
                group_variable = list()
                # changing the result of an analyse disturbs caching -> COPY
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
                    identifiers.remove(name)
                    for group in group_variable:
                        while name in identifiers:
                            name += "_"
                        for var in group:
                            self.update |= var.id != name
                            var.id = name
                        identifiers.add(name)
        return node
