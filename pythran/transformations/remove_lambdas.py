""" RemoveLambdas turns lambda into regular functions.  """

from pythran.analyses import GlobalDeclarations, ImportedIds
from pythran.passmanager import Transformation
from pythran.tables import MODULES
from pythran.conversion import mangle

import pythran.metadata as metadata

from copy import copy
import gast as ast


class _LambdaRemover(ast.NodeTransformer):

    def __init__(self, parent, prefix):
        super(_LambdaRemover, self).__init__()
        self.prefix = prefix
        self.parent = parent

    def __getattr__(self, attr):
        return getattr(self.parent, attr)

    def visit_Lambda(self, node):
        if MODULES['functools'] not in self.global_declarations.values():
            import_ = ast.Import([ast.alias('functools', mangle('functools'))])
            self.imports.append(import_)
            functools_module = MODULES['functools']
            self.global_declarations[mangle('functools')] = functools_module

        self.generic_visit(node)
        forged_name = "{0}_lambda{1}".format(
            self.prefix,
            len(self.lambda_functions))

        ii = self.gather(ImportedIds, node)
        ii.difference_update(self.lambda_functions)  # remove current lambdas

        binded_args = [ast.Name(iin, ast.Load(), None, None)
                       for iin in sorted(ii)]
        node.args.args = ([ast.Name(iin, ast.Param(), None, None)
                           for iin in sorted(ii)] +
                          node.args.args)
        forged_fdef = ast.FunctionDef(
            forged_name,
            copy(node.args),
            [ast.Return(node.body)],
            [], None, None)
        metadata.add(forged_fdef, metadata.Local())
        self.lambda_functions.append(forged_fdef)
        self.global_declarations[forged_name] = forged_fdef
        proxy_call = ast.Name(forged_name, ast.Load(), None, None)
        if binded_args:
            return ast.Call(
                ast.Attribute(
                    ast.Name(mangle('functools'), ast.Load(), None, None),
                    "partial",
                    ast.Load()
                    ),
                [proxy_call] + binded_args,
                [])
        else:
            return proxy_call


class RemoveLambdas(Transformation):

    """
    Turns lambda into top-level functions.

    >>> import gast as ast
    >>> from pythran import passmanager, backend
    >>> node = ast.parse("def foo(y): lambda x:y+x")
    >>> pm = passmanager.PassManager("test")
    >>> _, node = pm.apply(RemoveLambdas, node)
    >>> print(pm.dump(backend.Python, node))
    import functools as __pythran_import_functools
    def foo(y):
        __pythran_import_functools.partial(foo_lambda0, y)
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
        lr = _LambdaRemover(self, node.name)
        node.body = [lr.visit(n) for n in node.body]
        return node
