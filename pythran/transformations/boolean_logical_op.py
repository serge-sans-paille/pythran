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
    ... def foo(a, b, c, d):
    ...     if bar(a and b) or d:
    ...         return a and c
    ...     elif c and bar(c and d):
    ...         return c or d
    ...     elif bar(d or c):
    ...         tmp = a or b and c
    ...         return tmp if tmp else 1
    ...     elif (lambda x, y: x and y if x or y else y)(a, b):
    ...         return b or d
    ...     else
    ...         return b and d'''
    >>> node = ast.parse(code)
    >>> pm = passmanager.PassManager("test")
    >>> _, node = pm.apply(LogicOperateToBool, node)
    >>> print(pm.dump(backend.Python, node))
    def foo(a, b, c, d):
        if (bool(bar((a and b))) or bool(d)):
            return (a and c)
        elif (bool(c) and bool(bar((c and d)))):
            return (c or d)
        elif bar((d or c)):
            tmp = (a or (b and c))
            return (tmp if tmp else 1)
        elif (lambda x, y: ((x and y) if (bool(x) or bool(y)) else y))(a, b):
            return (b or d)
        else:
            return (b and d)
    """
    
    def __init__(self):
        super(LogicOperateToBool, self).__init__()
        self._if_stmt = False

    def visit(self, node: ast.AST):
        if isinstance(node, (ast.If, ast.IfExp)):
            # just handle BoolOp in If and IfExp
            self._if_stmt = True
        res = super().visit(node)
        self._if_stmt = False
        return res
    
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
