"""
Ancestors computes the ancestors of each node
"""

from pythran.passmanager import ModuleAnalysis
from pythran.utils import pushpop


class Ancestors(ModuleAnalysis):
    '''
    Associate each node with the list of its ancestors

    Based on the tree view of the AST: each node has the Module as parent.
    The result of this analysis is a dictionary with nodes as key,
    and list of nodes as values.
    '''

    def __init__(self):
        self.result = dict()
        self.current = list()
        super(Ancestors, self).__init__()

    def generic_visit(self, node):
        self.result[node] = list(self.current)
        with pushpop(self.current, node):
            super(Ancestors, self).generic_visit(node)


class AncestorsWithBody(Ancestors):

    def visit_metadata(self, node):
        if hasattr(node, 'metadata'):
            self.generic_visit(node.metadata)

    def visit_body(self, body):
        body_as_tuple = tuple(body)
        self.result[body_as_tuple] = list(self.current)
        with pushpop(self.current, body_as_tuple):
            for stmt in body:
                self.generic_visit(stmt)

    def visit_If(self, node):
        self.result[node] = list(self.current)
        with pushpop(self.current, node):
            self.generic_visit(node.test)
            self.visit_metadata(node)
            self.visit_body(node.body)
            self.visit_body(node.orelse)

    def visit_While(self, node):
        self.result[node] = list(self.current)
        with pushpop(self.current, node):
            self.generic_visit(node.test)
            self.visit_metadata(node)
            self.visit_body(node.body)
            self.visit_body(node.orelse)

    def visit_For(self, node):
        self.result[node] = list(self.current)
        with pushpop(self.current, node):
            self.generic_visit(node.target)
            self.generic_visit(node.iter)
            self.visit_metadata(node)
            self.visit_body(node.body)
            self.visit_body(node.orelse)

    def visit_Try(self, node):
        self.result[node] = list(self.current)
        with pushpop(self.current, node):
            self.visit_metadata(node)
            self.visit_body(node.body)
            for handler in node.handlers:
                self.generic_visit(handler)
            self.visit_body(node.orelse)
            self.visit_body(node.finalbody)
