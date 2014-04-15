"""
GlobalDeclarations gathers top-level declarations
"""
import ast
from pythran.passmanager import ModuleAnalysis


class GlobalDeclarations(ModuleAnalysis):
    """Generates a function name -> function node binding"""
    def __init__(self):
        self.result = dict()
        super(GlobalDeclarations, self).__init__()

    def visit_Import(self, node):
        self.result.update((a.name, a) for a in node.names)

    def visit_ImportFrom(self, node):
        self.result.update((a.asname or a.name, a) for a in node.names)

    def visit_FunctionDef(self, node):
        self.result[node.name] = node
        # no generic visit here, so no diving into function body
