"""
HasContinue detects if a loop has a direct continue
"""

from pythran.passmanager import NodeAnalysis


class HasContinue(NodeAnalysis):

    def __init__(self):
        self.result = False
        super(HasContinue, self).__init__()

    def visit_For(self, _):
        return

    def visit_Continue(self, _):
        self.result = True
