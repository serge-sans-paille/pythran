"""
NormalizeException simplifies try blocks
"""
import ast
from pythran.passmanager import Transformation


class NormalizeException(Transformation):
    '''
    Transform else statement in try except block in nested try except.

    >>> import ast, passmanager, backend
    >>> node = ast.parse("try:print 't'\\nexcept: print 'x'\\nelse: print 'e'")
    >>> pm = passmanager.PassManager("test")
    >>> node = pm.apply(NormalizeException, node)
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
        return node

    def visit_TryFinally(self, node):
        node.body.extend(node.finalbody)
        node.finalbody.append(ast.Raise(None, None, None))
        return ast.TryExcept(
            node.body,
            [ast.ExceptHandler(None, None, node.finalbody)],
            [])
