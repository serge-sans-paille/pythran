'Replaces division by a constant float by a multiplication by its reprocical'

from pythran.passmanager import Transformation

import ast


class ConstantReciprocal(Transformation):

    """
    Replaces a / cst by a * ( 1 / cst )

    see http://en.wikipedia.org/wiki/Division_algorithm#Division_by_a_constant

    >>> import ast
    >>> from pythran import passmanager, backend
    >>> node = ast.parse('a / 2.')
    >>> pm = passmanager.PassManager("test")
    >>> _, node = pm.apply(ConstantReciprocal, node)
    >>> print pm.dump(backend.Python, node)
    (a * 0.5)
    """

    def visit_BinOp(self, node):
        self.generic_visit(node)
        if (isinstance(node.op, ast.Div) and
                isinstance(node.right, ast.Num) and
                isinstance(node.right.n, float)):
            self.update = True
            node.op = ast.Mult()
            node.right.n = 1. / node.right.n
        return node
