""" Module Analysing code to extract positive subscripts from code.  """
# TODO check bound of while and if for more occurate values.

import ast
import copy

from pythran.analyses import Globals, Aliases
from pythran.intrinsic import Intrinsic
from pythran.passmanager import FunctionAnalysis
from pythran.range import Range, UNKNOWN_RANGE, combine


class RangeValues(FunctionAnalysis):

    """
    This analyse extract positive subscripts from code.

    It is flow insensitif and aliasing is not taken into account as integer
    doesn't create aliasing in Python.
    """

    def __init__(self):
        """Initialize instance variable and gather globals name information."""
        self.result = dict()
        super(RangeValues, self).__init__(Globals, Aliases)

    def add(self, variable, range_):
        """
        Add a new low and high bound for a variable.

        As it is flow insensitif, it compares it with olds values and update it
        if needed.
        """
        if variable not in self.result:
            self.result[variable] = range_
        else:
            self.result[variable].update(range_)

    def visit_FunctionDef(self, node):
        """ Set default range value for globals and attributs.

        >>> import ast
        >>> from pythran import passmanager, backend
        >>> node = ast.parse("def foo(a, b): pass")
        >>> pm = passmanager.PassManager("test")
        >>> res = pm.gather(RangeValues, node)
        >>> res['a']
        Range(low=-inf, high=inf)
        """
        for global_name in self.globals:
            self.result[global_name] = UNKNOWN_RANGE
        for attr in node.args.args:
            self.result[attr.id] = UNKNOWN_RANGE

        map(self.visit, node.body)

    def visit_Assign(self, node):
        """
        Set range value for assigned variable.

        We do not handle container values.

        >>> import ast
        >>> from pythran import passmanager, backend
        >>> node = ast.parse("def foo(): a = b = 2")
        >>> pm = passmanager.PassManager("test")
        >>> res = pm.gather(RangeValues, node)
        >>> res['a']
        Range(low=2, high=2)
        >>> res['b']
        Range(low=2, high=2)
        """
        assigned_range = self.visit(node.value)
        for target in node.targets:
            if isinstance(target, ast.Name):
                # Make sure all Range doesn't alias for multiple variables.
                self.add(target.id, copy.deepcopy(assigned_range))

    def visit_AugAssign(self, node):
        """ Update range value for augassigned variables.

        >>> import ast
        >>> from pythran import passmanager, backend
        >>> node = ast.parse("def foo(): a = 2; a -= 1")
        >>> pm = passmanager.PassManager("test")
        >>> res = pm.gather(RangeValues, node)
        >>> res['a']
        Range(low=1, high=2)
        """
        if isinstance(node.target, ast.Name):
            self.result[node.target.id].update(
                combine(self.result[node.target.id],
                        self.visit(node.value),
                        node.op))

    def visit_For(self, node):
        """ Handle iterate variable in for loops.

        >>> import ast
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
        Range(low=-inf, high=2)
        >>> res['b']
        Range(low=2, high=inf)
        >>> res['c']
        Range(low=2, high=2)
        """
        assert isinstance(node.target, ast.Name), "For apply on variables."
        if isinstance(node.iter, ast.Call):
            for alias in self.aliases[node.iter.func]:
                if isinstance(alias, Intrinsic):
                    self.add(node.target.id,
                             alias.return_range_content(map(self.visit,
                                                            node.iter.args)))
                else:
                    self.add(node.target.id, UNKNOWN_RANGE)
        else:
            self.add(node.target.id, UNKNOWN_RANGE)

        self.visit_loop(node)

    def visit_loop(self, node):
        """ Handle incremented variables in loop body.

        >>> import ast
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
        Range(low=-inf, high=2)
        >>> res['b']
        Range(low=2, high=inf)
        >>> res['c']
        Range(low=2, high=2)
        """
        old_range = copy.deepcopy(self.result)
        map(self.visit, node.body)
        for name, range_ in old_range.iteritems():
            self.result[name].widen(range_)
        map(self.visit, node.orelse)

    visit_While = visit_loop

    def visit_BoolOp(self, node):
        """ Merge right and left operands ranges.

        TODO : We could exclude some operand with this range information...

        >>> import ast
        >>> from pythran import passmanager, backend
        >>> node = ast.parse('''
        ... def foo():
        ...     a = 2
        ...     c = 3
        ...     d = a or c''')
        >>> pm = passmanager.PassManager("test")
        >>> res = pm.gather(RangeValues, node)
        >>> res['d']
        Range(low=2, high=3)
        """
        res = zip(*map(self.visit, node.values))
        return Range(min(res[0]), max(res[1]))

    def visit_BinOp(self, node):
        """ Combine operands ranges for given operator.

        >>> import ast
        >>> from pythran import passmanager, backend
        >>> node = ast.parse('''
        ... def foo():
        ...     a = 2
        ...     c = 3
        ...     d = a - c''')
        >>> pm = passmanager.PassManager("test")
        >>> res = pm.gather(RangeValues, node)
        >>> res['d']
        Range(low=-1, high=-1)
        """
        return combine(self.visit(node.left), self.visit(node.right), node.op)

    def visit_UnaryOp(self, node):
        """ Update range with given unary operation.

        >>> import ast
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
        Range(low=2, high=2)
        >>> res['c']
        Range(low=-2, high=-2)
        >>> res['d']
        Range(low=-3, high=-3)
        >>> res['e']
        Range(low=0, high=1)
        """
        res = self.visit(node.operand)
        if isinstance(node.op, ast.Not):
            return Range(0, 1)
        elif(isinstance(node.op, ast.Invert) and
             isinstance(res.high, int) and
             isinstance(res.low, int)):
            return Range(~res.high, ~res.low)
        elif isinstance(node.op, ast.UAdd):
            return res
        elif isinstance(node.op, ast.USub):
            return Range(-res.high, -res.low)
        else:
            return UNKNOWN_RANGE

    def visit_IfExp(self, node):
        """ Use worst case for both possible values.

        >>> import ast
        >>> from pythran import passmanager, backend
        >>> node = ast.parse('''
        ... def foo():
        ...     a = 2 or 3
        ...     b = 4 or 5
        ...     c = a if a else b''')
        >>> pm = passmanager.PassManager("test")
        >>> res = pm.gather(RangeValues, node)
        >>> res['c']
        Range(low=2, high=5)
        """
        self.visit(node.test)
        body_res = self.visit(node.body)
        orelse_res = self.visit(node.orelse)
        return Range(min(orelse_res.low, body_res.low),
                     max(orelse_res.high, body_res.high))

    @staticmethod
    def visit_Compare(_):
        """ Boolean are possible index.

        >>> import ast
        >>> from pythran import passmanager, backend
        >>> node = ast.parse('''
        ... def foo():
        ...     a = 2 or 3
        ...     b = 4 or 5
        ...     c = a < b''')
        >>> pm = passmanager.PassManager("test")
        >>> res = pm.gather(RangeValues, node)
        >>> res['c']
        Range(low=0, high=1)
        """
        return Range(0, 1)

    def visit_Call(self, node):
        """ Function calls are not handled for now.

        >>> import ast
        >>> from pythran import passmanager, backend
        >>> node = ast.parse('''
        ... def foo():
        ...     a = __builtin__.range(10)''')
        >>> pm = passmanager.PassManager("test")
        >>> res = pm.gather(RangeValues, node)
        >>> res['a']
        Range(low=-inf, high=inf)
        """
        result = None
        for alias in self.aliases[node.func]:
            if isinstance(alias, Intrinsic):
                alias_range = alias.return_range(map(self.visit, node.args))
                result = result.update(alias_range) if result else alias_range
            else:
                return UNKNOWN_RANGE
        return result or UNKNOWN_RANGE

    @staticmethod
    def visit_Num(node):
        """ Handle literals integers values. """
        if isinstance(node.n, int):
            return Range(node.n, node.n)
        else:
            return UNKNOWN_RANGE

    def visit_Name(self, node):
        """ Get range for parameters for examples or false branching. """
        return self.result[node.id]

    def visit_ExceptHandler(self, node):
        """ Add a range value for exception variable.

        >>> import ast
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
        Range(low=-inf, high=inf)
        """
        if node.name:
            self.result[node.name.id] = UNKNOWN_RANGE
        map(self.visit, node.body)

    def generic_visit(self, node):
        """ Other nodes are not known and range value neither. """
        super(RangeValues, self).generic_visit(node)
        return UNKNOWN_RANGE
