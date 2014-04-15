"""
NormalizeTuples removes implicit variable -> tuple conversion
"""
import ast
from pythran.passmanager import Transformation


class _ConvertToTuple(ast.NodeTransformer):
    def __init__(self, tuple_id, renamings):
        self.tuple_id = tuple_id
        self.renamings = renamings

    def visit_Name(self, node):
        if node.id in self.renamings:
            nnode = reduce(
                lambda x, y: ast.Subscript(
                    x,
                    ast.Index(ast.Num(y)),
                    ast.Load()),
                self.renamings[node.id],
                ast.Name(self.tuple_id, ast.Load())
                )
            nnode.ctx = node.ctx
            return nnode
        return node


class NormalizeTuples(Transformation):
    """
    Remove implicit tuple -> variable conversion.

    >>> import ast, passmanager, backend
    >>> node = ast.parse("a=(1,2.) ; i,j = a")
    >>> pm = passmanager.PassManager("test")
    >>> node = pm.apply(NormalizeTuples, node)
    >>> print pm.dump(backend.Python, node)
    a = (1, 2.0)
    if 1:
        __tuple10 = a
        i = __tuple10[0]
        j = __tuple10[1]
    """
    tuple_name = "__tuple"

    def __init__(self):
        self.counter = 0
        Transformation.__init__(self)

    def traverse_tuples(self, node, state, renamings):
        if isinstance(node, ast.Name):
            if state:
                renamings[node.id] = state
        elif isinstance(node, ast.Tuple) or isinstance(node, ast.List):
            [self.traverse_tuples(n, state + (i,), renamings)
             for i, n in enumerate(node.elts)]
        elif type(node) in (ast.Subscript, ast.Attribute):
            if state:
                renamings[node] = state
        else:
            raise NotImplementedError

    def visit_comprehension(self, node):
        renamings = dict()
        self.traverse_tuples(node.target, (), renamings)
        if renamings:
            self.counter += 1
            return ("{0}{1}".format(
                NormalizeTuples.tuple_name,
                self.counter),
                renamings)
        else:
            return node

    def visit_AnyComp(self, node, *fields):
        for field in fields:
            setattr(node, field, self.visit(getattr(node, field)))
        generators = map(self.visit, node.generators)
        nnode = node
        for i, g in enumerate(generators):
            if isinstance(g, tuple):
                gtarget = "{0}{1}".format(g[0], i)
                nnode.generators[i].target = ast.Name(
                    gtarget,
                    nnode.generators[i].target.ctx)
                nnode = _ConvertToTuple(gtarget, g[1]).visit(nnode)
        for field in fields:
            setattr(node, field, getattr(nnode, field))
        node.generators = nnode.generators
        return node

    def visit_ListComp(self, node):
        return self.visit_AnyComp(node, 'elt')

    def visit_SetComp(self, node):
        return self.visit_AnyComp(node, 'elt')

    def visit_DictComp(self, node):
        return self.visit_AnyComp(node, 'key', 'value')

    def visit_GeneratorExp(self, node):
        return self.visit_AnyComp(node, 'elt')

    def visit_Lambda(self, node):
        self.generic_visit(node)
        for i, arg in enumerate(node.args.args):
            renamings = dict()
            self.traverse_tuples(arg, (), renamings)
            if renamings:
                self.counter += 1
                nname = "{0}{1}".format(
                    NormalizeTuples.tuple_name,
                    self.counter)
                node.args.args[i] = ast.Name(nname, ast.Param())
                node.body = _ConvertToTuple(nname, renamings).visit(node.body)
        return node

    def visit_Assign(self, node):
        self.generic_visit(node)
        extra_assign = [node]
        for i, t in enumerate(node.targets):
            if isinstance(t, ast.Tuple) or isinstance(t, ast.List):
                renamings = dict()
                self.traverse_tuples(t, (), renamings)
                if renamings:
                    self.counter += 1
                    gtarget = "{0}{1}{2}".format(
                        NormalizeTuples.tuple_name,
                        self.counter,
                        i)
                    node.targets[i] = ast.Name(gtarget, node.targets[i].ctx)
                    for rename, state in sorted(renamings.iteritems()):
                        nnode = reduce(
                            lambda x, y: ast.Subscript(
                                x,
                                ast.Index(ast.Num(y)),
                                ast.Load()),
                            state,
                            ast.Name(gtarget, ast.Load()))
                        if isinstance(rename, str):
                            extra_assign.append(
                                ast.Assign(
                                    [ast.Name(rename, ast.Store())],
                                    nnode))
                        else:
                            extra_assign.append(ast.Assign([rename], nnode))
        return (ast.If(ast.Num(1), extra_assign, [])
                if len(extra_assign) > 1
                else extra_assign)

    def visit_For(self, node):
        target = node.target
        if isinstance(target, ast.Tuple) or isinstance(target, ast.List):
            renamings = dict()
            self.traverse_tuples(target, (), renamings)
            if renamings:
                self.counter += 1
                gtarget = "{0}{1}".format(
                    NormalizeTuples.tuple_name,
                    self.counter
                    )
                node.target = ast.Name(gtarget, node.target.ctx)
                for rename, state in sorted(renamings.iteritems()):
                    nnode = reduce(
                        lambda x, y: ast.Subscript(
                            x,
                            ast.Index(ast.Num(y)),
                            ast.Load()),
                        state,
                        ast.Name(gtarget, ast.Load()))
                    if isinstance(rename, str):
                        node.body.insert(0,
                                         ast.Assign(
                                             [ast.Name(rename, ast.Store())],
                                             nnode)
                                         )
                    else:
                        node.body.insert(0, ast.Assign([rename], nnode))

        self.generic_visit(node)
        return node
