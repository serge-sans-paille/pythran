""" DeadCodeElimination remove useless code. """

from pythran.analyses import PureExpressions, UseDefChain
from pythran.openmp import OMPDirective
from pythran.passmanager import Transformation
import pythran.metadata as metadata

import ast


class DeadCodeElimination(Transformation):
    """
    Remove useless statement like:
        - assignment to unused variables
        - remove alone pure statement
        - remove empty if

    >>> import ast
    >>> from pythran import passmanager, backend
    >>> pm = passmanager.PassManager("test")
    >>> node = ast.parse("def foo(): a = [2, 3]; return 1")
    >>> _, node = pm.apply(DeadCodeElimination, node)
    >>> print pm.dump(backend.Python, node)
    def foo():
        pass
        return 1
    >>> node = ast.parse("def foo(): 'a simple string'; return 1")
    >>> _, node = pm.apply(DeadCodeElimination, node)
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
    >>> _, node = pm.apply(DeadCodeElimination, node)
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

            def is_use(x):
                return udc.node[x]['action'] in ("U", "UD")
            use_count = len(filter(is_use, udc.nodes()))
            return use_count != 0
        return True

    def visit_Assign(self, node):
        node.targets = filter(self.used_target, node.targets)
        if node.targets:
            return node
        self.update = True
        if node.value in self.pure_expressions:
            return ast.Pass()
        else:
            return ast.Expr(value=node.value)

    def visit_Expr(self, node):
        if (node in self.pure_expressions and
                not isinstance(node.value, ast.Yield)):
            self.update = True
            return ast.Pass()
        self.generic_visit(node)
        return node

    def visit_If(self, node):
        self.generic_visit(node)
        have_body = any(not isinstance(x, ast.Pass) for x in node.body)
        have_else = any(not isinstance(x, ast.Pass) for x in node.orelse)
        # If the "body" is empty but "else content" is useful, switch branches
        # and remove else content
        if not have_body and have_else:
            test = ast.UnaryOp(op=ast.Not(), operand=node.test)
            self.update = True
            return ast.If(test=test, body=node.orelse, orelse=list())
        # if neither "if" and "else" are useful, keep test if it is not pure
        elif not have_body:
            self.update = True
            if node.test in self.pure_expressions:
                return ast.Pass()
            else:
                node = ast.Expr(value=node.test)
                self.generic_visit(node)
        return node

    def visit(self, node):
        """ Add OMPDirective from the old node to the new one. """
        old_omp = metadata.get(node, OMPDirective)
        node = super(DeadCodeElimination, self).visit(node)
        if not metadata.get(node, OMPDirective):
            for omp_directive in old_omp:
                metadata.add(node, omp_directive)
        return node
