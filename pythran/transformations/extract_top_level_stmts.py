"""
ExtractTopLevelStmts moves top level statements into __init__
"""
import ast
from pythran.passmanager import Transformation


class ExtractTopLevelStmts(Transformation):
    """
    Turns top level statements into __init__.
    """

    TYPEDEFS = (ast.ClassDef, ast.FunctionDef, ast.Import, ast.ImportFrom)

    def visit_Module(self, node):
        module_body = list()
        init_body = list()
        for stmt in node.body:
            if type(stmt) in ExtractTopLevelStmts.TYPEDEFS:
                module_body.append(stmt)
            else:
                init_body.append(stmt)
        init = ast.FunctionDef('__init__',
                               ast.arguments([], None, None, []),
                               init_body,
                               [])
        module_body.append(init)
        node.body = module_body
        return node
