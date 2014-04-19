"""
Replaces **2 by a call to pow2
"""
import ast
from pythran.passmanager import Transformation


class Pow2(Transformation):
    '''
    Replaces **2 by a call to pow2

    >>> import ast, passmanager, backend
    >>> node = ast.parse('a**2')
    >>> pm = passmanager.PassManager("test")
    >>> node = pm.apply(Pow2, node)
    >>> print pm.dump(backend.Python, node)
    __builtin__.pow2(a)
    '''

    def visit_BinOp(self, node):
        self.generic_visit(node)
        if (type(node.op) is ast.Pow
                and type(node.right) is ast.Num
                and node.right.n == 2):
            return ast.Call(
                ast.Attribute(
                    ast.Name('__builtin__', ast.Load()),
                    'pow2',
                    ast.Load()),
                [node.left],
                [],
                None,
                None
                )
        else:
            return node
