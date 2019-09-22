""" This module provides way to convert a Python value into an ast. """
from __future__ import absolute_import

import gast as ast
import numpy as np
import sys
import numbers


# Maximum length of folded sequences
# Containers larger than this are not unfolded to limit code size growth
MAX_LEN = 2 ** 8


class ConversionError(Exception):

    """ Exception raised when conversion from value to ast can't be done. """


class ToNotEval(Exception):

    """
    Exception raised when we don't want to evaluate the value.

    It is case of too long expression for example.
    """


def totuple(l):
    try:
        return tuple(map(totuple, l))
    except TypeError:
        return l


def dtype_to_ast(name):
    if name in ('bool',):
        return ast.Attribute(
            ast.Name('__builtin__', ast.Load(), None, None),
            name,
            ast.Load())
    else:
        return ast.Attribute(
            ast.Name(mangle('numpy'), ast.Load(), None, None),
            name,
            ast.Load())


def size_container_folding(value):
    """
    Convert value to ast expression if size is not too big.

    Converter for sized container.
    """

    def size(x):
        return len(getattr(x, 'flatten', lambda: x)())

    if size(value) < MAX_LEN:
        if isinstance(value, list):
            return ast.List([to_ast(elt) for elt in value], ast.Load())
        elif isinstance(value, tuple):
            return ast.Tuple([to_ast(elt) for elt in value], ast.Load())
        elif isinstance(value, set):
            if value:
                return ast.Set([to_ast(elt) for elt in value])
            else:
                return ast.Call(func=ast.Attribute(
                    ast.Name(mangle('__builtin__'), ast.Load(), None, None),
                    'set',
                    ast.Load()),
                    args=[],
                    keywords=[])
        elif isinstance(value, dict):
            keys = [to_ast(elt) for elt in value.keys()]
            values = [to_ast(elt) for elt in value.values()]
            return ast.Dict(keys, values)
        elif isinstance(value, np.ndarray):
            return ast.Call(func=ast.Attribute(
                ast.Name(mangle('numpy'), ast.Load(), None, None),
                'array',
                ast.Load()),
                args=[to_ast(totuple(value.tolist())),
                      dtype_to_ast(value.dtype.name)],
                keywords=[])
        else:
            raise ConversionError()
    else:
        raise ToNotEval()


def builtin_folding(value):
    """ Convert builtin function to ast expression. """
    if isinstance(value, (type(None), bool)):
        name = str(value)
    else:
        name = value.__name__
    return ast.Attribute(ast.Name('__builtin__', ast.Load(), None, None),
                         name, ast.Load())


def to_ast(value):
    """
    Turn a value into ast expression.

    >>> a = 1
    >>> print(ast.dump(to_ast(a)))
    Num(n=1)
    >>> a = [1, 2, 3]
    >>> print(ast.dump(to_ast(a)))
    List(elts=[Num(n=1), Num(n=2), Num(n=3)], ctx=Load())
    """

    if isinstance(value, (type(None), bool)):
        return builtin_folding(value)
    if sys.version_info[0] == 2 and isinstance(value, long):
        from pythran.syntax import PythranSyntaxError
        raise PythranSyntaxError("constant folding results in big int")
    if any(value is t for t in (bool, int, float)):
        iinfo = np.iinfo(int)
        if isinstance(value, int) and not (iinfo.min <= value <= iinfo.max):
            from pythran.syntax import PythranSyntaxError
            raise PythranSyntaxError("constant folding results in big int")
        return builtin_folding(value)
    elif isinstance(value, np.generic):
        return to_ast(np.asscalar(value))
    elif isinstance(value, (numbers.Number, str)):
        return ast.Constant(value, None)
    elif isinstance(value, (list, tuple, set, dict, np.ndarray)):
        return size_container_folding(value)
    elif hasattr(value, "__module__") and value.__module__ == "__builtin__":
        # TODO Can be done the same way for others modules
        return builtin_folding(value)
    # only meaningful for python3
    elif sys.version_info.major == 3:
        if isinstance(value, (filter, map, zip)):
            return to_ast(list(value))
    raise ToNotEval()


PYTHRAN_IMPORT_MANGLING = '__pythran_import_'


def mangle(name):
    '''
    Mangle a module name, except the __builtin__ module
    >>> mangle('numpy')
    __pythran_import_numpy
    >>> mangle('__builtin__')
    __builtin__
    '''
    if name == '__builtin__':
        return name
    else:
        return PYTHRAN_IMPORT_MANGLING + name


def demangle(name):
    '''
    Demangle a module name, if needed
    >>> demangle('__pythran_import_numpy')
    numpy
    >>> mangle('numpy')
    numpy
    '''
    if name.startswith(PYTHRAN_IMPORT_MANGLING):
        return name[len(PYTHRAN_IMPORT_MANGLING):]
    else:
        return name
