"""
Boolean logical operators in if-orelse stmt
"""

import gast as ast
from pythran.passmanager import Transformation

class LogicOperateToBool(Transformation):
    """
    Boolean logical operators in if-orelse stmt

    >>> import gast as ast
    >>> from pythran import passmanager, backend
    >>> code = '''
    ... def foo():
    ...     if a and b in c:
    ...         return 1
    ...     else:
    ...         return 0'''
    >>> node = ast.parse(code)
    >>> pm = passmanager.PassManager("test")
    >>> _, node = pm.apply(LogicOperateToBool, node)
    >>> print(pm.dump(backend.Python, node))
    def foo():
        if bool(a) and bool(b in c):
            return 1
        else:
            return 0
    """
    
    def __init__(self):
        super(LogicOperateToBool, self).__init__()
        self._if_stmt = False
    
    def visit_If(self, node: ast.If) -> ast.If:
        self._if_stmt = True
        node.test = self.visit(node.test)

        orelse = []
        for stmt in node.orelse:
            orelse.append(
                self.visit(stmt)
            )
        node.orelse[:] = orelse
        self._if_stmt = False
        return node

    def visit_BoolOp(self, node: ast.BoolOp) -> ast.BoolOp:
        if not self._if_stmt:
            return node

        values = []

        for value in node.values:
            val = ast.Call(
                func=ast.Name(
                    id="bool", ctx=ast.Load(), 
                    annotation=None, type_comment=None),
                args=[value],
                keywords=[]
            )
            values.append(val)
        node.values[:] = values
        return node