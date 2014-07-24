'''
This module provides way to convert a Python value into an ast
'''

import ast
import numpy
import types
import itertools

# maximum length of folded sequences
# containers larger than this are not unfolded to limit code size growth
MAX_LEN = 2 ** 8


class ConversionError(Exception):
    pass


class ToNotEval(Exception):
    """
    Exception raised when we don't want to evaluate the value (case of
    too long expression for example).
    """
    pass


def to_ast(value):
    '''
    Turns a value into ast expression

    >>> a = 1
    >>> print ast.dump(to_ast(a))
    Num(n=1)
    >>> a = [1, 2, 3]
    >>> print ast.dump(to_ast(a))
    List(elts=[Num(n=1), Num(n=2), Num(n=3)], ctx=Load())
    '''
    numpy_type = (numpy.float64, numpy.float32, numpy.float16,
                  numpy.complex_, numpy.complex64, numpy.complex128,
                  numpy.float_, numpy.uint8, numpy.uint16, numpy.uint32,
                  numpy.uint64, numpy.int8, numpy.int16, numpy.int32,
                  numpy.int64, numpy.intp, numpy.intc, numpy.int_,
                  numpy.bool_)
    unfolded_type = (types.BuiltinFunctionType, types.BuiltinMethodType,
                     types.FunctionType, types.TypeType, types.XRangeType,
                     numpy.ufunc, type(list.append), types.FileType,
                     BaseException, types.GeneratorType, itertools.count)
    if (type(value) in (int, long, float, complex)):
        return ast.Num(value)
    elif value is None:
        return ast.Attribute(ast.Name('__builtin__', ast.Load()),
                             'None', ast.Load())
    elif value is repr:
        return ast.Attribute(ast.Name('__builtin__', ast.Load()),
                             'repr', ast.Load())
    elif isinstance(value, bool):
        return ast.Attribute(ast.Name('__builtin__', ast.Load()),
                             'True' if value else 'False', ast.Load())
    elif isinstance(value, str):
        return ast.Str(value)
    elif isinstance(value, list):
        if len(value) < MAX_LEN:
            return ast.List(map(to_ast, value), ast.Load())
        else:
            raise ToNotEval()
    elif isinstance(value, tuple):
        if len(value) < MAX_LEN:
            return ast.Tuple(map(to_ast, value), ast.Load())
        else:
            raise ToNotEval()
    elif isinstance(value, set):
        if len(value) < MAX_LEN:
            return ast.Set(map(to_ast, value))
        else:
            raise ToNotEval()
    elif isinstance(value, dict):
        if len(value) < MAX_LEN:
            keys = map(to_ast, value.iterkeys())
            values = map(to_ast, value.itervalues())
            return ast.Dict(keys, values)
        else:
            raise ToNotEval()
    elif isinstance(value, numpy.ndarray):
        return ast.Call(func=ast.Attribute(ast.Name('numpy', ast.Load()),
                                           'array',
                                           ast.Load()),
                        args=[to_ast(value.tolist())],
                        keywords=[],
                        starargs=None,
                        kwargs=None)
    elif value in (bool, int, long, float, complex):
        if value is complex:
            name = value.__name__
        else:
            name = value.__name__ + '_'
        return ast.Attribute(ast.Name('__builtin__', ast.Load()),
                             name, ast.Load())
    elif isinstance(value, numpy_type):
        return to_ast(numpy.asscalar(value))
    elif isinstance(value, unfolded_type):
        raise ToNotEval()
    else:
        raise ConversionError()
