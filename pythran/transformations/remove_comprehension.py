"""
RemoveComprehension turns list comprehension into function calls
"""
import ast
from pythran import metadata
from pythran.analyses import ImportedIds
from pythran.passmanager import Transformation


class RemoveComprehension(Transformation):
    """
    Turns all list comprehension from a node into new function calls.

    >>> import ast, passmanager, backend
    >>> node = ast.parse("[x*x for x in (1,2,3)]")
    >>> pm = passmanager.PassManager("test")
    >>> node = pm.apply(RemoveComprehension, node)
    >>> print pm.dump(backend.Python, node)
    list_comprehension0()
    def list_comprehension0():
        __target = __builtin__.list()
        for x in (1, 2, 3):
            __list__.append(__target, (x * x))
        return __target
    """

    def __init__(self):
        self.count = 0
        Transformation.__init__(self)

    def nest_reducer(self, x, g):
        def wrap_in_ifs(node, ifs):
            return reduce(lambda n, if_: ast.If(if_, [n], []), ifs, node)
        metadata.add(g.target, metadata.LocalVariable())
        return ast.For(g.target, g.iter, [wrap_in_ifs(x, g.ifs)], [])

    def visit_AnyComp(self, node, comp_type, comp_module, comp_method):
        node.elt = self.visit(node.elt)
        name = "{0}_comprehension{1}".format(comp_type, self.count)
        self.count += 1
        args = self.passmanager.gather(ImportedIds, node, self.ctx)
        self.count_iter = 0

        starget = "__target"
        body = reduce(self.nest_reducer,
                      reversed(node.generators),
                      ast.Expr(
                          ast.Call(
                              ast.Attribute(
                                  ast.Name(comp_module, ast.Load()),
                                  comp_method,
                                  ast.Load()),
                              [ast.Name(starget, ast.Load()), node.elt],
                              [],
                              None,
                              None
                              )
                          )
                      )
        # add extra metadata to this node
        metadata.add(body, metadata.Comprehension(starget))
        init = ast.Assign(
            [ast.Name(starget, ast.Store())],
            ast.Call(
                ast.Attribute(
                    ast.Name('__builtin__', ast.Load()),
                    comp_type,
                    ast.Load()
                    ),
                [], [], None, None)
            )
        result = ast.Return(ast.Name(starget, ast.Load()))
        sargs = sorted(ast.Name(arg, ast.Param()) for arg in args)
        fd = ast.FunctionDef(name,
                             ast.arguments(sargs, None, None, []),
                             [init, body, result],
                             [])
        self.ctx.module.body.append(fd)
        return ast.Call(
            ast.Name(name, ast.Load()),
            [ast.Name(arg.id, ast.Load()) for arg in sargs],
            [],
            None,
            None
            )  # no sharing !

    def visit_ListComp(self, node):
        return self.visit_AnyComp(node, "list", "__list__", "append")

    def visit_SetComp(self, node):
        return self.visit_AnyComp(node, "set", "__set__", "add")

    def visit_DictComp(self, node):
        # this is a quickfix to match visit_AnyComp signature
        # potential source of improvement there!
        node.elt = ast.List(
            [ast.Tuple([node.key, node.value], ast.Load())],
            ast.Load()
            )
        return self.visit_AnyComp(node, "dict", "__dispatch__", "update")

    def visit_GeneratorExp(self, node):
        node.elt = self.visit(node.elt)
        name = "generator_expression{0}".format(self.count)
        self.count += 1
        args = self.passmanager.gather(ImportedIds, node, self.ctx)
        self.count_iter = 0

        body = reduce(self.nest_reducer,
                      reversed(node.generators),
                      ast.Expr(ast.Yield(node.elt))
                      )

        sargs = sorted(ast.Name(arg, ast.Param()) for arg in args)
        fd = ast.FunctionDef(name,
                             ast.arguments(sargs, None, None, []),
                             [body],
                             [])
        self.ctx.module.body.append(fd)
        return ast.Call(
            ast.Name(name, ast.Load()),
            [ast.Name(arg.id, ast.Load()) for arg in sargs],
            [],
            None,
            None
            )  # no sharing !
