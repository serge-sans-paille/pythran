'''This module performs a few early syntax check on the input AST.'''
import ast
import tables

class PythranSyntaxError(SyntaxError):
    def __init__(self, msg, node=None):
        SyntaxError.__init__(self,msg)
        if node:
            self.lineno=node.lineno
            self.offset=node.col_offset

class SyntaxChecker(ast.NodeVisitor):
    def visit_Module(self, node):
        for n in node.body:
            if isinstance(n, ast.Expr) and isinstance(n.value, ast.Str):
                continue
            else:
                if not any(map(lambda t:isinstance(n,t),(ast.FunctionDef, ast.Import, ast.ImportFrom,))):
                    raise PythranSyntaxError("Top level statements can only be functions, comments or imports", n)
        [ self.visit(n) for n in node.body ]

    def visit_Interactive(self, node):
        raise PythranSyntaxError("Interactive session are not supported", node)

    def visit_Expression(self, node):
        raise PythranSyntaxError("Top-Level expressions are not supported", node)

    def visit_Suite(self, node):
        raise PythranSyntaxError("Suite are specific to Jython and not supported", node)

    def visit_ClassDef(self, node):
        raise PythranSyntaxError("Classes not supported")

    def visit_Print(self, node):
        if node.dest: raise PythranSyntaxError("Printing to a specific stream", node.dest)

    def visit_With(self, node):
        raise PythranSyntaxError("With statements are not supported")

    def visit_Call(self, node):
        if node.keywords:raise PythranSyntaxError("Call with keywords are not supported", node)
        if node.starargs: raise PythranSyntaxError("Call with star arguments are not supported", node)
        if node.kwargs: raise PythranSyntaxError("Call with kwargs are not supported", node)

    def visit_FunctionDef(self, node):
        if node.args.vararg: raise PythranSyntaxError("Varargs are not supported", node)
        if node.args.kwarg: raise PythranSyntaxError("Keyword arguments are not supported", node)
        self.visit(node.args)
        [ self.visit(n) for n in node.body ]

    def visit_Raise(self, node):
        if node.tback: raise PythranSyntaxError("Traceback in raise statements are not supported")

    def visit_TryExcept(self, node):
        raise PythranSyntaxError("Try blocks are not supported", node)

    def visit_TryFinally(self, node):
        raise PythranSyntaxError("Try blocks are not supported", node)

    def visit_Import(self, node):
        for alias in node.names:
            if alias.name not in tables.modules:
                PythranSyntaxError("Module '{0}'".format(name), node)

    def visit_ImportFrom(self, node):
        if node.level != 0: raise PythranSyntaxError("Specifying a level in an import", node)
        if not node.module: raise PythranSyntaxError("The import from syntax without module", node)
        module = node.module
        if module not in tables.modules: raise PythranSyntaxError("Module '{0}'".format(module), node)

    def visit_Exec(self, node):
        raise PythranSyntaxError("Exec statement are not supported", node)

    def visit_Global(self, node):
        raise PythranSyntaxError("Global variables are not supported", node)

    def visit_DictComp(self, node):
        raise PythranSyntaxError("Dictionary comprehension are not supported", node)


def check_syntax(node):
    '''Does nothing but raising exception when pythran syntax is not respected'''
    SyntaxChecker().visit(node)
