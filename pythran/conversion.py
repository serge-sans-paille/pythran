""" This module provides way to convert a Python value into an ast. """

from __future__ import absolute_import

import ast
import itertools
import numpy
import types

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


def size_container_folding(value):
    """
    Convert value to ast expression if size is not too big.

    Converter for sized container.
    """
    if len(value) < MAX_LEN:
        if isinstance(value, list):
            return ast.List(map(to_ast, value), ast.Load())
        elif isinstance(value, tuple):
            return ast.Tuple(map(to_ast, value), ast.Load())
        elif isinstance(value, set):
            return ast.Set(map(to_ast, value))
        elif isinstance(value, dict):
            keys = map(to_ast, value.iterkeys())
            values = map(to_ast, value.itervalues())
            return ast.Dict(keys, values)
        elif isinstance(value, numpy.ndarray):
            return ast.Call(func=ast.Attribute(ast.Name('numpy', ast.Load()),
                                               'array',
                                               ast.Load()),
                            args=[to_ast(value.tolist())],
                            keywords=[],
                            starargs=None,
                            kwargs=None)
        else:
            raise ConversionError()
    else:
        raise ToNotEval()


def builtin_folding(value):
    """ Convert builtin function to ast expression. """
    if value.__name__ in ("bool", "float", "int", "long"):
        name = value.__name__ + "_"
    else:
        name = value.__name__
    return ast.Attribute(ast.Name('__builtin__', ast.Load()),
                         name, ast.Load())


def to_ast(value):
    """
    Turn a value into ast expression.

    >>> a = 1
    >>> print ast.dump(to_ast(a))
    Num(n=1)
    >>> a = [1, 2, 3]
    >>> print ast.dump(to_ast(a))
    List(elts=[Num(n=1), Num(n=2), Num(n=3)], ctx=Load())
    """
    numpy_type = (numpy.float64, numpy.float32, numpy.float16,
                  numpy.complex_, numpy.complex64, numpy.complex128,
                  numpy.float_, numpy.uint8, numpy.uint16, numpy.uint32,
                  numpy.uint64, numpy.int8, numpy.int16, numpy.int32,
                  numpy.int64, numpy.intp, numpy.intc, numpy.int_,
                  numpy.bool_)
    itertools_t = [getattr(itertools, fun) for fun in dir(itertools)
                   if isinstance(getattr(itertools, fun), types.TypeType)]
    unfolded_type = (types.BuiltinFunctionType, types.BuiltinMethodType,
                     types.FunctionType, types.TypeType, types.XRangeType,
                     numpy.ufunc, type(list.append), types.FileType,
                     BaseException, types.GeneratorType) + tuple(itertools_t)
    if isinstance(value, (types.NoneType, bool)):
        return ast.Attribute(ast.Name('__builtin__', ast.Load()),
                             str(value), ast.Load())
    elif isinstance(value, (int, long, float, complex)):
        return ast.Num(value)
    elif isinstance(value, str):
        return ast.Str(value)
    elif isinstance(value, (list, tuple, set, dict, numpy.ndarray)):
        return size_container_folding(value)
    elif hasattr(value, "__module__") and value.__module__ == "__builtin__":
        # TODO Can be done the same way for others modules
        return builtin_folding(value)
    elif isinstance(value, numpy_type):
        return to_ast(numpy.asscalar(value))
    elif isinstance(value, unfolded_type):
        raise ToNotEval()
    elif value in numpy_type:
        raise ToNotEval()
    else:
        raise ConversionError()
