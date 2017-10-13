""" ListToTuple transforms some List node into more Efficient Tuple nodes. """

from pythran.analyses import Aliases
from pythran.tables import MODULES
from pythran.passmanager import Transformation

import gast as ast
import copy

patterns = (MODULES['numpy']['ones'],
            MODULES['numpy']['zeros'],
            MODULES['numpy']['empty'],
            )


def islist(node):
    return isinstance(node, ast.List)


def totuple(node):
    return ast.Tuple(node.elts, node.ctx)


class ListToTuple(Transformation):

    """
    Replace list nodes by tuple nodes when possible

    >>> import gast as ast
    >>> from pythran import passmanager, backend
    >>> node = ast.parse("def foo(n): import numpy; return numpy.ones([n,n])")
    >>> pm = passmanager.PassManager("test")
    >>> _, node = pm.apply(ListToTuple, node)
    >>> print(pm.dump(backend.Python, node))
    def foo(n):
        import numpy
        return numpy.ones((n, n))
    """
    def __init__(self):
        self.update = False
        super(ListToTuple, self).__init__(Aliases)

    def visit_AugAssign(self, node):
        if not islist(node.value):
            return self.generic_visit(node)
        node.value = totuple(node.value)
        self.update = True
        return self.generic_visit(node)

    def visit_Call(self, node):
        func_aliases = self.aliases[node.func]
        if func_aliases.issubset(patterns):
            if islist(node.args[0]):
                node.args[0] = totuple(node.args[0])
        return self.generic_visit(node)
