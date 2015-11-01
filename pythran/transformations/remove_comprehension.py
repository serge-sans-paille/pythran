""" RemoveComprehension turns list comprehension into function calls. """

from pythran import metadata
from pythran.analyses import ImportedIds
from pythran.passmanager import Transformation

import ast


class RemoveComprehension(Transformation):
    """
    Turns all list comprehension from a node into new function calls.

    >>> import ast
    >>> from pythran import passmanager, backend
    >>> node = ast.parse("[x*x for x in (1,2,3)]")
    >>> pm = passmanager.PassManager("test")
    >>> _, node = pm.apply(RemoveComprehension, node)
    >>> print pm.dump(backend.Python, node)
    list_comprehension0()
    def list_comprehension0():
        __target = __builtin__.list()
        for x in (1, 2, 3):
            __builtin__.list.append(__target, (x * x))
        return __target
    """

    def __init__(self):
        self.count = 0
        Transformation.__init__(self)

    @staticmethod
    def nest_reducer(x, g):
        """
        Create a ast.For node from a comprehension and another node.

        g is an ast.comprehension.
        x is the code that have to be executed.

        Examples
        --------
        >> [i for i in xrange(2)]

        Becomes

        >> for i in xrange(2):
        >>    ... x code with if clauses ...

        It is a reducer as it can be call recursively for mutli generator.

        Ex : >> [i, j for i in xrange(2) for j in xrange(4)]
        """
        def wrap_in_ifs(node, ifs):
            """
            Wrap comprehension content in all possibles if clauses.

            Examples
            --------
            >> [i for i in xrange(2) if i < 3 if 0 < i]

            Becomes

            >> for i in xrange(2):
            >>    if i < 3:
            >>        if 0 < i:
            >>            ... the code from `node` ...

            Note the nested ifs clauses.
            """
            return reduce(lambda n, if_: ast.If(if_, [n], []), ifs, node)
        return ast.For(g.target, g.iter, [wrap_in_ifs(x, g.ifs)], [])

    def visit_AnyComp(self, node, comp_type, *path):
        self.update = True
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
                              reduce(lambda x, y: ast.Attribute(x, y,
                                                                ast.Load()),
                                     path[1:],
                                     ast.Name(path[0], ast.Load())),
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
        return self.visit_AnyComp(node, "list",
                                  "__builtin__", "list", "append")

    def visit_SetComp(self, node):
        return self.visit_AnyComp(node, "set", "__builtin__", "set", "add")

    def visit_DictComp(self, node):
        # this is a quickfix to match visit_AnyComp signature
        # potential source of improvement there!
        node.elt = ast.List(
            [ast.Tuple([node.key, node.value], ast.Load())],
            ast.Load()
            )
        return self.visit_AnyComp(node, "dict", "__dispatch__", "update")

    def visit_GeneratorExp(self, node):
        self.update = True
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
