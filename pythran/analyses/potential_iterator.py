"""
PotentialIterator finds if it is possible to use an iterator.
"""
import ast
from aliases import Aliases
from argument_read_once import ArgumentReadOnce
from pythran.passmanager import NodeAnalysis


class PotentialIterator(NodeAnalysis):
    """Find whether an expression can be replaced with an iterator."""
    def __init__(self):
        self.result = set()
        NodeAnalysis.__init__(self, Aliases, ArgumentReadOnce)

    def visit_For(self, node):
        self.result.add(node.iter)
        self.generic_visit(node)

    def visit_Compare(self, node):
        if type(node.ops[0]) in [ast.In, ast.NotIn]:
            self.result.update(node.comparators)
        self.generic_visit(node)

    def visit_Call(self, node):
        for i, arg in enumerate(node.args):
            isReadOnce = lambda f: (f in self.argument_read_once
                                    and self.argument_read_once[f][i] <= 1)
            if all(isReadOnce(alias)
                   for alias in self.aliases[node.func].aliases):
                self.result.add(arg)
        self.generic_visit(node)
