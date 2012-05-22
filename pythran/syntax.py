import ast

class PythranSyntaxError(SyntaxError):
    def __init__(self, msg, node):
        SyntaxError.__init__(self,msg)
        self.lineno=node.lineno
        self.offset=node.col_offset

class SyntaxChecker(ast.NodeVisitor):
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

    def visit_Dict(self, node):
        raise PythranSyntaxError("Dictionaries are not supported", node)

    def visit_Set(self, node):
        raise PythranSyntaxError("Sets are not supported", node)

    def visit_SetComp(self, node):
        raise PythranSyntaxError("Set comprehension are not supported", node)

    def visit_DictComp(self, node):
        raise PythranSyntaxError("Dictionary comprehension are not supported", node)

    def visit_GeneratorExp(self, node):
        raise PythranSyntaxError("Generator expression are not supported", node)

    def visit_Yield(self, node):
        raise PythranSyntaxError("yield keyword is not supported", node)

