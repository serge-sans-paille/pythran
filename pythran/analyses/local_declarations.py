""" LocalDeclarations gathers declarations local to a node. """

from pythran.passmanager import NodeAnalysis

import ast


class LocalDeclarations(NodeAnalysis):

    """
    Gathers all local symbols from a function.

    It should not be use from outside a function.

    >>> import ast
    >>> from pythran import passmanager, backend
    >>> node = ast.parse('''
    ... def foo(a):
    ...     b = a + 1''')
    >>> pm = passmanager.PassManager("test")
    >>> [name.id for name in pm.gather(LocalDeclarations, node)]
    ['b']
    >>> node = ast.parse('''
    ... for c in xrange(n):
    ...     b = a + 1''')
    >>> pm = passmanager.PassManager("test")
    >>> sorted([name.id for name in pm.gather(LocalDeclarations, node)])
    ['b', 'c']
    """

    def __init__(self):
        """ Initialize empty set as the result. """
        self.result = set()
        super(LocalDeclarations, self).__init__()

    def visit_Name(self, node):
        """ Any node with Store context is a new declaration. """
        if isinstance(node.ctx, ast.Store):
            self.result.add(node)
