""" NormalizeException simplifies try blocks. """

from pythran.passmanager import Transformation

import ast


class NormalizeException(Transformation):
    '''
    Transform else statement in try except block in nested try except.

    >>> import ast
    >>> from pythran import passmanager, backend
    >>> node = ast.parse("try:print 't'\\nexcept: print 'x'\\nelse: print 'e'")
    >>> pm = passmanager.PassManager("test")
    >>> _, node = pm.apply(NormalizeException, node)
    >>> print pm.dump(backend.Python, node)
    try:
        print 't'
        try:
            print 'e'
        except:
            pass
    except:
        print 'x'
    '''
    def visit_TryExcept(self, node):
        if node.orelse:
            node.body.append(
                ast.TryExcept(
                    node.orelse,
                    [ast.ExceptHandler(None, None, [ast.Pass()])],
                    []
                    )
                )
            node.orelse = []
            self.update = True
        return node

    def visit_TryFinally(self, node):
        node.body.extend(node.finalbody)
        node.finalbody.append(ast.Raise(None, None, None))
        self.update = True
        return ast.TryExcept(
            node.body,
            [ast.ExceptHandler(None, None, node.finalbody)],
            [])
