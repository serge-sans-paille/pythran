""" Globals computes the value of globals(). """

from pythran.analyses.global_declarations import GlobalDeclarations
from pythran.passmanager import ModuleAnalysis
import sys


class Globals(ModuleAnalysis):
    def __init__(self):
        self.result = set()
        super(Globals, self).__init__(GlobalDeclarations)

    def visit(self, node):
        pass  # everything is done by the run method

    def run(self, node, ctx):
        super(Globals, self).run(node, ctx)
        default = {'builtins', '__dispatch__'}
        if sys.version_info[0] < 3:
            default.add('__builtin__')
        return default.union(self.global_declarations.keys())
