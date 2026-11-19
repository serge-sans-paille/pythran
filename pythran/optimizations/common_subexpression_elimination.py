"""
CommonSubexpressionElimination evaluates once an expression that is computed
several times in a row.
"""

from pythran.analyses.inlinable import Inlinable
from pythran.analyses.pure_expressions import PureExpressions
from pythran.openmp import OMPDirective
from pythran.passmanager import Transformation
from pythran.utils import isattr
import pythran.metadata as metadata

from collections import namedtuple
import gast as ast


# what a shared expression can be made of
Shareable = (ast.BinOp, ast.UnaryOp, ast.BoolOp, ast.Compare, ast.Call,
             ast.IfExp, ast.Attribute, ast.Name, ast.Constant, ast.keyword)

# what may update a value in place, or run some code we know nothing about
Barriers = (ast.AugAssign, ast.Delete, ast.Import, ast.ImportFrom, ast.With,
            ast.Yield, ast.YieldFrom, ast.Await, OMPDirective)

Occurrence = namedtuple('Occurrence',
                        'index holder field position node counted')


def get(holder, field, position):
    value = getattr(holder, field)
    return value if position is None else value[position]


def identifiers(node):
    """ Return the identifiers `node` reads. """
    return {n.id for n in ast.walk(node) if isinstance(n, ast.Name)}


def trivial(node):
    """ Tell if `node` is too cheap to deserve a variable. """
    if isinstance(node, ast.Attribute):
        return trivial(node.value)
    if isinstance(node, ast.UnaryOp):
        return trivial(node.operand)
    # isattr stands for x.shape, x.real...
    return isinstance(node, (ast.Name, ast.Constant)) or isattr(node)


def iterated(holder, node):
    """
    Tell if `holder` may iterate over the value of `node`.

    This matters for the result of a call, that may be an iterator: it can
    only be read once. The result of an operation never is.
    """
    if isinstance(node, (ast.BinOp, ast.UnaryOp, ast.Compare)):
        return False
    if isinstance(holder, ast.Compare):
        return any(isinstance(op, (ast.In, ast.NotIn)) for op in holder.ops)
    return isinstance(holder, (ast.Call, ast.BoolOp))


def views(node):
    """ Return the identifiers `node` may evaluate to a view of. """
    # an operation evaluates to a new value
    if isinstance(node, (ast.BinOp, ast.Compare, ast.Constant)):
        return set()
    if isinstance(node, ast.Name):
        return {node.id}
    if isinstance(node, ast.Subscript):
        return views(node.value)
    return set().union(*map(views, ast.iter_child_nodes(node)))


class CommonSubexpressionElimination(Transformation[PureExpressions,
                                                    Inlinable]):

    """
    Store in a variable the value of an expression computed several times.

    >>> import gast as ast
    >>> from pythran import passmanager, backend
    >>> pm = passmanager.PassManager("test")
    >>> node = ast.parse("def foo(a, b, c): return (a + b) * c + (a + b) / c")
    >>> _, node = pm.apply(CommonSubexpressionElimination, node)
    >>> print(pm.dump(backend.Python, node))
    def foo(a, b, c):
        __cse0 = (a + b)
        return ((__cse0 * c) + (__cse0 / c))

    The variable is a lazy one: an array expression is not stored in a new
    array but still evaluated where it is used, while any other value, as the
    result of a reduction, is computed once.

    Only the statements of a same block are considered. Nothing between the
    first and the last evaluation may update a value in place, and what the
    expression reads may not be updated in place anywhere in the function.

    >>> node = ast.parse('''
    ... def foo(a, b, c):
    ...     x = (a + b) * c
    ...     c[0] = 1
    ...     return x + (a + b) / c''')
    >>> _, node = pm.apply(CommonSubexpressionElimination, node)
    >>> print(pm.dump(backend.Python, node))
    def foo(a, b, c):
        x = ((a + b) * c)
        c[0] = 1
        return (x + ((a + b) / c))

    The expression is left as is when its value may be referenced afterward,
    as sharing it would turn two different objects into a single one.

    >>> node = ast.parse('''
    ... def foo(a, b):
    ...     x = a + b
    ...     y = a + b
    ...     return x, y''')
    >>> _, node = pm.apply(CommonSubexpressionElimination, node)
    >>> print(pm.dump(backend.Python, node))
    def foo(a, b):
        x = (a + b)
        y = (a + b)
        return (x, y)
    """

    def operands(self, node, kept, guarded):
        """
        Yield the operands of `node`, as (holder, field, position, kept,
        guarded)

        `kept` tells if the value of the operand may still be referenced once
        `node` is evaluated, and `guarded` if the operand may not be evaluated
        at all.
        """
        if isinstance(node, ast.BinOp):
            yield node, 'left', None, False, guarded
            yield node, 'right', None, False, guarded
        elif isinstance(node, ast.UnaryOp):
            yield node, 'operand', None, False, guarded
        elif isinstance(node, ast.Compare):
            # an identity test tells two evaluations apart
            kept = any(isinstance(op, (ast.Is, ast.IsNot)) for op in node.ops)
            yield node, 'left', None, kept, guarded
            for i in range(len(node.comparators)):
                yield node, 'comparators', i, kept, guarded or i > 0
        elif isinstance(node, ast.BoolOp):
            for i in range(len(node.values)):
                yield node, 'values', i, kept, guarded or i > 0
        elif isinstance(node, ast.IfExp):
            yield node, 'test', None, False, guarded
            yield node, 'body', None, kept, True
            yield node, 'orelse', None, kept, True
        elif isinstance(node, ast.Call):
            # a function without side effect may still return its argument
            kept = kept or node not in self.pure_expressions
            for i in range(len(node.args)):
                yield node, 'args', i, kept, guarded
        elif isinstance(node, (ast.Attribute, ast.Subscript)):
            kept = kept or not isinstance(node.ctx, ast.Load)
            yield node, 'value', None, kept, guarded
            if isinstance(node, ast.Subscript):
                yield from self.indices(node, 'slice', None, guarded)
        elif isinstance(node, (ast.Tuple, ast.List, ast.Set)):
            for i in range(len(node.elts)):
                yield node, 'elts', i, True, guarded

    def indices(self, holder, field, position, guarded):
        """ Yield the expressions an index is made of, they are only read. """
        node = get(holder, field, position)
        if isinstance(node, ast.Tuple):
            for i in range(len(node.elts)):
                yield from self.indices(node, 'elts', i, guarded)
        elif isinstance(node, ast.Slice):
            for bound in ('lower', 'upper', 'step'):
                if getattr(node, bound) is not None:
                    yield node, bound, None, False, guarded
        else:
            yield holder, field, position, False, guarded

    def roots(self, stmt):
        """
        Yield the expressions evaluated by `stmt` itself, and not by the
        statements it holds, as (holder, field, position, kept, counted)

        `counted` tells if LazynessAnalysis counts the identifiers read there.
        """
        if isinstance(stmt, (ast.Assign, ast.AnnAssign, ast.AugAssign)):
            if stmt.value is not None:
                yield stmt, 'value', None, True, True
            targets = getattr(stmt, 'targets', None) or [stmt.target]
            # several targets are assigned one after the other
            if len(targets) == 1 and isinstance(targets[0], ast.Subscript):
                for operand in self.operands(targets[0], True, False):
                    yield operand[:4] + (False,)
        elif isinstance(stmt, ast.Return):
            if stmt.value is not None:
                yield stmt, 'value', None, True, True
        elif isinstance(stmt, ast.Expr):
            yield stmt, 'value', None, False, True
        elif isinstance(stmt, (ast.If, ast.Assert)):
            yield stmt, 'test', None, False, True
        elif isinstance(stmt, ast.For):
            yield stmt, 'iter', None, True, True

    def number(self, node):
        """
        Give the same number to the expressions that compute the same value,
        and None to the ones that cannot be shared.
        """
        if id(node) in self.numbered:
            return self.numbered[id(node)]
        self.numbered[id(node)] = number = self.compute_number(node)
        return number

    def compute_number(self, node):
        if isinstance(node, ast.Constant):
            key = ast.Constant, type(node.value), repr(node.value)
        elif isinstance(node, ast.Name):
            key = ast.Name, node.id
        elif isinstance(node, Shareable):
            # the meaning of builtins.pythran.* and isinstance depends on
            # where they are evaluated
            if getattr(node, 'attr', None) in ('pythran', 'isinstance'):
                return None
            key = [type(node)]
            for _, value in ast.iter_fields(node):
                for item in value if isinstance(value, list) else [value]:
                    if isinstance(item, (ast.expr, ast.keyword)):
                        item = self.number(item)
                        if item is None:
                            return None
                    elif isinstance(item, ast.AST):
                        item = type(item)
                    key.append(item)
            key = tuple(key)
        else:
            return None
        return self.numbers.setdefault(key, len(self.numbers))

    def scan(self, index, holder, field, position, kept, guarded, counted):
        """ Record the expressions of statement `index` that can be shared. """
        node = get(holder, field, position)
        if not (kept or guarded or trivial(node) or iterated(holder, node)):
            # the expression may be evaluated lazily, once a value it reads
            # is updated
            if (id(holder) not in self.shared and
                    node in self.pure_expressions and
                    self.updated.isdisjoint(identifiers(node))):
                number = self.number(node)
                if number is not None:
                    self.found.setdefault(number, []).append(
                        Occurrence(index, holder, field, position, node,
                                   counted))
        for operand in self.operands(node, kept, guarded):
            self.scan(index, *operand, counted)

    def effects(self, nodes):
        """
        Return the identifiers assigned when evaluating `nodes`, or None if
        that may update a value in place.
        """
        assigned = set()
        for root in nodes:
            for node in ast.walk(root):
                if isinstance(node, Barriers):
                    return None
                if isinstance(node, ast.Call):
                    if node not in self.pure_expressions:
                        return None
                elif isinstance(node, (ast.Subscript, ast.Attribute)):
                    if not isinstance(node.ctx, ast.Load):
                        return None
                elif isinstance(node, ast.Name):
                    if not isinstance(node.ctx, ast.Load):
                        assigned.add(node.id)
        return assigned

    def steady(self, block, first, last, names):
        """
        Tell if an expression reading `names` has the same value from the
        beginning of statement `first` to the evaluation of statement `last`.
        """
        for index in range(first, last + 1):
            key = index, index == last
            if key not in self.assigned:
                stmt = block[index]
                if index == last:
                    # what the last statement holds or assigns comes too late
                    nodes = [get(*root[:3]) for root in self.roots(stmt)]
                else:
                    nodes = [stmt]
                self.assigned[key] = self.effects(nodes)
            assigned = self.assigned[key]
            if assigned is None or not assigned.isdisjoint(names):
                return False
        return True

    def select(self, block, occurrences):
        """
        Return the first occurrences in a row that can share their value.

        At least two of them must be counted by LazynessAnalysis, otherwise
        ForwardSubstitution would put the expression back.
        """
        names = identifiers(occurrences[0].node)
        for start in range(len(occurrences) - 1):
            first = occurrences[start].index
            stop = start + 1
            while (stop < len(occurrences) and
                   self.steady(block, first, occurrences[stop].index, names)):
                stop += 1
            selected = occurrences[start:stop]
            if sum(occurrence.counted for occurrence in selected) > 1:
                return selected
        return None

    def share(self, block, occurrences):
        while True:
            name = '__cse{}'.format(self.count)
            self.count += 1
            if name not in self.names:
                break
        self.names.add(name)
        for occurrence in occurrences:
            load = ast.Name(name, ast.Load(), None, None)
            if occurrence.position is None:
                setattr(occurrence.holder, occurrence.field, load)
            else:
                operands = getattr(occurrence.holder, occurrence.field)
                operands[occurrence.position] = load
        store = ast.Name(name, ast.Store(), None, None)
        # storing the value of an array expression costs more than evaluating
        # it where it is used
        metadata.add(store, metadata.Lazy())
        block.insert(occurrences[0].index,
                     ast.Assign([store], occurrences[0].node, None))
        self.update = True

    def visit_block(self, block):
        while True:
            self.found, self.numbers = {}, {}
            self.numbered, self.assigned = {}, {}
            for index, stmt in enumerate(block):
                if metadata.get(stmt, OMPDirective):
                    continue
                for root in self.roots(stmt):
                    holder, field, position, kept, counted = root
                    self.scan(index, holder, field, position, kept, False,
                              counted)

            # larger expressions first, so that they are not split
            def size(group):
                return len(list(ast.walk(group[0].node)))

            groups = sorted(self.found.values(), key=size, reverse=True)
            for group in groups:
                selected = self.select(block, group)
                if selected:
                    self.share(block, selected)
                    break
            else:
                return

    def blocks(self, node):
        """ Yield the lists of statements held by `node`. """
        for field in ('body', 'orelse', 'finalbody', 'handlers'):
            block = getattr(node, field, None)
            if isinstance(block, list):
                if field != 'handlers':
                    yield block
                for stmt in block:
                    if not metadata.get(stmt, OMPDirective):
                        yield from self.blocks(stmt)

    def update_in_place(self, function):
        """ Return the identifiers `function` may update the value of. """
        updated = set()
        for node in ast.walk(function):
            if isinstance(node, ast.AugAssign):
                updated.update(views(node.target))
            elif isinstance(node, (ast.Subscript, ast.Attribute)):
                if not isinstance(node.ctx, ast.Load):
                    updated.update(views(node.value))
            elif isinstance(node, ast.Call):
                if node not in self.pure_expressions:
                    keywords = [keyword.value for keyword in node.keywords]
                    updated.update(*map(views, node.args + keywords))
        return updated

    def visit_Module(self, node):
        # a function that is about to be inlined is better left as is
        self.inlined = identifiers(node).intersection(self.inlinable)
        return self.generic_visit(node)

    def visit_FunctionDef(self, node):
        if node.name in self.inlined:
            return node

        self.count = 0
        self.names = identifiers(node)
        self.updated = self.update_in_place(node)

        # ForwardSubstitution may reference a node from several places,
        # updating such a node updates all these places at once
        seen, self.shared = set(), set()
        for n in ast.walk(node):
            (self.shared if id(n) in seen else seen).add(id(n))

        for block in list(self.blocks(node)):
            self.visit_block(block)
        return node
