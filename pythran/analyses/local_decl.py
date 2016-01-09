""" LocalDecl gathers declarations local to a node. """

from pythran.passmanager import NodeAnalysis

import ast


class LocalDecl(NodeAnalysis):

    """
    Gathers all local identifiers from a node.

    >>> import ast
    >>> from pythran import passmanager, backend
    >>> node = ast.parse('''
    ... def foo(a):
    ...     b = a + 1''')
    >>> pm = passmanager.PassManager("test")
    >>> pm.gather(LocalDecl, node)
    set(['a', 'foo', 'b'])
    """

    def __init__(self):
        """ Initialize empty set as the result. """
        self.result = set()
        super(LocalDecl, self).__init__()

    def visit_Name(self, node):
        """ Any node with Store or Param context is a new identifier. """
        if isinstance(node.ctx, (ast.Store, ast.Param)):
            self.result.add(node.id)

    def visit_FunctionDef(self, node):
        """ Function name is a possible identifier. """
        self.result.add(node.name)
        self.generic_visit(node)
