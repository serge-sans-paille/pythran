""" This modules provides the translation tables from python to c++. """

import ast
import inspect
import logging
import sys

from pythran import cxxtypes
from pythran.conversion import to_ast, ToNotEval
from pythran.cxxtypes import NamedType
from pythran.intrinsic import Class
from pythran.intrinsic import ClassWithConstConstructor, ExceptionClass
from pythran.intrinsic import ClassWithReadOnceConstructor
from pythran.intrinsic import ConstFunctionIntr, FunctionIntr, UpdateEffect
from pythran.intrinsic import ConstMethodIntr, MethodIntr, AttributeIntr
from pythran.intrinsic import ReadEffect, ConstantIntr
from pythran.intrinsic import ReadOnceFunctionIntr, ConstExceptionIntr
from pythran.types.conversion import PYTYPE_TO_CTYPE_TABLE
from pythran import range as prange

logger = logging.getLogger("pythran")

pythran_ward = '__pythran_'

namespace = "pythonic"

cxx_keywords = {
    'and', 'and_eq', 'asm', 'auto', 'bitand', 'bitor',
    'bool', 'break', 'case', 'catch', 'char', 'class',
    'compl', 'const', 'const_cast', 'continue', 'default', 'delete',
    'do', 'double', 'dynamic_cast', 'else', 'enum', 'explicit',
    'export', 'extern', 'false', 'float', 'for', 'friend',
    'goto', 'if', 'inline', 'int', 'long', 'mutable', 'namespace', 'new',
    'not', 'not_eq', 'operator', 'or', 'or_eq', 'private', 'protected',
    'public', 'register', 'reinterpret_cast', 'return', 'short', 'signed',
    'sizeof', 'static', 'static_cast',
    'struct', 'switch', 'template', 'this', 'throw', 'true',
    'try', 'typedef', 'typeid', 'typename', 'union', 'unsigned',
    'using', 'virtual', 'void', 'volatile', 'wchar_t', 'while',
    'xor', 'xor_eq',
    # C++11 additions
    'constexpr', 'decltype', 'noexcept', 'nullptr', 'static_assert',
    # reserved namespaces
    'std',
    }


operator_to_lambda = {
    # boolop
    ast.And:
        "(pythonic::__builtin__::functor::bool_{{}}({0})?({1}):({0}))".format,
    ast.Or:
        "(pythonic::__builtin__::functor::bool_{{}}({0})?({0}):({1}))".format,
    # operator
    ast.Add: "({0} + {1})".format,
    ast.Sub: "({0} - {1})".format,
    ast.Mult: "({0} * {1})".format,
    ast.Div: "({0} / {1})".format,
    ast.Mod: "(pythonic::operator_::mod({0}, {1}))".format,
    ast.Pow: "(pythonic::__builtin__::pow({0}, {1}))".format,
    ast.LShift: "({0} << {1})".format,
    ast.RShift: "({0} >> {1})".format,
    ast.BitOr: "({0} | {1})".format,
    ast.BitXor: "({0} ^ {1})".format,
    ast.BitAnd: "({0} & {1})".format,
    # assume from __future__ import division
    ast.FloorDiv: "(pythonic::operator_::floordiv({0}, {1}))".format,
    # unaryop
    ast.Invert: "(~{0})".format,
    ast.Not: "(not {0})".format,
    ast.UAdd: "(+{0})".format,
    ast.USub: "(-{0})".format,
    # cmpop
    ast.Eq: "({0} == {1})".format,
    ast.NotEq: "({0} != {1})".format,
    ast.Lt: "({0} < {1})".format,
    ast.LtE: "({0} <= {1})".format,
    ast.Gt: "({0} > {1})".format,
    ast.GtE: "({0} >= {1})".format,
    ast.Is: ("(pythonic::__builtin__::id({0}) == "
             "pythonic::__builtin__::id({1}))").format,
    ast.IsNot: ("(pythonic::__builtin__::id({0}) != "
                "pythonic::__builtin__::id({1}))").format,
    ast.In: "(pythonic::in({1}, {0}))".format,
    ast.NotIn: "(not pythonic::in({1}, {0}))".format,
}


def update_effects(self, node):
    """
    Combiner when we update the fisrst argument of a function.

    It turn type of first parameter in combination of all others
    parameters types.
    """
    return [self.combine(node.args[0], node_args_k, register=True,
                         aliasing_type=True)
            for node_args_k in node.args[1:]]


CLASSES = {
    "list": {
        "append": MethodIntr(
            lambda self, node:
            self.combine(
                node.args[0],
                node.args[1],
                unary_op=cxxtypes.ListType,
                register=True,
                aliasing_type=True)
            ),
        "extend": MethodIntr(update_effects),
        "index": ConstMethodIntr(),
        "pop": MethodIntr(),
        "reverse": MethodIntr(),
        "sort": MethodIntr(),
        "count": ConstMethodIntr(),
        "remove": MethodIntr(),
        "insert": MethodIntr(
            lambda self, node:
            self.combine(
                node.args[0],
                node.args[2],
                unary_op=cxxtypes.ListType,
                register=True,
                aliasing_type=True)
            ),
        },
    "str": {
        "capitalize": ConstMethodIntr(),
        "count": ConstMethodIntr(),
        "endswith": ConstMethodIntr(return_range=prange.bool_values),
        "startswith": ConstMethodIntr(return_range=prange.bool_values),
        "find": ConstMethodIntr(),
        "isalpha": ConstMethodIntr(return_range=prange.bool_values),
        "isdigit": ConstMethodIntr(return_range=prange.bool_values),
        "join": ConstMethodIntr(),
        "lower": ConstMethodIntr(),
        "replace": ConstMethodIntr(),
        "split": ConstMethodIntr(),
        "strip": ConstMethodIntr(),
        "lstrip": ConstMethodIntr(),
        "rstrip": ConstMethodIntr(),
        "upper": ConstMethodIntr(),
    },
    "set": {
        "add": MethodIntr(
            lambda self, node:
            self.combine(
                node.args[0],
                node.args[1],
                unary_op=cxxtypes.SetType,
                register=True,
                aliasing_type=True)
        ),
        "clear": MethodIntr(),
        "copy": ConstMethodIntr(),
        "discard": MethodIntr(),
        "remove": MethodIntr(),
        "isdisjoint": ConstMethodIntr(return_range=prange.bool_values),
        "union_": ConstMethodIntr(),
        "update": MethodIntr(update_effects),
        "intersection": ConstMethodIntr(),
        "intersection_update": MethodIntr(update_effects),
        "difference": ConstMethodIntr(),
        "difference_update": MethodIntr(update_effects),
        "symmetric_difference": ConstMethodIntr(),
        "symmetric_difference_update": MethodIntr(update_effects),
        "issuperset": ConstMethodIntr(return_range=prange.bool_values),
        "issubset": ConstMethodIntr(return_range=prange.bool_values),
    },
    "Exception": {
        "args": AttributeIntr(return_type=NamedType("pythonic::types::str")),
        "errno": AttributeIntr(return_type=NamedType("pythonic::types::str")),
        "strerror": AttributeIntr(
            return_type=NamedType("pythonic::types::str")),
        "filename": AttributeIntr(
            return_type=NamedType("pythonic::types::str")),
    },
    "float": {
        "is_integer": ConstMethodIntr(return_range=prange.bool_values),
    },
    "complex": {
        "conjugate": ConstMethodIntr(),
        "real": AttributeIntr(return_type=NamedType("double")),
        "imag": AttributeIntr(return_type=NamedType("double")),
    },
    "dict": {
        "fromkeys": ConstFunctionIntr(),
        "clear": MethodIntr(),
        "copy": ConstMethodIntr(),
        "get": ConstMethodIntr(),
        "has_key": ConstMethodIntr(return_range=prange.bool_values),
        "items": MethodIntr(),
        "iteritems": MethodIntr(),
        "iterkeys": MethodIntr(),
        "itervalues": MethodIntr(),
        "keys": MethodIntr(),
        "pop": MethodIntr(),
        "popitem": MethodIntr(),
        "setdefault": MethodIntr(
            lambda self, node:
            len(node.args) == 3 and
            self.combine(
                node.args[0],
                node.args[1],
                unary_op=lambda x: cxxtypes.DictType(
                    x,
                    self.result[node.args[2]]),
                register=True,
                aliasing_type=True),
            return_alias=lambda args: {
                ast.Subscript(args[0],
                              ast.Index(args[1]),
                              ast.Load())
            }.union({args[2]} if len(args) == 3 else set())
        ),
        "update": MethodIntr(update_effects),
        "values": MethodIntr(),
        "viewitems": MethodIntr(),
        "viewkeys": MethodIntr(),
        "viewvalues": MethodIntr(),
    },
    "file": {
        # Member variables
        "closed": AttributeIntr(return_type=NamedType("bool")),
        "mode": AttributeIntr(return_type=NamedType("pythonic::types::str")),
        "name": AttributeIntr(return_type=NamedType("pythonic::types::str")),
        "newlines": AttributeIntr(
            return_type=NamedType("pythonic::types::str")),
        # Member functions
        "close": MethodIntr(global_effects=True),
        "flush": MethodIntr(global_effects=True),
        "fileno": MethodIntr(),
        "isatty": MethodIntr(),
        "next": MethodIntr(global_effects=True),
        "read": MethodIntr(global_effects=True),
        "readline": MethodIntr(global_effects=True),
        "readlines": MethodIntr(global_effects=True),
        "xreadlines": MethodIntr(global_effects=True),
        "seek": MethodIntr(global_effects=True),
        "tell": MethodIntr(),
        "truncate": MethodIntr(global_effects=True),
        "write": MethodIntr(global_effects=True),
        "writelines": MethodIntr(global_effects=True),
    },
    "finfo": {
        "eps": AttributeIntr(),
    },
    "ndarray": {
        "astype": MethodIntr(),
        "dtype": AttributeIntr(),
        "fill": MethodIntr(),
        "flat": AttributeIntr(),
        "flatten": MethodIntr(),
        "item": MethodIntr(),
        "itemsize": AttributeIntr(return_type=NamedType("long"),
                                  return_range=prange.positive_values),
        "nbytes": AttributeIntr(return_type=NamedType("long"),
                                return_range=prange.positive_values),
        "ndim": AttributeIntr(return_type=NamedType("long"),
                              return_range=prange.positive_values),
        "shape": AttributeIntr(),
        "size": AttributeIntr(return_type=NamedType("long"),
                              return_range=prange.positive_values),
        "strides": AttributeIntr(),
        "T": AttributeIntr(),
        "tolist": ConstMethodIntr(),
        "tostring": ConstMethodIntr(),
    },
}

# each module consist in a module_name <> set of symbols
MODULES = {
    "__builtin__": {
        "pythran": {
            "len_set": ConstFunctionIntr()
        },
        "abs": ConstFunctionIntr(),
        "BaseException": ConstExceptionIntr(),
        "SystemExit": ConstExceptionIntr(),
        "KeyboardInterrupt": ConstExceptionIntr(),
        "GeneratorExit": ConstExceptionIntr(),
        "Exception": ExceptionClass(CLASSES["Exception"]),
        "StopIteration": ConstExceptionIntr(),
        "StandardError": ConstExceptionIntr(),
        "Warning": ConstExceptionIntr(),
        "BytesWarning": ConstExceptionIntr(),
        "UnicodeWarning": ConstExceptionIntr(),
        "ImportWarning": ConstExceptionIntr(),
        "FutureWarning": ConstExceptionIntr(),
        "UserWarning": ConstExceptionIntr(),
        "SyntaxWarning": ConstExceptionIntr(),
        "RuntimeWarning": ConstExceptionIntr(),
        "PendingDeprecationWarning": ConstExceptionIntr(),
        "DeprecationWarning": ConstExceptionIntr(),
        "BufferError": ConstExceptionIntr(),
        "ArithmeticError": ConstExceptionIntr(),
        "AssertionError": ConstExceptionIntr(),
        "AttributeError": ConstExceptionIntr(),
        "EnvironmentError": ConstExceptionIntr(),
        "EOFError": ConstExceptionIntr(),
        "ImportError": ConstExceptionIntr(),
        "LookupError": ConstExceptionIntr(),
        "MemoryError": ConstExceptionIntr(),
        "NameError": ConstExceptionIntr(),
        "ReferenceError": ConstExceptionIntr(),
        "RuntimeError": ConstExceptionIntr(),
        "SyntaxError": ConstExceptionIntr(),
        "SystemError": ConstExceptionIntr(),
        "TypeError": ConstExceptionIntr(),
        "ValueError": ConstExceptionIntr(),
        "FloatingPointError": ConstExceptionIntr(),
        "OverflowError": ConstExceptionIntr(),
        "ZeroDivisionError": ConstExceptionIntr(),
        "IOError": ConstExceptionIntr(),
        "OSError": ConstExceptionIntr(),
        "IndexError": ConstExceptionIntr(),
        "KeyError": ConstExceptionIntr(),
        "UnboundLocalError": ConstExceptionIntr(),
        "NotImplementedError": ConstExceptionIntr(),
        "IndentationError": ConstExceptionIntr(),
        "TabError": ConstExceptionIntr(),
        "UnicodeError": ConstExceptionIntr(),
        #  "UnicodeDecodeError": ConstExceptionIntr(),
        #  "UnicodeEncodeError": ConstExceptionIntr(),
        #  "UnicodeTranslateError": ConstExceptionIntr(),
        "all": ReadOnceFunctionIntr(return_range=prange.bool_values),
        "any": ReadOnceFunctionIntr(return_range=prange.bool_values),
        "bin": ConstFunctionIntr(),
        "bool_": ConstFunctionIntr(return_range=prange.bool_values),
        "chr": ConstFunctionIntr(),
        "cmp": ConstFunctionIntr(return_range=prange.cmp_values),
        "complex": ClassWithConstConstructor(CLASSES['complex']),
        "dict": ClassWithReadOnceConstructor(CLASSES['dict']),
        "divmod": ConstFunctionIntr(),
        "enumerate": ReadOnceFunctionIntr(),
        "file": ClassWithConstConstructor(CLASSES['file'],
                                          global_effects=True),
        "filter": ReadOnceFunctionIntr(),
        "float_": ClassWithConstConstructor(CLASSES['float']),
        "getattr": ConstFunctionIntr(),
        "hex": ConstFunctionIntr(),
        "id": ConstFunctionIntr(),
        "int_": ConstFunctionIntr(),
        "iter": FunctionIntr(),  # not const
        "len": ConstFunctionIntr(return_range=prange.positive_values),
        "list": ClassWithReadOnceConstructor(CLASSES['list']),
        "long_": ConstFunctionIntr(),
        "map": ReadOnceFunctionIntr(),
        "max": ReadOnceFunctionIntr(return_range=prange.max_values),
        "min": ReadOnceFunctionIntr(return_range=prange.min_values),
        "next": FunctionIntr(),  # not const
        "oct": ConstFunctionIntr(),
        "ord": ConstFunctionIntr(return_range=prange.ord_values),
        "open": ConstFunctionIntr(global_effects=True),
        "pow": ConstFunctionIntr(),
        "range": ConstFunctionIntr(return_range_content=prange.range_values),
        "reduce": ReadOnceFunctionIntr(),
        "reversed": ReadOnceFunctionIntr(),
        "round": ConstFunctionIntr(),
        "set": ClassWithReadOnceConstructor(CLASSES['set']),
        "sorted": ConstFunctionIntr(),
        "str": ClassWithConstConstructor(CLASSES['str']),
        "sum": ReadOnceFunctionIntr(),
        "tuple": ReadOnceFunctionIntr(),
        "xrange": ConstFunctionIntr(return_range_content=prange.range_values),
        "zip": ReadOnceFunctionIntr(),
        "False": ConstantIntr(return_range=lambda args: prange.Range(0, 0)),
        "None": ConstantIntr(),
        "True": ConstantIntr(return_range=lambda args: prange.Range(1, 1)),
        },
    "numpy": {
        "abs": ConstFunctionIntr(),
        "absolute": ConstFunctionIntr(),
        "add": ConstFunctionIntr(),
        "alen": ConstFunctionIntr(return_range=prange.positive_values),
        "all": ConstMethodIntr(return_range=prange.bool_values),
        "allclose": ConstFunctionIntr(return_range=prange.bool_values),
        "alltrue": ConstFunctionIntr(return_range=prange.bool_values),
        "amax": ConstFunctionIntr(),
        "amin": ConstFunctionIntr(),
        "angle": ConstFunctionIntr(),
        "any": ConstMethodIntr(return_range=prange.bool_values),
        "append": ConstFunctionIntr(),
        "arange": ConstFunctionIntr(return_range_content=prange.range_values,
                                    args=('start', 'stop', 'step', 'dtype'),
                                    defaults=(1, None)),
        "arccos": ConstFunctionIntr(),
        "arccosh": ConstFunctionIntr(),
        "arcsin": ConstFunctionIntr(),
        "arcsinh": ConstFunctionIntr(),
        "arctan": ConstFunctionIntr(),
        "arctan2": ConstFunctionIntr(),
        "arctanh": ConstFunctionIntr(),
        "argmax": ConstMethodIntr(),
        "argmin": ConstMethodIntr(),
        "argsort": ConstFunctionIntr(),
        "argwhere": ConstFunctionIntr(),
        "around": ConstFunctionIntr(),
        "array": ConstFunctionIntr(),
        "array2string": ConstFunctionIntr(),
        "array_equal": ConstFunctionIntr(return_range=prange.bool_values),
        "array_equiv": ConstFunctionIntr(return_range=prange.bool_values),
        "array_split": ConstFunctionIntr(),
        "array_str": ConstFunctionIntr(),
        "asarray": ConstFunctionIntr(),
        "asarray_chkfinite": ConstFunctionIntr(
            return_range=prange.bool_values),
        "ascontiguousarray": ConstFunctionIntr(),
        "asfarray": ConstFunctionIntr(),
        "asscalar": ConstFunctionIntr(),
        "atleast_1d": ConstFunctionIntr(),
        "atleast_2d": ConstFunctionIntr(),
        "atleast_3d": ConstFunctionIntr(),
        "average": ConstFunctionIntr(),
        "base_repr": ConstFunctionIntr(),
        "binary_repr": ConstFunctionIntr(),
        "bincount": ConstFunctionIntr(),
        "bitwise_and": ConstFunctionIntr(),
        "bitwise_not": ConstFunctionIntr(),
        "bitwise_or": ConstFunctionIntr(),
        "bitwise_xor": ConstFunctionIntr(),
        "ceil": ConstFunctionIntr(),
        "clip": ConstMethodIntr(),
        "concatenate": ConstFunctionIntr(),
        "complex": ConstFunctionIntr(),
        "complex64": ConstFunctionIntr(),
        "complex128": ConstFunctionIntr(),
        "conj": ConstMethodIntr(),
        "conjugate": ConstMethodIntr(),
        "copy": ConstMethodIntr(),
        "copyto": FunctionIntr(argument_effects=[UpdateEffect(), ReadEffect(),
                                                 ReadEffect(), ReadEffect()]),
        "copysign": ConstFunctionIntr(),
        "count_nonzero": ConstFunctionIntr(),
        "cos": ConstFunctionIntr(),
        "cosh": ConstFunctionIntr(),
        "cumprod": ConstMethodIntr(),
        "cumproduct": ConstFunctionIntr(),
        "cumsum": ConstMethodIntr(),
        "deg2rad": ConstFunctionIntr(),
        "degrees": ConstFunctionIntr(),
        "delete_": ConstFunctionIntr(),
        "diag": ConstFunctionIntr(),
        "diagflat": ConstFunctionIntr(),
        "diagonal": ConstMethodIntr(),
        "diff": ConstFunctionIntr(),
        "digitize": ConstFunctionIntr(),
        "divide": ConstFunctionIntr(),
        "dot": ConstMethodIntr(),
        "double_": ConstFunctionIntr(),
        "e": ConstantIntr(),
        "ediff1d": ConstFunctionIntr(),
        "empty": ConstFunctionIntr(args=('shape', 'dtype'),
                                   defaults=("numpy.float64",)),
        "empty_like": ConstFunctionIntr(args=('a', 'dtype'),
                                        defaults=("numpy.float64",)),
        "equal": ConstFunctionIntr(),
        "exp": ConstFunctionIntr(),
        "expm1": ConstFunctionIntr(),
        "eye": ConstFunctionIntr(),
        "fabs": ConstFunctionIntr(),
        "finfo": ClassWithConstConstructor(CLASSES['finfo']),
        "fix": ConstFunctionIntr(),
        "flatnonzero": ConstFunctionIntr(),
        "fliplr": ConstFunctionIntr(),
        "flipud": ConstFunctionIntr(),
        "float32": ConstFunctionIntr(),
        "float64": ConstFunctionIntr(),
        "float_": ConstFunctionIntr(),
        "floor": ConstFunctionIntr(),
        "floor_divide": ConstFunctionIntr(),
        "fmax": ConstFunctionIntr(),
        "fmin": ConstFunctionIntr(),
        "fmod": ConstFunctionIntr(),
        "frexp": ConstFunctionIntr(),
        "fromfunction": ConstFunctionIntr(),
        "fromiter": ConstFunctionIntr(),
        "fromstring": ConstFunctionIntr(),
        "greater": ConstFunctionIntr(),
        "greater_equal": ConstFunctionIntr(),
        "hstack": ConstFunctionIntr(),
        "hypot": ConstFunctionIntr(),
        "identity": ConstFunctionIntr(),
        "imag": FunctionIntr(),
        "indices": ConstFunctionIntr(),
        "inf": ConstantIntr(),
        "inner": ConstFunctionIntr(),
        "insert": ConstFunctionIntr(),
        "intersect1d": ConstFunctionIntr(),
        "int16": ConstFunctionIntr(),
        "int32": ConstFunctionIntr(),
        "int64": ConstFunctionIntr(),
        "int8": ConstFunctionIntr(),
        "invert": ConstFunctionIntr(),
        "isclose": ConstFunctionIntr(),
        "iscomplex": ConstFunctionIntr(),
        "isfinite": ConstFunctionIntr(),
        "isinf": ConstFunctionIntr(),
        "isnan": ConstFunctionIntr(),
        "isneginf": ConstFunctionIntr(),
        "isposinf": ConstFunctionIntr(),
        "isreal": ConstFunctionIntr(),
        "isrealobj": ConstFunctionIntr(),
        "isscalar": ConstFunctionIntr(),
        "issctype": ConstFunctionIntr(),
        "ldexp": ConstFunctionIntr(),
        "left_shift": ConstFunctionIntr(),
        "less": ConstFunctionIntr(),
        "less_equal": ConstFunctionIntr(),
        "lexsort": ConstFunctionIntr(),
        "linalg": {
            "norm": FunctionIntr(args=('x', 'ord', 'axis'),
                                 defaults=(None, None)),
        },
        "linspace": ConstFunctionIntr(),
        "log": ConstFunctionIntr(),
        "log10": ConstFunctionIntr(),
        "log1p": ConstFunctionIntr(),
        "log2": ConstFunctionIntr(),
        "logaddexp": ConstFunctionIntr(),
        "logaddexp2": ConstFunctionIntr(),
        "logspace": ConstFunctionIntr(),
        "logical_and": ConstFunctionIntr(),
        "logical_not": ConstFunctionIntr(),
        "logical_or": ConstFunctionIntr(),
        "logical_xor": ConstFunctionIntr(),
        "max": ConstMethodIntr(),
        "maximum": ConstFunctionIntr(),
        "mean": ConstMethodIntr(),
        "median": ConstFunctionIntr(),
        "min": ConstMethodIntr(),
        "minimum": ConstFunctionIntr(),
        "mod": ConstFunctionIntr(),
        "multiply": ConstFunctionIntr(),
        "nan": ConstantIntr(),
        "nan_to_num": ConstFunctionIntr(),
        "nanargmax": ConstFunctionIntr(),
        "nanargmin": ConstFunctionIntr(),
        "nanmax": ConstFunctionIntr(),
        "nanmin": ConstFunctionIntr(),
        "nansum": ConstFunctionIntr(),
        "ndenumerate": ConstFunctionIntr(),
        "ndarray": ClassWithConstConstructor(CLASSES["ndarray"]),
        "ndindex": ConstFunctionIntr(),
        "ndim": ConstFunctionIntr(return_range=prange.positive_values),
        "negative": ConstFunctionIntr(),
        "newaxis": ConstantIntr(),
        "nextafter": ConstFunctionIntr(),
        "NINF": ConstantIntr(),
        "nonzero": ConstMethodIntr(),
        "not_equal": ConstFunctionIntr(),
        "ones": ConstFunctionIntr(),
        "ones_like": ConstFunctionIntr(),
        "outer": ConstFunctionIntr(),
        "pi": ConstantIntr(),
        "place": FunctionIntr(),
        "power": ConstFunctionIntr(),
        "prod": ConstMethodIntr(),
        "product": ConstFunctionIntr(),
        "ptp": ConstMethodIntr(),
        "put": MethodIntr(),
        "putmask": FunctionIntr(),
        "rad2deg": ConstFunctionIntr(),
        "radians": ConstFunctionIntr(),
        "random": {
            "binomial": FunctionIntr(args=('n', 'p', 'size'),
                                     global_effects=True),
            "bytes": FunctionIntr(args=('length',),
                                  global_effects=True),
            "choice": FunctionIntr(args=('a', 'size', 'replace', 'p'),
                                   global_effects=True),
            "normal": FunctionIntr(args=('loc', 'scale', 'size',),
                                   defaults=(0.0, 1.0, None,),
                                   global_effects=True),
            "rand": FunctionIntr(args=(),
                                 global_effects=True),
            "ranf": FunctionIntr(args=('size',),
                                 global_effects=True),
            "randint": FunctionIntr(args=("low", "high", "size"),
                                    global_effects=True),
            "randn": FunctionIntr(args=(),
                                  global_effects=True),
            "random": FunctionIntr(args=('size',),
                                   global_effects=True),
            "random_integers": FunctionIntr(args=("low", "high", "size"),
                                            global_effects=True),
            "random_sample": FunctionIntr(args=('size',),
                                          global_effects=True),
            "sample": FunctionIntr(args=('size',),
                                   global_effects=True),
            "standard_normal": FunctionIntr(args=('size',),
                                            global_effects=True),
        },
        "rank": ConstFunctionIntr(),
        "ravel": ConstMethodIntr(),
        "real": FunctionIntr(),
        "reciprocal": ConstFunctionIntr(),
        "remainder": ConstFunctionIntr(),
        "repeat": ConstMethodIntr(),
        "reshape": ConstMethodIntr(),
        "resize": ConstMethodIntr(),
        "right_shift": ConstFunctionIntr(),
        "rint": ConstFunctionIntr(),
        "roll": ConstFunctionIntr(),
        "rollaxis": ConstFunctionIntr(),
        "rot90": ConstFunctionIntr(),
        "round": ConstMethodIntr(),
        "round_": ConstMethodIntr(),
        "searchsorted": ConstFunctionIntr(),
        "select": ConstFunctionIntr(),
        "shape": ConstFunctionIntr(),
        "sign": ConstFunctionIntr(),
        "signbit": ConstFunctionIntr(),
        "sin": ConstFunctionIntr(),
        "sinh": ConstFunctionIntr(),
        "size": ConstFunctionIntr(return_range=prange.positive_values),
        "sometrue": ConstFunctionIntr(),
        "sort": ConstFunctionIntr(),
        "sort_complex": ConstFunctionIntr(),
        "spacing": ConstFunctionIntr(),
        "split": ConstFunctionIntr(),
        "sqrt": ConstFunctionIntr(),
        "square": ConstFunctionIntr(),
        "std_": ConstMethodIntr(args=('a', 'axis', 'dtype'),
                                defaults=(None, None)),
        "subtract": ConstFunctionIntr(),
        "sum": ConstMethodIntr(),
        "swapaxes": ConstMethodIntr(),
        "take": ConstMethodIntr(),
        "tan": ConstFunctionIntr(),
        "tanh": ConstFunctionIntr(),
        "tile": ConstFunctionIntr(),
        "trace": ConstMethodIntr(),
        "transpose": ConstMethodIntr(),
        "tri": ConstMethodIntr(),
        "tril": ConstMethodIntr(),
        "trim_zeros": ConstMethodIntr(),
        "triu": ConstMethodIntr(),
        "true_divide": ConstFunctionIntr(),
        "trunc": ConstFunctionIntr(),
        "uint16": ConstFunctionIntr(),
        "uint32": ConstFunctionIntr(),
        "uint64": ConstFunctionIntr(),
        "uint8": ConstFunctionIntr(),
        "union1d": ConstFunctionIntr(),
        "unique": ConstFunctionIntr(),
        "unwrap": ConstFunctionIntr(),
        "var": ConstMethodIntr(),
        "vstack": ConstFunctionIntr(),
        "where": ConstFunctionIntr(),
        "zeros": ConstFunctionIntr(args=('shape', 'dtype'),
                                   defaults=("numpy.float64",)),
        "zeros_like": ConstFunctionIntr(),
        },
    "time": {
        "sleep": FunctionIntr(global_effects=True),
        "time": FunctionIntr(global_effects=True),
        },
    "math": {
        "isinf": ConstFunctionIntr(),
        "modf": ConstFunctionIntr(),
        "frexp": ConstFunctionIntr(),
        "factorial": ConstFunctionIntr(),
        "gamma": ConstFunctionIntr(),
        "lgamma": ConstFunctionIntr(),
        "trunc": ConstFunctionIntr(),
        "erf": ConstFunctionIntr(),
        "erfc": ConstFunctionIntr(),
        "asinh": ConstFunctionIntr(),
        "atanh": ConstFunctionIntr(),
        "acosh": ConstFunctionIntr(),
        "radians": ConstFunctionIntr(),
        "degrees": ConstFunctionIntr(),
        "hypot": ConstFunctionIntr(),
        "tanh": ConstFunctionIntr(),
        "cosh": ConstFunctionIntr(),
        "sinh": ConstFunctionIntr(),
        "atan": ConstFunctionIntr(),
        "atan2": ConstFunctionIntr(),
        "asin": ConstFunctionIntr(),
        "tan": ConstFunctionIntr(),
        "log": ConstFunctionIntr(),
        "log1p": ConstFunctionIntr(),
        "expm1": ConstFunctionIntr(),
        "ldexp": ConstFunctionIntr(),
        "fmod": ConstFunctionIntr(),
        "fabs": ConstFunctionIntr(),
        "copysign": ConstFunctionIntr(),
        "acos": ConstFunctionIntr(),
        "cos": ConstFunctionIntr(),
        "sin": ConstFunctionIntr(),
        "exp": ConstFunctionIntr(),
        "sqrt": ConstFunctionIntr(),
        "log10": ConstFunctionIntr(),
        "isnan": ConstFunctionIntr(),
        "ceil": ConstFunctionIntr(),
        "floor": ConstFunctionIntr(),
        "pow": ConstFunctionIntr(),
        "pi": ConstantIntr(),
        "e": ConstantIntr(),
        },
    "functools": {
        "partial": FunctionIntr(),
        },
    "bisect": {
        "bisect_left": ConstFunctionIntr(return_range=prange.positive_values),
        "bisect_right": ConstFunctionIntr(return_range=prange.positive_values),
        "bisect": ConstFunctionIntr(return_range=prange.positive_values),
        },
    "cmath": {
        "cos": FunctionIntr(),
        "sin": FunctionIntr(),
        "exp": FunctionIntr(),
        "sqrt": FunctionIntr(),
        "log10": FunctionIntr(),
        "isnan": FunctionIntr(),
        "pi": ConstantIntr(),
        "e": ConstantIntr(),
        },
    "itertools": {
        "count": ReadOnceFunctionIntr(),
        "imap": ReadOnceFunctionIntr(),
        "ifilter": ReadOnceFunctionIntr(),
        "islice": ReadOnceFunctionIntr(),
        "product": ConstFunctionIntr(),
        "izip": ReadOnceFunctionIntr(),
        "combinations": ConstFunctionIntr(),
        "permutations": ConstFunctionIntr(),
        },
    "random": {
        "seed": FunctionIntr(global_effects=True),
        "random": FunctionIntr(global_effects=True),
        "randint": FunctionIntr(global_effects=True),
        "randrange": FunctionIntr(global_effects=True),
        "gauss": FunctionIntr(global_effects=True),
        "uniform": FunctionIntr(global_effects=True),
        "expovariate": FunctionIntr(global_effects=True),
        "sample": FunctionIntr(global_effects=True),
        "choice": FunctionIntr(global_effects=True),
        "shuffle": FunctionIntr(global_effects=True),
        },
    "omp": {
        "set_num_threads": FunctionIntr(global_effects=True),
        "get_num_threads": FunctionIntr(global_effects=True),
        "get_max_threads": FunctionIntr(global_effects=True),
        "get_thread_num": FunctionIntr(global_effects=True),
        "get_num_procs": FunctionIntr(global_effects=True),
        "in_parallel": FunctionIntr(global_effects=True),
        "set_dynamic": FunctionIntr(global_effects=True),
        "get_dynamic": FunctionIntr(global_effects=True),
        "set_nested": FunctionIntr(global_effects=True),
        "get_nested": FunctionIntr(global_effects=True),
        "init_lock": FunctionIntr(global_effects=True),
        "destroy_lock": FunctionIntr(global_effects=True),
        "set_lock": FunctionIntr(global_effects=True),
        "unset_lock": FunctionIntr(global_effects=True),
        "test_lock": FunctionIntr(global_effects=True),
        "init_nest_lock": FunctionIntr(global_effects=True),
        "destroy_nest_lock": FunctionIntr(global_effects=True),
        "set_nest_lock": FunctionIntr(global_effects=True),
        "unset_nest_lock": FunctionIntr(global_effects=True),
        "test_nest_lock": FunctionIntr(global_effects=True),
        "get_wtime": FunctionIntr(global_effects=True),
        "get_wtick": FunctionIntr(global_effects=True),
        "set_schedule": FunctionIntr(global_effects=True),
        "get_schedule": FunctionIntr(global_effects=True),
        "get_thread_limit": FunctionIntr(global_effects=True),
        "set_max_active_levels": FunctionIntr(global_effects=True),
        "get_max_active_levels": FunctionIntr(global_effects=True),
        "get_level": FunctionIntr(global_effects=True),
        "get_ancestor_thread_num": FunctionIntr(global_effects=True),
        "get_team_size": FunctionIntr(global_effects=True),
        "get_active_level": FunctionIntr(global_effects=True),
        "in_final": FunctionIntr(global_effects=True),
        },
    "operator_": {
        "lt": ConstFunctionIntr(),
        "le": ConstFunctionIntr(),
        "eq": ConstFunctionIntr(),
        "ne": ConstFunctionIntr(),
        "ge": ConstFunctionIntr(),
        "gt": ConstFunctionIntr(),
        "__lt__": ConstFunctionIntr(),
        "__le__": ConstFunctionIntr(),
        "__eq__": ConstFunctionIntr(),
        "__ne__": ConstFunctionIntr(),
        "__ge__": ConstFunctionIntr(),
        "__gt__": ConstFunctionIntr(),
        "not_": ConstFunctionIntr(),
        "__not__": ConstFunctionIntr(),
        "truth": ConstFunctionIntr(),
        "is_": ConstFunctionIntr(),
        "is_not": ConstFunctionIntr(),
        "abs": ConstFunctionIntr(),
        "__abs__": ConstFunctionIntr(),
        "add": ConstFunctionIntr(),
        "__add__": ConstFunctionIntr(),
        "and_": ConstFunctionIntr(),
        "__and__": ConstFunctionIntr(),
        "div": ConstFunctionIntr(),
        "__div__": ConstFunctionIntr(),
        "floordiv": ConstFunctionIntr(),
        "__floordiv__": ConstFunctionIntr(),
        "inv": ConstFunctionIntr(),
        "invert": ConstFunctionIntr(),
        "__inv__": ConstFunctionIntr(),
        "__invert__": ConstFunctionIntr(),
        "lshift": ConstFunctionIntr(),
        "__lshift__": ConstFunctionIntr(),
        "mod": ConstFunctionIntr(),
        "__mod__": ConstFunctionIntr(),
        "mul": ConstFunctionIntr(),
        "__mul__": ConstFunctionIntr(),
        "neg": ConstFunctionIntr(),
        "__neg__": ConstFunctionIntr(),
        "or_": ConstFunctionIntr(),
        "__or__": ConstFunctionIntr(),
        "pos": ConstFunctionIntr(),
        "__pos__": ConstFunctionIntr(),
        "rshift": ConstFunctionIntr(),
        "__rshift__": ConstFunctionIntr(),
        "sub": ConstFunctionIntr(),
        "__sub__": ConstFunctionIntr(),
        "truediv": ConstFunctionIntr(),
        "__truediv__": ConstFunctionIntr(),
        "xor_": ConstFunctionIntr(),
        "__xor__": ConstFunctionIntr(),
        "concat": ConstFunctionIntr(),
        "__concat__": ConstFunctionIntr(),
        "iadd": MethodIntr(update_effects),
        "__iadd__": MethodIntr(update_effects),
        "iand": MethodIntr(update_effects),
        "__iand__": MethodIntr(update_effects),
        "iconcat": MethodIntr(update_effects),
        "__iconcat__": MethodIntr(update_effects),
        "idiv": MethodIntr(update_effects),
        "__idiv__": MethodIntr(update_effects),
        "ifloordiv": MethodIntr(update_effects),
        "__ifloordiv__": MethodIntr(update_effects),
        "ilshift": MethodIntr(update_effects),
        "__ilshift__": MethodIntr(update_effects),
        "imod": MethodIntr(update_effects),
        "__imod__": MethodIntr(update_effects),
        "imul": MethodIntr(update_effects),
        "__imul__": MethodIntr(update_effects),
        "ior": MethodIntr(update_effects),
        "__ior__": MethodIntr(update_effects),
        "ipow": MethodIntr(update_effects),
        "__ipow__": MethodIntr(update_effects),
        "irshift": MethodIntr(update_effects),
        "__irshift__": MethodIntr(update_effects),
        "isub": MethodIntr(update_effects),
        "__isub__": MethodIntr(update_effects),
        "itruediv": MethodIntr(update_effects),
        "__itruediv__": MethodIntr(update_effects),
        "ixor": MethodIntr(update_effects),
        "__ixor__": MethodIntr(update_effects),
        "contains": MethodIntr(update_effects),
        "__contains__": ConstFunctionIntr(),
        "countOf": ConstFunctionIntr(),
        "delitem": FunctionIntr(
            argument_effects=[UpdateEffect(), ReadEffect()]),
        "__delitem__": FunctionIntr(
            argument_effects=[UpdateEffect(), ReadEffect()]),
        "getitem": ConstFunctionIntr(),
        "__getitem__": ConstFunctionIntr(),
        "indexOf": ConstFunctionIntr(),
        "__theitemgetter__": ConstFunctionIntr(),
        "itemgetter": MethodIntr(
            return_alias=lambda _: {
                MODULES['operator_']['__theitemgetter__']}
            ),

    },
    "string": {
        "ascii_lowercase": ConstantIntr(),
        "ascii_uppercase": ConstantIntr(),
        "ascii_letters": ConstantIntr(),
        "digits": ConstantIntr(),
        "find": ConstFunctionIntr(),
        "hexdigits": ConstantIntr(),
        "octdigits": ConstantIntr(),
        },
    "os": {
        "path": {
            "join": ConstFunctionIntr(),
            }
        },
    # conflicting method names must be listed here
    "__dispatch__": {
        "clear": MethodIntr(),
        "conjugate": ConstMethodIntr(),
        "copy": ConstMethodIntr(),
        "count": ConstMethodIntr(return_range=prange.positive_values),
        "next": MethodIntr(global_effects=True),  # because of file.next
        "pop": MethodIntr(),
        "remove": MethodIntr(),
        "update": MethodIntr(update_effects),
        },
    }

if sys.version_info[0] > 2:
    sys.modules['__builtin__'] = sys.modules['builtins']

# VMSError is only available on VMS
if 'VMSError' in sys.modules['__builtin__'].__dict__:
    MODULES['__builtin__']['VMSError'] = ConstExceptionIntr()

# WindowsError is only available on Windows
if 'WindowsError' in sys.modules['__builtin__'].__dict__:
    MODULES['__builtin__']['WindowsError'] = ConstExceptionIntr()

# detect and prune unsupported modules
try:
    __import__("omp")
except ImportError:
    logger.warn("Pythran support disabled for module: omp")
    del MODULES["omp"]

# check and delete unimplemented numpy methods
for method in MODULES['numpy'].keys():
    if (method not in sys.modules['numpy'].__dict__ and not
            (method[-1:] == '_' and method[:-1] in cxx_keywords and
                method[:-1] in sys.modules['numpy'].__dict__)):
        del MODULES['numpy'][method]


# populate argument description through introspection
def save_arguments(module_name, elements):
    """ Recursively save arguments name and default value. """
    for elem, signature in elements.items():
        if isinstance(signature, dict):  # Submodule case
            save_arguments(module_name + (elem,), signature)
        else:
            # use introspection to get the Python obj
            try:
                themodule = __import__(".".join(module_name))
                obj = getattr(themodule, elem)
                spec = inspect.getargspec(obj)
                assert not signature.args.args
                signature.args.args = [ast.Name(arg, ast.Param())
                                       for arg in spec.args]
                if spec.defaults:
                    signature.args.defaults = map(to_ast, spec.defaults)
            except (AttributeError, ImportError, TypeError, ToNotEval):
                pass

save_arguments((), MODULES)


# Fill return_type field for constants
def fill_constants_types(module_name, elements):
    """ Recursively save arguments name and default value. """
    for elem, intrinsic in elements.items():
        if isinstance(intrinsic, dict):  # Submodule case
            fill_constants_types(module_name + (elem,), intrinsic)
        elif isinstance(intrinsic, ConstantIntr):
            # use introspection to get the Python constants types
            cst = getattr(__import__(".".join(module_name)), elem)
            intrinsic.return_type = NamedType(PYTYPE_TO_CTYPE_TABLE[type(cst)])

fill_constants_types((), MODULES)
# a method name to module binding
# {method_name : ((full module path), signature)}
methods = {}


def save_method(elements, module_path):
    """ Recursively save methods with module name and signature. """
    for elem, signature in elements.items():
        if isinstance(signature, dict):  # Submodule case
            save_method(signature, module_path + (elem,))
        elif isinstance(signature, Class):
            save_method(signature.fields, module_path + (elem,))
        elif signature.ismethod():
            # in case of duplicates, there must be a __dispatch__ record
            # and it is the only recorded one
            if elem in methods and module_path[0] != '__dispatch__':
                assert elem in MODULES['__dispatch__']
                path = ('__dispatch__',)
                methods[elem] = (path, MODULES['__dispatch__'][elem])
            else:
                methods[elem] = (module_path, signature)

save_method(MODULES, ())

# a function name to module binding
# {function_name : [((full module path), signature)]}
functions = {}


def save_function(elements, module_path):
    """ Recursively save functions with module name and signature. """
    for elem, signature in elements.items():
        if isinstance(signature, dict):  # Submodule case
            save_function(signature, module_path + (elem,))
        elif signature.isstaticfunction():
            functions.setdefault(elem, []).append((module_path, signature,))
        elif isinstance(signature, Class):
            save_function(signature.fields, module_path + (elem,))

save_function(MODULES, ())

# a attribute name to module binding
# {attribute_name : ((full module path), signature)}
attributes = {}


def save_attribute(elements, module_path):
    """ Recursively save attributes with module name and signature. """
    for elem, signature in elements.items():
        if isinstance(signature, dict):  # Submodule case
            save_attribute(signature, module_path + (elem,))
        elif signature.isattribute():
            assert elem not in attributes  # we need unicity
            attributes[elem] = (module_path, signature,)
        elif isinstance(signature, Class):
            save_attribute(signature.fields, module_path + (elem,))

save_attribute(MODULES, ())
