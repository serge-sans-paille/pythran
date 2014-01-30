'''
This module performs a few early syntax check on the input AST.
It checks the conformance of the input code to Pythran specific
constraints.
'''

import ast
import tables


class PythranSyntaxError(SyntaxError):
    def __init__(self, msg, node=None):
        SyntaxError.__init__(self, msg)
        if node:
            self.lineno = node.lineno
            self.offset = node.col_offset


class SyntaxChecker(ast.NodeVisitor):
    '''
    Visit an AST and raise a PythranSyntaxError upon unsupported construct
    '''

    def __init__(self):
        self.attributes = set()
        for module in tables.modules.itervalues():
            self.attributes.update(module.iterkeys())

    def visit_Module(self, node):
        err = ("Top level statements can only be strings, functions, comments"
               " or imports")
        for n in node.body:
            if isinstance(n, ast.Expr) and isinstance(n.value, ast.Str):
                continue
            else:
                if not any(isinstance(n, getattr(ast, t))
                           for t in ('FunctionDef', 'Import', 'ImportFrom',)):
                    raise PythranSyntaxError(err, n)
        self.generic_visit(node)

    def visit_Interactive(self, node):
        raise PythranSyntaxError("Interactive session not supported", node)

    def visit_Expression(self, node):
        raise PythranSyntaxError("Interactive expressions not supported", node)

    def visit_Suite(self, node):
        raise PythranSyntaxError(
            "Suites are specific to Jython and not supported", node)

    def visit_ClassDef(self, node):
        raise PythranSyntaxError("Classes not supported")

    def visit_Print(self, node):
        self.generic_visit(node)
        if node.dest:
            raise PythranSyntaxError(
                "Printing to a specific stream not supported", node.dest)

    def visit_With(self, node):
        raise PythranSyntaxError("With statements not supported")

    def visit_Call(self, node):
        self.generic_visit(node)
        if node.keywords:
            raise PythranSyntaxError("Call with keywords not supported", node)
        if node.starargs:
            raise PythranSyntaxError("Call with star arguments not supported",
                                     node)
        if node.kwargs:
            raise PythranSyntaxError("Call with kwargs not supported", node)

    def visit_FunctionDef(self, node):
        self.generic_visit(node)
        if node.args.vararg:
            raise PythranSyntaxError("Varargs not supported", node)
        if node.args.kwarg:
            raise PythranSyntaxError("Keyword arguments not supported",
                                     node)

    def visit_Raise(self, node):
        self.generic_visit(node)
        if node.tback:
            raise PythranSyntaxError(
                "Traceback in raise statements not supported",
                node)

    def visit_Attribute(self, node):
        self.generic_visit(node)
        if node.attr not in self.attributes:
            raise PythranSyntaxError(
                "Attribute '{0}' unknown".format(node.attr),
                node)

    def visit_Import(self, node):
        for alias in node.names:
            if alias.name not in tables.modules:
                raise PythranSyntaxError(
                    "Module '{0}' unknown.".format(alias.name),
                    node)

    def visit_ImportFrom(self, node):
        if node.level != 0:
            raise PythranSyntaxError("Specifying a level in an import", node)
        if not node.module:
            raise PythranSyntaxError("import from without module", node)
        module = node.module
        if module not in tables.modules:
            raise PythranSyntaxError("Module '{0}' unknown".format(module),
                                     node)
        for alias in node.names:
            if alias.name == '*':
                continue
            if alias.name not in tables.modules[module]:
                raise PythranSyntaxError(
                    "identifier '{0}' not found in module '{1}'".format(
                        alias.name,
                        module),
                    node)

    def visit_Exec(self, node):
        raise PythranSyntaxError("Exec statement not supported", node)

    def visit_Global(self, node):
        raise PythranSyntaxError("Global variables not supported", node)


def check_syntax(node):
    '''Does nothing but raising PythranSyntaxError when needed'''
    SyntaxChecker().visit(node)
