""" Gathers variables that have value modification in the given node. """

from pythran.passmanager import NodeAnalysis

from collections import defaultdict
import ast


class IsAssigned(NodeAnalysis):

    """
    Gather variable that change in given node.

    It doesn't check constness as it is use for integer so we don't care about
    arguments effects as it is use by value.
    """

    def __init__(self):
        """ Basic initialiser. """
        self.result = defaultdict(bool)
        super(IsAssigned, self).__init__()

    def visit_Name(self, node):
        """ Stored variable have new value. """
        if isinstance(node.ctx, ast.Store):
            self.result[node.id] = True
