"""
LocalDeclarations gathers declarations local to a node
"""
import ast
from pythran.passmanager import NodeAnalysis


class LocalDeclarations(NodeAnalysis):
    """Gathers all local symbols from a function"""
    def __init__(self):
        self.result = set()
        super(LocalDeclarations, self).__init__()

    def visit_Assign(self, node):
        for t in node.targets:
            assert isinstance(t, ast.Name) or isinstance(t, ast.Subscript)
            if isinstance(t, ast.Name):
                self.result.add(t)

    def visit_For(self, node):
        assert isinstance(node.target, ast.Name)
        self.result.add(node.target)
        map(self.visit, node.body)
        map(self.visit, node.orelse)
