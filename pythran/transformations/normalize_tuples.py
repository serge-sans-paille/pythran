""" NormalizeTuples removes implicit variable -> tuple conversion. """

from pythran.analyses import Identifiers
from pythran.passmanager import Transformation

import ast


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

    >>> import ast
    >>> from pythran import passmanager, backend
    >>> node = ast.parse("def foo(): a=(1,2.) ; i,j = a")
    >>> pm = passmanager.PassManager("test")
    >>> _, node = pm.apply(NormalizeTuples, node)
    >>> print pm.dump(backend.Python, node)
    def foo():
        a = (1, 2.0)
        i = a[0]
        j = a[1]
    """
    tuple_name = "__tuple"

    def __init__(self):
        Transformation.__init__(self)

    def get_new_id(self):
        i = 0
        while 1:
            new_id = "{}{}".format(NormalizeTuples.tuple_name, i)
            if new_id not in self.ids:
                self.ids.add(new_id)
                return new_id
            else:
                i += 1

    def traverse_tuples(self, node, state, renamings):
        if isinstance(node, ast.Name):
            if state:
                renamings[node.id] = state
                self.update = True
        elif isinstance(node, ast.Tuple) or isinstance(node, ast.List):
            [self.traverse_tuples(n, state + (i,), renamings)
             for i, n in enumerate(node.elts)]
        elif isinstance(node, (ast.Subscript, ast.Attribute)):
            if state:
                renamings[node] = state
                self.update = True
        else:
            raise NotImplementedError

    def visit_comprehension(self, node):
        renamings = dict()
        self.traverse_tuples(node.target, (), renamings)
        if renamings:
            self.update = True
            return self.get_new_id(), renamings
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
                self.update = True
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
                nname = self.get_new_id()
                node.args.args[i] = ast.Name(nname, ast.Param())
                node.body = _ConvertToTuple(nname, renamings).visit(node.body)
        return node

    def visit_Assign(self, node):
        self.generic_visit(node)
        # if the rhs is an identifier, we don't need to duplicate it
        # otherwise, better duplicate it...
        no_tmp = isinstance(node.value, ast.Name)
        extra_assign = [] if no_tmp else [node]
        for i, t in enumerate(node.targets):
            if isinstance(t, ast.Tuple) or isinstance(t, ast.List):
                renamings = dict()
                self.traverse_tuples(t, (), renamings)
                if renamings:
                    gtarget = node.value.id if no_tmp else self.get_new_id()
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
        return extra_assign or node

    def visit_For(self, node):
        target = node.target
        if isinstance(target, ast.Tuple) or isinstance(target, ast.List):
            renamings = dict()
            self.traverse_tuples(target, (), renamings)
            if renamings:
                gtarget = self.get_new_id()
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

    def visit_FunctionDef(self, node):
        self.ids = self.passmanager.gather(Identifiers, node, self.ctx)
        return self.generic_visit(node)
