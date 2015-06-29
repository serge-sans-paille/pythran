"""
Dependencies lists the functions and types required by a function
"""

from pythran.passmanager import ModuleAnalysis
from pythran.tables import MODULES

import ast
import math
import sys


class Dependencies(ModuleAnalysis):
    def __init__(self):
        self.result = set()
        super(Dependencies, self).__init__()

    def visit_List(self, node):
        self.result.add(('builtins', 'list'))
        self.generic_visit(node)

    def visit_Tuple(self, node):
        self.result.add(('builtins', 'tuple'))
        self.generic_visit(node)

    def visit_Set(self, node):
        self.result.add(('builtins', 'set'))
        self.generic_visit(node)

    def visit_Dict(self, node):
        self.result.add(('builtins', 'dict'))
        self.generic_visit(node)

    def visit_Str(self, node):
        self.result.add(('builtins', 'str'))
        self.generic_visit(node)

    def visit_Pow(self, node):
        self.result.add(('builtins', 'pow'))
        self.generic_visit(node)

    def visit_In(self, node):
        self.result.add(('builtins', 'in'))
        self.generic_visit(node)

    visit_NotIn = visit_In

    def visit_Is(self, node):
        self.result.add(('builtins', 'id'))
        self.generic_visit(node)

    def visit_IfExp(self, node):
        self.result.add(('builtins', 'bool_'))
        self.generic_visit(node)

    visit_And = visit_Or = visit_IfExp

    visit_IsNot = visit_Is

    def visit_Print(self, node):
        self.result.add(('builtins', 'print'))
        self.generic_visit(node)

    def visit_Assert(self, node):
        self.result.add(('builtins', 'assert'))
        self.generic_visit(node)

    def visit_Yield(self, node):
        self.result.add(('utils', 'yield'))
        self.generic_visit(node)

    def visit_Mod(self, node):
        self.result.add(('operator_', 'mod'))

    def visit_FloorDiv(self, node):
        self.result.add(('operator_', 'floordiv'))

    def visit_Num(self, node):
        if type(node.n) is complex:
            self.result.add(('types', 'complex'))
        elif sys.version_info[0] < 3 and type(node.n) is long:
            self.result.add(('types', 'long'))
        elif math.isnan(node.n):
            self.result.add(('numpy', 'nan'))
        elif math.isinf(node.n):
            self.result.add(('numpy', 'inf'))

        self.generic_visit(node)

    def visit_Attribute(self, node):
        def rec(w, n):
            if isinstance(n, ast.Name):
                return (n.id,)
            elif isinstance(n, ast.Attribute):
                return rec(w, n.value) + (n.attr,)
        attr = rec(MODULES, node)

        if attr:
            self.result.add(attr)
