"""
Dependencies lists the functions and types required by a function
"""

from pythran.passmanager import ModuleAnalysis
from pythran.conversion import demangle

import gast as ast
import math


class Dependencies(ModuleAnalysis):
    def __init__(self):
        self.result = set()
        super(Dependencies, self).__init__()

    def visit_List(self, node):
        self.result.add(('__builtin__', 'list'))
        self.generic_visit(node)

    def visit_Tuple(self, node):
        self.result.add(('__builtin__', 'tuple'))
        self.generic_visit(node)

    def visit_Set(self, node):
        self.result.add(('__builtin__', 'set'))
        self.generic_visit(node)

    def visit_Dict(self, node):
        self.result.add(('__builtin__', 'dict'))
        self.generic_visit(node)

    def visit_Str(self, node):
        self.result.add(('types', 'str'))
        self.generic_visit(node)

    def visit_Pow(self, node):
        self.result.add(('__builtin__', 'pow'))
        self.generic_visit(node)

    def visit_MatMult(self, node):
        self.result.add(('operator_', 'matmul'))
        self.generic_visit(node)

    def visit_In(self, node):
        self.result.add(('__builtin__', 'in'))
        self.generic_visit(node)

    visit_NotIn = visit_In

    def visit_Is(self, node):
        self.result.add(('__builtin__', 'id'))
        self.generic_visit(node)

    visit_IsNot = visit_Is

    def visit_IfExp(self, node):
        self.result.add(('__builtin__', 'pythran', 'ifexp'))
        self.generic_visit(node)

    def visit_And(self, node):
        self.result.add(('__builtin__', 'pythran', 'and_'))
        self.generic_visit(node)

    def visit_Or(self, node):
        self.result.add(('__builtin__', 'pythran', 'or_'))
        self.generic_visit(node)

    def visit_Print(self, node):
        self.result.add(('__builtin__', 'print'))
        self.generic_visit(node)

    def visit_Assert(self, node):
        self.result.add(('__builtin__', 'assert'))
        self.generic_visit(node)

    def visit_Yield(self, node):
        self.result.add(('utils', 'yield'))
        self.generic_visit(node)

    def visit_Mod(self, _):
        self.result.add(('operator_', 'mod'))

    def visit_Div(self, _):
        self.result.add(('operator_', 'div'))

    def visit_FloorDiv(self, _):
        self.result.add(('operator_', 'floordiv'))

    def visit_Num(self, node):
        if isinstance(node.n, complex):
            self.result.add(('types', 'complex'))
        elif isinstance(node.n, long):
            self.result.add(('types', 'long'))
        elif math.isnan(node.n):
            self.result.add(('numpy', 'nan'))
        elif math.isinf(node.n):
            self.result.add(('numpy', 'inf'))

        self.generic_visit(node)

    def visit_Attribute(self, node):
        def rec(n):
            if isinstance(n, ast.Name):
                return demangle(n.id),
            elif isinstance(n, ast.Attribute):
                return rec(n.value) + (n.attr,)
        attr = rec(node)

        attr and self.result.add(attr)
