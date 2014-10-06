"""
RangeLoopUnfolding turns unfolded range of non unrolled loops back to range.
"""

from pythran.passmanager import Transformation

import ast


class RangeLoopUnfolding(Transformation):
    """
    Turns iteration over an incrementing list of literals into a range

    >>> import ast
    >>> from pythran import passmanager, backend
    >>> node = ast.parse("for i in [1,2,3]: print i")
    >>> pm = passmanager.PassManager("test")
    >>> _, node = pm.apply(RangeLoopUnfolding, node)
    >>> print pm.dump(backend.Python, node)
    for i in __builtin__.xrange(1, 4, 1):
        print i
    """

    def isrange(self, elts):
        if not elts:
            return None
        if not all(isinstance(x, ast.Num) and isinstance(x.n, int)
                   for x in elts):
            return None
        unboxed_ints = [x.n for x in elts]
        start = unboxed_ints[0]
        if len(unboxed_ints) == 1:
            return start, start + 1, 1
        else:
            step = unboxed_ints[1] - start
            stop = unboxed_ints[-1] + step
            if unboxed_ints == range(start, stop, step):
                return start, stop, step
            else:
                return None

    def visit_For(self, node):
        if isinstance(node.iter, (ast.List, ast.Tuple)):
            range_params = self.isrange(node.iter.elts)
            if range_params:
                node.iter = ast.Call(ast.Attribute(
                    ast.Name('__builtin__', ast.Load()),
                    'xrange',
                    node.iter.ctx),
                    map(ast.Num, range_params),
                    [], None, None)
                self.update = True
        return self.generic_visit(node)
