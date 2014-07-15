"""
Ancestors computes the ancestors of each node
"""

from pythran.passmanager import ModuleAnalysis


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
        self.current.append(node)
        super(Ancestors, self).generic_visit(node)
        self.current.pop()
