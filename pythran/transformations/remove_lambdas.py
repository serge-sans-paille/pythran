""" RemoveLambdas turns lambda into regular functions.  """

from pythran.analyses import GlobalDeclarations, ImportedIds
from pythran.passmanager import Transformation
from pythran.tables import MODULES

from copy import copy
import ast


class _LambdaRemover(Transformation):

    def __init__(self, pm, name, ctx, lambdas, imports, global_decls):
        Transformation.__init__(self)
        self.passmanager = pm
        self.ctx = ctx
        self.prefix = name
        self.lambda_functions = lambdas
        self.imports = imports
        self.global_declarations = global_decls

    def visit_Lambda(self, node):
        if MODULES['functools'] not in self.global_declarations.values():
            import_ = ast.Import([ast.alias('functools', None)])
            self.imports.append(import_)
            self.global_declarations['functools'] = MODULES['functools']

        self.generic_visit(node)
        forged_name = "{0}_lambda{1}".format(
            self.prefix,
            len(self.lambda_functions))

        ii = self.passmanager.gather(ImportedIds, node, self.ctx)
        ii.difference_update(self.lambda_functions)  # remove current lambdas

        binded_args = [ast.Name(iin, ast.Load()) for iin in sorted(ii)]
        node.args.args = ([ast.Name(iin, ast.Param()) for iin in sorted(ii)] +
                          node.args.args)
        forged_fdef = ast.FunctionDef(
            forged_name,
            copy(node.args),
            [ast.Return(node.body)],
            [])
        self.lambda_functions.append(forged_fdef)
        self.global_declarations[forged_name] = forged_fdef
        proxy_call = ast.Name(forged_name, ast.Load())
        if binded_args:
            return ast.Call(
                ast.Attribute(
                    ast.Name('functools', ast.Load()),
                    "partial",
                    ast.Load()
                    ),
                [proxy_call] + binded_args,
                [],
                None,
                None)
        else:
            return proxy_call


class RemoveLambdas(Transformation):

    """
    Turns lambda into top-level functions.

    >>> import ast
    >>> from pythran import passmanager, backend
    >>> node = ast.parse("def foo(y): lambda x:y+x")
    >>> pm = passmanager.PassManager("test")
    >>> _, node = pm.apply(RemoveLambdas, node)
    >>> print pm.dump(backend.Python, node)
    import functools
    def foo(y):
        functools.partial(foo_lambda0, y)
    def foo_lambda0(y, x):
        return (y + x)
    """

    def __init__(self):
        super(RemoveLambdas, self).__init__(GlobalDeclarations)

    def visit_Module(self, node):
        self.lambda_functions = list()
        self.imports = list()
        self.generic_visit(node)
        node.body = self.imports + node.body + self.lambda_functions
        self.update |= bool(self.imports) or bool(self.lambda_functions)
        return node

    def visit_FunctionDef(self, node):
        lr = _LambdaRemover(self.passmanager, node.name, self.ctx,
                            self.lambda_functions, self.imports,
                            self.global_declarations)
        node.body = map(lr.visit, node.body)
        return node
