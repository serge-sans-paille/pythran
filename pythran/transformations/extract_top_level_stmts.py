""" ExtractTopLevelStmts moves top level statements into __init__. """

from pythran.passmanager import Transformation

import ast


class ExtractTopLevelStmts(Transformation):

    """ Turns top level statements into __init__.  """

    TYPEDEFS = (ast.ClassDef, ast.FunctionDef, ast.Import, ast.ImportFrom,
                ast.Assign)

    @staticmethod
    def visit_Module(node):
        """
        Move TYPEDEFS type expressions from global namespace to init function.

        >>> import ast
        >>> from pythran import passmanager, backend
        >>> node = ast.parse('''
        ... a = 'ok'
        ... print a
        ... def foo():
        ...     return list()''')
        >>> pm = passmanager.PassManager("test")
        >>> _, node = pm.apply(ExtractTopLevelStmts, node)
        >>> print pm.dump(backend.Python, node)
        a = 'ok'
        def foo():
            return list()
        def __init__():
            print a
        __init__()
        """
        module_body = list()
        init_body = list()
        for stmt in node.body:
            if isinstance(stmt, ExtractTopLevelStmts.TYPEDEFS):
                module_body.append(stmt)
            else:
                init_body.append(stmt)

        if init_body:
            self.update = True
            init = ast.FunctionDef('__init__',
                                   ast.arguments([], None, None, []),
                                   init_body,
                                   [])
            module_body.append(init)
            node.body = module_body
        self.has_init = bool(init_body)
        return node

    def run(self, node, ctx):
        super(ExtractTopLevelStmts, self).run(node, ctx)
        return self.has_init
