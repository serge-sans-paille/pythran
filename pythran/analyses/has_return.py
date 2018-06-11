"""
HasReturn detects if there's a return or yield statement
"""

from pythran.passmanager import NodeAnalysis


class HasReturn(NodeAnalysis):

    def __init__(self):
        self.result = False
        super(HasReturn, self).__init__()

    def visit_Return(self, _):
        self.result = True

    def visit_Yield(self, _):
        self.result = True
