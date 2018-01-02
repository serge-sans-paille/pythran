""" Module Analysing code to extract positive subscripts from code.  """
# TODO check bound of while and if for more accurate values.

import gast as ast
from collections import defaultdict

from pythran.analyses import Globals, Aliases
from pythran.intrinsic import Intrinsic
from pythran.passmanager import FunctionAnalysis
from pythran.interval import Interval, UNKNOWN_RANGE
from pythran.tables import MODULES, attributes


def combine(op, node0, node1):
    key = '__{}__'.format(op.__class__.__name__.lower())
    try:
        return getattr(Interval, key)(node0, node1)
    except AttributeError:
        return UNKNOWN_RANGE


class RangeValues(FunctionAnalysis):

    """
    This analyse extract positive subscripts from code.

    It is flow sensitive and aliasing is not taken into account as integer
    doesn't create aliasing in Python.

    >>> import gast as ast
    >>> from pythran import passmanager, backend
    >>> node = ast.parse('''
    ... def foo(a):
    ...     for i in __builtin__.range(1, 10):
    ...         c = i // 2''')
    >>> pm = passmanager.PassManager("test")
    >>> res = pm.gather(RangeValues, node)
    >>> res['c'], res['i']
    (Interval(low=0, high=5), Interval(low=1, high=10))
    """

    def __init__(self):
        """Initialize instance variable and gather globals name information."""
        self.result = defaultdict(lambda: UNKNOWN_RANGE)
        super(RangeValues, self).__init__(Globals, Aliases)

    def add(self, variable, range_):
        """
        Add a new low and high bound for a variable.

        As it is flow insensitive, it compares it with old values and update it
        if needed.
        """
        if variable not in self.result:
            self.result[variable] = range_
        else:
            self.result[variable] = self.result[variable].union(range_)
        return self.result[variable]

    def visit_FunctionDef(self, node):
        """ Set default range value for globals and attributes.

        >>> import gast as ast
        >>> from pythran import passmanager, backend
        >>> node = ast.parse("def foo(a, b): pass")
        >>> pm = passmanager.PassManager("test")
        >>> res = pm.gather(RangeValues, node)
        >>> res['a']
        Interval(low=-inf, high=inf)
        """
        for stmt in node.body:
            self.visit(stmt)

    def visit_Assign(self, node):
        """
        Set range value for assigned variable.

        We do not handle container values.

        >>> import gast as ast
        >>> from pythran import passmanager, backend
        >>> node = ast.parse("def foo(): a = b = 2")
        >>> pm = passmanager.PassManager("test")
        >>> res = pm.gather(RangeValues, node)
        >>> res['a']
        Interval(low=2, high=2)
        >>> res['b']
        Interval(low=2, high=2)
        """
        assigned_range = self.visit(node.value)
        for target in node.targets:
            if isinstance(target, ast.Name):
                # Make sure all Interval doesn't alias for multiple variables.
                self.add(target.id, assigned_range)
            else:
                self.visit(target)

    def visit_AugAssign(self, node):
        """ Update range value for augassigned variables.

        >>> import gast as ast
        >>> from pythran import passmanager, backend
        >>> node = ast.parse("def foo(): a = 2; a -= 1")
        >>> pm = passmanager.PassManager("test")
        >>> res = pm.gather(RangeValues, node)
        >>> res['a']
        Interval(low=1, high=2)
        """
        self.generic_visit(node)
        if isinstance(node.target, ast.Name):
            name = node.target.id
            res = combine(node.op,
                          self.result[name],
                          self.result[node.value])
            self.result[name] = self.result[name].union(res)

    def visit_For(self, node):
        """ Handle iterate variable in for loops.

        >>> import gast as ast
        >>> from pythran import passmanager, backend
        >>> node = ast.parse('''
        ... def foo():
        ...     a = b = c = 2
        ...     for i in __builtin__.range(1):
        ...         a -= 1
        ...         b += 1''')
        >>> pm = passmanager.PassManager("test")
        >>> res = pm.gather(RangeValues, node)
        >>> res['a']
        Interval(low=-inf, high=2)
        >>> res['b']
        Interval(low=2, high=inf)
        >>> res['c']
        Interval(low=2, high=2)
        """
        assert isinstance(node.target, ast.Name), "For apply on variables."
        self.visit(node.iter)
        if isinstance(node.iter, ast.Call):
            for alias in self.aliases[node.iter.func]:
                if isinstance(alias, Intrinsic):
                    self.add(node.target.id,
                             alias.return_range_content(
                                 [self.visit(n) for n in node.iter.args]))

        self.visit_loop(node)

    def visit_loop(self, node, cond=None):
        """ Handle incremented variables in loop body.

        >>> import gast as ast
        >>> from pythran import passmanager, backend
        >>> node = ast.parse('''
        ... def foo():
        ...     a = b = c = 2
        ...     while a > 0:
        ...         a -= 1
        ...         b += 1''')
        >>> pm = passmanager.PassManager("test")
        >>> res = pm.gather(RangeValues, node)
        >>> res['a']
        Interval(low=-inf, high=2)
        >>> res['b']
        Interval(low=2, high=inf)
        >>> res['c']
        Interval(low=2, high=2)
        """
        # visit once to gather newly declared vars
        for stmt in node.body:
            self.visit(stmt)

        # freeze current state
        old_range = self.result.copy()

        # extra round
        for stmt in node.body:
            self.visit(stmt)

        # widen any change
        for expr, range_ in old_range.items():
            self.result[expr] = self.result[expr].widen(range_)

        # propagate  the new informations
        cond and self.visit(cond)
        for stmt in node.body:
            self.visit(stmt)

        for stmt in node.orelse:
            self.visit(stmt)

    def visit_While(self, node):
        self.visit(node.test)
        return self.visit_loop(node, node.test)

    def visit_BoolOp(self, node):
        """ Merge right and left operands ranges.

        TODO : We could exclude some operand with this range information...

        >>> import gast as ast
        >>> from pythran import passmanager, backend
        >>> node = ast.parse('''
        ... def foo():
        ...     a = 2
        ...     c = 3
        ...     d = a or c''')
        >>> pm = passmanager.PassManager("test")
        >>> res = pm.gather(RangeValues, node)
        >>> res['d']
        Interval(low=2, high=3)
        """
        res = list(zip(*[self.visit(elt).bounds() for elt in node.values]))
        return self.add(node, Interval(min(res[0]), max(res[1])))

    def visit_BinOp(self, node):
        """ Combine operands ranges for given operator.

        >>> import gast as ast
        >>> from pythran import passmanager, backend
        >>> node = ast.parse('''
        ... def foo():
        ...     a = 2
        ...     c = 3
        ...     d = a - c''')
        >>> pm = passmanager.PassManager("test")
        >>> res = pm.gather(RangeValues, node)
        >>> res['d']
        Interval(low=-1, high=-1)
        """
        res = combine(node.op, self.visit(node.left), self.visit(node.right))
        return self.add(node, res)

    def visit_UnaryOp(self, node):
        """ Update range with given unary operation.

        >>> import gast as ast
        >>> from pythran import passmanager, backend
        >>> node = ast.parse('''
        ... def foo():
        ...     a = 2
        ...     c = -a
        ...     d = ~a
        ...     f = +a
        ...     e = not a''')
        >>> pm = passmanager.PassManager("test")
        >>> res = pm.gather(RangeValues, node)
        >>> res['f']
        Interval(low=2, high=2)
        >>> res['c']
        Interval(low=-2, high=-2)
        >>> res['d']
        Interval(low=-3, high=-3)
        >>> res['e']
        Interval(low=0, high=1)
        """
        res = self.visit(node.operand)
        if isinstance(node.op, ast.Not):
            res = Interval(0, 1)
        elif(isinstance(node.op, ast.Invert) and
             isinstance(res.high, int) and
             isinstance(res.low, int)):
            res = Interval(~res.high, ~res.low)
        elif isinstance(node.op, ast.UAdd):
            pass
        elif isinstance(node.op, ast.USub):
            res = Interval(-res.high, -res.low)
        else:
            res = UNKNOWN_RANGE
        return self.add(node, res)

    def visit_If(self, node):
        """ Handle iterate variable across branches

        >>> import gast as ast
        >>> from pythran import passmanager, backend
        >>> node = ast.parse('''
        ... def foo(a):
        ...     if a > 1: b = 1
        ...     else: b = 3''')

        >>> pm = passmanager.PassManager("test")
        >>> res = pm.gather(RangeValues, node)
        >>> res['b']
        Interval(low=1, high=3)
        """
        self.visit(node.test)
        old_range = self.result

        self.result = old_range.copy()
        for stmt in node.body:
            self.visit(stmt)
        body_range = self.result

        self.result = old_range.copy()
        for stmt in node.orelse:
            self.visit(stmt)
        orelse_range = self.result

        self.result = body_range
        for k, v in orelse_range.items():
            if k in self.result:
                self.result[k] = self.result[k].union(v)
            else:
                self.result[k] = v

    def visit_IfExp(self, node):
        """ Use worst case for both possible values.

        >>> import gast as ast
        >>> from pythran import passmanager, backend
        >>> node = ast.parse('''
        ... def foo():
        ...     a = 2 or 3
        ...     b = 4 or 5
        ...     c = a if a else b''')
        >>> pm = passmanager.PassManager("test")
        >>> res = pm.gather(RangeValues, node)
        >>> res['c']
        Interval(low=2, high=5)
        """
        self.visit(node.test)
        body_res = self.visit(node.body)
        orelse_res = self.visit(node.orelse)
        return self.add(node, orelse_res.union(body_res))

    def visit_Compare(self, node):
        """ Boolean are possible index.

        >>> import gast as ast
        >>> from pythran import passmanager, backend
        >>> node = ast.parse('''
        ... def foo():
        ...     a = 2 or 3
        ...     b = 4 or 5
        ...     c = a < b
        ...     d = b < 3
        ...     e = b == 4''')
        >>> pm = passmanager.PassManager("test")
        >>> res = pm.gather(RangeValues, node)
        >>> res['c']
        Interval(low=1, high=1)
        >>> res['d']
        Interval(low=0, high=0)
        >>> res['e']
        Interval(low=0, high=1)
        """
        if any(isinstance(op, (ast.In, ast.NotIn, ast.Is, ast.IsNot))
               for op in node.ops):
            self.generic_visit(node)
            return self.add(node, Interval(0, 1))

        curr = self.visit(node.left)
        res = []
        for op, comparator in zip(node.ops, node.comparators):
            comparator = self.visit(comparator)
            fake = ast.Compare(ast.Name('x', ast.Load(), None),
                               [op],
                               [ast.Name('y', ast.Load(), None)])
            fake = ast.Expression(fake)
            ast.fix_missing_locations(fake)
            expr = compile(ast.gast_to_ast(fake), '<range_values>', 'eval')
            res.append(eval(expr, {'x': curr, 'y': comparator}))
        if all(res):
            return self.add(node, Interval(1, 1))
        elif any(r.low == r.high == 0 for r in res):
            return self.add(node, Interval(0, 0))
        else:
            return self.add(node, Interval(0, 1))

    def visit_Call(self, node):
        """ Function calls are not handled for now.

        >>> import gast as ast
        >>> from pythran import passmanager, backend
        >>> node = ast.parse('''
        ... def foo():
        ...     a = __builtin__.range(10)''')
        >>> pm = passmanager.PassManager("test")
        >>> res = pm.gather(RangeValues, node)
        >>> res['a']
        Interval(low=-inf, high=inf)
        """
        for alias in self.aliases[node.func]:
            if alias is MODULES['__builtin__']['getattr']:
                attr_name = node.args[-1].s
                attribute = attributes[attr_name][-1]
                self.add(node, attribute.return_range(None))
            elif isinstance(alias, Intrinsic):
                alias_range = alias.return_range(
                    [self.visit(n) for n in node.args])
                self.add(node, alias_range)
            else:
                return self.generic_visit(node)
        return self.result[node]

    def visit_Num(self, node):
        """ Handle literals integers values. """
        if isinstance(node.n, int):
            return self.add(node, Interval(node.n, node.n))
        return UNKNOWN_RANGE

    def visit_Name(self, node):
        """ Get range for parameters for examples or false branching. """
        return self.add(node, self.result[node.id])

    def visit_Index(self, node):
        return self.add(node, self.visit(node.value))

    def visit_Subscript(self, node):
        if isinstance(node.value, ast.Call):
            for alias in self.aliases[node.value.func]:
                if alias is MODULES['__builtin__']['getattr']:
                    attr_name = node.value.args[-1].s
                    attribute = attributes[attr_name][-1]
                    self.add(node, attribute.return_range_content(None))
                elif isinstance(alias, Intrinsic):
                    self.add(node,
                             alias.return_range_content(
                                 [self.visit(n) for n in node.value.args]))
                else:
                    return self.generic_visit(node)
            if not self.aliases[node.value.func]:
                return self.generic_visit(node)
            self.visit(node.slice)
            return self.result[node]
        else:
            return self.generic_visit(node)

    def visit_ExceptHandler(self, node):
        """ Add a range value for exception variable.

        >>> import gast as ast
        >>> from pythran import passmanager, backend
        >>> node = ast.parse('''
        ... def foo():
        ...     try:
        ...         pass
        ...     except __builtin__.RuntimeError as e:
        ...         pass''')
        >>> pm = passmanager.PassManager("test")
        >>> res = pm.gather(RangeValues, node)
        >>> res['e']
        Interval(low=-inf, high=inf)
        """
        for stmt in node.body:
            self.visit(stmt)

    def generic_visit(self, node):
        """ Other nodes are not known and range value neither. """
        super(RangeValues, self).generic_visit(node)
        return self.add(node, UNKNOWN_RANGE)
