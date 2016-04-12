""" ParallelMaps detects parallel map(...).  """
from __future__ import print_function

from pythran.analyses.aliases import Aliases
from pythran.analyses.pure_expressions import PureExpressions
from pythran.passmanager import ModuleAnalysis
from pythran.tables import MODULES


class ParallelMaps(ModuleAnalysis):

    """Yields the est of maps that could be parallel."""

    def __init__(self):
        self.result = set()
        super(ParallelMaps, self).__init__(PureExpressions, Aliases)

    def visit_Call(self, node):
        if all(alias == MODULES['__builtin__']['map']
               for alias in self.aliases[node.func]):
            if all(self.pure_expressions.__contains__(f)
                    for f in self.aliases[node.args[0]]):
                self.result.add(node)

    def display(self, data):
        for node in data:
            print("I:", "{0} {1}".format(
                "call to the `map' intrinsic could be parallel",
                "(line {0})".format(node.lineno)
                ))
