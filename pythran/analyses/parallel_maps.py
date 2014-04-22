"""
ParallelMaps detects parallel map(...)
"""
import ast
from aliases import Aliases
from pure_expressions import PureExpressions
from pythran.passmanager import ModuleAnalysis
from pythran.tables import modules


class ParallelMaps(ModuleAnalysis):
    '''Yields the est of maps that could be parallel'''
    def __init__(self):
        self.result = set()
        super(ParallelMaps, self).__init__(PureExpressions, Aliases)

    def visit_Call(self, node):
        if all(alias == modules['__builtin__']['map']
                for alias in self.aliases[node.func].aliases):
            if all(self.pure_expressions.__contains__(f)
                    for f in self.aliases[node.args[0]].aliases):
                self.result.add(node)

    def display(self, data):
        for node in data:
            print "I:", "{0} {1}".format(
                "call to the `map' intrinsic could be parallel",
                "(line {0})".format(node.lineno)
                )
