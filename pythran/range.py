""" Module with facilities to represent range values. """

from math import isinf
import ast
import itertools

import numpy


class Range(object):

    """ Representation for a range of values. """

    def __init__(self, low, high):
        """ Set initial bound of the range object. """
        self.low = low
        self.high = high

    def __repr__(self):
        """ Return a nicely formatted representation string. """
        return "Range(low={low}, high={high})".format(low=self.low,
                                                      high=self.high)

    def update(self, new_range):
        """ Intersect current range with new_range."""
        self.low = min(self.low, new_range.low)
        self.high = max(self.high, new_range.high)

    def __iter__(self):
        """ Iterate over a range bound."""
        yield self.low
        yield self.high

    def widen(self, range_):
        """ Widen current range. """
        if self.low < range_.low:
            self.low = -float("inf")
        if self.high > range_.high:
            self.high = float("inf")


UNKNOWN_RANGE = Range(-float("inf"), float("inf"))


def range_values(args):
    """ Function used to compute returned range value of [x]range function. """
    if len(args) == 1:
        return (0, args[0].high)
    elif len(args) == 2:
        return (args[0].low, args[1].high)
    elif len(args) == 3:
        is_neg = args[2].low < 0
        is_pos = args[2].high > 0
        if is_neg and is_pos:
            return UNKNOWN_RANGE
        elif is_neg:
            return (args[1].low, args[0].high)
        else:
            return (args[0].low, args[1].high)


def bool_values(_):
    """ Return the range of a boolean value, i.e. [0, 1]. """
    return Range(0, 1)


def cmp_values(_):
    """ Return the range of a comparison value, i.e. [-1, 1]. """
    return Range(-1, 1)


def positive_values(_):
    """ Return a positive range without upper bound. """
    return Range(0, float("inf"))


def max_values(args):
    """ Return possible range for max function. """
    return Range(max(x.low for x in args), max(x.high for x in args))


def min_values(args):
    """ Return possible range for min function. """
    return Range(min(x.low for x in args), min(x.high for x in args))


def ord_values(_):
    """ Return possible range for ord function. """
    return Range(0, 255)


def combine_sub(range1, range2):
    """
    Combiner for Subtraction operation.

    >>> import ast
    >>> combine(Range(1, 5), Range(-5, -4), ast.Sub())
    Range(low=5, high=10)
    """
    return Range(range1.low - range2.high, range1.high - range2.low)


def combine_mult(range1, range2):
    """
    Combiner for Multiplication operation.

    >>> import ast
    >>> combine(Range(1, 5), Range(-5, -4), ast.Mult())
    Range(low=-25, high=-4)
    >>> combine(Range(-1, 5), Range(-5, 3), ast.Mult())
    Range(low=-25, high=15)
    >>> combine(Range(1, 5), Range(3, 8), ast.Mult())
    Range(low=3, high=40)
    """
    res = [v1 * v2 for v1, v2 in itertools.product(range1, range2)]
    return Range(numpy.min(res), numpy.max(res))


def combine_add(range1, range2):
    """
    Combiner for Addition operation.

    >>> import ast
    >>> combine(Range(-12, 5), Range(-5, -3), ast.Add())
    Range(low=-17, high=2)
    """
    return Range(range1.low + range2.low, range1.high + range2.high)


def combine_div(range1, range2):
    """
    Combiner for Divide operation.

    >>> import ast
    >>> combine(Range(-1, 5), Range(3, 8), ast.Div())
    Range(low=-1, high=1)
    >>> combine(Range(-1, 5), Range(-5, -4), ast.Div())
    Range(low=-2, high=0)
    >>> combine(Range(-1, 5), Range(-5, 3), ast.Div())
    Range(low=-inf, high=inf)
    """
    if range2.low <= 0 and range2.high >= 0:
        return UNKNOWN_RANGE
    if 0 in range2:
        return UNKNOWN_RANGE
    res = [v1 / v2 for v1, v2 in itertools.product(range1, range2)]
    return Range(numpy.min(res), numpy.max(res))


def combine_floordiv(range1, range2):
    """
    Combiner for Floor divide operation.

    >>> import ast
    >>> combine(Range(-1, 5), Range(3, 8), ast.FloorDiv())
    Range(low=-1, high=1)
    >>> combine(Range(-1, 5), Range(-5, -4), ast.FloorDiv())
    Range(low=-2, high=0)
    >>> combine(Range(-1, 5), Range(-5, 3), ast.FloorDiv())
    Range(low=-inf, high=inf)
    """
    if range2.low <= 0 and range2.high >= 0:
        return UNKNOWN_RANGE
    if 0 in range2:
        return UNKNOWN_RANGE
    res = [v1 // v2 for v1, v2 in itertools.product(range1, range2)]
    return Range(numpy.min(res), numpy.max(res))


def combine_unknown(*_):
    """
    Combiner for operation with unknown range result.

    >>> import ast
    >>> combine(Range(1, 5), Range(3, 8), ast.BitXor())
    Range(low=-inf, high=inf)
    >>> combine(Range(1, 5), Range(3, 8), ast.BitOr())
    Range(low=-inf, high=inf)
    >>> combine(Range(1, 5), Range(3, 8), ast.BitAnd())
    Range(low=-inf, high=inf)
    """
    return UNKNOWN_RANGE


def combine_rshift(range1, range2):
    """
    Combiner for Right shift operation.

    >>> import ast
    >>> combine(Range(10, 100), Range(3, 8), ast.RShift())
    Range(low=0, high=12)
    >>> combine(Range(10, float("inf")), Range(3, 8),
    ...                       ast.RShift())
    Range(low=0, high=inf)
    >>> combine(Range(-float("inf"), 0), Range(3, 8),
    ...                       ast.RShift())
    Range(low=-inf, high=0)
    >>> combine(Range(-30, 10), Range(3, float('inf')),
    ...                       ast.RShift())
    Range(low=-4, high=1)
    """
    if range1.low <= 0:
        if isinf(range1.low):
            min_ = range1.low
        else:
            min_ = range1.low >> range2.low
    elif isinf(range2.high):
        min_ = 0
    else:
        min_ = range1.low >> range2.high
    if isinf(range1.high):
        max_ = range1.high
    elif isinf(range2.low):
        max_ = 0
    else:
        max_ = range1.high >> range2.low
    return Range(min_, max_)


def combine_lshift(range1, range2):
    """
    Combiner for Left shift operation.

    >>> import ast
    >>> combine(Range(1, 5), Range(3, 8), ast.LShift())
    Range(low=8, high=1280)
    >>> combine(Range(1, float("inf")), Range(3, 8),
    ...                       ast.LShift())
    Range(low=8, high=inf)
    >>> combine(Range(-float("inf"), 0), Range(3, 8),
    ...                       ast.LShift())
    Range(low=-inf, high=0)
    >>> combine(Range(-3, 1), Range(3, float('inf')),
    ...                       ast.LShift())
    Range(low=-24, high=inf)
    """
    min_inf = isinf(range1.low) or isinf(range2.low)
    max_inf = isinf(range1.high) or isinf(range2.high)
    min_ = -float("inf") if min_inf else (range1.low << range2.low)
    max_ = float("inf") if max_inf else (range1.high << range2.high)
    return Range(min_, max_)


def combine_pow(range1, range2):
    """
    Combiner for Power operation.

    >>> import ast
    >>> combine(Range(1, 5), Range(-5, -4), ast.Pow())
    Range(low=1.0, high=1.0)
    >>> combine(Range(-1, 5), Range(-5, 3), ast.Pow())
    Range(low=-1.0, high=125.0)
    >>> combine(Range(1, 5), Range(3, 8), ast.Pow())
    Range(low=1.0, high=390625.0)
    """
    res = [v1 ** v2 for v1, v2 in itertools.product(range1, range2)]
    return Range(numpy.ceil(numpy.min(res)), numpy.floor(numpy.max(res)))


def combine_mod(range1, range2):
    """ Combiner for Modulo operation.

    >>> import ast
    >>> combine(Range(-1, 5), Range(1, 13), ast.Mod())
    Range(low=0, high=5)
    >>> combine(Range(-21, 5), Range(1, 13), ast.Mod())
    Range(low=0, high=13)
    """
    return Range(0, min(range2.high, max(abs(range1.high), abs(range1.low))))


COMBINE_DISPATCHER = {
    ast.Add: combine_add,
    ast.Sub: combine_sub,
    ast.Mult: combine_mult,
    ast.Div: combine_div,
    ast.Mod: combine_mod,
    ast.Pow: combine_pow,
    ast.LShift: combine_lshift,
    ast.RShift: combine_rshift,
    ast.BitXor: combine_unknown,
    ast.BitOr: combine_unknown,
    ast.BitAnd: combine_unknown,
    ast.FloorDiv: combine_floordiv
}


def combine(range1, range2, op):
    """ Combine two range joined by a given operation. """
    return COMBINE_DISPATCHER[type(op)](range1, range2)
