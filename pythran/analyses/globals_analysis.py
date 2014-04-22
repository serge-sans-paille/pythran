"""
Globals computes the value of globals()
"""
import ast
from global_declarations import GlobalDeclarations
from pythran.passmanager import ModuleAnalysis
from pythran.tables import modules


class Globals(ModuleAnalysis):
    def __init__(self):
        self.result = set()
        super(Globals, self).__init__(GlobalDeclarations)

    def visit(self, node):
        pass  # everything is done by the run method

    def run(self, node, ctx):
        super(Globals, self).run(node, ctx)
        return set(self.global_declarations.keys()
                   + [i for i in modules if i.startswith('__')])
