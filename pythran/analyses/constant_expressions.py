"""
ConstantExpressions gathers constant expression
"""
import ast
from aliases import Aliases
from globals_analysis import Globals
from locals_analysis import Locals
from pure_expressions import PureExpressions
from pythran.intrinsic import Intrinsic
from pythran.passmanager import NodeAnalysis
from pythran.tables import modules


class ConstantExpressions(NodeAnalysis):
    """Identify constant expressions"""
    def __init__(self):
        self.result = set()
        super(ConstantExpressions, self).__init__(Globals, Locals,
                                                  PureExpressions, Aliases)

    def add(self, node):
        self.result.add(node)
        return True

    def visit_BoolOp(self, node):
        return all(map(self.visit, node.values)) and self.add(node)

    def visit_BinOp(self, node):
        rec = all(map(self.visit, (node.left, node.right)))
        return rec and self.add(node)

    def visit_UnaryOp(self, node):
        return self.visit(node.operand) and self.add(node)

    def visit_IfExp(self, node):
        rec = all(map(self.visit, (node.test, node.body, node.orelse)))
        return rec and self.add(node)

    def visit_Compare(self, node):
        rec = all(map(self.visit, [node.left] + node.comparators))
        return rec and self.add(node)

    def visit_Call(self, node):
        rec = all(map(self.visit, node.args + [node.func]))
        return rec and self.add(node)

    visit_Num = add
    visit_Str = add

    def visit_Subscript(self, node):
        rec = all(map(self.visit, (node.value, node.slice)))
        return rec and self.add(node)

    def visit_Name(self, node):
        if node in self.aliases:
            is_function = lambda x: (isinstance(x, Intrinsic) or
                                     isinstance(x, ast.FunctionDef) or
                                     isinstance(x, ast.alias))
            pure_fun = all(alias in self.pure_expressions and
                           is_function(alias)
                           for alias in self.aliases[node].aliases)
            return pure_fun and self.add(node)
        else:
            return False

    def visit_Attribute(self, node):
        def rec(w, n):
            if isinstance(n, ast.Name):
                return w[n.id]
            elif isinstance(n, ast.Attribute):
                return rec(w, n.value)[n.attr]
        return rec(modules, node).isconst() and self.add(node)

    def visit_Dict(self, node):
        rec = all(map(self.visit, node.keys + node.values))
        return rec and self.add(node)

    def visit_List(self, node):
        return all(map(self.visit, node.elts)) and self.add(node)

    visit_Tuple = visit_List
    visit_Set = visit_List

    def visit_Slice(self, node):
        # ultra-conservative, indeed
        return False

    def visit_Index(self, node):
        return self.visit(node.value) and self.add(node)
