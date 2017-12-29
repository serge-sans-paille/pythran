''' Simplify modulo computation based on index'''

from pythran.analyses import UseDefChain, Ancestors, Aliases, RangeValues
from pythran.analyses import Identifiers
from pythran.passmanager import Transformation
from pythran.tables import MODULES

import gast as ast
from math import isinf
from copy import deepcopy


class ModIndex(Transformation):
    '''
    Simplify modulo on loop index

    >>> import gast as ast
    >>> from pythran import passmanager, backend
    >>> pm = passmanager.PassManager("test")
    >>> code = """
    ... def foo(x):
    ...     y = __builtin__.len(x)
    ...     for i in __builtin__.xrange(8):
    ...         z = i % y"""
    >>> node = ast.parse(code)
    >>> _, node = pm.apply(ModIndex, node)
    >>> print pm.dump(backend.Python, node)
    def foo(x):
        y = __builtin__.len(x)
        i_m = ((0 - 1) % y)
        for i in __builtin__.xrange(8):
            i_m = (0 if ((i_m + 1) == y) else (i_m + 1))
            z = i_m
    '''

    def __init__(self):
        Transformation.__init__(self, UseDefChain, Ancestors, Aliases,
                                RangeValues, Identifiers)
        self.loops_mod = dict()

    def has_single_def(node):
        chain = self.use_def_chain[node.id]
        head = [chain.node[n] for n in chain.nodes()
                if chain.node[n]['action'] in ('D', 'UD')]
        return len(head) == 1 and head[0]

    def visit_BinOp(self, node):
        if not isinstance(node.op, ast.Mod):
            return self.generic_visit(node)

        # check that right is a name defined once outside of loop
        # TODO: handle expression instead of names
        if not isinstance(node.right, ast.Name):
            return self.generic_visit(node)

        if not self.has_single_def(node.right):
            return self.generic_visit(node)

        if self.range_values[node.right.id].low < 0:
            return self.generic_visit(node)

        # same for lhs
        if not isinstance(node.left, ast.Name):
            return self.generic_visit(node)

        head = self.has_single_def(node.left)
        if head:
            return self.generic_visit(node)

        # check lhs is the actual index of a loop
        head = head[0]['name']
        loop = self.ancestors[head][-1]

        if not isinstance(loop, ast.For):
            return self.generic_visit(node)

        if not isinstance(loop.iter, ast.Call):
            return self.generic_visit(node)

        # make sure rhs is defined out of the loop
        if loop in self.ancestors[node.right]:
            return self.generic_visit(node)

        # gather range informations
        range_ = None
        for alias in self.aliases[loop.iter.func]:
            if alias is MODULES['__builtin__']['xrange']:
                range_ = alias
            else:
                break

        if range_ is None:
            return self.generic_visit(node)

        # everything is setup for the transformation!
        new_id = node.left.id + '_m'
        i = 0
        while new_id in self.identifiers:
            new_id = '{}_m{}'.format(node.left.id, i)
            i += 1

        rargs = range_.args.args
        lower = rargs[0] if len(rargs) > 1 else ast.Num(0)
        header = ast.Assign([ast.Name(new_id, ast.Store(), None)],
                            ast.BinOp(
                                ast.BinOp(deepcopy(lower),
                                          ast.Sub(),
                                          ast.Num(1)),
                                ast.Mod(),
                                deepcopy(node.right)))
        incr = ast.BinOp(ast.Name(new_id, ast.Load(), None),
                         ast.Add(),
                         ast.Num(1))
        step = ast.Assign([ast.Name(new_id, ast.Store(), None)],
                          ast.IfExp(
                              ast.Compare(incr,
                                          [ast.Eq()], [deepcopy(node.right)]),
                              ast.Num(0),
                              deepcopy(incr)))

        self.loops_mod.setdefault(loop, []).append((header, step))
        self.update = True
        return ast.Name(new_id, ast.Load(), None)

    def visit_For(self, node):
        self.generic_visit(node)
        if node not in self.loops_mod:
            return node

        headers = [h for h, _ in self.loops_mod[node]]
        steps = [s for _, s in self.loops_mod[node]]
        node.body = steps + node.body
        return headers + [node]
