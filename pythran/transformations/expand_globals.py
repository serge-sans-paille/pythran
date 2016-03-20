"""
ExpandGlobals replaces globals variables by function call.

It also turn globals assignment in function definition.
"""

from pythran.analyses import LocalNameDeclarations
from pythran.passmanager import Transformation
from pythran.syntax import PythranSyntaxError
from pythran import metadata


import ast


class ExpandGlobals(Transformation):

    """
    Expands all builtins into full paths.

    >>> import ast
    >>> from pythran import passmanager, backend
    >>> node = ast.parse('''
    ... a = 1
    ... def foo():
    ...     return a''')
    >>> pm = passmanager.PassManager("test")
    >>> _, node = pm.apply(ExpandGlobals, node)
    >>> print pm.dump(backend.Python, node)
    def a():
        return 1
    def foo():
        return a()
    """

    def __init__(self):
        """ Initialize local declaration and constant name to expand. """
        self.local_decl = set()
        self.to_expand = set()
        super(ExpandGlobals, self).__init__()

    def visit_Module(self, node):
        """Turn globals assignement to functionDef and visit function defs. """
        module_body = list()
        # Gather top level assigned variables.
        for stmt in node.body:
            if not isinstance(stmt, ast.Assign):
                continue
            for target in stmt.targets:
                assert isinstance(target, ast.Name)
                if target.id in self.to_expand:
                    raise PythranSyntaxError(
                        "Multiple top-level definition of %s." % target.id,
                        target)
                self.to_expand.add(target.id)

        for stmt in node.body:
            if isinstance(stmt, ast.Assign):
                self.local_decl = set()
                cst_value = self.visit(stmt.value)
                for target in stmt.targets:
                    assert isinstance(target, ast.Name)
                    module_body.append(
                        ast.FunctionDef(target.id,
                                        ast.arguments([], None, None, []),
                                        [ast.Return(value=cst_value)], []))
                    metadata.add(module_body[-1].body[0],
                                 metadata.StaticReturn())
            else:
                self.local_decl = self.passmanager.gather(
                    LocalNameDeclarations, stmt,
                    self.ctx)
                module_body.append(self.visit(stmt))

        node.body = module_body
        return node

    def visit_Name(self, node):
        """
        Turn global variable used not shadows to function call.

        We check it is a name from an assignement as import or functions use
        should not be turn into call.
        """
        if (isinstance(node.ctx, ast.Load) and
                node.id not in self.local_decl and
                node.id in self.to_expand):
            return ast.Call(func=node,
                            args=[], keywords=[], starargs=None, kwargs=None)
        return node
