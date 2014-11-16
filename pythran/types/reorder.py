import ast

import networkx as nx

from pythran.analyses import OrderedGlobalDeclarations
from pythran.passmanager import Transformation
from pythran.syntax import PythranSyntaxError
from pythran.types.type_dependencies import TypeDependencies


class Reorder(Transformation):

    """ Reorder top-level functions to prevent circular type dependencies.  """

    def __init__(self):
        Transformation.__init__(self, TypeDependencies,
                                OrderedGlobalDeclarations)

    def prepare(self, node, ctx):
        super(Reorder, self).prepare(node, ctx)
        none_successors = self.type_dependencies.successors(
            TypeDependencies.NoDeps)
        candidates = sorted(none_successors)
        while candidates:
            new_candidates = list()
            for n in candidates:
                # remove edges that imply a circular dependency
                for p in sorted(self.type_dependencies.predecessors(n)):
                    if nx.has_path(self.type_dependencies, n, p):
                        try:
                            while True:  # may be multiple edges
                                self.type_dependencies.remove_edge(p, n)
                        except:
                            pass  # no more edges to remove
                    # nx.write_dot(self.type_dependencies,"b.dot")
                if n not in self.type_dependencies.successors(n):
                    new_candidates.extend(self.type_dependencies.successors(n))
            candidates = new_candidates

    def visit_Module(self, node):
        newbody = list()
        olddef = list()
        for stmt in node.body:
            if isinstance(stmt, ast.FunctionDef):
                olddef.append(stmt)
            else:
                newbody.append(stmt)
            try:
                newdef = nx.topological_sort(
                    self.type_dependencies,
                    self.ordered_global_declarations)
                newdef = [f for f in newdef if isinstance(f, ast.FunctionDef)]

            except nx.exception.NetworkXUnfeasible:
                raise PythranSyntaxError("Infinite function recursion",
                                         stmt)
        assert set(newdef) == set(olddef)
        node.body = newbody + newdef
        return node
