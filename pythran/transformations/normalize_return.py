""" NormalizeReturn adds return statement where relevant. """

from pythran.analyses import CFG, YieldPoints
from pythran.passmanager import Transformation

import ast


class NormalizeReturn(Transformation):
    '''
    Adds Return statement when they are implicit,
    and adds the None return value when not set

    >>> import ast
    >>> from pythran import passmanager, backend
    >>> node = ast.parse("def foo(y): print y")
    >>> pm = passmanager.PassManager("test")
    >>> _, node = pm.apply(NormalizeReturn, node)
    >>> print pm.dump(backend.Python, node)
    def foo(y):
        print y
        return __builtin__.None
    '''

    def __init__(self):
        super(NormalizeReturn, self).__init__(CFG)

    def visit_FunctionDef(self, node):
        self.yield_points = self.passmanager.gather(YieldPoints, node)
        map(self.visit, node.body)
        # Look for nodes that have no successors
        for n in self.cfg.predecessors(None):
            if not isinstance(n, (ast.Return, ast.Raise)):
                self.update = True
                if self.yield_points:
                    node.body.append(ast.Return(None))
                else:
                    none = ast.Attribute(ast.Name("__builtin__", ast.Load()),
                                         'None', ast.Load())
                    node.body.append(ast.Return(none))
                break

        return node

    def visit_Return(self, node):
        if not node.value and not self.yield_points:
            none = ast.Attribute(ast.Name("__builtin__", ast.Load()),
                                 'None', ast.Load())
            node.value = none
            self.update = True
        return node
