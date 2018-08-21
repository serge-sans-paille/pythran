""" StaticExpressions gathers constant expression that involve types.  """

from pythran.passmanager import NodeAnalysis


class StaticExpressions(NodeAnalysis):

    """Identify constant expressions."""

    def __init__(self):
        self.result = set()
        self.constant_expressions = set()
        super(StaticExpressions, self).__init__()

    def add(self, node):
        self.result.add(node)
        return True

    def not_add(self, _):
        return False

    def match_all(self, *args):
        static = False
        const = True
        for value in args:
            if self.visit(value):
                static = True
            else:
                const &= value in self.constant_expressions
        return static and const

    def visit_BoolOp(self, node):
        return self.match_all(*node.values) and self.add(node)

    def visit_BinOp(self, node):
        return self.match_all(node.left, node.right) and self.add(node)

    def visit_UnaryOp(self, node):
        return self.visit(node.operand) and self.add(node)

    def visit_IfExp(self, node):
        return (self.match_all(node.test, node.body, node.orelse)
                and self.add(node))

    def visit_Compare(self, node):
        return self.match_all(node.left, *node.comparators) and self.add(node)

    def visit_Call(self, node):
        return self.visit(node.func) and self.match_all(*node.args) and self.add(node)  # very limited

    def visit_Attribute(self, node):
        return node.attr == 'is_none'

    def add_to_constant_expressions(self, node):
        self.constant_expressions.add(node)

    visit_Num = add_to_constant_expressions
    visit_Str = add_to_constant_expressions

    visit_Subscript = not_add
    visit_Name = not_add
    visit_Dict = not_add
    visit_List = not_add
    visit_Tuple = not_add
    visit_Set = not_add
    visit_Slice = not_add
    visit_Index = not_add
