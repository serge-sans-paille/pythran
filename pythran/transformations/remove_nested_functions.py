""" RemoveNestedFunctions turns nested function into top-level functions. """

from pythran.analyses import GlobalDeclarations, ImportedIds
from pythran.passmanager import Transformation
from pythran.tables import MODULES

import ast


class _NestedFunctionRemover(Transformation):
    def __init__(self, pm, ctx, global_declarations):
        Transformation.__init__(self)
        self.ctx = ctx
        self.passmanager = pm
        self.global_declarations = global_declarations

    def visit_FunctionDef(self, node):
        self.update = True
        if MODULES['functools'] not in self.global_declarations.values():
            import_ = ast.Import([ast.alias('functools', None)])
            self.ctx.module.body.insert(0, import_)
            self.global_declarations['functools'] = MODULES['functools']

        self.ctx.module.body.append(node)

        former_name = node.name
        new_name = "pythran_{0}".format(former_name)

        ii = self.passmanager.gather(ImportedIds, node, self.ctx)
        binded_args = [ast.Name(iin, ast.Load()) for iin in sorted(ii)]
        node.args.args = ([ast.Name(iin, ast.Param()) for iin in sorted(ii)] +
                          node.args.args)

        class Renamer(ast.NodeTransformer):
            def visit_Call(self, node):
                self.generic_visit(node)
                if (isinstance(node.func, ast.Name) and
                        node.func.id == former_name):
                    node.func.id = new_name
                    node.args = (
                        [ast.Name(iin, ast.Load()) for iin in sorted(ii)] +
                        node.args
                        )
                return node
        Renamer().visit(node)

        node.name = new_name
        self.global_declarations[node.name] = node
        proxy_call = ast.Name(new_name, ast.Load())

        new_node = ast.Assign(
            [ast.Name(former_name, ast.Store())],
            ast.Call(
                ast.Attribute(
                    ast.Name('functools', ast.Load()),
                    "partial",
                    ast.Load()
                    ),
                [proxy_call] + binded_args,
                [],
                None,
                None
                )
            )

        self.generic_visit(node)
        return new_node


class RemoveNestedFunctions(Transformation):

    """
    Replace nested function by top-level functions.

    Also add a call to a bind intrinsic that
    generates a local function with some arguments binded.

    >>> import ast
    >>> from pythran import passmanager, backend
    >>> node = ast.parse("def foo(x):\\n def bar(y): return x+y\\n bar(12)")
    >>> pm = passmanager.PassManager("test")
    >>> _, node = pm.apply(RemoveNestedFunctions, node)
    >>> print pm.dump(backend.Python, node)
    import functools
    def foo(x):
        bar = functools.partial(pythran_bar, x)
        bar(12)
    def pythran_bar(x, y):
        return (x + y)
    """
    def __init__(self):
        super(RemoveNestedFunctions, self).__init__(GlobalDeclarations)

    def visit_Module(self, node):
        map(self.visit, node.body)
        return node

    def visit_FunctionDef(self, node):
        nfr = _NestedFunctionRemover(self.passmanager, self.ctx,
                                     self.global_declarations)
        node.body = map(nfr.visit, node.body)
        self.update |= nfr.update
        return node
