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

    def visit_Slice(self, node):
        self.result.add(('types', 'slice'))
        self.generic_visit(node)

    def visit_Pow(self, node):
        self.result.add(('__builtin__', 'pow'))
        self.result.add(('operator', 'ipow'))

    def visit_Add(self, node):
        self.result.add(('operator', 'add'))

    def visit_Mult(self, node):
        self.result.add(('operator', 'mul'))

    def visit_MatMult(self, node):
        self.result.add(('operator', 'matmul'))
        self.result.add(('operator', 'imatmul'))

    def visit_Eq(self, node):
        self.result.add(('operator', 'eq'))

    def visit_NotEq(self, node):
        self.result.add(('operator', 'ne'))

    def visit_Lt(self, node):
        self.result.add(('operator', 'lt'))

    def visit_LtE(self, node):
        self.result.add(('operator', 'le'))

    def visit_Gt(self, node):
        self.result.add(('operator', 'gt'))

    def visit_GtE(self, node):
        self.result.add(('operator', 'ge'))

    def visit_In(self, node):
        self.result.add(('__builtin__', 'in'))

    visit_NotIn = visit_In

    def visit_Is(self, node):
        self.result.add(('__builtin__', 'id'))
        self.generic_visit(node)

    visit_IsNot = visit_Is

    def visit_Add(self, node):
        self.result.add(('operator', 'add'))

    def visit_And(self, node):
        self.result.add(('__builtin__', 'pythran', 'and'))
        self.generic_visit(node)

    def visit_Or(self, node):
        self.result.add(('__builtin__', 'pythran', 'or'))
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
        self.result.add(('operator', 'mod'))
        self.result.add(('operator', 'imod'))

    def visit_Div(self, _):
        self.result.add(('operator', 'div'))
        self.result.add(('operator', 'idiv'))

    def visit_FloorDiv(self, _):
        self.result.add(('operator', 'floordiv'))
        self.result.add(('operator', 'ifloordiv'))

    def visit_Constant(self, node):
        if node.value is None:
            self.result.add(('__builtin__', 'None'))
        elif isinstance(node.value, str):
            self.result.add(('types', 'str'))
        elif isinstance(node.value, complex):
            self.result.add(('types', 'complex'))
        elif math.isnan(node.value):
            self.result.add(('numpy', 'nan'))
        elif math.isinf(node.value):
            self.result.add(('numpy', 'inf'))

    def visit_Attribute(self, node):
        def rec(n):
            if isinstance(n, ast.Name):
                return demangle(n.id),
            elif isinstance(n, ast.Attribute):
                return rec(n.value) + (n.attr,)
        attr = rec(node)

        attr and self.result.add(attr)
