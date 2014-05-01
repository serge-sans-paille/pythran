"""
ExpandBuiltins replaces builtins by their full paths
"""
import ast
from pythran.analyses import Globals, Locals
from pythran.passmanager import Transformation
from pythran.tables import modules
from pythran.syntax import PythranSyntaxError


class ExpandBuiltins(Transformation):
    '''
    Expands all builtins into full paths.
    >>> import ast, passmanager, backend
    >>> node = ast.parse("def foo(): return list()")
    >>> pm = passmanager.PassManager("test")
    >>> node = pm.apply(ExpandBuiltins, node)
    >>> print pm.dump(backend.Python, node)
    def foo():
        return __builtin__.list()
    '''

    def __init__(self):
        Transformation.__init__(self, Locals, Globals)

    def visit_Name(self, node):
        s = node.id
        if (isinstance(node.ctx, ast.Load)
                and s not in self.locals[node]
                and s not in self.globals
                and s in modules['__builtin__']):
            if s == 'getattr':
                raise PythranSyntaxError("You fool! Trying a getattr?", node)
            return ast.Attribute(
                ast.Name('__builtin__', ast.Load()),
                s,
                node.ctx)
        else:
            return node
