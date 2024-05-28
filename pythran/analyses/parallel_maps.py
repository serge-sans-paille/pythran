""" ParallelMaps detects parallel map(...).  """

from pythran.analyses.aliases import Aliases
from pythran.analyses.pure_expressions import PureExpressions
from pythran.passmanager import ModuleAnalysis
from pythran.tables import MODULES


class ParallelMaps(ModuleAnalysis):

    """Yields the est of maps that could be parallel."""

    def __init__(self):
        self.result = set()
        super().__init__(PureExpressions, Aliases)

    def visit_Call(self, node):
        if all(alias == MODULES['builtins']['map']
               for alias in self.aliases[node.func]):
            if all(f in self.pure_expressions
                   for f in self.aliases[node.args[0]]):
                self.result.add(node)

    def display(self, data):
        for node in data:
            print("I:", "{} {}".format(
                "call to the `map' intrinsic could be parallel",
                f"(line {node.lineno})"
                ))
