"""
expand boolean logical operators
"""

from typing import Union
import gast as ast
from pythran.passmanager import Transformation

def _is_bool_call(node: ast.Call) -> bool:
    if not isinstance(node, ast.Call):
        return False
    func = node.func
    return len(node.args) == 1 and not node.keywords and\
        isinstance(func, ast.Attribute) and \
        func.attr == "bool" and \
        isinstance(func.value, ast.Name) and \
        func.value.id == "builtins"

def _boolean_BoolOp(op: ast.BoolOp):
    for i, val in enumerate(op.values):
        if _is_bool_call(val):
            continue
        op.values[i] = _boolean_stmt(val)
    return op

def _boolean_stmt(stmt: ast.AST) -> ast.Call:
    if isinstance(stmt, ast.BoolOp):
        return _boolean_BoolOp(stmt)
    return ast.Call(
        func=ast.Attribute(
            value=ast.Name(
                id='builtins', ctx=ast.Load(),
                annotation=None, type_comment=None
            ),
            attr='bool',
            ctx=ast.Load()
        ),
        args=[stmt],
        keywords=[]
    )


class ExpandBooleanOperator(Transformation):

    """Expand bool() to each logical element of BoolOp node.

    This optimization should work after ExpandBuiltins
    
    >>> import gast as ast
    >>> from pythran import passmanager, backend
    >>> code = '''
    ... def foo(a, b, c, d):
    ...     if builtins.bool(a and b) or builtins.bool(c or d):
    ...         return b or d
    ...     elif builtins.bool( bar(c or a) or bar(b and d) ):
    ...         return a
    ...     else:
    ...         return b and d'''
    >>> node = ast.parse(code)
    >>> pm = passmanager.PassManager("test")
    >>> _, node = pm.apply(ExpandBooleanOperator, node)
    >>> print(pm.dump(backend.Python, node))
    def foo(a, b, c, d):
        if ((builtins.bool(a) and builtins.bool(b)) or (builtins.bool(c) or builtins.bool(d))):
            return (b or d)
        elif (builtins.bool(bar((c or a))) or builtins.bool(bar((b and d)))):
            return a
        else:
            return (b and d)
    """

    def __init__(self):
        super(ExpandBooleanOperator, self).__init__()
        self._bool_call = False
        self._is_logical = False

    def visit_Call(self, node: ast.Call) -> Union[ast.Call, ast.BoolOp]:

        old_bool_call = self._bool_call
        old_is_logical = self._is_logical

        cur = node
        while _is_bool_call(cur):
            cur = cur.args[0]

        self._bool_call = cur is not node

        if cur is node:     # to avoid recursive call
            res = self.generic_visit(cur)
        elif not isinstance(cur, ast.BoolOp):
            self._is_logical = False
            res = _boolean_stmt(self.visit(cur))
        else:
            self._is_logical = True
            res = self.visit(cur)               # handle bool(x and y)

        self._is_logical = old_is_logical
        self._bool_call = old_bool_call
        return res

    def visit(self, node: ast.AST) -> ast.AST:
        old_is_logical = self._is_logical

        # we should expand expr like bool(a and (b + (c and d)) ) 
        # into bool(a) and bool( b + (c and d) ), rather than
        # bool(a) and (  bool(b) + ( bool(c) and bool(d) )  )
        # so if meet other kind AST, such as ast.Add, we set 
        # `_is_logical` to `False`, when we are in `logical_bool_call`
        # status.
        if self._is_logical_bool_call() and not \
                isinstance(node, ast.BoolOp):
            self._is_logical = False

        res = super().visit(node)
        self._is_logical = old_is_logical
        return res

    def visit_BoolOp(self, node: ast.BoolOp) -> ast.BoolOp:
        if self._is_logical_bool_call():
            values = [_boolean_stmt(self.visit(v)) for v in node.values]
        else:
            values = [ self.visit(v) for v in node.values ]
        node.values[:] = values
        return node

    def _is_logical_bool_call(self) -> bool:
        return self._is_logical and self._bool_call


class CombineBoolCall(Transformation):

    """combine continious bool() to single, like bool(bool(bool(x))) => bool(x)
    
    This optimization should work following ExpandBooleanOperator

    >>> import gast as ast
    >>> from pythran import passmanager, backend
    >>> code = '''
    ... def expand_bool(a, b, c, d):
    ...     if ((builtins.bool(builtins.bool(a)) and builtins.bool(builtins.bool(b))) or builtins.bool(d)):
    ...         return (a and c)
    ...     elif bar(opt=builtins.bool(builtins.bool(a))):
    ...         return foo(builtins.bool(builtins.bool(c)))'''
    >>> node = ast.parse(code)
    >>> pm = passmanager.PassManager("test")
    >>> _, node = pm.apply(CombineBoolCall, node)
    >>> print(pm.dump(backend.Python, node))
    def expand_bool(a, b, c, d):
        if ((builtins.bool(a) and builtins.bool(b)) or builtins.bool(d)):
            return (a and c)
        elif bar(opt=builtins.bool(a)):
            return foo(builtins.bool(c))
    """

    def __init__(self):
        super(CombineBoolCall, self).__init__()


    def visit_Call(self, node: ast.Call):
        cur = node
        while _is_bool_call(cur):
            cur = cur.args[0]

        if cur is node:
            res = self.generic_visit(cur)
        else:
            res = _boolean_stmt(self.visit(cur))
        return res



if __name__ == "__main__":
    import doctest
    doctest.testmod()
