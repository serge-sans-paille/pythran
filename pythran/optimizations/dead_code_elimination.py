"""
DeadCodeElimination remove useless code
"""
import ast
from pythran.analyses import PureExpressions, UseDefChain

from pythran.passmanager import Transformation


class DeadCodeElimination(Transformation):
    """
        Remove useless statement like:
            - assignment to unused variables
            - remove alone pure statement

        >>> import ast, passmanager, backend
        >>> pm = passmanager.PassManager("test")
        >>> node = ast.parse("def foo(): a = [2, 3]; return 1")
        >>> node = pm.apply(DeadCodeElimination, node)
        >>> print pm.dump(backend.Python, node)
        def foo():
            pass
            return 1
        >>> node = ast.parse("def foo(): 'a simple string'; return 1")
        >>> node = pm.apply(DeadCodeElimination, node)
        >>> print pm.dump(backend.Python, node)
        def foo():
            pass
            return 1
        >>> node = ast.parse('''
        ... def bar(a):
        ...     return a
        ... def foo(a):
        ...    bar(a)
        ...    return 1''')
        >>> node = pm.apply(DeadCodeElimination, node)
        >>> print pm.dump(backend.Python, node)
        def bar(a):
            return a
        def foo(a):
            pass
            return 1
    """
    def __init__(self):
        super(DeadCodeElimination, self).__init__(PureExpressions,
                                                  UseDefChain)

    def used_target(self, node):
        if isinstance(node, ast.Name):
            udc = self.use_def_chain[node.id]
            is_use = lambda x: udc.node[x]['action'] in ("U", "UD")
            use_count = len(filter(is_use, udc.nodes()))
            return use_count != 0
        return True

    def visit_Assign(self, node):
        node.targets = filter(self.used_target, node.targets)
        if node.targets:
            return node
        elif node.value in self.pure_expressions:
            return ast.Pass()
        else:
            return ast.Expr(value=node.value)

    def visit_Expr(self, node):
        if (node in self.pure_expressions and
                not isinstance(node.value, ast.Yield)):
            return ast.Pass()
        return node
