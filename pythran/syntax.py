'''
This module performs a few early syntax check on the input AST.
It checks the conformance of the input code to Pythran specific
constraints.
'''

from pythran.tables import MODULES
from pythran.intrinsic import Class

import gast as ast


class PythranSyntaxError(SyntaxError):
    def __init__(self, msg, node=None):
        SyntaxError.__init__(self, msg)
        if node:
            self.filename = getattr(node, 'filename', None)
            self.lineno = node.lineno
            self.offset = node.col_offset


class SyntaxChecker(ast.NodeVisitor):

    """
    Visit an AST and raise a PythranSyntaxError upon unsupported construct.

    Attributes
    ----------
    attributes : {str}
        Possible attributes from Pythonic modules/submodules.
    """

    def __init__(self):
        """ Gather attributes from MODULES content. """
        self.attributes = set()

        def save_attribute(module):
            """ Recursively save Pythonic keywords as possible attributes. """
            self.attributes.update(module.keys())
            for signature in module.values():
                if isinstance(signature, dict):
                    save_attribute(signature)
                elif isinstance(signature, Class):
                    save_attribute(signature.fields)

        for module in MODULES.values():
            save_attribute(module)

    def visit_Module(self, node):
        err = ("Top level statements can only be assignments, strings,"
               "functions, comments, or imports")
        WhiteList = ast.FunctionDef, ast.Import, ast.ImportFrom, ast.Assign
        for n in node.body:
            if isinstance(n, ast.Expr) and isinstance(n.value, ast.Str):
                continue
            if isinstance(n, WhiteList):
                continue
            raise PythranSyntaxError(err, n)
        self.generic_visit(node)

    def visit_Interactive(self, node):
        raise PythranSyntaxError("Interactive session not supported", node)

    def visit_Expression(self, node):
        raise PythranSyntaxError("Interactive expressions not supported", node)

    def visit_Suite(self, node):
        raise PythranSyntaxError(
            "Suites are specific to Jython and not supported", node)

    def visit_ClassDef(self, _):
        raise PythranSyntaxError("Classes not supported")

    def visit_Print(self, node):
        self.generic_visit(node)
        if node.dest:
            raise PythranSyntaxError(
                "Printing to a specific stream not supported", node.dest)

    def visit_With(self, node):
        raise PythranSyntaxError("With statements not supported", node)

    def visit_Starred(self, node):
        raise PythranSyntaxError("Call with star arguments not supported",
                                 node)

    def visit_keyword(self, node):
        if node.arg is None:
            raise PythranSyntaxError("Call with kwargs not supported", node)

    def visit_Call(self, node):
        self.generic_visit(node)

    def visit_FunctionDef(self, node):
        self.generic_visit(node)
        if node.args.vararg:
            raise PythranSyntaxError("Varargs not supported", node)
        if node.args.kwarg:
            raise PythranSyntaxError("Keyword arguments not supported",
                                     node)

    def visit_Raise(self, node):
        self.generic_visit(node)
        if node.cause:
            raise PythranSyntaxError(
                "Cause in raise statements not supported",
                node)

    def visit_Attribute(self, node):
        self.generic_visit(node)
        if node.attr not in self.attributes:
            raise PythranSyntaxError(
                "Attribute '{0}' unknown".format(node.attr),
                node)

    def visit_Import(self, node):
        """ Check if imported module exists in MODULES. """
        for alias in node.names:
            current_module = MODULES
            # Recursive check for submodules
            for path in alias.name.split('.'):
                if path not in current_module:
                    raise PythranSyntaxError(
                        "Module '{0}' unknown.".format(alias.name),
                        node)
                else:
                    current_module = current_module[path]

    def visit_ImportFrom(self, node):
        """
            Check validity of imported functions.

            Check:
                - no level specific value are provided.
                - a module is provided
                - module/submodule exists in MODULES
                - imported function exists in the given module/submodule
        """
        if node.level:
            raise PythranSyntaxError("Relative import not supported", node)
        if not node.module:
            raise PythranSyntaxError("import from without module", node)
        module = node.module
        current_module = MODULES
        # Check if module exists
        for path in module.split('.'):
            if path not in current_module:
                raise PythranSyntaxError(
                    "Module '{0}' unknown.".format(module),
                    node)
            else:
                current_module = current_module[path]

        # Check if imported functions exist
        for alias in node.names:
            if alias.name == '*':
                continue
            elif alias.name not in current_module:
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


def check_specs(mod, specs, renamings, types):
    '''
    Does nothing but raising PythranSyntaxError if specs
    are incompatible with the actual code
    '''
    from pythran.types.tog import unify, clone, tr
    from pythran.types.tog import Function, TypeVariable, InferenceError

    functions = {renamings.get(k, k): v for k, v in specs.functions.items()}
    for fname, signatures in functions.items():
        try:
            ftype = types[fname]
        except KeyError:
            raise PythranSyntaxError(
                "Invalid spec: exporting undefined function `{}`"
                .format(fname))
        for signature in signatures:
            sig_type = Function([tr(p) for p in signature], TypeVariable())
            try:
                unify(clone(sig_type), clone(ftype))
            except InferenceError:
                raise PythranSyntaxError(
                    "Specification for `{}` does not match inferred type:\n"
                    "expected `{}`\n"
                    "got `Callable[[{}], ...]`".format(
                        fname,
                        ftype,
                        ", ".join(map(str, sig_type.types[:-1])))
                )
