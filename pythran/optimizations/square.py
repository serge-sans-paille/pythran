""" Replaces **2 by a call to numpy.square. """

from pythran.passmanager import Transformation

import ast


class Square(Transformation):

    """
    Replaces **2 by a call to numpy.square.

    >>> import ast
    >>> from pythran import passmanager, backend
    >>> node = ast.parse('a**2')
    >>> pm = passmanager.PassManager("test")
    >>> _, node = pm.apply(Square, node)
    >>> print pm.dump(backend.Python, node)
    import numpy
    numpy.square(a)
    """

    def visit_Module(self, node):
        self.need_import = False
        self.generic_visit(node)
        if self.need_import:
            importIt = ast.Import(names=[ast.alias(name='numpy', asname=None)])
            node.body.insert(0, importIt)
        return node

    def visit_BinOp(self, node):
        self.generic_visit(node)
        if (type(node.op) is ast.Pow
                and type(node.right) is ast.Num
                and node.right.n == 2):
            self.need_import = True
            self.update = True
            return ast.Call(
                ast.Attribute(
                    ast.Name('numpy', ast.Load()),
                    'square',
                    ast.Load()),
                [node.left],
                [],
                None,
                None
                )
        else:
            return node
