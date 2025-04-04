""" RemoveNestedFunctions turns nested function into top-level functions. """

from pythran.analyses import GlobalDeclarations, ImportedIds
from pythran.passmanager import Transformation
from pythran.tables import MODULES
from pythran.conversion import mangle

import pythran.metadata as metadata

import gast as ast


class _NestedFunctionRemover(ast.NodeTransformer):
    def __init__(self, parent):
        ast.NodeTransformer.__init__(self)
        self.parent = parent
        self.identifiers = set(self.global_declarations.keys())
        self.boxes = set()

    def __getattr__(self, attr):
        return getattr(self.parent, attr)

    def visit_FunctionDef(self, node):
        self.update = True
        if MODULES['functools'] not in self.global_declarations.values():
            import_ = ast.Import([ast.alias('functools', mangle('functools'))])
            self.ctx.module.body.insert(0, import_)
            functools_module = MODULES['functools']
            self.global_declarations[mangle('functools')] = functools_module

        self.ctx.module.body.append(node)

        former_name = node.name
        seed = 0
        new_name = "pythran_{}{}"

        while new_name.format(former_name, seed) in self.identifiers:
            seed += 1

        new_name = new_name.format(former_name, seed)
        self.identifiers.add(new_name)

        ii = self.gather(ImportedIds, node)
        self.boxes.update(ii)
        binded_args = [ast.Name('__pythran_boxed_' + iin, ast.Load(), None,
                                              None)
                       for iin in sorted(ii)]
        node.args.args = ([ast.Name(iin, ast.Param(), None, None)
                           for iin in sorted(ii)] +
                          node.args.args)

        unboxing = [ast.Assign([ast.Name(iin, ast.Store(), None, None)],
                               ast.Subscript(ast.Name('__pythran_boxed_args_' + iin, ast.Load(), None,
                                                      None),
                                             ast.Constant(None, None),
                                             ast.Load()))
                    for iin in ii]
        for arg in node.args.args:
            if arg.id in ii:
                arg.id = '__pythran_boxed_args_' + arg.id

        node.body = unboxing + node.body

        metadata.add(node, metadata.Local())

        class Renamer(ast.NodeTransformer):
            def visit_Call(self, node):
                self.generic_visit(node)
                if (isinstance(node.func, ast.Name) and
                        node.func.id == former_name):
                    node.func.id = new_name
                    node.args = (
                        [ast.Name('__pythran_boxed_args_' + iin, ast.Load(), None, None)
                         for iin in sorted(ii)] +
                        node.args
                        )
                return node

        Renamer().visit(node)

        node.name = new_name
        self.global_declarations[node.name] = node
        proxy_call = ast.Name(new_name, ast.Load(), None, None)

        new_node = ast.Assign(
            [ast.Name(former_name, ast.Store(), None, None)],
            ast.Call(
                ast.Attribute(
                    ast.Name(mangle('functools'), ast.Load(), None, None),
                    "partial",
                    ast.Load()
                    ),
                [proxy_call] + binded_args,
                [],
                ),
            None)

        nfr = _NestedFunctionRemover(self)
        nfr.remove_nested(node)

        return new_node

    def remove_nested(self, node):
        node.body = [self.visit(stmt) for stmt in node.body]
        if self.update:
            boxes = []
            arg_ids = {arg.id for arg in node.args.args}
            for i in self.boxes:
                if i in arg_ids:
                    box_value = ast.Dict([ast.Constant(None, None)], [ast.Name(i,
                                                                               ast.Load(),
                                                                               None,
                                                                               None)])
                else:
                    box_value = ast.Dict([], [])
                box = ast.Assign([ast.Name('__pythran_boxed_' + i, ast.Store(),
                                          None, None)], box_value)
                boxes.append(box)

            BoxInserter(self.boxes).visit(node)
            node.body = boxes + node.body
        return self.update

class BoxInserter(ast.NodeTransformer):

    def __init__(self, insertion_points):
        self.insertion_points = insertion_points
        self.skip_function = False

    def visit_Assign(self, node):
        extras = []
        for t in node.targets:
            if getattr(t, 'id', None) not in self.insertion_points:
                continue
            extra = ast.Assign(
                    [ast.Subscript(
                        ast.Name('__pythran_boxed_' + t.id, ast.Load(), None, None),
                                 ast.Constant(None, None),
                                 ast.Store())],
                    ast.Name(t.id, ast.Load(), None, None))
            extras.append(extra)
        if extras:
            return [node] + extras
        else:
            return node


class RemoveNestedFunctions(Transformation[GlobalDeclarations]):

    """
    Replace nested function by top-level functions.

    Also add a call to a bind intrinsic that
    generates a local function with some arguments binded.

    >>> import gast as ast
    >>> from pythran import passmanager, backend
    >>> node = ast.parse("def foo(x):\\n def bar(y): return x+y\\n bar(12)")
    >>> pm = passmanager.PassManager("test")
    >>> _, node = pm.apply(RemoveNestedFunctions, node)
    >>> print(pm.dump(backend.Python, node))
    import functools as __pythran_import_functools
    def foo(x):
        __pythran_boxed_x = {None: x}
        bar = __pythran_import_functools.partial(pythran_bar0, __pythran_boxed_x)
        bar(12)
    def pythran_bar0(__pythran_boxed_args_x, y):
        x = __pythran_boxed_args_x[None]
        return (x + y)
    """

    def visit_Module(self, node):
        # keep original node as it's updated by _NestedFunctionRemover
        for stmt in node.body:
            self.visit(stmt)
        return node

    def visit_FunctionDef(self, node):
        nfr = _NestedFunctionRemover(self)
        self.update |= nfr.remove_nested(node)
        return node
