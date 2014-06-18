"""
ConstantExpressions gathers constant expression
"""
import ast
from aliases import Aliases
from globals_analysis import Globals
from locals_analysis import Locals
from pure_expressions import PureExpressions
from pythran.intrinsic import FunctionIntr
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
            # params and store are not constants
            if not isinstance(node.ctx, ast.Load):
                return False
            # if we can alias on multiple value, it is not constant
            elif len(self.aliases[node].aliases) > 1:
                return False
            # if it is not a globals, it depends on variable so it is not
            # constant
            elif node.id not in self.globals:
                return False
            # if it is defined in the current function, it is not constant
            elif node.id in self.locals[node]:
                return False
            is_function = lambda x: (isinstance(x, FunctionIntr) or
                                     isinstance(x, ast.FunctionDef) or
                                     isinstance(x, ast.alias))
            pure_fun = all(alias in self.pure_expressions and
                           is_function(alias)
                           for alias in self.aliases[node].aliases)
            return pure_fun
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
