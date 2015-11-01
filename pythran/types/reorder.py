""" Reorder top-level functions to prevent circular type dependencies.  """

import ast

import networkx as nx

from pythran.analyses import OrderedGlobalDeclarations
from pythran.passmanager import Transformation
from pythran.syntax import PythranSyntaxError
from pythran.types.type_dependencies import TypeDependencies


class Reorder(Transformation):

    """ Reorder top-level functions to prevent circular type dependencies.  """

    def __init__(self):
        """ Trigger others analysis informations. """
        super(Reorder, self).__init__(TypeDependencies,
                                      OrderedGlobalDeclarations)

    def prepare(self, node, ctx):
        """ Format type dependencies information to use if for reordering. """
        super(Reorder, self).prepare(node, ctx)
        none_successors = self.type_dependencies.successors(
            TypeDependencies.NoDeps)
        candidates = sorted(none_successors)
        # We first select function which may have a result without calling any
        # others functions.
        # Then we check if no loops type dependencies exists. If it exists, we
        # can safely remove the dependency as it could be compute without this
        # information.
        # As we can compute type for this function, successors can potentially
        # be computed
        # FIXME: This is false in some cases
        #
        # def bar(i):
        #   if i > 0:
        #     return foo(i)
        #   else:
        #     return []
        #
        # def foo(i):
        #   return [len(bar(i-1)) + len(bar(i - 2))]
        #
        # If we check for function without deps first, we will pick bar and say
        # it returns empty list
        while candidates:
            new_candidates = list()
            for n in candidates:
                # remove edges that imply a circular dependency
                for p in sorted(self.type_dependencies.predecessors(n)):
                    if nx.has_path(self.type_dependencies, n, p):
                        self.type_dependencies.remove_edge(p, n)
                if n not in self.type_dependencies.successors(n):
                    new_candidates.extend(self.type_dependencies.successors(n))
            candidates = new_candidates

    def visit_Module(self, node):
        """
        Keep everything but function definition then add sorted functions.

        Most of the time, many function sort work so we use function calldepth
        as a "sort hint" to simplify typing.
        """
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
            raise PythranSyntaxError("Infinite function recursion")

        assert set(newdef) == set(olddef), "A function have been lost..."
        node.body = newbody + newdef
        self.update = True
        return node
