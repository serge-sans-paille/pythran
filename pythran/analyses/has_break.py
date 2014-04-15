"""
HasBreak detects if a loop has a direct break
"""
from pythran.passmanager import NodeAnalysis


class HasBreak(NodeAnalysis):

    def __init__(self):
        self.result = False
        super(HasBreak, self).__init__()

    def visit_For(self, node):
        return

    def visit_Break(self, node):
        self.result = True
