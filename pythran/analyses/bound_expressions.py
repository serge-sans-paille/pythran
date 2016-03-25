"""
BoundExpressions gathers temporary objects
"""

from pythran.passmanager import ModuleAnalysis

import ast


class BoundExpressions(ModuleAnalysis):
    '''Gathers all nodes that are bound to an identifier.'''

    Bindable = (
        ast.Name,
        ast.Subscript,
        ast.BoolOp,
        )

    def __init__(self):
        self.result = set()
        super(BoundExpressions, self).__init__()

    def isbindable(self, node):
        return any(isinstance(node, t) for t in BoundExpressions.Bindable)

    def visit_Assign(self, node):
        self.result.add(node.value)
        if self.isbindable(node.value):
            self.result.add(node.value)
        self.generic_visit(node)

    def visit_Call(self, node):
        for n in node.args:
            if self.isbindable(n):
                self.result.add(n)
        self.generic_visit(node)

    def visit_Return(self, node):
        node.value and self.visit(node.value)
        if node.value:
            self.result.add(node.value)
            if self.isbindable(node.value):
                self.result.add(node.value)
        self.generic_visit(node)

    def visit_BoolOp(self, node):
        if node in self.result:
            self.result.update(node.values)
        self.generic_visit(node)

    def visit_Subscript(self, node):
        if node in self.result:
            self.result.add(node.slice)
