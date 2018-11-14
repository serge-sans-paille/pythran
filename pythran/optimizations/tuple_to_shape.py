""" TupleToShap transforms some Tuple node into shape nodes when relevant. """

from pythran.analyses import Aliases
from pythran.tables import MODULES
from pythran.passmanager import Transformation
from pythran.utils import pythran_builtin_attr

import gast as ast

patterns = (MODULES['numpy']['ones'],
            MODULES['numpy']['zeros'],
            MODULES['numpy']['empty'],
            )


def istuple(node):
    return isinstance(node, ast.Tuple)

def toshape(node):
    b = pythran_builtin_attr("make_shape")
    return ast.Call(b, node.elts, [])

class TupleToShape(Transformation):

    """
    Replace tuple nodes by shape when relevant

    >>> import gast as ast
    >>> from pythran import passmanager, backend
    >>> node = ast.parse("def foo(n): import numpy; return numpy.ones((n,4))")
    >>> pm = passmanager.PassManager("test")
    >>> _, node = pm.apply(TupleToShape, node)
    >>> print(pm.dump(backend.Python, node))
    def foo(n):
        import numpy
        return numpy.ones(__builtin__.pythran.make_shape(n, 4))
    """
    def __init__(self):
        self.update = False
        super(TupleToShape, self).__init__(Aliases)

    def visit_Call(self, node):
        func_aliases = self.aliases.get(node.func, None)
        if not func_aliases is None and func_aliases.issubset(patterns):
            if istuple(node.args[0]):
                self.update = True
                node.args[0] = toshape(node.args[0])
        return self.generic_visit(node)
