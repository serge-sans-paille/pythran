""" This modules provides the translation tables from python to c++. """

import gast as ast
import inspect
import logging
import sys

from pythran.typing import Dict, Set, List, TypeVar, Union, Optional, NDArray
from pythran.typing import Generator, Fun, Tuple, Iterable, Sized, File

from pythran.conversion import to_ast, ToNotEval
from pythran.intrinsic import Class
from pythran.intrinsic import ClassWithConstConstructor, ExceptionClass
from pythran.intrinsic import ClassWithReadOnceConstructor
from pythran.intrinsic import ConstFunctionIntr, FunctionIntr, UpdateEffect
from pythran.intrinsic import ConstMethodIntr, MethodIntr, AttributeIntr
from pythran.intrinsic import ReadEffect, ConstantIntr, UFunc
from pythran.intrinsic import ReadOnceFunctionIntr, ConstExceptionIntr
from pythran import interval
from functools import reduce

if sys.version_info.major == 3:
    sys.modules['__builtin__'] = sys.modules['builtins']
    sys.modules['__builtin__'].xrange = sys.modules['builtins'].range

    class long(int):
        pass
    sys.modules['__builtin__'].long = long
    import functools
    sys.modules['__builtin__'].reduce = functools.reduce
    getargspec = inspect.getfullargspec
else:
    getargspec = inspect.getargspec

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


def make_lazy(exp):
    return '[&] () {{ return {0}; }}'.format(exp)


def make_and(x, y):
    lx, ly = make_lazy(x), make_lazy(y)
    return 'pythonic::__builtin__::pythran::and_({0}, {1})'.format(lx, ly)


def make_or(x, y):
    lx, ly = make_lazy(x), make_lazy(y)
    return 'pythonic::__builtin__::pythran::or_({0}, {1})'.format(lx, ly)

operator_to_lambda = {
    # boolop
    ast.And: make_and,
    ast.Or: make_or,
    # operator
    ast.Add: "({0} + {1})".format,
    ast.Sub: "({0} - {1})".format,
    ast.Mult: "({0} * {1})".format,
    ast.Div: "(pythonic::operator_::div({0}, {1}))".format,
    ast.Mod: "(pythonic::operator_::mod({0}, {1}))".format,
    ast.Pow: "(pythonic::__builtin__::pow({0}, {1}))".format,
    ast.LShift: "({0} << {1})".format,
    ast.RShift: "({0} >> {1})".format,
    ast.BitOr: "({0} | {1})".format,
    ast.BitXor: "({0} ^ {1})".format,
    ast.BitAnd: "({0} & {1})".format,
    ast.MatMult: "pythonic::operator_::matmul({0}, {1})".format,
    # assume from __future__ import division
    ast.FloorDiv:
        "(pythonic::operator_::functor::floordiv{{}}({0}, {1}))".format,
    # unaryop
    ast.Invert: "(~{0})".format,
    ast.Not: "(! {0})".format,
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
    ast.NotIn: "(! pythonic::in({1}, {0}))".format,
}

T0, T1, T2, T3 = TypeVar('T0'), TypeVar('T1'), TypeVar('T2'), TypeVar('T3')
T4, T5, T6, T7 = TypeVar('T4'), TypeVar('T5'), TypeVar('T6'), TypeVar('T7')


_bool_signature = Union[
    Fun[[], bool],
    Fun[[T0], bool]
]

_int_signature = Union[
    Fun[[], int],
    Fun[[bool], int],
    Fun[[int], int],
    Fun[[float], int],
    Fun[[str], int],
]

_float_signature = Union[
    Fun[[], float],
    Fun[[str], float],
    Fun[[float], float],
]

_complex_signature = Union[
    Fun[[float], complex],
    Fun[[float, float], complex],
]


def update_effects(self, node):
    """
    Combiner when we update the first argument of a function.

    It turn type of first parameter in combination of all others
    parameters types.
    """
    return [self.combine(node.args[0], node_args_k, register=True,
                         aliasing_type=True)
            for node_args_k in node.args[1:]]

BINARY_UFUNC = {"accumulate": FunctionIntr()}

CLASSES = {
    "list": {
        "append": MethodIntr(signature=Fun[[List[T0], T0], None]),
        "extend": MethodIntr(update_effects),
        "index": ConstMethodIntr(
            signature=Union[
                Fun[[List[T0], T0], int],
                Fun[[List[T0], T0, int], int],
                Fun[[List[T0], T0, int, int], int],
            ]
        ),
        "pop": MethodIntr(
            signature=Union[
                Fun[[List[T0]], T0],
                Fun[[List[T0], int], T0],
            ],
        ),
        "reverse": MethodIntr(signature=Fun[[List[T0]], None]),
        "sort": MethodIntr(
            signature=Union[
                Fun[[List[T0]], None],
                Fun[[List[T0], Fun[[T0, T0], int]], None],
            ],
        ),
        "count": ConstMethodIntr(signature=Fun[[List[T0], T0], int]),
        "remove": MethodIntr(signature=Fun[[List[T0], T0], None]),
        "insert": MethodIntr(signature=Fun[[List[T0], int, T0], None]),
    },
    "str": {
        "__mod__": ConstMethodIntr(
            signature=Union[
                Fun[[str, T0], str],
                Fun[[str, T0, T1], str],
                Fun[[str, T0, T1, T2], str],
                Fun[[str, T0, T1, T2, T3, T4], str],
                Fun[[str, T0, T1, T2, T3, T4, T5], str],
                Fun[[str, T0, T1, T2, T3, T4, T5, T6], str],
            ],
        ),

        "capitalize": ConstMethodIntr(signature=Fun[[str], str]),
        "count": ConstMethodIntr(signature=Union[
            Fun[[str, str], int],
            Fun[[str, str, int], int],
            Fun[[str, str, int, int], int],
        ]),
        "endswith": ConstMethodIntr(
            signature=Union[
                Fun[[str, str], bool],
                Fun[[str, str, Optional[int]], bool],
                Fun[[str, str, Optional[int], Optional[int]], bool],
            ],
        ),
        "startswith": ConstMethodIntr(
            signature=Union[
                Fun[[str, str], bool],
                Fun[[str, str, Optional[int]], bool],
                Fun[[str, str, Optional[int], Optional[int]], bool],
            ],
        ),
        "find": ConstMethodIntr(
            signature=Union[
                Fun[[str, str], int],
                Fun[[str, str, Optional[int]], int],
                Fun[[str, str, Optional[int], Optional[int]], int],
            ],
        ),
        "isalpha": ConstMethodIntr(signature=Fun[[str], bool]),
        "isdigit": ConstMethodIntr(signature=Fun[[str], bool]),
        "join": ConstMethodIntr(signature=Fun[[str, Iterable[str]], str]),
        "lower": ConstMethodIntr(signature=Fun[[str], str]),
        "replace": ConstMethodIntr(
            signature=Union[
                Fun[[str, str, str], str],
                Fun[[str, str, str, int], str],
            ]
        ),
        "split": ConstMethodIntr(
            signature=Union[
                Fun[[str], List[str]],
                Fun[[str, str], List[str]],
                Fun[[str, None], List[str]],
                Fun[[str, str, int], List[str]],
                Fun[[str, None, int], List[str]],
            ]
        ),
        "strip": ConstMethodIntr(
            signature=Union[
                Fun[[str], str],
                Fun[[str, str], str],
            ]
        ),
        "lstrip": ConstMethodIntr(
            signature=Union[
                Fun[[str], str],
                Fun[[str, str], str],
            ]
        ),
        "rstrip": ConstMethodIntr(
            signature=Union[
                Fun[[str], str],
                Fun[[str, str], str],
            ]
        ),
        "upper": ConstMethodIntr(
            signature=Fun[[str], str]
        ),
    },
    "set": {
        "add": MethodIntr(signature=Fun[[Set[T0], T0], None]),
        "clear": MethodIntr(signature=Fun[[Set[T0]], None]),
        "copy": ConstMethodIntr(signature=Fun[[Set[T0]], Iterable[T0]]),
        "discard": MethodIntr(signature=Fun[[Set[T0], T0], None]),
        "remove": MethodIntr(signature=Fun[[Set[T0], T0], None]),
        "isdisjoint": ConstMethodIntr(
            signature=Fun[[Set[T0], Set[T0]], bool]),
        "union_": ConstMethodIntr(
            signature=Union[
                Fun[[Set[T0], Iterable[T0]], Set[T0]],
                Fun[[Set[T0], Iterable[T0], Iterable[T0]], Set[T0]],
                Fun[[Set[T0], Iterable[T0], Iterable[T0], Iterable[T0]],
                    Set[T0]],
            ]
        ),
        "update": MethodIntr(update_effects),
        "intersection": ConstMethodIntr(
            signature=Union[
                Fun[[Set[T0], Iterable[T0]], Set[T0]],
                Fun[[Set[T0], Iterable[T0], Iterable[T0]], Set[T0]],
                Fun[[Set[T0], Iterable[T0], Iterable[T0], Iterable[T0]],
                    Set[T0]],
            ]
        ),
        "intersection_update": MethodIntr(update_effects),
        "difference": ConstMethodIntr(
            signature=Union[
                Fun[[Set[T0], Iterable[T0]], Set[T0]],
                Fun[[Set[T0], Iterable[T0], Iterable[T0]], Set[T0]],
                Fun[[Set[T0], Iterable[T0], Iterable[T0], Iterable[T0]],
                    Set[T0]],
            ]
        ),
        "difference_update": MethodIntr(update_effects),
        "symmetric_difference": ConstMethodIntr(
            signature=Union[
                Fun[[Set[T0], Iterable[T0]], Set[T0]],
                Fun[[Set[T0], Iterable[T0], Iterable[T0]], Set[T0]],
                Fun[[Set[T0], Iterable[T0], Iterable[T0], Iterable[T0]],
                    Set[T0]],
            ]
        ),
        "symmetric_difference_update": MethodIntr(update_effects),
        "issuperset": ConstMethodIntr(
            signature=Fun[[Set[T0], Set[T0]], bool]),
        "issubset": ConstMethodIntr(
            signature=Fun[[Set[T0], Set[T0]], bool]),
    },
    "Exception": {
        "args": AttributeIntr(signature=Fun[[T0], str]),
        "errno": AttributeIntr(signature=Fun[[T0], str]),
        "strerror": AttributeIntr(signature=Fun[[T0], str]),
        "filename": AttributeIntr(signature=Fun[[T0], str]),
    },
    "float": {
        "is_integer": ConstMethodIntr(signature=Fun[[float], bool]),
    },
    "complex": {
        "conjugate": ConstMethodIntr(),
        "real": AttributeIntr(
            signature=Union[
                Fun[[complex], float],
                Fun[[NDArray[complex, :]], NDArray[float, :]],
                Fun[[NDArray[complex, :, :]], NDArray[float, :, :]],
                Fun[[NDArray[complex, :, :, :]], NDArray[float, :, :, :]],
                Fun[[NDArray[complex, :, :, :, :]],
                    NDArray[float, :, :, :, :]],
            ]
        ),
        "imag": AttributeIntr(
            signature=Union[
                Fun[[complex], float],
                Fun[[NDArray[complex, :]], NDArray[float, :]],
                Fun[[NDArray[complex, :, :]], NDArray[float, :, :]],
                Fun[[NDArray[complex, :, :, :]], NDArray[float, :, :, :]],
                Fun[[NDArray[complex, :, :, :, :]],
                    NDArray[float, :, :, :, :]],
            ]
        ),
    },
    "dict": {
        "fromkeys": ConstFunctionIntr(
            signature=Union[
                Fun[[Iterable[T0]], Dict[T0, Optional[T1]]],
                Fun[[Iterable[T0], T1], Dict[T0, T1]],
            ],
        ),
        "clear": MethodIntr(signature=Fun[[Dict[T0, T1]], None]),
        "copy": ConstMethodIntr(
            signature=Fun[[Dict[T0, T1]], Dict[T0, T1]]),
        "get": ConstMethodIntr(
            signature=Union[
                Fun[[Dict[T0, T1], T0], Optional[T1]],
                Fun[[Dict[T0, T1], T0, T1], T1],
            ],
        ),
        "has_key": ConstMethodIntr(
            signature=Fun[[Dict[T0, T1], T0], bool]
        ),
        "items": MethodIntr(
            signature=Fun[[Dict[T0, T1]], List[Tuple[T0, T1]]]),
        "iteritems": MethodIntr(
            signature=Fun[[Dict[T0, T1]], Generator[Tuple[T0, T1]]]),
        "iterkeys": MethodIntr(
            signature=Fun[[Dict[T0, T1]], Generator[T0]]),
        "itervalues": MethodIntr(
            signature=Fun[[Dict[T0, T1]], Generator[T1]]),
        "keys": MethodIntr(signature=Fun[[Dict[T0, T1]], List[T0]]),
        "pop": MethodIntr(
            signature=Union[
                Fun[[Dict[T0, T1], T0], T1],
                Fun[[Dict[T0, T1], T0, T1], T1],
            ]
        ),
        "popitem": MethodIntr(
            signature=Fun[[Dict[T0, T1]], Tuple[T0, T1]]),
        "setdefault": MethodIntr(
            signature=Union[
                Fun[[Dict[T0, T1], T0, T1], T1],
                Fun[[Dict[T0, T1], T0], T1]
            ],
            return_alias=lambda args: {
                ast.Subscript(args[0],
                              ast.Index(args[1]),
                              ast.Load())
            }.union({args[2]} if len(args) == 3 else set())
        ),
        "update": MethodIntr(update_effects),
        "values": MethodIntr(signature=Fun[[Dict[T0, T1]], List[T1]]),
        "viewitems": MethodIntr(
            signature=Fun[[Dict[T0, T1]], List[Tuple[T0, T1]]]),
        "viewkeys": MethodIntr(signature=Fun[[Dict[T0, T1]], List[T0]]),
        "viewvalues": MethodIntr(signature=Fun[[Dict[T0, T1]], List[T1]]),
    },
    "file": {
        # Member variables
        "closed": AttributeIntr(signature=Fun[[File], bool]),
        "mode": AttributeIntr(signature=Fun[[File], str]),
        "name": AttributeIntr(signature=Fun[[File], str]),
        "newlines": AttributeIntr(signature=Fun[[File], str]),
        # Member functions
        "close": MethodIntr(
            signature=Fun[[File], None],
            global_effects=True
        ),
        "flush": MethodIntr(
            signature=Fun[[File], None],
            global_effects=True
        ),
        "fileno": MethodIntr(
            signature=Fun[[File], int],
        ),
        "isatty": MethodIntr(signature=Fun[[File], bool]),
        "next": MethodIntr(global_effects=True),
        "read": MethodIntr(
            signature=Union[
                Fun[[File], str],
                Fun[[File, int], str],
            ],
            global_effects=True
        ),
        "readline": MethodIntr(
            signature=Union[
                Fun[[File], str],
                Fun[[File, int], str],
            ],
            global_effects=True
        ),
        "readlines": MethodIntr(
            signature=Union[
                Fun[[File], List[str]],
                Fun[[File, int], List[str]],
            ],
            global_effects=True
        ),
        "xreadlines": MethodIntr(
            signature=Fun[[File], File],
            global_effects=True
        ),
        "seek": MethodIntr(
            signature=Union[
                Fun[[File, int], None],
                Fun[[File, int, int], None],
            ],
            global_effects=True
        ),
        "tell": MethodIntr(signature=Fun[[File], int]),
        "truncate": MethodIntr(
            signature=Union[
                Fun[[File], None],
                Fun[[File, int], None],
            ],
            global_effects=True
        ),
        "write": MethodIntr(
            signature=Fun[[File, str], None],
            global_effects=True
        ),
        "writelines": MethodIntr(
            signature=Fun[[File, Iterable[str]], None],
            global_effects=True
        ),
    },
    "finfo": {
        "eps": AttributeIntr(signature=float),
    },
    "ndarray": {
        "astype": MethodIntr(
            signature=Union[
                # dtype = bool
                Fun[[NDArray[bool, :], _bool_signature], NDArray[bool, :]],
                Fun[[NDArray[int, :], _bool_signature], NDArray[bool, :]],
                Fun[[NDArray[float, :], _bool_signature], NDArray[bool, :]],
                Fun[[NDArray[complex, :], _bool_signature], NDArray[bool, :]],
                Fun[[NDArray[bool, :, :], _bool_signature],
                    NDArray[bool, :, :]],
                Fun[[NDArray[int, :, :], _bool_signature],
                    NDArray[bool, :, :]],
                Fun[[NDArray[float, :, :], _bool_signature],
                    NDArray[bool, :, :]],
                Fun[[NDArray[complex, :, :], _bool_signature],
                    NDArray[bool, :, :]],
                Fun[[NDArray[bool, :, :, :], _bool_signature],
                    NDArray[bool, :, :, :]],
                Fun[[NDArray[int, :, :, :], _bool_signature],
                    NDArray[bool, :, :, :]],
                Fun[[NDArray[float, :, :, :], _bool_signature],
                    NDArray[bool, :, :, :]],
                Fun[[NDArray[complex, :, :, :], _bool_signature],
                    NDArray[bool, :, :, :]],
                Fun[[NDArray[bool, :, :, :, :], _bool_signature],
                    NDArray[bool, :, :, :, :]],
                Fun[[NDArray[int, :, :, :, :], _bool_signature],
                    NDArray[bool, :, :, :, :]],
                Fun[[NDArray[float, :, :, :, :], _bool_signature],
                    NDArray[bool, :, :, :, :]],
                Fun[[NDArray[complex, :, :, :, :], _bool_signature],
                    NDArray[bool, :, :, :, :]],
                # dtype = int
                Fun[[NDArray[bool, :], _int_signature], NDArray[int, :]],
                Fun[[NDArray[int, :], _int_signature], NDArray[int, :]],
                Fun[[NDArray[float, :], _int_signature], NDArray[int, :]],
                Fun[[NDArray[complex, :], _int_signature], NDArray[int, :]],
                Fun[[NDArray[bool, :, :], _int_signature], NDArray[int, :, :]],
                Fun[[NDArray[int, :, :], _int_signature], NDArray[int, :, :]],
                Fun[[NDArray[float, :, :], _int_signature],
                    NDArray[int, :, :]],
                Fun[[NDArray[complex, :, :], _int_signature],
                    NDArray[int, :, :]],
                Fun[[NDArray[bool, :, :, :], _int_signature],
                    NDArray[int, :, :, :]],
                Fun[[NDArray[int, :, :, :], _int_signature],
                    NDArray[int, :, :, :]],
                Fun[[NDArray[float, :, :, :], _int_signature],
                    NDArray[int, :, :, :]],
                Fun[[NDArray[complex, :, :, :], _int_signature],
                    NDArray[int, :, :, :]],
                Fun[[NDArray[bool, :, :, :, :], _int_signature],
                    NDArray[int, :, :, :, :]],
                Fun[[NDArray[int, :, :, :, :], _int_signature],
                    NDArray[int, :, :, :, :]],
                Fun[[NDArray[float, :, :, :, :], _int_signature],
                    NDArray[int, :, :, :, :]],
                Fun[[NDArray[complex, :, :, :, :], _int_signature],
                    NDArray[int, :, :, :, :]],
                # dtype = float
                Fun[[NDArray[bool, :], _float_signature], NDArray[float, :]],
                Fun[[NDArray[int, :], _float_signature], NDArray[float, :]],
                Fun[[NDArray[float, :], _float_signature], NDArray[float, :]],
                Fun[[NDArray[complex, :], _float_signature],
                    NDArray[float, :]],
                Fun[[NDArray[bool, :, :], _float_signature],
                    NDArray[float, :, :]],
                Fun[[NDArray[int, :, :], _float_signature],
                    NDArray[float, :, :]],
                Fun[[NDArray[float, :, :], _float_signature],
                    NDArray[float, :, :]],
                Fun[[NDArray[complex, :, :], _float_signature],
                    NDArray[float, :, :]],
                Fun[[NDArray[bool, :, :, :], _float_signature],
                    NDArray[float, :, :, :]],
                Fun[[NDArray[int, :, :, :], _float_signature],
                    NDArray[float, :, :, :]],
                Fun[[NDArray[float, :, :, :], _float_signature],
                    NDArray[float, :, :, :]],
                Fun[[NDArray[complex, :, :, :], _float_signature],
                    NDArray[float, :, :, :]],
                Fun[[NDArray[bool, :, :, :, :], _float_signature],
                    NDArray[float, :, :, :, :]],
                Fun[[NDArray[int, :, :, :, :], _float_signature],
                    NDArray[float, :, :, :, :]],
                Fun[[NDArray[float, :, :, :, :], _float_signature],
                    NDArray[float, :, :, :, :]],
                Fun[[NDArray[complex, :, :, :, :], _float_signature],
                    NDArray[float, :, :, :, :]],
                # dtype = complex
                Fun[[NDArray[bool, :], _complex_signature],
                    NDArray[complex, :]],
                Fun[[NDArray[int, :], _complex_signature],
                    NDArray[complex, :]],
                Fun[[NDArray[float, :], _complex_signature],
                    NDArray[complex, :]],
                Fun[[NDArray[complex, :], _complex_signature],
                    NDArray[complex, :]],
                Fun[[NDArray[bool, :, :], _complex_signature],
                    NDArray[complex, :, :]],
                Fun[[NDArray[int, :, :], _complex_signature],
                    NDArray[complex, :, :]],
                Fun[[NDArray[float, :, :], _complex_signature],
                    NDArray[complex, :, :]],
                Fun[[NDArray[complex, :, :], _complex_signature],
                    NDArray[complex, :, :]],
                Fun[[NDArray[bool, :, :, :], _complex_signature],
                    NDArray[complex, :, :, :]],
                Fun[[NDArray[int, :, :, :], _complex_signature],
                    NDArray[complex, :, :, :]],
                Fun[[NDArray[float, :, :, :], _complex_signature],
                    NDArray[complex, :, :, :]],
                Fun[[NDArray[complex, :, :, :], _complex_signature],
                    NDArray[complex, :, :, :]],
                Fun[[NDArray[bool, :, :, :, :], _complex_signature],
                    NDArray[complex, :, :, :, :]],
                Fun[[NDArray[int, :, :, :, :], _complex_signature],
                    NDArray[complex, :, :, :, :]],
                Fun[[NDArray[float, :, :, :, :], _complex_signature],
                    NDArray[complex, :, :, :, :]],
                Fun[[NDArray[complex, :, :, :, :], _complex_signature],
                    NDArray[complex, :, :, :, :]],
            ]
        ),
        "dtype": AttributeIntr(),
        "fill": MethodIntr(
            signature=Union[
                # 1d
                Fun[[NDArray[bool, :], bool], None],
                Fun[[NDArray[int, :], int], None],
                Fun[[NDArray[float, :], float], None],
                Fun[[NDArray[complex, :], complex], None],
                # 2d
                Fun[[NDArray[bool, :, :], bool], None],
                Fun[[NDArray[int, :, :], int], None],
                Fun[[NDArray[float, :, :], float], None],
                Fun[[NDArray[complex, :, :], complex], None],
                # 3d
                Fun[[NDArray[bool, :, :, :], bool], None],
                Fun[[NDArray[int, :, :, :], int], None],
                Fun[[NDArray[float, :, :, :], float], None],
                Fun[[NDArray[complex, :, :, :], complex], None],
                # 4d
                Fun[[NDArray[bool, :, :, :, :], bool], None],
                Fun[[NDArray[int, :, :, :, :], int], None],
                Fun[[NDArray[float, :, :, :, :], float], None],
                Fun[[NDArray[complex, :, :, :, :], complex], None],

            ],
        ),
        "flat": AttributeIntr(
            signature=Union[
                # 1d
                Fun[[NDArray[bool, :]], Generator[bool]],
                Fun[[NDArray[int, :]], Generator[int]],
                Fun[[NDArray[float, :]], Generator[float]],
                Fun[[NDArray[complex, :]], Generator[complex]],
                # 2d
                Fun[[NDArray[bool, :, :]], Generator[bool]],
                Fun[[NDArray[int, :, :]], Generator[int]],
                Fun[[NDArray[float, :, :]], Generator[float]],
                Fun[[NDArray[complex, :, :]], Generator[complex]],
                # 3d
                Fun[[NDArray[bool, :, :, :]], Generator[bool]],
                Fun[[NDArray[int, :, :, :]], Generator[int]],
                Fun[[NDArray[float, :, :, :]], Generator[float]],
                Fun[[NDArray[complex, :, :, :]], Generator[complex]],
                # 4d
                Fun[[NDArray[bool, :, :, :, :]], Generator[bool]],
                Fun[[NDArray[int, :, :, :, :]], Generator[int]],
                Fun[[NDArray[float, :, :, :, :]], Generator[float]],
                Fun[[NDArray[complex, :, :, :, :]], Generator[complex]],
            ]
        ),
        "flatten": MethodIntr(
            signature=Union[
                # 1d
                Fun[[NDArray[bool, :]], NDArray[bool, :]],
                Fun[[NDArray[int, :]], NDArray[int, :]],
                Fun[[NDArray[float, :]], NDArray[float, :]],
                Fun[[NDArray[complex, :]], NDArray[complex, :]],
                # 2d
                Fun[[NDArray[bool, :, :]], NDArray[bool, :]],
                Fun[[NDArray[int, :, :]], NDArray[int, :]],
                Fun[[NDArray[float, :, :]], NDArray[float, :]],
                Fun[[NDArray[complex, :, :]], NDArray[complex, :]],
                # 3d
                Fun[[NDArray[bool, :, :, :]], NDArray[bool, :]],
                Fun[[NDArray[int, :, :, :]], NDArray[int, :]],
                Fun[[NDArray[float, :, :, :]], NDArray[float, :]],
                Fun[[NDArray[complex, :, :, :]], NDArray[complex, :]],
                # 4d
                Fun[[NDArray[bool, :, :, :, :]], NDArray[bool, :]],
                Fun[[NDArray[int, :, :, :, :]], NDArray[int, :]],
                Fun[[NDArray[float, :, :, :, :]], NDArray[float, :]],
                Fun[[NDArray[complex, :, :, :, :]], NDArray[complex, :]],
            ]
        ),
        "item": MethodIntr(
            signature=Union[
                # item = int
                # 1d
                Fun[[NDArray[bool, :], int], bool],
                Fun[[NDArray[int, :], int], int],
                Fun[[NDArray[float, :], int], float],
                Fun[[NDArray[complex, :], int], complex],
                # 2d
                Fun[[NDArray[bool, :, :], int], bool],
                Fun[[NDArray[int, :, :], int], int],
                Fun[[NDArray[float, :, :], int], float],
                Fun[[NDArray[complex, :, :], int], complex],
                # 3d
                Fun[[NDArray[bool, :, :, :], int], bool],
                Fun[[NDArray[int, :, :, :], int], int],
                Fun[[NDArray[float, :, :, :], int], float],
                Fun[[NDArray[complex, :, :, :], int], complex],
                # 4d
                Fun[[NDArray[bool, :, :, :, :], int], bool],
                Fun[[NDArray[int, :, :, :, :], int], int],
                Fun[[NDArray[float, :, :, :, :], int], float],
                Fun[[NDArray[complex, :, :, :, :], int], complex],

                # item = tuple
                # 1d
                Fun[[NDArray[bool, :], Tuple[int]], bool],
                Fun[[NDArray[int, :], Tuple[int]], int],
                Fun[[NDArray[float, :], Tuple[int]], float],
                Fun[[NDArray[complex, :], Tuple[int]], complex],
                # 2d
                Fun[[NDArray[bool, :, :], Tuple[int, int]], bool],
                Fun[[NDArray[int, :, :], Tuple[int, int]], int],
                Fun[[NDArray[float, :, :], Tuple[int, int]], float],
                Fun[[NDArray[complex, :, :], Tuple[int, int]], complex],
                # 3d
                Fun[[NDArray[bool, :, :, :], Tuple[int, int, int]], bool],
                Fun[[NDArray[int, :, :, :], Tuple[int, int, int]], int],
                Fun[[NDArray[float, :, :, :], Tuple[int, int, int]], float],
                Fun[[NDArray[complex, :, :, :], Tuple[int, int, int]],
                    complex],
                # 4d
                Fun[[NDArray[bool, :, :, :, :], Tuple[int, int, int, int]],
                    bool],
                Fun[[NDArray[int, :, :, :, :], Tuple[int, int, int, int]],
                    int],
                Fun[[NDArray[float, :, :, :, :], Tuple[int, int, int, int]],
                    float],
                Fun[[NDArray[complex, :, :, :, :], Tuple[int, int, int, int]],
                    complex],
            ]
        ),
        "itemsize": AttributeIntr(signature=Fun[[NDArray[T0, :]], int],
                                  return_range=interval.positive_values),
        "nbytes": AttributeIntr(
            signature=Fun[[NDArray[T0, :]], int],
            return_range=interval.positive_values
        ),
        "ndim": AttributeIntr(signature=Fun[[NDArray[T0, :]], int],
                              return_range=interval.positive_values),
        "shape": AttributeIntr(
            signature=Union[
                # bool
                Fun[[NDArray[bool, :]], Tuple[int]],
                Fun[[NDArray[bool, :, :]], Tuple[int, int]],
                Fun[[NDArray[bool, :, :, :]], Tuple[int, int, int]],
                Fun[[NDArray[bool, :, :, :, :]], Tuple[int, int, int, int]],
                # int
                Fun[[NDArray[int, :]], Tuple[int]],
                Fun[[NDArray[int, :, :]], Tuple[int, int]],
                Fun[[NDArray[int, :, :, :]], Tuple[int, int, int]],
                Fun[[NDArray[int, :, :, :, :]], Tuple[int, int, int, int]],
                # float
                Fun[[NDArray[float, :]], Tuple[int]],
                Fun[[NDArray[float, :, :]], Tuple[int, int]],
                Fun[[NDArray[float, :, :, :]], Tuple[int, int, int]],
                Fun[[NDArray[float, :, :, :, :]], Tuple[int, int, int, int]],
                # complex
                Fun[[NDArray[complex, :]], Tuple[int]],
                Fun[[NDArray[complex, :, :]], Tuple[int, int]],
                Fun[[NDArray[complex, :, :, :]], Tuple[int, int, int]],
                Fun[[NDArray[complex, :, :, :, :]], Tuple[int, int, int, int]],
            ],
            return_range_content=interval.positive_values
        ),
        "size": AttributeIntr(signature=Fun[[NDArray[T0, :]], int],
                              return_range=interval.positive_values),
        "strides": AttributeIntr(
            signature=Union[
                # bool
                Fun[[NDArray[bool, :]], Tuple[int]],
                Fun[[NDArray[bool, :, :]], Tuple[int, int]],
                Fun[[NDArray[bool, :, :, :]], Tuple[int, int, int]],
                Fun[[NDArray[bool, :, :, :, :]], Tuple[int, int, int, int]],
                # int
                Fun[[NDArray[int, :]], Tuple[int]],
                Fun[[NDArray[int, :, :]], Tuple[int, int]],
                Fun[[NDArray[int, :, :, :]], Tuple[int, int, int]],
                Fun[[NDArray[int, :, :, :, :]], Tuple[int, int, int, int]],
                # float
                Fun[[NDArray[float, :]], Tuple[int]],
                Fun[[NDArray[float, :, :]], Tuple[int, int]],
                Fun[[NDArray[float, :, :, :]], Tuple[int, int, int]],
                Fun[[NDArray[float, :, :, :, :]], Tuple[int, int, int, int]],
                # complex
                Fun[[NDArray[complex, :]], Tuple[int]],
                Fun[[NDArray[complex, :, :]], Tuple[int, int]],
                Fun[[NDArray[complex, :, :, :]], Tuple[int, int, int]],
                Fun[[NDArray[complex, :, :, :, :]], Tuple[int, int, int, int]],
            ]
        ),
        "T": AttributeIntr(signature=Fun[[NDArray[T0, :]], NDArray[T0, :]]),
        "tolist": ConstMethodIntr(
            signature=Union[
                # 1d
                Fun[[NDArray[bool, :]], List[bool]],
                Fun[[NDArray[int, :]], List[int]],
                Fun[[NDArray[float, :]], List[float]],
                Fun[[NDArray[complex, :]], List[complex]],
                # 2d
                Fun[[NDArray[bool, :, :]], List[bool]],
                Fun[[NDArray[int, :, :]], List[int]],
                Fun[[NDArray[float, :, :]], List[float]],
                Fun[[NDArray[complex, :, :]], List[complex]],
                # 3d
                Fun[[NDArray[bool, :, :, :]], List[bool]],
                Fun[[NDArray[int, :, :, :]], List[int]],
                Fun[[NDArray[float, :, :, :]], List[float]],
                Fun[[NDArray[complex, :, :, :]], List[complex]],
                # 4d
                Fun[[NDArray[bool, :, :, :, :]], List[bool]],
                Fun[[NDArray[int, :, :, :, :]], List[int]],
                Fun[[NDArray[float, :, :, :, :]], List[float]],
                Fun[[NDArray[complex, :, :, :, :]], List[complex]],
            ]
        ),
        "tostring": ConstMethodIntr(signature=Fun[[NDArray[T0, :]], str]),
    },
}


_numpy_ones_signature = Union[
    # 1d
    Fun[[int], NDArray[float, :]],
    Fun[[int, _bool_signature], NDArray[bool, :]],
    Fun[[int, _int_signature], NDArray[int, :]],
    Fun[[int, _float_signature], NDArray[float, :]],
    Fun[[int, _complex_signature], NDArray[complex, :]],
    # 1D tuple
    Fun[[Tuple[int]], NDArray[float, :]],
    Fun[[Tuple[int], _bool_signature], NDArray[bool, :]],
    Fun[[Tuple[int], _int_signature], NDArray[int, :]],
    Fun[[Tuple[int], _float_signature], NDArray[float, :]],
    Fun[[Tuple[int], _complex_signature], NDArray[complex, :]],
    # 2D tuple
    Fun[[Tuple[int, int]], NDArray[float, :, :]],
    Fun[[Tuple[int, int], _bool_signature], NDArray[bool, :, :]],
    Fun[[Tuple[int, int], _int_signature], NDArray[int, :, :]],
    Fun[[Tuple[int, int], _float_signature], NDArray[float, :, :]],
    Fun[[Tuple[int, int], _complex_signature], NDArray[complex, :, :]],
    # 3D tuple
    Fun[[Tuple[int, int, int]], NDArray[float, :, :, :]],
    Fun[[Tuple[int, int, int], _bool_signature], NDArray[bool, :, :, :]],
    Fun[[Tuple[int, int, int], _int_signature], NDArray[int, :, :, :]],
    Fun[[Tuple[int, int, int], _float_signature], NDArray[float, :, :, :]],
    Fun[[Tuple[int, int, int], _complex_signature], NDArray[complex, :, :, :]],
    # 4D tuple
    Fun[[Tuple[int, int, int, int]], NDArray[float, :, :, :, :]],
    Fun[[Tuple[int, int, int, int], _bool_signature],
        NDArray[bool, :, :, :, :]],
    Fun[[Tuple[int, int, int, int], _int_signature],
        NDArray[int, :, :, :, :]],
    Fun[[Tuple[int, int, int, int], _float_signature],
        NDArray[float, :, :, :, :]],
    Fun[[Tuple[int, int, int, int], _complex_signature],
        NDArray[complex, :, :, :, :]],
]
_numpy_ones_like_signature = Union[
    # scalar
    Fun[[bool], bool],
    Fun[[int], int],
    Fun[[float], float],
    Fun[[complex], complex],
    # scalar + None
    Fun[[bool, None], bool],
    Fun[[int, None], int],
    Fun[[float, None], float],
    Fun[[complex, None], complex],
    # scalar + dtype
    Fun[[bool, _bool_signature], bool],
    Fun[[bool, _int_signature], int],
    Fun[[bool, _float_signature], float],
    Fun[[bool, _complex_signature], complex],
    Fun[[int, _bool_signature], bool],
    Fun[[int, _int_signature], int],
    Fun[[int, _float_signature], float],
    Fun[[int, _complex_signature], complex],
    Fun[[complex, _bool_signature], bool],
    Fun[[complex, _int_signature], int],
    Fun[[complex, _float_signature], float],
    Fun[[complex, _complex_signature], complex],
    # array 1D
    Fun[[Iterable[bool]], NDArray[bool, :]],
    Fun[[Iterable[int]], NDArray[int, :]],
    Fun[[Iterable[float]], NDArray[float, :]],
    Fun[[Iterable[complex]], NDArray[complex, :]],

    # array 2d
    Fun[[Iterable[Iterable[bool]]], NDArray[bool, :, :]],
    Fun[[Iterable[Iterable[int]]], NDArray[int, :, :]],
    Fun[[Iterable[Iterable[float]]], NDArray[float, :, :]],
    Fun[[Iterable[Iterable[complex]]], NDArray[complex, :, :]],

    # array 3d
    Fun[[Iterable[Iterable[Iterable[bool]]]], NDArray[bool, :, :, :]],
    Fun[[Iterable[Iterable[Iterable[int]]]], NDArray[int, :, :, :]],
    Fun[[Iterable[Iterable[Iterable[float]]]], NDArray[float, :, :, :]],
    Fun[[Iterable[Iterable[Iterable[float]]], _float_signature],
        NDArray[float, :, :, :]],
    Fun[[Iterable[Iterable[Iterable[complex]]]], NDArray[complex, :, :, :]],

    # array 4d
    Fun[[Iterable[Iterable[Iterable[Iterable[bool]]]]],
        NDArray[bool, :, :, :, :]],
    Fun[[Iterable[Iterable[Iterable[Iterable[int]]]]],
        NDArray[int, :, :, :, :]],
    Fun[[Iterable[Iterable[Iterable[Iterable[float]]]]],
        NDArray[float, :, :, :, :]],
    Fun[[Iterable[Iterable[Iterable[Iterable[complex]]]]],
        NDArray[complex, :, :, :, :]],

    # with dtype
]

_numpy_unary_op_signature = Union[
    # 1d
    Fun[[bool], bool],
    Fun[[int], int],
    Fun[[float], float],
    Fun[[complex], complex],
    # 1d Iterable
    Fun[[Iterable[bool]], NDArray[bool, :]],
    Fun[[Iterable[int]], NDArray[int, :]],
    Fun[[Iterable[float]], NDArray[float, :]],
    Fun[[Iterable[complex]], NDArray[complex, :]],
    # 2d Iterable
    Fun[[Iterable[Iterable[bool]]], NDArray[bool, :, :]],
    Fun[[Iterable[Iterable[int]]], NDArray[int, :, :]],
    Fun[[Iterable[Iterable[float]]], NDArray[float, :, :]],
    Fun[[Iterable[Iterable[complex]]], NDArray[complex, :, :]],
    # 3d Iterable
    Fun[[Iterable[Iterable[Iterable[bool]]]], NDArray[bool, :, :, :]],
    Fun[[Iterable[Iterable[Iterable[int]]]], NDArray[int, :, :, :]],
    Fun[[Iterable[Iterable[Iterable[float]]]], NDArray[float, :, :, :]],
    Fun[[Iterable[Iterable[Iterable[complex]]]], NDArray[complex, :, :, :]],
    # 4d Iterable
    Fun[[Iterable[Iterable[Iterable[Iterable[bool]]]]],
        NDArray[bool, :, :, :, :]],
    Fun[[Iterable[Iterable[Iterable[Iterable[int]]]]],
        NDArray[int, :, :, :, :]],
    Fun[[Iterable[Iterable[Iterable[Iterable[float]]]]],
        NDArray[float, :, :, :, :]],
    Fun[[Iterable[Iterable[Iterable[Iterable[complex]]]]],
        NDArray[complex, :, :, :, :]],
]

_numpy_float_unary_op_signature = Union[
    # 1d
    Fun[[bool], float],
    Fun[[int], float],
    Fun[[float], float],
    # 1d Iterable
    Fun[[Iterable[bool]], NDArray[float, :]],
    Fun[[Iterable[int]], NDArray[float, :]],
    Fun[[Iterable[float]], NDArray[float, :]],
    # 2d Iterable
    Fun[[Iterable[Iterable[bool]]], NDArray[float, :, :]],
    Fun[[Iterable[Iterable[int]]], NDArray[float, :, :]],
    Fun[[Iterable[Iterable[float]]], NDArray[float, :, :]],
    # 3d Iterable
    Fun[[Iterable[Iterable[Iterable[bool]]]], NDArray[float, :, :, :]],
    Fun[[Iterable[Iterable[Iterable[int]]]], NDArray[float, :, :, :]],
    Fun[[Iterable[Iterable[Iterable[float]]]], NDArray[float, :, :, :]],
    # 4d Iterable
    Fun[[Iterable[Iterable[Iterable[Iterable[bool]]]]],
        NDArray[float, :, :, :, :]],
    Fun[[Iterable[Iterable[Iterable[Iterable[int]]]]],
        NDArray[float, :, :, :, :]],
    Fun[[Iterable[Iterable[Iterable[Iterable[float]]]]],
        NDArray[float, :, :, :, :]],
]

_numpy_int_unary_op_signature = Union[
    # 1d
    Fun[[bool], bool],
    Fun[[int], int],
    # 1d Iterable
    Fun[[Iterable[bool]], NDArray[bool, :]],
    Fun[[Iterable[int]], NDArray[int, :]],
    # 2d Iterable
    Fun[[Iterable[Iterable[bool]]], NDArray[bool, :, :]],
    Fun[[Iterable[Iterable[int]]], NDArray[int, :, :]],
    # 3d Iterable
    Fun[[Iterable[Iterable[Iterable[bool]]]], NDArray[bool, :, :, :]],
    Fun[[Iterable[Iterable[Iterable[int]]]], NDArray[int, :, :, :]],
    # 4d Iterable
    Fun[[Iterable[Iterable[Iterable[Iterable[bool]]]]],
        NDArray[bool, :, :, :, :]],
    Fun[[Iterable[Iterable[Iterable[Iterable[int]]]]],
        NDArray[int, :, :, :, :]],
]

_numpy_unary_op_angle_signature = Union[
    # no extra option
    # 1d
    Fun[[bool], float],
    Fun[[int], float],
    Fun[[float], float],
    Fun[[complex], float],
    # 1d Iterable
    Fun[[Iterable[bool]], NDArray[float, :]],
    Fun[[Iterable[int]], NDArray[float, :]],
    Fun[[Iterable[float]], NDArray[float, :]],
    Fun[[Iterable[complex]], NDArray[float, :]],
    # 2d Iterable
    Fun[[Iterable[Iterable[bool]]], NDArray[float, :, :]],
    Fun[[Iterable[Iterable[int]]], NDArray[float, :, :]],
    Fun[[Iterable[Iterable[float]]], NDArray[float, :, :]],
    Fun[[Iterable[Iterable[complex]]], NDArray[float, :, :]],
    # 3d Iterable
    Fun[[Iterable[Iterable[Iterable[bool]]]], NDArray[float, :, :, :]],
    Fun[[Iterable[Iterable[Iterable[int]]]], NDArray[float, :, :, :]],
    Fun[[Iterable[Iterable[Iterable[float]]]], NDArray[float, :, :, :]],
    Fun[[Iterable[Iterable[Iterable[complex]]]], NDArray[float, :, :, :]],
    # 4d Iterable
    Fun[[Iterable[Iterable[Iterable[Iterable[bool]]]]],
        NDArray[float, :, :, :, :]],
    Fun[[Iterable[Iterable[Iterable[Iterable[int]]]]],
        NDArray[float, :, :, :, :]],
    Fun[[Iterable[Iterable[Iterable[Iterable[float]]]]],
        NDArray[float, :, :, :, :]],
    Fun[[Iterable[Iterable[Iterable[Iterable[complex]]]]],
        NDArray[float, :, :, :, :]],

    # extra option
    # 1d
    Fun[[bool, bool], float],
    Fun[[int, bool], float],
    Fun[[float, bool], float],
    Fun[[complex, bool], float],
    # 1d Iterable
    Fun[[Iterable[bool], bool], NDArray[float, :]],
    Fun[[Iterable[int], bool], NDArray[float, :]],
    Fun[[Iterable[float], bool], NDArray[float, :]],
    Fun[[Iterable[complex], bool], NDArray[float, :]],
    # 2d Iterable
    Fun[[Iterable[Iterable[bool]], bool], NDArray[float, :, :]],
    Fun[[Iterable[Iterable[int]], bool], NDArray[float, :, :]],
    Fun[[Iterable[Iterable[float]], bool], NDArray[float, :, :]],
    Fun[[Iterable[Iterable[complex]], bool], NDArray[float, :, :]],
    # 3d Iterable
    Fun[[Iterable[Iterable[Iterable[bool]]], bool], NDArray[float, :, :, :]],
    Fun[[Iterable[Iterable[Iterable[int]]], bool], NDArray[float, :, :, :]],
    Fun[[Iterable[Iterable[Iterable[float]]], bool], NDArray[float, :, :, :]],
    Fun[[Iterable[Iterable[Iterable[complex]]], bool],
        NDArray[float, :, :, :]],
    # 4d Iterable
    Fun[[Iterable[Iterable[Iterable[Iterable[bool]]]], bool],
        NDArray[float, :, :, :, :]],
    Fun[[Iterable[Iterable[Iterable[Iterable[int]]]], bool],
        NDArray[float, :, :, :, :]],
    Fun[[Iterable[Iterable[Iterable[Iterable[float]]]], bool],
        NDArray[float, :, :, :, :]],
    Fun[[Iterable[Iterable[Iterable[Iterable[complex]]]], bool],
        NDArray[float, :, :, :, :]],
]

_numpy_array_str_signature = Union[
    tuple(Fun[[NDArray[(dtype,) + slices]], str]
          for dtype in (bool, int, float, complex)
          for slices in [(slice(0),) * i
                         for i in range(1, 5)])
]
_numpy_float_unary_op_float_signature = Union[
    # 1d
    Fun[[bool], float],
    Fun[[int], float],
    Fun[[float], float],
    # 1d Iterable
    Fun[[Iterable[bool]], NDArray[float, :]],
    Fun[[Iterable[int]], NDArray[float, :]],
    Fun[[Iterable[float]], NDArray[float, :]],
    # 2d Iterable
    Fun[[Iterable[Iterable[bool]]], NDArray[float, :, :]],
    Fun[[Iterable[Iterable[int]]], NDArray[float, :, :]],
    Fun[[Iterable[Iterable[float]]], NDArray[float, :, :]],
    # 3d Iterable
    Fun[[Iterable[Iterable[Iterable[bool]]]], NDArray[float, :, :, :]],
    Fun[[Iterable[Iterable[Iterable[int]]]], NDArray[float, :, :, :]],
    Fun[[Iterable[Iterable[Iterable[float]]]], NDArray[float, :, :, :]],
    # 4d Iterable
    Fun[[Iterable[Iterable[Iterable[Iterable[bool]]]]],
        NDArray[float, :, :, :, :]],
    Fun[[Iterable[Iterable[Iterable[Iterable[int]]]]],
        NDArray[float, :, :, :, :]],
    Fun[[Iterable[Iterable[Iterable[Iterable[float]]]]],
        NDArray[float, :, :, :, :]],
]


_numpy_unary_op_float_signature = Union[
    # 1d
    Fun[[bool], float],
    Fun[[int], float],
    Fun[[float], float],
    Fun[[complex], complex],
    # 1d Iterable
    Fun[[Iterable[bool]], NDArray[float, :]],
    Fun[[Iterable[int]], NDArray[float, :]],
    Fun[[Iterable[float]], NDArray[float, :]],
    Fun[[Iterable[complex]], NDArray[complex, :]],
    # 2d Iterable
    Fun[[Iterable[Iterable[bool]]], NDArray[float, :, :]],
    Fun[[Iterable[Iterable[int]]], NDArray[float, :, :]],
    Fun[[Iterable[Iterable[float]]], NDArray[float, :, :]],
    Fun[[Iterable[Iterable[complex]]], NDArray[complex, :, :]],
    # 3d Iterable
    Fun[[Iterable[Iterable[Iterable[bool]]]], NDArray[float, :, :, :]],
    Fun[[Iterable[Iterable[Iterable[int]]]], NDArray[float, :, :, :]],
    Fun[[Iterable[Iterable[Iterable[float]]]], NDArray[float, :, :, :]],
    Fun[[Iterable[Iterable[Iterable[complex]]]], NDArray[complex, :, :, :]],
    # 4d Iterable
    Fun[[Iterable[Iterable[Iterable[Iterable[bool]]]]],
        NDArray[float, :, :, :, :]],
    Fun[[Iterable[Iterable[Iterable[Iterable[int]]]]],
        NDArray[float, :, :, :, :]],
    Fun[[Iterable[Iterable[Iterable[Iterable[float]]]]],
        NDArray[float, :, :, :, :]],
    Fun[[Iterable[Iterable[Iterable[Iterable[complex]]]]],
        NDArray[complex, :, :, :, :]],
]

_numpy_unary_op_int_signature = Union[
    # 1d
    Fun[[bool], int],
    Fun[[int], int],
    Fun[[float], int],
    Fun[[complex], int],
    # 1d Iterable
    Fun[[Iterable[bool]], NDArray[int, :]],
    Fun[[Iterable[int]], NDArray[int, :]],
    Fun[[Iterable[float]], NDArray[int, :]],
    Fun[[Iterable[complex]], NDArray[int, :]],
    # 2d Iterable
    Fun[[Iterable[Iterable[bool]]], NDArray[int, :, :]],
    Fun[[Iterable[Iterable[int]]], NDArray[int, :, :]],
    Fun[[Iterable[Iterable[float]]], NDArray[int, :, :]],
    Fun[[Iterable[Iterable[complex]]], NDArray[int, :, :]],
    # 3d Iterable
    Fun[[Iterable[Iterable[Iterable[bool]]]], NDArray[int, :, :, :]],
    Fun[[Iterable[Iterable[Iterable[int]]]], NDArray[int, :, :, :]],
    Fun[[Iterable[Iterable[Iterable[float]]]], NDArray[int, :, :, :]],
    Fun[[Iterable[Iterable[Iterable[complex]]]], NDArray[int, :, :, :]],
    # 4d Iterable
    Fun[[Iterable[Iterable[Iterable[Iterable[bool]]]]],
        NDArray[int, :, :, :, :]],
    Fun[[Iterable[Iterable[Iterable[Iterable[int]]]]],
        NDArray[int, :, :, :, :]],
    Fun[[Iterable[Iterable[Iterable[Iterable[float]]]]],
        NDArray[int, :, :, :, :]],
    Fun[[Iterable[Iterable[Iterable[Iterable[complex]]]]],
        NDArray[int, :, :, :, :]],
]

_numpy_unary_op_axis_signature = Union[
    # no axis
    # 1d
    Fun[[bool], bool],
    Fun[[int], int],
    Fun[[float], float],
    Fun[[complex], complex],
    # 1d Iterable
    Fun[[Iterable[bool]], bool],
    Fun[[Iterable[int]], int],
    Fun[[Iterable[float]], float],
    Fun[[Iterable[complex]], complex],
    # 2d Iterable
    Fun[[Iterable[Iterable[bool]]], bool],
    Fun[[Iterable[Iterable[int]]], int],
    Fun[[Iterable[Iterable[float]]], float],
    Fun[[Iterable[Iterable[complex]]], complex],
    # 3d Iterable
    Fun[[Iterable[Iterable[Iterable[bool]]]], bool],
    Fun[[Iterable[Iterable[Iterable[int]]]], int],
    Fun[[Iterable[Iterable[Iterable[float]]]], float],
    Fun[[Iterable[Iterable[Iterable[complex]]]], complex],
    # 4d Iterable
    Fun[[Iterable[Iterable[Iterable[Iterable[bool]]]]], bool],
    Fun[[Iterable[Iterable[Iterable[Iterable[int]]]]], int],
    Fun[[Iterable[Iterable[Iterable[Iterable[float]]]]], float],
    Fun[[Iterable[Iterable[Iterable[Iterable[complex]]]]], complex],

    # axis
    # 1d Iterable
    Fun[[Iterable[bool], int], bool],
    Fun[[Iterable[int], int], int],
    Fun[[Iterable[float], int], float],
    Fun[[Iterable[complex], int], complex],
    # 2d Iterable
    Fun[[Iterable[Iterable[bool]], int], NDArray[bool, :]],
    Fun[[Iterable[Iterable[int]], int], NDArray[int, :]],
    Fun[[Iterable[Iterable[float]], int], NDArray[float, :]],
    Fun[[Iterable[Iterable[complex]], int], NDArray[complex, :]],
    # 3d Iterable
    Fun[[Iterable[Iterable[Iterable[bool]]], int], NDArray[bool, :, :]],
    Fun[[Iterable[Iterable[Iterable[int]]], int], NDArray[int, :, :]],
    Fun[[Iterable[Iterable[Iterable[float]]], int], NDArray[float, :, :]],
    Fun[[Iterable[Iterable[Iterable[complex]]], int], NDArray[complex, :, :]],
    # 4d Iterable
    Fun[[Iterable[Iterable[Iterable[Iterable[bool]]]], int],
        NDArray[bool, :, :, :]],
    Fun[[Iterable[Iterable[Iterable[Iterable[int]]]], int],
        NDArray[int, :, :, :]],
    Fun[[Iterable[Iterable[Iterable[Iterable[float]]]], int],
        NDArray[float, :, :, :]],
    Fun[[Iterable[Iterable[Iterable[Iterable[complex]]]], int],
        NDArray[complex, :, :, :]],
]

_numpy_unary_op_int_axis_signature = Union[
    # no axis
    # 1d
    Fun[[bool], int],
    Fun[[int], int],
    Fun[[float], int],
    Fun[[complex], int],
    # 1d Iterable
    Fun[[Iterable[bool]], int],
    Fun[[Iterable[int]], int],
    Fun[[Iterable[float]], int],
    Fun[[Iterable[complex]], int],
    # 2d Iterable
    Fun[[Iterable[Iterable[bool]]], int],
    Fun[[Iterable[Iterable[int]]], int],
    Fun[[Iterable[Iterable[float]]], int],
    Fun[[Iterable[Iterable[complex]]], int],
    # 3d Iterable
    Fun[[Iterable[Iterable[Iterable[bool]]]], int],
    Fun[[Iterable[Iterable[Iterable[int]]]], int],
    Fun[[Iterable[Iterable[Iterable[float]]]], int],
    Fun[[Iterable[Iterable[Iterable[complex]]]], int],
    # 4d Iterable
    Fun[[Iterable[Iterable[Iterable[Iterable[bool]]]]], int],
    Fun[[Iterable[Iterable[Iterable[Iterable[int]]]]], int],
    Fun[[Iterable[Iterable[Iterable[Iterable[float]]]]], int],
    Fun[[Iterable[Iterable[Iterable[Iterable[complex]]]]], int],

    # axis
    # 1d Iterable
    Fun[[Iterable[bool], int], int],
    Fun[[Iterable[int], int], int],
    Fun[[Iterable[float], int], int],
    Fun[[Iterable[complex], int], int],
    # 2d Iterable
    Fun[[Iterable[Iterable[bool]], int], NDArray[int, :]],
    Fun[[Iterable[Iterable[int]], int], NDArray[int, :]],
    Fun[[Iterable[Iterable[float]], int], NDArray[int, :]],
    Fun[[Iterable[Iterable[complex]], int], NDArray[int, :]],
    # 3d Iterable
    Fun[[Iterable[Iterable[Iterable[bool]]], int], NDArray[int, :, :]],
    Fun[[Iterable[Iterable[Iterable[int]]], int], NDArray[int, :, :]],
    Fun[[Iterable[Iterable[Iterable[float]]], int], NDArray[int, :, :]],
    Fun[[Iterable[Iterable[Iterable[complex]]], int], NDArray[int, :, :]],
    # 4d Iterable
    Fun[[Iterable[Iterable[Iterable[Iterable[bool]]]], int],
        NDArray[int, :, :, :]],
    Fun[[Iterable[Iterable[Iterable[Iterable[int]]]], int],
        NDArray[int, :, :, :]],
    Fun[[Iterable[Iterable[Iterable[Iterable[float]]]], int],
        NDArray[int, :, :, :]],
    Fun[[Iterable[Iterable[Iterable[Iterable[complex]]]], int],
        NDArray[int, :, :, :]],
]

_numpy_unary_op_sum_axis_signature = Union[
    # no axis
    # 1d
    Fun[[bool], int],
    Fun[[int], int],
    Fun[[float], float],
    Fun[[complex], complex],
    # 1d Iterable
    Fun[[Iterable[bool]], int],
    Fun[[Iterable[int]], int],
    Fun[[Iterable[float]], float],
    Fun[[Iterable[complex]], complex],
    # 2d Iterable
    Fun[[Iterable[Iterable[bool]]], int],
    Fun[[Iterable[Iterable[int]]], int],
    Fun[[Iterable[Iterable[float]]], float],
    Fun[[Iterable[Iterable[complex]]], complex],
    # 3d Iterable
    Fun[[Iterable[Iterable[Iterable[bool]]]], int],
    Fun[[Iterable[Iterable[Iterable[int]]]], int],
    Fun[[Iterable[Iterable[Iterable[float]]]], float],
    Fun[[Iterable[Iterable[Iterable[complex]]]], complex],
    # 4d Iterable
    Fun[[Iterable[Iterable[Iterable[Iterable[bool]]]]], int],
    Fun[[Iterable[Iterable[Iterable[Iterable[int]]]]], int],
    Fun[[Iterable[Iterable[Iterable[Iterable[float]]]]], float],
    Fun[[Iterable[Iterable[Iterable[Iterable[complex]]]]], complex],

    # axis
    # 1d
    Fun[[bool, int], int],
    Fun[[int, int], int],
    Fun[[float, int], float],
    Fun[[complex, int], complex],
    # 1d Iterable
    Fun[[Iterable[bool], int], int],
    Fun[[Iterable[int], int], int],
    Fun[[Iterable[float], int], float],
    Fun[[Iterable[complex], int], complex],
    # 2d Iterable
    Fun[[Iterable[Iterable[bool]], int], NDArray[int, :]],
    Fun[[Iterable[Iterable[int]], int], NDArray[int, :]],
    Fun[[Iterable[Iterable[float]], int], NDArray[float, :]],
    Fun[[Iterable[Iterable[complex]], int], NDArray[complex, :]],
    # 3d Iterable
    Fun[[Iterable[Iterable[Iterable[bool]]], int], NDArray[int, :, :]],
    Fun[[Iterable[Iterable[Iterable[int]]], int], NDArray[int, :, :]],
    Fun[[Iterable[Iterable[Iterable[float]]], int], NDArray[float, :, :]],
    Fun[[Iterable[Iterable[Iterable[complex]]], int], NDArray[complex, :, :]],
    # 4d Iterable
    Fun[[Iterable[Iterable[Iterable[Iterable[bool]]]], int],
        NDArray[int, :, :, :]],
    Fun[[Iterable[Iterable[Iterable[Iterable[int]]]], int],
        NDArray[int, :, :, :]],
    Fun[[Iterable[Iterable[Iterable[Iterable[float]]]], int],
        NDArray[float, :, :, :]],
    Fun[[Iterable[Iterable[Iterable[Iterable[complex]]]], int],
        NDArray[complex, :, :, :]],
]

_numpy_unary_op_cumsum_axis_signature = Union[
    # no axis
    # 1d
    Fun[[bool], NDArray[int, :]],
    Fun[[int], NDArray[int, :]],
    Fun[[float], NDArray[float, :]],
    Fun[[complex], NDArray[complex, :]],
    # 1d Iterable
    Fun[[Iterable[bool]], NDArray[int, :]],
    Fun[[Iterable[int]], NDArray[int, :]],
    Fun[[Iterable[float]], NDArray[float, :]],
    Fun[[Iterable[complex]], NDArray[complex, :]],
    # 2d Iterable
    Fun[[Iterable[Iterable[bool]]], NDArray[int, :]],
    Fun[[Iterable[Iterable[int]]], NDArray[int, :]],
    Fun[[Iterable[Iterable[float]]], NDArray[float, :]],
    Fun[[Iterable[Iterable[complex]]], NDArray[complex, :]],
    # 3d Iterable
    Fun[[Iterable[Iterable[Iterable[bool]]]], NDArray[int, :]],
    Fun[[Iterable[Iterable[Iterable[int]]]], NDArray[int, :]],
    Fun[[Iterable[Iterable[Iterable[float]]]], NDArray[float, :]],
    Fun[[Iterable[Iterable[Iterable[complex]]]], NDArray[complex, :]],
    # 4d Iterable
    Fun[[Iterable[Iterable[Iterable[Iterable[bool]]]]], NDArray[int, :]],
    Fun[[Iterable[Iterable[Iterable[Iterable[int]]]]], NDArray[int, :]],
    Fun[[Iterable[Iterable[Iterable[Iterable[float]]]]], NDArray[float, :]],
    Fun[[Iterable[Iterable[Iterable[Iterable[complex]]]]],
        NDArray[complex, :]],

    # axis
    # 1d
    Fun[[bool, int], NDArray[int, :]],
    Fun[[int, int], NDArray[int, :]],
    Fun[[float, int], NDArray[float, :]],
    Fun[[complex, int], NDArray[complex, :]],
    # 1d Iterable
    Fun[[Iterable[bool], int], NDArray[int, :]],
    Fun[[Iterable[int], int], NDArray[int, :]],
    Fun[[Iterable[float], int], NDArray[float, :]],
    Fun[[Iterable[complex], int], NDArray[complex, :]],
    # 2d Iterable
    Fun[[Iterable[Iterable[bool]], int], NDArray[int, :, :]],
    Fun[[Iterable[Iterable[int]], int], NDArray[int, :, :]],
    Fun[[Iterable[Iterable[float]], int], NDArray[float, :, :]],
    Fun[[Iterable[Iterable[complex]], int], NDArray[complex, :, :]],
    # 3d Iterable
    Fun[[Iterable[Iterable[Iterable[bool]]], int], NDArray[int, :, :, :]],
    Fun[[Iterable[Iterable[Iterable[int]]], int], NDArray[int, :, :, :]],
    Fun[[Iterable[Iterable[Iterable[float]]], int], NDArray[float, :, :, :]],
    Fun[[Iterable[Iterable[Iterable[complex]]], int],
        NDArray[complex, :, :, :]],
    # 4d Iterable
    Fun[[Iterable[Iterable[Iterable[Iterable[bool]]]], int],
        NDArray[int, :, :, :, :]],
    Fun[[Iterable[Iterable[Iterable[Iterable[int]]]], int],
        NDArray[int, :, :, :, :]],
    Fun[[Iterable[Iterable[Iterable[Iterable[float]]]], int],
        NDArray[float, :, :, :, :]],
    Fun[[Iterable[Iterable[Iterable[Iterable[complex]]]], int],
        NDArray[complex, :, :, :, :]],
]
_numpy_unary_op_average_axis_signature = Union[
    # no axis
    # 1d
    Fun[[bool], float],
    Fun[[int], float],
    Fun[[float], float],
    Fun[[complex], complex],
    # 1d Iterable
    Fun[[Iterable[bool]], float],
    Fun[[Iterable[int]], float],
    Fun[[Iterable[float]], float],
    Fun[[Iterable[complex]], complex],
    # 2d Iterable
    Fun[[Iterable[Iterable[bool]]], float],
    Fun[[Iterable[Iterable[int]]], float],
    Fun[[Iterable[Iterable[float]]], float],
    Fun[[Iterable[Iterable[complex]]], complex],
    # 3d Iterable
    Fun[[Iterable[Iterable[Iterable[bool]]]], float],
    Fun[[Iterable[Iterable[Iterable[int]]]], float],
    Fun[[Iterable[Iterable[Iterable[float]]]], float],
    Fun[[Iterable[Iterable[Iterable[complex]]]], complex],
    # 4d Iterable
    Fun[[Iterable[Iterable[Iterable[Iterable[bool]]]]], float],
    Fun[[Iterable[Iterable[Iterable[Iterable[int]]]]], float],
    Fun[[Iterable[Iterable[Iterable[Iterable[float]]]]], float],
    Fun[[Iterable[Iterable[Iterable[Iterable[complex]]]]], complex],

    # axis None
    # 1d
    Fun[[bool, None], float],
    Fun[[int, None], float],
    Fun[[float, None], float],
    Fun[[complex, None], complex],
    # 1d Iterable
    Fun[[Iterable[bool], None], float],
    Fun[[Iterable[int], None], float],
    Fun[[Iterable[float], None], float],
    Fun[[Iterable[complex], None], complex],
    # 2d Iterable
    Fun[[Iterable[Iterable[bool]], None], float],
    Fun[[Iterable[Iterable[int]], None], float],
    Fun[[Iterable[Iterable[float]], None], float],
    Fun[[Iterable[Iterable[complex]], None], complex],
    # 3d Iterable
    Fun[[Iterable[Iterable[Iterable[bool]]], None], float],
    Fun[[Iterable[Iterable[Iterable[int]]], None], float],
    Fun[[Iterable[Iterable[Iterable[float]]], None], float],
    Fun[[Iterable[Iterable[Iterable[complex]]], None], complex],
    # 4d Iterable
    Fun[[Iterable[Iterable[Iterable[Iterable[bool]]]], None], float],
    Fun[[Iterable[Iterable[Iterable[Iterable[int]]]], None], float],
    Fun[[Iterable[Iterable[Iterable[Iterable[float]]]], None], float],
    Fun[[Iterable[Iterable[Iterable[Iterable[complex]]]], None], complex],

    # axis
    # 1d
    Fun[[bool, int], float],
    Fun[[int, int], float],
    Fun[[float, int], float],
    Fun[[complex, int], complex],
    # 1d Iterable
    Fun[[Iterable[bool], int], float],
    Fun[[Iterable[int], int], float],
    Fun[[Iterable[float], int], float],
    Fun[[Iterable[complex], int], complex],
    # 2d Iterable
    Fun[[Iterable[Iterable[bool]], int], NDArray[float, :]],
    Fun[[Iterable[Iterable[int]], int], NDArray[float, :]],
    Fun[[Iterable[Iterable[float]], int], NDArray[float, :]],
    Fun[[Iterable[Iterable[complex]], int], NDArray[complex, :]],
    # 3d Iterable
    Fun[[Iterable[Iterable[Iterable[bool]]], int], NDArray[float, :, :]],
    Fun[[Iterable[Iterable[Iterable[int]]], int], NDArray[float, :, :]],
    Fun[[Iterable[Iterable[Iterable[float]]], int], NDArray[float, :, :]],
    Fun[[Iterable[Iterable[Iterable[complex]]], int], NDArray[complex, :, :]],
    # 4d Iterable
    Fun[[Iterable[Iterable[Iterable[Iterable[bool]]]], int],
        NDArray[float, :, :, :]],
    Fun[[Iterable[Iterable[Iterable[Iterable[int]]]], int],
        NDArray[float, :, :, :]],
    Fun[[Iterable[Iterable[Iterable[Iterable[float]]]], int],
        NDArray[float, :, :, :]],
    Fun[[Iterable[Iterable[Iterable[Iterable[complex]]]], int],
        NDArray[complex, :, :, :]],

    # axis None + weight
    # 1d
    Fun[[bool, None, float], float],
    Fun[[int, None, float], float],
    Fun[[float, None, float], float],
    Fun[[complex, None, float], complex],
    # 1d Iterable
    Fun[[Iterable[bool], None, Iterable[float]], float],
    Fun[[Iterable[int], None, Iterable[float]], float],
    Fun[[Iterable[float], None, Iterable[float]], float],
    Fun[[Iterable[complex], None, Iterable[float]], complex],
    # 2d Iterable
    Fun[[Iterable[Iterable[bool]], None, Iterable[float]], float],
    Fun[[Iterable[Iterable[int]], None, Iterable[float]], float],
    Fun[[Iterable[Iterable[float]], None, Iterable[float]], float],
    Fun[[Iterable[Iterable[complex]], None, Iterable[float]], complex],
    # 3d Iterable
    Fun[[Iterable[Iterable[Iterable[bool]]], None, Iterable[float]], float],
    Fun[[Iterable[Iterable[Iterable[int]]], None, Iterable[float]], float],
    Fun[[Iterable[Iterable[Iterable[float]]], None, Iterable[float]], float],
    Fun[[Iterable[Iterable[Iterable[complex]]], None, Iterable[float]],
        complex],
    # 4d Iterable
    Fun[[Iterable[Iterable[Iterable[Iterable[bool]]]], None, Iterable[float]],
        float],
    Fun[[Iterable[Iterable[Iterable[Iterable[int]]]], None, Iterable[float]],
        float],
    Fun[[Iterable[Iterable[Iterable[Iterable[float]]]], None, Iterable[float]],
        float],
    Fun[[Iterable[Iterable[Iterable[Iterable[complex]]]],
         None, Iterable[float]], complex],

    # axis
    # 1d
    Fun[[bool, int, float], float],
    Fun[[int, int, float], float],
    Fun[[float, int, float], float],
    Fun[[complex, int, float], complex],
    # 1d Iterable
    Fun[[Iterable[bool], int, Iterable[float]], float],
    Fun[[Iterable[int], int, Iterable[float]], float],
    Fun[[Iterable[float], int, Iterable[float]], float],
    Fun[[Iterable[complex], int, Iterable[float]], complex],
    # 2d Iterable
    Fun[[Iterable[Iterable[bool]], int, Iterable[Iterable[bool]]],
        NDArray[float, :]],
    Fun[[Iterable[Iterable[int]], int, Iterable[Iterable[int]]],
        NDArray[float, :]],
    Fun[[Iterable[Iterable[float]], int, Iterable[
        Iterable[float]]], NDArray[float, :]],
    Fun[[Iterable[Iterable[complex]], int, Iterable[
        Iterable[complex]]], NDArray[complex, :]],
    # 3d Iterable
    Fun[[Iterable[Iterable[Iterable[bool]]], int, Iterable[
        Iterable[Iterable[bool]]]], NDArray[float, :, :]],
    Fun[[Iterable[Iterable[Iterable[int]]], int, Iterable[
        Iterable[Iterable[int]]]], NDArray[float, :, :]],
    Fun[[Iterable[Iterable[Iterable[float]]], int, Iterable[
        Iterable[Iterable[float]]]], NDArray[float, :, :]],
    Fun[[Iterable[Iterable[Iterable[complex]]], int, Iterable[
        Iterable[Iterable[complex]]]], NDArray[complex, :, :]],
    # 4d Iterable
    Fun[[Iterable[Iterable[Iterable[Iterable[bool]]]], int, Iterable[
        Iterable[Iterable[Iterable[bool]]]]], NDArray[float, :, :, :]],
    Fun[[Iterable[Iterable[Iterable[Iterable[int]]]], int, Iterable[
        Iterable[Iterable[Iterable[int]]]]], NDArray[float, :, :, :]],
    Fun[[Iterable[Iterable[Iterable[Iterable[float]]]], int, Iterable[
        Iterable[Iterable[Iterable[float]]]]], NDArray[float, :, :, :]],
    Fun[[Iterable[Iterable[Iterable[Iterable[complex]]]], int, Iterable[
        Iterable[Iterable[Iterable[complex]]]]], NDArray[complex, :, :, :]],

]

_numpy_unary_op_bool_axis_signature = Union[
    # no axis
    # 1d
    Fun[[bool], bool],
    Fun[[int], bool],
    Fun[[float], bool],
    Fun[[complex], bool],
    # 1d Iterable
    Fun[[Iterable[bool]], bool],
    Fun[[Iterable[int]], bool],
    Fun[[Iterable[float]], bool],
    Fun[[Iterable[complex]], bool],
    # 2d Iterable
    Fun[[Iterable[Iterable[bool]]], bool],
    Fun[[Iterable[Iterable[int]]], bool],
    Fun[[Iterable[Iterable[float]]], bool],
    Fun[[Iterable[Iterable[complex]]], bool],
    # 3d Iterable
    Fun[[Iterable[Iterable[Iterable[bool]]]], bool],
    Fun[[Iterable[Iterable[Iterable[int]]]], bool],
    Fun[[Iterable[Iterable[Iterable[float]]]], bool],
    Fun[[Iterable[Iterable[Iterable[complex]]]], bool],
    # 4d Iterable
    Fun[[Iterable[Iterable[Iterable[Iterable[bool]]]]], bool],
    Fun[[Iterable[Iterable[Iterable[Iterable[int]]]]], bool],
    Fun[[Iterable[Iterable[Iterable[Iterable[float]]]]], bool],
    Fun[[Iterable[Iterable[Iterable[Iterable[complex]]]]], bool],

    # axis
    # 1d
    Fun[[bool, int], bool],
    Fun[[int, int], bool],
    Fun[[float, int], bool],
    Fun[[complex, int], bool],
    # 1d Iterable
    Fun[[Iterable[bool], int], bool],
    Fun[[Iterable[int], int], bool],
    Fun[[Iterable[float], int], bool],
    Fun[[Iterable[complex], int], bool],
    # 2d Iterable
    Fun[[Iterable[Iterable[bool]], int], NDArray[bool, :]],
    Fun[[Iterable[Iterable[int]], int], NDArray[bool, :]],
    Fun[[Iterable[Iterable[float]], int], NDArray[bool, :]],
    Fun[[Iterable[Iterable[complex]], int], NDArray[bool, :]],
    # 3d Iterable
    Fun[[Iterable[Iterable[Iterable[bool]]], int], NDArray[bool, :, :]],
    Fun[[Iterable[Iterable[Iterable[int]]], int], NDArray[bool, :, :]],
    Fun[[Iterable[Iterable[Iterable[float]]], int], NDArray[bool, :, :]],
    Fun[[Iterable[Iterable[Iterable[complex]]], int], NDArray[bool, :, :]],
    # 4d Iterable
    Fun[[Iterable[Iterable[Iterable[Iterable[bool]]]], int],
        NDArray[bool, :, :, :]],
    Fun[[Iterable[Iterable[Iterable[Iterable[int]]]], int],
        NDArray[bool, :, :, :]],
    Fun[[Iterable[Iterable[Iterable[Iterable[float]]]], int],
        NDArray[bool, :, :, :]],
    Fun[[Iterable[Iterable[Iterable[Iterable[complex]]]], int],
        NDArray[bool, :, :, :]],
]


_numpy_binary_op_signature = Union[
    # 1d
    Fun[[bool, bool], bool],
    Fun[[int, int], int],
    Fun[[float, float], float],
    Fun[[complex, complex], complex],

    # 1d Iterable
    Fun[[Iterable[bool], Iterable[bool]], NDArray[bool, :]],
    Fun[[Iterable[bool], bool], NDArray[bool, :]],
    Fun[[bool, Iterable[bool]], NDArray[bool, :]],
    Fun[[Iterable[int], Iterable[int]], NDArray[int, :]],
    Fun[[Iterable[int], int], NDArray[int, :]],
    Fun[[int, Iterable[int]], NDArray[int, :]],
    Fun[[Iterable[float], Iterable[float]], NDArray[float, :]],
    Fun[[Iterable[float], float], NDArray[float, :]],
    Fun[[float, Iterable[float]], NDArray[float, :]],
    Fun[[Iterable[complex], Iterable[complex]], NDArray[complex, :]],
    Fun[[Iterable[complex], complex], NDArray[complex, :]],
    Fun[[complex, Iterable[complex]], NDArray[complex, :]],

    # 2d Iterable
    Fun[[Iterable[Iterable[bool]], Iterable[Iterable[bool]]],
        NDArray[bool, :, :]],
    Fun[[Iterable[bool], Iterable[Iterable[bool]]], NDArray[bool, :, :]],
    Fun[[Iterable[Iterable[bool]], Iterable[bool]], NDArray[bool, :, :]],
    Fun[[bool, Iterable[Iterable[bool]]], NDArray[bool, :, :]],
    Fun[[Iterable[Iterable[bool]], bool], NDArray[bool, :, :]],
    Fun[[Iterable[Iterable[int]], Iterable[Iterable[int]]],
        NDArray[int, :, :]],
    Fun[[Iterable[int], Iterable[Iterable[int]]], NDArray[int, :, :]],
    Fun[[Iterable[Iterable[int]], Iterable[int]], NDArray[int, :, :]],
    Fun[[int, Iterable[Iterable[int]]], NDArray[int, :, :]],
    Fun[[Iterable[Iterable[int]], int], NDArray[int, :, :]],
    Fun[[Iterable[Iterable[float]], Iterable[Iterable[float]]],
        NDArray[float, :, :]],
    Fun[[Iterable[float], Iterable[Iterable[float]]], NDArray[float, :, :]],
    Fun[[Iterable[Iterable[float]], Iterable[float]], NDArray[float, :, :]],
    Fun[[float, Iterable[Iterable[float]]], NDArray[float, :, :]],
    Fun[[Iterable[Iterable[float]], float], NDArray[float, :, :]],
    Fun[[Iterable[Iterable[complex]], Iterable[
        Iterable[complex]]], NDArray[complex, :, :]],
    Fun[[Iterable[complex], Iterable[Iterable[complex]]],
        NDArray[complex, :, :]],
    Fun[[Iterable[Iterable[complex]], Iterable[complex]],
        NDArray[complex, :, :]],
    Fun[[complex, Iterable[Iterable[complex]]], NDArray[complex, :, :]],
    Fun[[Iterable[Iterable[complex]], complex], NDArray[complex, :, :]],

    # 3d Iterable
    Fun[[Iterable[Iterable[Iterable[bool]]], Iterable[
        Iterable[Iterable[bool]]]], NDArray[bool, :, :, :]],
    Fun[[Iterable[Iterable[bool]], Iterable[
        Iterable[Iterable[bool]]]], NDArray[bool, :, :, :]],
    Fun[[Iterable[bool], Iterable[Iterable[Iterable[bool]]]],
        NDArray[bool, :, :, :]],
    Fun[[bool, Iterable[Iterable[Iterable[bool]]]], NDArray[bool, :, :, :]],
    Fun[[Iterable[Iterable[Iterable[bool]]], Iterable[
        Iterable[bool]]], NDArray[bool, :, :, :]],
    Fun[[Iterable[Iterable[Iterable[bool]]], Iterable[bool]],
        NDArray[bool, :, :, :]],
    Fun[[Iterable[Iterable[Iterable[bool]]], bool], NDArray[bool, :, :, :]],
    Fun[[Iterable[Iterable[Iterable[int]]], Iterable[
        Iterable[Iterable[int]]]], NDArray[int, :, :, :]],
    Fun[[Iterable[Iterable[int]], Iterable[
        Iterable[Iterable[int]]]], NDArray[int, :, :, :]],
    Fun[[Iterable[int], Iterable[Iterable[Iterable[int]]]],
        NDArray[int, :, :, :]],
    Fun[[int, Iterable[Iterable[Iterable[int]]]], NDArray[int, :, :, :]],
    Fun[[Iterable[Iterable[Iterable[int]]], Iterable[
        Iterable[int]]], NDArray[int, :, :, :]],
    Fun[[Iterable[Iterable[Iterable[int]]], Iterable[int]],
        NDArray[int, :, :, :]],
    Fun[[Iterable[Iterable[Iterable[int]]], int],
        NDArray[int, :, :, :]],
    Fun[[Iterable[Iterable[Iterable[float]]], Iterable[
        Iterable[Iterable[float]]]], NDArray[float, :, :, :]],
    Fun[[Iterable[Iterable[float]], Iterable[
        Iterable[Iterable[float]]]], NDArray[float, :, :, :]],
    Fun[[Iterable[float], Iterable[Iterable[Iterable[float]]]],
        NDArray[float, :, :, :]],
    Fun[[float, Iterable[Iterable[Iterable[float]]]], NDArray[float, :, :, :]],
    Fun[[Iterable[Iterable[Iterable[float]]], Iterable[
        Iterable[float]]], NDArray[float, :, :, :]],
    Fun[[Iterable[Iterable[Iterable[float]]],
         Iterable[float]], NDArray[float, :, :, :]],
    Fun[[Iterable[Iterable[Iterable[float]]], float], NDArray[float, :, :, :]],
    Fun[[Iterable[Iterable[Iterable[complex]]], Iterable[
        Iterable[Iterable[complex]]]], NDArray[complex, :, :, :]],
    Fun[[Iterable[Iterable[complex]], Iterable[
        Iterable[Iterable[complex]]]], NDArray[complex, :, :, :]],
    Fun[[Iterable[complex], Iterable[Iterable[Iterable[complex]]]],
        NDArray[complex, :, :, :]],
    Fun[[complex, Iterable[Iterable[Iterable[complex]]]],
        NDArray[complex, :, :, :]],
    Fun[[Iterable[Iterable[Iterable[complex]]], Iterable[
        Iterable[complex]]], NDArray[complex, :, :, :]],
    Fun[[Iterable[Iterable[Iterable[complex]]],
         Iterable[complex]], NDArray[complex, :, :, :]],
    Fun[[Iterable[Iterable[Iterable[complex]]], complex],
        NDArray[complex, :, :, :]],
]
_numpy_binary_op_bool_signature = Union[
    # 1d
    Fun[[bool, bool], bool],
    Fun[[int, int], bool],
    Fun[[float, float], bool],
    Fun[[complex, complex], bool],

    # 1d Iterable
    Fun[[Iterable[bool], Iterable[bool]], NDArray[bool, :]],
    Fun[[Iterable[bool], bool], NDArray[bool, :]],
    Fun[[bool, Iterable[bool]], NDArray[bool, :]],
    Fun[[Iterable[int], Iterable[int]], NDArray[bool, :]],
    Fun[[Iterable[int], int], NDArray[bool, :]],
    Fun[[int, Iterable[int]], NDArray[bool, :]],
    Fun[[Iterable[float], Iterable[float]], NDArray[bool, :]],
    Fun[[Iterable[float], float], NDArray[bool, :]],
    Fun[[float, Iterable[float]], NDArray[bool, :]],
    Fun[[Iterable[complex], Iterable[complex]], NDArray[bool, :]],
    Fun[[Iterable[complex], complex], NDArray[bool, :]],
    Fun[[complex, Iterable[complex]], NDArray[bool, :]],

    # 2d Iterable
    Fun[[Iterable[Iterable[bool]], Iterable[Iterable[bool]]],
        NDArray[bool, :, :]],
    Fun[[Iterable[bool], Iterable[Iterable[bool]]], NDArray[bool, :, :]],
    Fun[[Iterable[Iterable[bool]], Iterable[bool]], NDArray[bool, :, :]],
    Fun[[bool, Iterable[Iterable[bool]]], NDArray[bool, :, :]],
    Fun[[Iterable[Iterable[bool]], bool], NDArray[bool, :, :]],
    Fun[[Iterable[Iterable[int]], Iterable[Iterable[int]]],
        NDArray[bool, :, :]],
    Fun[[Iterable[int], Iterable[Iterable[int]]], NDArray[bool, :, :]],
    Fun[[Iterable[Iterable[int]], Iterable[int]], NDArray[bool, :, :]],
    Fun[[int, Iterable[Iterable[int]]], NDArray[bool, :, :]],
    Fun[[Iterable[Iterable[int]], int], NDArray[bool, :, :]],
    Fun[[Iterable[Iterable[float]], Iterable[Iterable[float]]],
        NDArray[bool, :, :]],
    Fun[[Iterable[float], Iterable[Iterable[float]]], NDArray[bool, :, :]],
    Fun[[Iterable[Iterable[float]], Iterable[float]], NDArray[bool, :, :]],
    Fun[[float, Iterable[Iterable[float]]], NDArray[bool, :, :]],
    Fun[[Iterable[Iterable[float]], float], NDArray[bool, :, :]],
    Fun[[Iterable[Iterable[complex]], Iterable[
        Iterable[complex]]], NDArray[bool, :, :]],
    Fun[[Iterable[complex], Iterable[Iterable[complex]]],
        NDArray[bool, :, :]],
    Fun[[Iterable[Iterable[complex]], Iterable[complex]],
        NDArray[bool, :, :]],
    Fun[[complex, Iterable[Iterable[complex]]], NDArray[bool, :, :]],
    Fun[[Iterable[Iterable[complex]], complex], NDArray[bool, :, :]],

    # 3d Iterable
    Fun[[Iterable[Iterable[Iterable[bool]]], Iterable[
        Iterable[Iterable[bool]]]], NDArray[bool, :, :, :]],
    Fun[[Iterable[Iterable[bool]], Iterable[
        Iterable[Iterable[bool]]]], NDArray[bool, :, :, :]],
    Fun[[Iterable[bool], Iterable[Iterable[Iterable[bool]]]],
        NDArray[bool, :, :, :]],
    Fun[[bool, Iterable[Iterable[Iterable[bool]]]], NDArray[bool, :, :, :]],
    Fun[[Iterable[Iterable[Iterable[bool]]], Iterable[
        Iterable[bool]]], NDArray[bool, :, :, :]],
    Fun[[Iterable[Iterable[Iterable[bool]]], Iterable[bool]],
        NDArray[bool, :, :, :]],
    Fun[[Iterable[Iterable[Iterable[bool]]], bool], NDArray[bool, :, :, :]],
    Fun[[Iterable[Iterable[Iterable[int]]], Iterable[
        Iterable[Iterable[int]]]], NDArray[bool, :, :, :]],
    Fun[[Iterable[Iterable[int]], Iterable[
        Iterable[Iterable[int]]]], NDArray[bool, :, :, :]],
    Fun[[Iterable[int], Iterable[Iterable[Iterable[int]]]],
        NDArray[bool, :, :, :]],
    Fun[[int, Iterable[Iterable[Iterable[int]]]], NDArray[bool, :, :, :]],
    Fun[[Iterable[Iterable[Iterable[int]]], Iterable[
        Iterable[int]]], NDArray[bool, :, :, :]],
    Fun[[Iterable[Iterable[Iterable[int]]], Iterable[int]],
        NDArray[bool, :, :, :]],
    Fun[[Iterable[Iterable[Iterable[int]]], int],
        NDArray[bool, :, :, :]],
    Fun[[Iterable[Iterable[Iterable[float]]], Iterable[
        Iterable[Iterable[float]]]], NDArray[bool, :, :, :]],
    Fun[[Iterable[Iterable[float]], Iterable[
        Iterable[Iterable[float]]]], NDArray[bool, :, :, :]],
    Fun[[Iterable[float], Iterable[Iterable[Iterable[float]]]],
        NDArray[bool, :, :, :]],
    Fun[[float, Iterable[Iterable[Iterable[float]]]], NDArray[bool, :, :, :]],
    Fun[[Iterable[Iterable[Iterable[float]]], Iterable[
        Iterable[float]]], NDArray[bool, :, :, :]],
    Fun[[Iterable[Iterable[Iterable[float]]],
         Iterable[float]], NDArray[bool, :, :, :]],
    Fun[[Iterable[Iterable[Iterable[float]]], float], NDArray[bool, :, :, :]],
    Fun[[Iterable[Iterable[Iterable[complex]]], Iterable[
        Iterable[Iterable[complex]]]], NDArray[bool, :, :, :]],
    Fun[[Iterable[Iterable[complex]], Iterable[
        Iterable[Iterable[complex]]]], NDArray[bool, :, :, :]],
    Fun[[Iterable[complex], Iterable[Iterable[Iterable[complex]]]],
        NDArray[bool, :, :, :]],
    Fun[[complex, Iterable[Iterable[Iterable[complex]]]],
        NDArray[bool, :, :, :]],
    Fun[[Iterable[Iterable[Iterable[complex]]], Iterable[
        Iterable[complex]]], NDArray[bool, :, :, :]],
    Fun[[Iterable[Iterable[Iterable[complex]]],
         Iterable[complex]], NDArray[bool, :, :, :]],
    Fun[[Iterable[Iterable[Iterable[complex]]], complex],
        NDArray[bool, :, :, :]],
]
_numpy_binary_op_float_signature = Union[
    # 1d
    Fun[[bool, bool], float],
    Fun[[int, int], float],
    Fun[[float, float], float],
    Fun[[complex, complex], complex],

    # 1d Iterable
    Fun[[Iterable[bool], Iterable[bool]], NDArray[float, :]],
    Fun[[Iterable[bool], bool], NDArray[float, :]],
    Fun[[bool, Iterable[bool]], NDArray[float, :]],
    Fun[[Iterable[int], Iterable[int]], NDArray[float, :]],
    Fun[[Iterable[int], int], NDArray[float, :]],
    Fun[[int, Iterable[int]], NDArray[float, :]],
    Fun[[Iterable[float], Iterable[float]], NDArray[float, :]],
    Fun[[Iterable[float], float], NDArray[float, :]],
    Fun[[float, Iterable[float]], NDArray[float, :]],
    Fun[[Iterable[complex], Iterable[complex]], NDArray[complex, :]],
    Fun[[Iterable[complex], complex], NDArray[complex, :]],
    Fun[[complex, Iterable[complex]], NDArray[complex, :]],

    # 2d Iterable
    Fun[[Iterable[Iterable[bool]], Iterable[Iterable[bool]]],
        NDArray[float, :, :]],
    Fun[[Iterable[bool], Iterable[Iterable[bool]]], NDArray[float, :, :]],
    Fun[[Iterable[Iterable[bool]], Iterable[bool]], NDArray[float, :, :]],
    Fun[[bool, Iterable[Iterable[bool]]], NDArray[float, :, :]],
    Fun[[Iterable[Iterable[bool]], bool], NDArray[float, :, :]],
    Fun[[Iterable[Iterable[int]], Iterable[Iterable[int]]],
        NDArray[float, :, :]],
    Fun[[Iterable[int], Iterable[Iterable[int]]], NDArray[float, :, :]],
    Fun[[Iterable[Iterable[int]], Iterable[int]], NDArray[float, :, :]],
    Fun[[int, Iterable[Iterable[int]]], NDArray[float, :, :]],
    Fun[[Iterable[Iterable[int]], int], NDArray[float, :, :]],
    Fun[[Iterable[Iterable[float]], Iterable[Iterable[float]]],
        NDArray[float, :, :]],
    Fun[[Iterable[float], Iterable[Iterable[float]]], NDArray[float, :, :]],
    Fun[[Iterable[Iterable[float]], Iterable[float]], NDArray[float, :, :]],
    Fun[[float, Iterable[Iterable[float]]], NDArray[float, :, :]],
    Fun[[Iterable[Iterable[float]], float], NDArray[float, :, :]],
    Fun[[Iterable[Iterable[complex]], Iterable[
        Iterable[complex]]], NDArray[complex, :, :]],
    Fun[[Iterable[complex], Iterable[Iterable[complex]]],
        NDArray[complex, :, :]],
    Fun[[Iterable[Iterable[complex]], Iterable[complex]],
        NDArray[complex, :, :]],
    Fun[[complex, Iterable[Iterable[complex]]], NDArray[complex, :, :]],
    Fun[[Iterable[Iterable[complex]], complex], NDArray[complex, :, :]],

    # 3d Iterable
    Fun[[Iterable[Iterable[Iterable[bool]]], Iterable[
        Iterable[Iterable[bool]]]], NDArray[float, :, :, :]],
    Fun[[Iterable[Iterable[bool]], Iterable[
        Iterable[Iterable[bool]]]], NDArray[float, :, :, :]],
    Fun[[Iterable[bool], Iterable[Iterable[Iterable[bool]]]],
        NDArray[float, :, :, :]],
    Fun[[bool, Iterable[Iterable[Iterable[bool]]]], NDArray[float, :, :, :]],
    Fun[[Iterable[Iterable[Iterable[bool]]], Iterable[
        Iterable[bool]]], NDArray[float, :, :, :]],
    Fun[[Iterable[Iterable[Iterable[bool]]],
         Iterable[bool]], NDArray[float, :, :, :]],
    Fun[[Iterable[Iterable[Iterable[bool]]], bool], NDArray[float, :, :, :]],
    Fun[[Iterable[Iterable[Iterable[int]]], Iterable[
        Iterable[Iterable[int]]]], NDArray[float, :, :, :]],
    Fun[[Iterable[Iterable[int]], Iterable[Iterable[Iterable[int]]]],
        NDArray[float, :, :, :]],
    Fun[[Iterable[int], Iterable[Iterable[Iterable[int]]]],
        NDArray[float, :, :, :]],
    Fun[[int, Iterable[Iterable[Iterable[int]]]], NDArray[float, :, :, :]],
    Fun[[Iterable[Iterable[Iterable[int]]], Iterable[
        Iterable[int]]], NDArray[float, :, :, :]],
    Fun[[Iterable[Iterable[Iterable[int]]], Iterable[int]],
        NDArray[float, :, :, :]],
    Fun[[Iterable[Iterable[Iterable[int]]], int], NDArray[float, :, :, :]],
    Fun[[Iterable[Iterable[Iterable[float]]], Iterable[
        Iterable[Iterable[float]]]], NDArray[float, :, :, :]],
    Fun[[Iterable[Iterable[float]], Iterable[
        Iterable[Iterable[float]]]], NDArray[float, :, :, :]],
    Fun[[Iterable[float], Iterable[Iterable[Iterable[float]]]],
        NDArray[float, :, :, :]],
    Fun[[float, Iterable[Iterable[Iterable[float]]]], NDArray[float, :, :, :]],
    Fun[[Iterable[Iterable[Iterable[float]]], Iterable[
        Iterable[float]]], NDArray[float, :, :, :]],
    Fun[[Iterable[Iterable[Iterable[float]]],
         Iterable[float]], NDArray[float, :, :, :]],
    Fun[[Iterable[Iterable[Iterable[float]]], float], NDArray[float, :, :, :]],
    Fun[[Iterable[Iterable[Iterable[complex]]], Iterable[
        Iterable[Iterable[complex]]]], NDArray[complex, :, :, :]],
    Fun[[Iterable[Iterable[complex]], Iterable[
        Iterable[Iterable[complex]]]], NDArray[complex, :, :, :]],
    Fun[[Iterable[complex], Iterable[Iterable[Iterable[complex]]]],
        NDArray[complex, :, :, :]],
    Fun[[complex, Iterable[Iterable[Iterable[complex]]]],
        NDArray[complex, :, :, :]],
    Fun[[Iterable[Iterable[Iterable[complex]]], Iterable[
        Iterable[complex]]], NDArray[complex, :, :, :]],
    Fun[[Iterable[Iterable[Iterable[complex]]],
         Iterable[complex]], NDArray[complex, :, :, :]],
    Fun[[Iterable[Iterable[Iterable[complex]]], complex],
        NDArray[complex, :, :, :]],
]
_numpy_ternary_op_signature = Union[
    # scalar
    Fun[[int, int, int], int],
    Fun[[float, float, float], float],
    Fun[[complex, complex, complex], complex],

    # 1D
    Fun[[Iterable[int], int, int], NDArray[int, :]],
    Fun[[Iterable[int], Iterable[int], int], NDArray[int, :]],
    Fun[[Iterable[int], int, Iterable[int]], NDArray[int, :]],
    Fun[[Iterable[int], Iterable[int], Iterable[int]], NDArray[int, :]],

    Fun[[Iterable[float], float, float], NDArray[float, :]],
    Fun[[Iterable[float], Iterable[float], float], NDArray[float, :]],
    Fun[[Iterable[float], float, Iterable[float]], NDArray[float, :]],
    Fun[[Iterable[float], Iterable[float], Iterable[float]],
        NDArray[float, :]],

    Fun[[Iterable[complex], complex, complex], NDArray[complex, :]],
    Fun[[Iterable[complex], Iterable[complex], complex], NDArray[complex, :]],
    Fun[[Iterable[complex], complex, Iterable[complex]], NDArray[complex, :]],
    Fun[[Iterable[complex], Iterable[complex],
         Iterable[complex]], NDArray[complex, :]],

    # 2D
    Fun[[Iterable[Iterable[int]], int, int], NDArray[int, :, :]],

    Fun[[Iterable[Iterable[int]], Iterable[int], int], NDArray[int, :, :]],
    Fun[[Iterable[Iterable[int]], Iterable[int], Iterable[int]],
        NDArray[int, :, :]],
    Fun[[Iterable[Iterable[int]], int, Iterable[int]], NDArray[int, :, :]],

    Fun[[Iterable[Iterable[int]], Iterable[Iterable[int]], int],
        NDArray[int, :, :]],
    Fun[[Iterable[Iterable[int]], int, Iterable[Iterable[int]]],
        NDArray[int, :, :]],
    Fun[[Iterable[Iterable[int]], Iterable[Iterable[int]],
         Iterable[int]], NDArray[int, :, :]],
    Fun[[Iterable[Iterable[int]], Iterable[int],
         Iterable[Iterable[int]]], NDArray[int, :, :]],
    Fun[[Iterable[Iterable[int]], Iterable[Iterable[int]],
         Iterable[Iterable[int]]], NDArray[int, :, :]],

    Fun[[Iterable[Iterable[float]], float, float], NDArray[float, :, :]],

    Fun[[Iterable[Iterable[float]], Iterable[float], float],
        NDArray[float, :, :]],
    Fun[[Iterable[Iterable[float]], Iterable[float],
         Iterable[float]], NDArray[float, :, :]],
    Fun[[Iterable[Iterable[float]], float, Iterable[float]],
        NDArray[float, :, :]],

    Fun[[Iterable[Iterable[float]], Iterable[
        Iterable[float]], float], NDArray[float, :, :]],
    Fun[[Iterable[Iterable[float]], float, Iterable[
        Iterable[float]]], NDArray[float, :, :]],
    Fun[[Iterable[Iterable[float]], Iterable[Iterable[float]],
         Iterable[float]], NDArray[float, :, :]],
    Fun[[Iterable[Iterable[float]], Iterable[float],
         Iterable[Iterable[float]]], NDArray[float, :, :]],
    Fun[[Iterable[Iterable[float]], Iterable[Iterable[float]],
         Iterable[Iterable[float]]], NDArray[float, :, :]],

    Fun[[Iterable[Iterable[complex]], complex, complex],
        NDArray[complex, :, :]],

    Fun[[Iterable[Iterable[complex]], Iterable[
        complex], complex], NDArray[complex, :, :]],
    Fun[[Iterable[Iterable[complex]], Iterable[complex],
         Iterable[complex]], NDArray[complex, :, :]],
    Fun[[Iterable[Iterable[complex]], complex,
         Iterable[complex]], NDArray[complex, :, :]],

    Fun[[Iterable[Iterable[complex]], Iterable[
        Iterable[complex]], complex], NDArray[complex, :, :]],
    Fun[[Iterable[Iterable[complex]], complex, Iterable[
        Iterable[complex]]], NDArray[complex, :, :]],
    Fun[[Iterable[Iterable[complex]], Iterable[Iterable[complex]],
         Iterable[complex]], NDArray[complex, :, :]],
    Fun[[Iterable[Iterable[complex]], Iterable[complex],
         Iterable[Iterable[complex]]], NDArray[complex, :, :]],
    Fun[[Iterable[Iterable[complex]], Iterable[Iterable[complex]],
         Iterable[Iterable[complex]]], NDArray[complex, :, :]],
]

_numpy_int_binary_op_signature = Union[
    # 1d
    Fun[[bool, bool], bool],
    Fun[[int, int], int],

    # 1d Iterable
    Fun[[Iterable[bool], Iterable[bool]], NDArray[bool, :]],
    Fun[[Iterable[bool], bool], NDArray[bool, :]],
    Fun[[bool, Iterable[bool]], NDArray[bool, :]],
    Fun[[Iterable[int], Iterable[int]], NDArray[int, :]],
    Fun[[Iterable[int], int], NDArray[int, :]],
    Fun[[int, Iterable[int]], NDArray[int, :]],

    # 2d Iterable
    Fun[[Iterable[Iterable[bool]], Iterable[Iterable[bool]]],
        NDArray[bool, :, :]],
    Fun[[Iterable[bool], Iterable[Iterable[bool]]], NDArray[bool, :, :]],
    Fun[[Iterable[Iterable[bool]], Iterable[bool]], NDArray[bool, :, :]],
    Fun[[bool, Iterable[Iterable[bool]]], NDArray[bool, :, :]],
    Fun[[Iterable[Iterable[bool]], bool], NDArray[bool, :, :]],
    Fun[[Iterable[Iterable[int]], Iterable[Iterable[int]]],
        NDArray[int, :, :]],
    Fun[[Iterable[int], Iterable[Iterable[int]]], NDArray[int, :, :]],
    Fun[[Iterable[Iterable[int]], Iterable[int]], NDArray[int, :, :]],
    Fun[[int, Iterable[Iterable[int]]], NDArray[int, :, :]],
    Fun[[Iterable[Iterable[int]], int], NDArray[int, :, :]],

    # 3d Iterable
    Fun[[Iterable[Iterable[Iterable[bool]]], Iterable[
        Iterable[Iterable[bool]]]], NDArray[bool, :, :, :]],
    Fun[[Iterable[Iterable[bool]], Iterable[
        Iterable[Iterable[bool]]]], NDArray[bool, :, :, :]],
    Fun[[Iterable[bool], Iterable[Iterable[Iterable[bool]]]],
        NDArray[bool, :, :, :]],
    Fun[[bool, Iterable[Iterable[Iterable[bool]]]], NDArray[bool, :, :, :]],
    Fun[[Iterable[Iterable[Iterable[bool]]], Iterable[
        Iterable[bool]]], NDArray[bool, :, :, :]],
    Fun[[Iterable[Iterable[Iterable[bool]]], Iterable[bool]],
        NDArray[bool, :, :, :]],
    Fun[[Iterable[Iterable[Iterable[bool]]], bool], NDArray[bool, :, :, :]],
    Fun[[Iterable[Iterable[Iterable[int]]], Iterable[
        Iterable[Iterable[int]]]], NDArray[int, :, :, :]],
    Fun[[Iterable[Iterable[int]], Iterable[
        Iterable[Iterable[int]]]], NDArray[int, :, :, :]],
    Fun[[Iterable[int], Iterable[Iterable[Iterable[int]]]],
        NDArray[int, :, :, :]],
    Fun[[int, Iterable[Iterable[Iterable[int]]]], NDArray[int, :, :, :]],
    Fun[[Iterable[Iterable[Iterable[int]]], Iterable[
        Iterable[int]]], NDArray[int, :, :, :]],
    Fun[[Iterable[Iterable[Iterable[int]]], Iterable[int]],
        NDArray[int, :, :, :]],
    Fun[[Iterable[Iterable[Iterable[int]]], int], NDArray[int, :, :, :]],
]

_numpy_binary_op_float_no_complex_signature = Union[
    # 1d
    Fun[[bool, bool], float],
    Fun[[int, int], float],
    Fun[[float, float], float],

    # 1d Iterable
    Fun[[Iterable[bool], Iterable[bool]], NDArray[float, :]],
    Fun[[Iterable[bool], bool], NDArray[float, :]],
    Fun[[bool, Iterable[bool]], NDArray[float, :]],
    Fun[[Iterable[int], Iterable[int]], NDArray[float, :]],
    Fun[[Iterable[int], int], NDArray[float, :]],
    Fun[[int, Iterable[int]], NDArray[float, :]],
    Fun[[Iterable[float], Iterable[float]], NDArray[float, :]],
    Fun[[Iterable[float], float], NDArray[float, :]],
    Fun[[float, Iterable[float]], NDArray[float, :]],

    # 2d Iterable
    Fun[[Iterable[Iterable[bool]], Iterable[Iterable[bool]]],
        NDArray[float, :, :]],
    Fun[[Iterable[bool], Iterable[Iterable[bool]]], NDArray[float, :, :]],
    Fun[[Iterable[Iterable[bool]], Iterable[bool]], NDArray[float, :, :]],
    Fun[[bool, Iterable[Iterable[bool]]], NDArray[float, :, :]],
    Fun[[Iterable[Iterable[bool]], bool], NDArray[float, :, :]],
    Fun[[Iterable[Iterable[int]], Iterable[Iterable[int]]],
        NDArray[float, :, :]],
    Fun[[Iterable[int], Iterable[Iterable[int]]], NDArray[float, :, :]],
    Fun[[Iterable[Iterable[int]], Iterable[int]], NDArray[float, :, :]],
    Fun[[int, Iterable[Iterable[int]]], NDArray[float, :, :]],
    Fun[[Iterable[Iterable[int]], int], NDArray[float, :, :]],
    Fun[[Iterable[Iterable[float]], Iterable[Iterable[float]]],
        NDArray[float, :, :]],
    Fun[[Iterable[float], Iterable[Iterable[float]]], NDArray[float, :, :]],
    Fun[[Iterable[Iterable[float]], Iterable[float]], NDArray[float, :, :]],
    Fun[[float, Iterable[Iterable[float]]], NDArray[float, :, :]],
    Fun[[Iterable[Iterable[float]], float], NDArray[float, :, :]],

    # 3d Iterable
    Fun[[Iterable[Iterable[Iterable[bool]]], Iterable[
        Iterable[Iterable[bool]]]], NDArray[float, :, :, :]],
    Fun[[Iterable[Iterable[bool]], Iterable[
        Iterable[Iterable[bool]]]], NDArray[float, :, :, :]],
    Fun[[Iterable[bool], Iterable[Iterable[Iterable[bool]]]],
        NDArray[float, :, :, :]],
    Fun[[bool, Iterable[Iterable[Iterable[bool]]]], NDArray[float, :, :, :]],
    Fun[[Iterable[Iterable[Iterable[bool]]], Iterable[
        Iterable[bool]]], NDArray[float, :, :, :]],
    Fun[[Iterable[Iterable[Iterable[bool]]],
         Iterable[bool]], NDArray[float, :, :, :]],
    Fun[[Iterable[Iterable[Iterable[bool]]], bool], NDArray[float, :, :, :]],
    Fun[[Iterable[Iterable[Iterable[int]]], Iterable[
        Iterable[Iterable[int]]]], NDArray[float, :, :, :]],
    Fun[[Iterable[Iterable[int]], Iterable[Iterable[Iterable[int]]]],
        NDArray[float, :, :, :]],
    Fun[[Iterable[int], Iterable[Iterable[Iterable[int]]]],
        NDArray[float, :, :, :]],
    Fun[[int, Iterable[Iterable[Iterable[int]]]], NDArray[float, :, :, :]],
    Fun[[Iterable[Iterable[Iterable[int]]], Iterable[
        Iterable[int]]], NDArray[float, :, :, :]],
    Fun[[Iterable[Iterable[Iterable[int]]], Iterable[int]],
        NDArray[float, :, :, :]],
    Fun[[Iterable[Iterable[Iterable[int]]], int], NDArray[float, :, :, :]],
    Fun[[Iterable[Iterable[Iterable[float]]], Iterable[
        Iterable[Iterable[float]]]], NDArray[float, :, :, :]],
    Fun[[Iterable[Iterable[float]], Iterable[
        Iterable[Iterable[float]]]], NDArray[float, :, :, :]],
    Fun[[Iterable[float], Iterable[Iterable[Iterable[float]]]],
        NDArray[float, :, :, :]],
    Fun[[float, Iterable[Iterable[Iterable[float]]]], NDArray[float, :, :, :]],
    Fun[[Iterable[Iterable[Iterable[float]]], Iterable[
        Iterable[float]]], NDArray[float, :, :, :]],
    Fun[[Iterable[Iterable[Iterable[float]]],
         Iterable[float]], NDArray[float, :, :, :]],
    Fun[[Iterable[Iterable[Iterable[float]]], float], NDArray[float, :, :, :]],
]

_numpy_allclose_signature = Union[
    _numpy_binary_op_signature.__args__ +
    tuple([Fun[c.__args__[:-1] + (float,), c.__args__[-1]]
           for c in _numpy_unary_op_signature.__args__] +
          [Fun[c.__args__[:-1] + (float, float), c.__args__[-1]]
           for c in _numpy_unary_op_signature.__args__] +
          [Fun[c.__args__[:-1] + (float, float, bool), c.__args__[-1]]
           for c in _numpy_unary_op_signature.__args__]
          )
]

_numpy_around_signature = Union[
    _numpy_unary_op_float_signature.__args__ +
    tuple([Fun[c.__args__[:-1] + (int,), c.__args__[-1]]
           for c in _numpy_unary_op_float_signature.__args__])
]

_functools_reduce_signature = Union[
    Fun[[Fun[[T0, T0], T0], Iterable[T0]], T0],
    Fun[[Fun[[T0, T1], T0], Iterable[T1], T0], T0],
]


def partialsum(seq):
    s = tuple()
    for elt in seq:
        s += elt,
        yield s

_operator_add_signature = Union[
    _numpy_binary_op_signature.__args__ +
    (Fun[[str, str], str],
     Fun[[List[T0], List[T0]], List[T0]],) +
    tuple(Fun[[Tuple[t0], Tuple[t1]], Tuple[t0 + t1]]
          for t0 in partialsum([T0, T1, T2, T3])
          for t1 in partialsum([T4, T5, T6, T7]))
]

_operator_eq_signature = Union[
    _numpy_binary_op_bool_signature.__args__ +
    (Fun[[str, str], bool],
     Fun[[List[T0], List[T0]], bool],
     Fun[[Set[T0], Set[T0]], bool],
     Fun[[T0, None], bool],
     Fun[[None, T0], bool],
     Fun[[Dict[T0, T1], Dict[T0, T1]], bool],) +
    tuple(Fun[[Tuple[t0], Tuple[t1]], Tuple[t0 + t1]]
          for t0 in partialsum([T0, T1, T2, T3])
          for t1 in partialsum([T4, T5, T6, T7]))
]

_operator_sub_signature = Union[
    _numpy_binary_op_signature.__args__ +
    (Fun[[Set[T0], Set[T0]], Set[T0]],)
]

_operator_mod_signature = Union[
    _numpy_binary_op_signature.__args__ +
    (Fun[[str, T0], str],)
]

_operator_mul_signature = Union[
    _numpy_binary_op_signature.__args__ +
    (Fun[[str, int], str], Fun[[int, str], str],
     Fun[[List[T0], int], List[T0]], Fun[[int, List[T0]], List[T0]])
]

_operator_contains_signature = Fun[[Iterable[T0], T0], bool]

_operator_getitem_signature = Union[
    Fun[[List[T0], int], T0],
    Fun[[List[T0], slice], List[T0]],
    Fun[[Dict[T0, T1], T0], T1],
    Fun[[str, int], str],
    Fun[[str, slice], str],
    # arrays
    Fun[[NDArray[T0, :], T1], T2],
    # large tuple
    Fun[[Iterable[T0], int], T0],
]


_numpy_farray_signature = Union[
    # no dtype
    # scalar
    Fun[[bool], float],
    Fun[[int], float],
    Fun[[float], float],
    # 1D array
    Fun[[Iterable[bool]], NDArray[float, :]],
    Fun[[Iterable[int]], NDArray[float, :]],
    Fun[[Iterable[float]], NDArray[float, :]],
    # 2D array
    Fun[[Iterable[Iterable[bool]]], NDArray[float, :, :]],
    Fun[[Iterable[Iterable[int]]], NDArray[float, :, :]],
    Fun[[Iterable[Iterable[float]]], NDArray[float, :, :]],
    # 3D array
    Fun[[Iterable[Iterable[Iterable[bool]]]], NDArray[float, :, :, :]],
    Fun[[Iterable[Iterable[Iterable[int]]]], NDArray[float, :, :, :]],
    Fun[[Iterable[Iterable[Iterable[float]]]], NDArray[float, :, :, :]],
    # 4D array
    Fun[[Iterable[Iterable[Iterable[Iterable[bool]]]]],
        NDArray[float, :, :, :, :]],
    Fun[[Iterable[Iterable[Iterable[Iterable[int]]]]],
        NDArray[float, :, :, :, :]],
    Fun[[Iterable[Iterable[Iterable[Iterable[float]]]]],
        NDArray[float, :, :, :, :]],

    # bool dtype
    # scalar
    Fun[[bool, _bool_signature], float],
    Fun[[int, _bool_signature], float],
    Fun[[float, _bool_signature], float],
    Fun[[complex, _bool_signature], float],
    # 1D array
    Fun[[Iterable[bool], _bool_signature], NDArray[float, :]],
    Fun[[Iterable[int], _bool_signature], NDArray[float, :]],
    Fun[[Iterable[float], _bool_signature], NDArray[float, :]],
    # 2D array
    Fun[[Iterable[Iterable[bool]], _bool_signature], NDArray[float, :, :]],
    Fun[[Iterable[Iterable[int]], _bool_signature], NDArray[float, :, :]],
    Fun[[Iterable[Iterable[float]], _bool_signature], NDArray[float, :, :]],
    # 3D array
    Fun[[Iterable[Iterable[Iterable[bool]]],
         _bool_signature], NDArray[float, :, :, :]],
    Fun[[Iterable[Iterable[Iterable[int]]], _bool_signature],
        NDArray[float, :, :, :]],
    Fun[[Iterable[Iterable[Iterable[float]]],
         _bool_signature], NDArray[float, :, :, :]],
    # 4D array
    Fun[[Iterable[Iterable[Iterable[Iterable[bool]]]],
         _bool_signature], NDArray[float, :, :, :, :]],
    Fun[[Iterable[Iterable[Iterable[Iterable[int]]]],
         _bool_signature], NDArray[float, :, :, :, :]],
    Fun[[Iterable[Iterable[Iterable[Iterable[float]]]],
         _bool_signature], NDArray[float, :, :, :, :]],

    # int dtype
    Fun[[bool, _int_signature], float],
    Fun[[int, _int_signature], float],
    Fun[[float, _int_signature], float],
    Fun[[complex, _int_signature], float],
    # 1D array
    Fun[[Iterable[bool], _int_signature], NDArray[float, :]],
    Fun[[Iterable[int], _int_signature], NDArray[float, :]],
    Fun[[Iterable[float], _int_signature], NDArray[float, :]],
    # 2D array
    Fun[[Iterable[Iterable[bool]], _int_signature], NDArray[float, :, :]],
    Fun[[Iterable[Iterable[int]], _int_signature], NDArray[float, :, :]],
    Fun[[Iterable[Iterable[float]], _int_signature], NDArray[float, :, :]],
    # 3D array
    Fun[[Iterable[Iterable[Iterable[bool]]],
         _int_signature], NDArray[float, :, :, :]],
    Fun[[Iterable[Iterable[Iterable[int]]], _int_signature],
        NDArray[float, :, :, :]],
    Fun[[Iterable[Iterable[Iterable[float]]],
         _int_signature], NDArray[float, :, :, :]],
    # 4D array
    Fun[[Iterable[Iterable[Iterable[Iterable[bool]]]],
         _int_signature], NDArray[float, :, :, :, :]],
    Fun[[Iterable[Iterable[Iterable[Iterable[int]]]],
         _int_signature], NDArray[float, :, :, :, :]],
    Fun[[Iterable[Iterable[Iterable[Iterable[float]]]],
         _int_signature], NDArray[float, :, :, :, :]],

    # float dtype
    # scalar
    Fun[[bool, _float_signature], float],
    Fun[[int, _float_signature], float],
    Fun[[float, _float_signature], float],
    Fun[[complex, _float_signature], float],
    # 1D array
    Fun[[Iterable[bool], _float_signature], NDArray[float, :]],
    Fun[[Iterable[int], _float_signature], NDArray[float, :]],
    Fun[[Iterable[float], _float_signature], NDArray[float, :]],
    Fun[[Iterable[complex], _float_signature], NDArray[float, :]],
    # 2D array
    Fun[[Iterable[Iterable[bool]], _float_signature], NDArray[float, :, :]],
    Fun[[Iterable[Iterable[int]], _float_signature], NDArray[float, :, :]],
    Fun[[Iterable[Iterable[float]], _float_signature], NDArray[float, :, :]],
    Fun[[Iterable[Iterable[complex]], _float_signature], NDArray[float, :, :]],
    # 3D array
    Fun[[Iterable[Iterable[Iterable[bool]]],
         _float_signature], NDArray[float, :, :, :]],
    Fun[[Iterable[Iterable[Iterable[int]]],
         _float_signature], NDArray[float, :, :, :]],
    Fun[[Iterable[Iterable[Iterable[float]]],
         _float_signature], NDArray[float, :, :, :]],
    Fun[[Iterable[Iterable[Iterable[complex]]],
         _float_signature], NDArray[float, :, :, :]],
    # 4D array
    Fun[[Iterable[Iterable[Iterable[Iterable[bool]]]],
         _float_signature], NDArray[float, :, :, :, :]],
    Fun[[Iterable[Iterable[Iterable[Iterable[int]]]],
         _float_signature], NDArray[float, :, :, :, :]],
    Fun[[Iterable[Iterable[Iterable[Iterable[float]]]],
         _float_signature], NDArray[float, :, :, :, :]],
    Fun[[Iterable[Iterable[Iterable[Iterable[complex]]]],
         _float_signature], NDArray[float, :, :, :, :]],

    # complex dtype
    # scalar
    Fun[[bool, _complex_signature], complex],
    Fun[[int, _complex_signature], complex],
    Fun[[float, _complex_signature], complex],
    Fun[[complex, _complex_signature], complex],
    # 1D array
    Fun[[Iterable[bool], _complex_signature], NDArray[complex, :]],
    Fun[[Iterable[int], _complex_signature], NDArray[complex, :]],
    Fun[[Iterable[float], _complex_signature], NDArray[complex, :]],
    Fun[[Iterable[complex], _complex_signature], NDArray[complex, :]],
    # 2D array
    Fun[[Iterable[Iterable[bool]], _complex_signature],
        NDArray[complex, :, :]],
    Fun[[Iterable[Iterable[int]], _complex_signature], NDArray[complex, :, :]],
    Fun[[Iterable[Iterable[float]], _complex_signature],
        NDArray[complex, :, :]],
    Fun[[Iterable[Iterable[complex]], _complex_signature],
        NDArray[complex, :, :]],
    # 3D array
    Fun[[Iterable[Iterable[Iterable[bool]]], _complex_signature],
        NDArray[complex, :, :, :]],
    Fun[[Iterable[Iterable[Iterable[int]]], _complex_signature],
        NDArray[complex, :, :, :]],
    Fun[[Iterable[Iterable[Iterable[float]]],
         _complex_signature], NDArray[complex, :, :, :]],
    Fun[[Iterable[Iterable[Iterable[complex]]],
         _complex_signature], NDArray[complex, :, :, :]],
    # 4D array
    Fun[[Iterable[Iterable[Iterable[Iterable[bool]]]],
         _complex_signature], NDArray[complex, :, :, :, :]],
    Fun[[Iterable[Iterable[Iterable[Iterable[int]]]],
         _complex_signature], NDArray[complex, :, :, :, :]],
    Fun[[Iterable[Iterable[Iterable[Iterable[float]]]],
         _complex_signature], NDArray[complex, :, :, :, :]],
    Fun[[Iterable[Iterable[Iterable[Iterable[complex]]]],
         _complex_signature], NDArray[complex, :, :, :, :]],
]

_numpy_array_signature = Union[
    # no dtype
    # scalar
    Fun[[bool], bool],
    Fun[[int], int],
    Fun[[float], float],
    Fun[[complex], complex],
    # 1D array
    Fun[[Iterable[bool]], NDArray[bool, :]],
    Fun[[Iterable[int]], NDArray[int, :]],
    Fun[[Iterable[float]], NDArray[float, :]],
    Fun[[Iterable[complex]], NDArray[complex, :]],
    # 2D array
    Fun[[Iterable[Iterable[bool]]], NDArray[bool, :, :]],
    Fun[[Iterable[Iterable[int]]], NDArray[int, :, :]],
    Fun[[Iterable[Iterable[float]]], NDArray[float, :, :]],
    Fun[[Iterable[Iterable[complex]]], NDArray[complex, :, :]],
    # 3D array
    Fun[[Iterable[Iterable[Iterable[bool]]]], NDArray[bool, :, :, :]],
    Fun[[Iterable[Iterable[Iterable[int]]]], NDArray[int, :, :, :]],
    Fun[[Iterable[Iterable[Iterable[float]]]], NDArray[float, :, :, :]],
    Fun[[Iterable[Iterable[Iterable[complex]]]], NDArray[complex, :, :, :]],
    # 4D array
    Fun[[Iterable[Iterable[Iterable[Iterable[bool]]]]],
        NDArray[bool, :, :, :, :]],
    Fun[[Iterable[Iterable[Iterable[Iterable[int]]]]],
        NDArray[int, :, :, :, :]],
    Fun[[Iterable[Iterable[Iterable[Iterable[float]]]]],
        NDArray[float, :, :, :, :]],
    Fun[[Iterable[Iterable[Iterable[Iterable[complex]]]]],
        NDArray[complex, :, :, :, :]],

    # bool dtype
    # scalar
    Fun[[bool, _bool_signature], bool],
    Fun[[int, _bool_signature], bool],
    Fun[[float, _bool_signature], bool],
    Fun[[complex, _bool_signature], bool],
    # 1D array
    Fun[[Iterable[bool], _bool_signature], NDArray[bool, :]],
    Fun[[Iterable[int], _bool_signature], NDArray[bool, :]],
    Fun[[Iterable[float], _bool_signature], NDArray[bool, :]],
    Fun[[Iterable[complex], _bool_signature], NDArray[bool, :]],
    # 2D array
    Fun[[Iterable[Iterable[bool]], _bool_signature], NDArray[bool, :, :]],
    Fun[[Iterable[Iterable[int]], _bool_signature], NDArray[bool, :, :]],
    Fun[[Iterable[Iterable[float]], _bool_signature], NDArray[bool, :, :]],
    Fun[[Iterable[Iterable[complex]], _bool_signature], NDArray[bool, :, :]],
    # 3D array
    Fun[[Iterable[Iterable[Iterable[bool]]],
         _bool_signature], NDArray[bool, :, :, :]],
    Fun[[Iterable[Iterable[Iterable[int]]], _bool_signature],
        NDArray[bool, :, :, :]],
    Fun[[Iterable[Iterable[Iterable[float]]],
         _bool_signature], NDArray[bool, :, :, :]],
    Fun[[Iterable[Iterable[Iterable[complex]]],
         _bool_signature], NDArray[bool, :, :, :]],
    # 4D array
    Fun[[Iterable[Iterable[Iterable[Iterable[bool]]]],
         _bool_signature], NDArray[bool, :, :, :, :]],
    Fun[[Iterable[Iterable[Iterable[Iterable[int]]]],
         _bool_signature], NDArray[bool, :, :, :, :]],
    Fun[[Iterable[Iterable[Iterable[Iterable[float]]]],
         _bool_signature], NDArray[bool, :, :, :, :]],
    Fun[[Iterable[Iterable[Iterable[Iterable[complex]]]],
         _bool_signature], NDArray[bool, :, :, :, :]],

    # int dtype
    # scalar
    Fun[[bool, _int_signature], int],
    Fun[[int, _int_signature], int],
    Fun[[float, _int_signature], int],
    Fun[[complex, _int_signature], int],
    # 1D array
    Fun[[Iterable[bool], _int_signature], NDArray[int, :]],
    Fun[[Iterable[int], _int_signature], NDArray[int, :]],
    Fun[[Iterable[float], _int_signature], NDArray[int, :]],
    Fun[[Iterable[complex], _int_signature], NDArray[int, :]],
    # 2D array
    Fun[[Iterable[Iterable[bool]], _int_signature], NDArray[int, :, :]],
    Fun[[Iterable[Iterable[int]], _int_signature], NDArray[int, :, :]],
    Fun[[Iterable[Iterable[float]], _int_signature], NDArray[int, :, :]],
    Fun[[Iterable[Iterable[complex]], _int_signature], NDArray[int, :, :]],
    # 3D array
    Fun[[Iterable[Iterable[Iterable[bool]]], _int_signature],
        NDArray[int, :, :, :]],
    Fun[[Iterable[Iterable[Iterable[int]]], _int_signature],
        NDArray[int, :, :, :]],
    Fun[[Iterable[Iterable[Iterable[float]]],
         _int_signature], NDArray[int, :, :, :]],
    Fun[[Iterable[Iterable[Iterable[complex]]],
         _int_signature], NDArray[int, :, :, :]],
    # 4D array
    Fun[[Iterable[Iterable[Iterable[Iterable[bool]]]],
         _int_signature], NDArray[int, :, :, :, :]],
    Fun[[Iterable[Iterable[Iterable[Iterable[int]]]],
         _int_signature], NDArray[int, :, :, :, :]],
    Fun[[Iterable[Iterable[Iterable[Iterable[float]]]],
         _int_signature], NDArray[int, :, :, :, :]],
    Fun[[Iterable[Iterable[Iterable[Iterable[complex]]]],
         _int_signature], NDArray[int, :, :, :, :]],

    # float dtype
    # scalar
    Fun[[bool, _float_signature], float],
    Fun[[int, _float_signature], float],
    Fun[[float, _float_signature], float],
    Fun[[complex, _float_signature], float],
    # 1D array
    Fun[[Iterable[bool], _float_signature], NDArray[float, :]],
    Fun[[Iterable[int], _float_signature], NDArray[float, :]],
    Fun[[Iterable[float], _float_signature], NDArray[float, :]],
    Fun[[Iterable[complex], _float_signature], NDArray[float, :]],
    # 2D array
    Fun[[Iterable[Iterable[bool]], _float_signature], NDArray[float, :, :]],
    Fun[[Iterable[Iterable[int]], _float_signature], NDArray[float, :, :]],
    Fun[[Iterable[Iterable[float]], _float_signature], NDArray[float, :, :]],
    Fun[[Iterable[Iterable[complex]], _float_signature], NDArray[float, :, :]],
    # 3D array
    Fun[[Iterable[Iterable[Iterable[bool]]],
         _float_signature], NDArray[float, :, :, :]],
    Fun[[Iterable[Iterable[Iterable[int]]],
         _float_signature], NDArray[float, :, :, :]],
    Fun[[Iterable[Iterable[Iterable[float]]],
         _float_signature], NDArray[float, :, :, :]],
    Fun[[Iterable[Iterable[Iterable[complex]]],
         _float_signature], NDArray[float, :, :, :]],
    # 4D array
    Fun[[Iterable[Iterable[Iterable[Iterable[bool]]]],
         _float_signature], NDArray[float, :, :, :, :]],
    Fun[[Iterable[Iterable[Iterable[Iterable[int]]]],
         _float_signature], NDArray[float, :, :, :, :]],
    Fun[[Iterable[Iterable[Iterable[Iterable[float]]]],
         _float_signature], NDArray[float, :, :, :, :]],
    Fun[[Iterable[Iterable[Iterable[Iterable[complex]]]],
         _float_signature], NDArray[float, :, :, :, :]],

    # complex dtype
    # scalar
    Fun[[bool, _complex_signature], complex],
    Fun[[int, _complex_signature], complex],
    Fun[[float, _complex_signature], complex],
    Fun[[complex, _complex_signature], complex],
    # 1D array
    Fun[[Iterable[bool], _complex_signature], NDArray[complex, :]],
    Fun[[Iterable[int], _complex_signature], NDArray[complex, :]],
    Fun[[Iterable[float], _complex_signature], NDArray[complex, :]],
    Fun[[Iterable[complex], _complex_signature], NDArray[complex, :]],
    # 2D array
    Fun[[Iterable[Iterable[bool]], _complex_signature],
        NDArray[complex, :, :]],
    Fun[[Iterable[Iterable[int]], _complex_signature], NDArray[complex, :, :]],
    Fun[[Iterable[Iterable[float]], _complex_signature],
        NDArray[complex, :, :]],
    Fun[[Iterable[Iterable[complex]], _complex_signature],
        NDArray[complex, :, :]],
    # 3D array
    Fun[[Iterable[Iterable[Iterable[bool]]], _complex_signature],
        NDArray[complex, :, :, :]],
    Fun[[Iterable[Iterable[Iterable[int]]], _complex_signature],
        NDArray[complex, :, :, :]],
    Fun[[Iterable[Iterable[Iterable[float]]],
         _complex_signature], NDArray[complex, :, :, :]],
    Fun[[Iterable[Iterable[Iterable[complex]]],
         _complex_signature], NDArray[complex, :, :, :]],
    # 4D array
    Fun[[Iterable[Iterable[Iterable[Iterable[bool]]]],
         _complex_signature], NDArray[complex, :, :, :, :]],
    Fun[[Iterable[Iterable[Iterable[Iterable[int]]]],
         _complex_signature], NDArray[complex, :, :, :, :]],
    Fun[[Iterable[Iterable[Iterable[Iterable[float]]]],
         _complex_signature], NDArray[complex, :, :, :, :]],
    Fun[[Iterable[Iterable[Iterable[Iterable[complex]]]],
         _complex_signature], NDArray[complex, :, :, :, :]],
]

# each module consist in a module_name <> set of symbols
MODULES = {
    "__builtin__": {
        "pythran": {
            "len_set": ConstFunctionIntr(signature=Fun[[Iterable[T0]], int])
        },
        "abs": ConstFunctionIntr(
            signature=Union[
                Fun[[int], int],
                Fun[[float], float],
                Fun[[complex], float],
                Fun[[NDArray[int, :]], NDArray[int, :]],
                Fun[[NDArray[int, :, :]], NDArray[int, :, :]],
                Fun[[NDArray[int, :, :, :]], NDArray[int, :, :, :]],
                Fun[[NDArray[int, :, :, :, :]], NDArray[int, :, :, :, :]],
                Fun[[NDArray[float, :]], NDArray[float, :]],
                Fun[[NDArray[float, :, :]], NDArray[float, :, :]],
                Fun[[NDArray[float, :, :, :]], NDArray[float, :, :, :]],
                Fun[[NDArray[float, :, :, :, :]], NDArray[float, :, :, :, :]],
                Fun[[NDArray[complex, :]], NDArray[float, :]],
                Fun[[NDArray[complex, :, :]], NDArray[float, :, :]],
                Fun[[NDArray[complex, :, :, :]], NDArray[float, :, :, :]],
                Fun[[NDArray[complex, :, :, :, :]], NDArray[float, :, :, :, :]]
            ],
        ),
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
        "all": ReadOnceFunctionIntr(signature=Fun[[Iterable[T0]], bool]),
        "any": ReadOnceFunctionIntr(signature=Fun[[Iterable[T0]], bool]),
        "bin": ConstFunctionIntr(signature=Fun[[int], str]),
        "bool_": ConstFunctionIntr(signature=_bool_signature),
        "chr": ConstFunctionIntr(signature=Fun[[int], str]),
        "cmp": ConstFunctionIntr(
            signature=Fun[[T0, T0], int],
            return_range=interval.cmp_values
        ),
        "complex": ClassWithConstConstructor(
            CLASSES['complex'],
            signature=_complex_signature
        ),
        "dict": ClassWithReadOnceConstructor(
            CLASSES['dict'],
            signature=Union[
                Fun[[], Dict[T0, T1]],
                Fun[[Iterable[Tuple[T0, T1]]], Dict[T0, T1]],
            ],
        ),
        "divmod": ConstFunctionIntr(
            signature=Union[
                Fun[[int, int], Tuple[int, int]],
                Fun[[float, int], Tuple[float, float]],
                Fun[[int, float], Tuple[float, float]],
                Fun[[float, float], Tuple[float, float]],
            ],
        ),
        "enumerate": ReadOnceFunctionIntr(
            signature=Union[
                Fun[[Iterable[T0]], Generator[Tuple[int, T0]]],
                Fun[[Iterable[T0], int], Generator[Tuple[int, T0]]],
            ],
        ),
        "file": ClassWithConstConstructor(
            CLASSES['file'],
            signature=Union[
                Fun[[str], File],
                Fun[[str, str], File],
            ],
            global_effects=True
        ),
        "filter": ReadOnceFunctionIntr(
            signature=Union[
                Fun[[None, Iterable[T0]], List[T0]],
                Fun[[Fun[[T0], bool], Iterable[T0]], List[T0]],
            ],
        ),
        "float_": ClassWithConstConstructor(
            CLASSES['float'],
            signature=_float_signature
        ),
        "getattr": ConstFunctionIntr(),
        "hex": ConstFunctionIntr(signature=Fun[[int], str]),
        "id": ConstFunctionIntr(signature=Fun[[T0], int]),
        "int_": ConstFunctionIntr(signature=_int_signature),
        "iter": FunctionIntr(
            signature=Fun[[Iterable[T0]], Generator[T0]]),  # not const
        "len": ConstFunctionIntr(
            signature=Fun[[Sized], int],
            return_range=interval.positive_values
        ),
        "list": ClassWithReadOnceConstructor(
            CLASSES['list'],
            signature=Union[
                Fun[[], List[T0]],
                Fun[[Iterable[T0]], List[T0]]
            ],
        ),
        "long_": ConstFunctionIntr(
            signature=Union[
                Fun[[], int],
                Fun[[bool], int],
                Fun[[int], int],
                Fun[[float], int],
                Fun[[str], int],
            ]
        ),
        "map": ReadOnceFunctionIntr(
            signature=Union[
                Fun[[None, Iterable[T0]], List[T0]],
                Fun[[None, Iterable[T0], Iterable[T1]], List[Tuple[T0, T1]]],
                Fun[[None, Iterable[T0], Iterable[T1], Iterable[T2]],
                    List[Tuple[T0, T1, T2]]],
                Fun[[None, Iterable[T0], Iterable[T1], Iterable[T2],
                     Iterable[T3]], List[Tuple[T0, T1, T2, T3]]],
                Fun[[Fun[[T0], T7], Iterable[T0]], List[T7]],
                Fun[[Fun[[T0, T1], T7], Iterable[T0], Iterable[T1]], List[T7]],
                Fun[[Fun[[T0, T1, T2], T7], Iterable[T0], Iterable[T1],
                     Iterable[T2]], List[T7]],
                Fun[[Fun[[T0, T1, T2, T3], T7], Iterable[T0], Iterable[T1],
                     Iterable[T2], Iterable[T3]], List[T7]],
            ]
        ),
        "max": ReadOnceFunctionIntr(
            signature=Union[
                Fun[[T0, T0], T0],
                Fun[[T0, T0, T0], T0],
                Fun[[T0, T0, T0, T0], T0],
                Fun[[Iterable[T0]], T0],
            ],
            return_range=interval.max_values
        ),
        "min": ReadOnceFunctionIntr(
            signature=Union[
                Fun[[int, int], int],
                Fun[[float, float], float],
                Fun[[Iterable[T0]], T0],
            ],
            return_range=interval.min_values
        ),
        "next": FunctionIntr(  # not const
            signature=Union[
                Fun[[Iterable[T0]], T0],
                Fun[[Iterable[T0], T0], T0],
            ],
        ),  # not const
        "oct": ConstFunctionIntr(signature=Fun[[int], str]),
        "ord": ConstFunctionIntr(
            signature=Fun[[str], int],
            return_range=interval.ord_values
        ),
        "open": ConstFunctionIntr(
            signature=Union[
                Fun[[str], File],
                Fun[[str, str], File],
            ],
            global_effects=True
        ),
        "pow": ConstFunctionIntr(
            signature=Union[
                Fun[[int, int], int],
                Fun[[int, int, int], int],
                Fun[[int, float], float],
                Fun[[int, float, int], float],
                Fun[[float, float], float],
                Fun[[float, float, int], float],
            ]
        ),
        "range": ConstFunctionIntr(
            signature=Union[
                Fun[[int], List[int]],
                Fun[[int, int], List[int]],
                Fun[[int, int, int], List[int]],
            ],
            return_range_content=interval.range_values
        ),
        "reduce": ReadOnceFunctionIntr(signature=_functools_reduce_signature),
        "reversed": ReadOnceFunctionIntr(
            signature=Fun[[Iterable[T0]], Iterable[T0]]
        ),
        "round": ConstFunctionIntr(
            signature=Union[
                Fun[[float], float],
                Fun[[float, int], float],
            ],
        ),
        "set": ClassWithReadOnceConstructor(
            CLASSES['set'],
            signature=Union[
                Fun[[], Set[T0]],
                Fun[[Iterable[T0]], Set[T0]]
            ],
        ),
        "sorted": ConstFunctionIntr(signature=Fun[[Iterable[T0]], List[T0]]),
        "str": ClassWithConstConstructor(
            CLASSES['str'],
            signature=Fun[[T0], str],
        ),
        "sum": ReadOnceFunctionIntr(
            signature=Union[
                Fun[[Iterable[int]], int],
                Fun[[Iterable[float]], float],
                Fun[[Iterable[int], int], int],
                Fun[[Iterable[float], float], float],
            ],
        ),
        "tuple": ReadOnceFunctionIntr(
            signature=Union[
                Fun[[], Tuple[()]],
                Fun[[Tuple[T0]], Tuple[T0]],
                Fun[[Tuple[T0, T1]], Tuple[T0, T1]],
                Fun[[Tuple[T0, T1, T2]], Tuple[T0, T1, T2]],
                # FIXME: We accept some type loss here
                Fun[[List[T0]], Iterable[T0]],
            ],
        ),
        "xrange": ConstFunctionIntr(
            signature=Union[
                Fun[[int], Generator[int]],
                Fun[[int, int], Generator[int]],
                Fun[[int, int, int], Generator[int]],
            ],
            return_range_content=interval.range_values
        ),
        "zip": ReadOnceFunctionIntr(
            signature=Union[
                Fun[[], List[T0]],
                Fun[[Iterable[T0]], List[Tuple[T0]]],
                Fun[[Iterable[T0], Iterable[T1]], List[Tuple[T0, T1]]],
                Fun[[Iterable[T0], Iterable[T1], Iterable[T2]],
                    List[Tuple[T0, T1, T2]]],
                Fun[[Iterable[T0], Iterable[T1], Iterable[T2], Iterable[T3]],
                    List[Tuple[T0, T1, T2, T3]]],
            ]
        ),
        "False": ConstantIntr(
            signature=bool,
            return_range=lambda _: interval.Range(0, 0)
        ),
        "None": ConstantIntr(signature=None),
        "True": ConstantIntr(
            signature=bool,
            return_range=lambda _: interval.Range(1, 1)
        ),
    },
    "scipy": {
        "special": {
            "gammaln": ConstFunctionIntr(
                signature=_numpy_unary_op_float_signature
            ),
            "gamma": ConstFunctionIntr(
                signature=_numpy_unary_op_float_signature
            ),
        }
    },
    "numpy": {
        "abs": ConstFunctionIntr(signature=_numpy_unary_op_signature),
        "absolute": ConstFunctionIntr(signature=_numpy_ones_signature),
        "add": UFunc(
            BINARY_UFUNC,
            signature=_numpy_binary_op_signature,
        ),
        "alen": ConstFunctionIntr(
            signature=Union[
                # scalar
                Fun[[bool], int],
                Fun[[int], int],
                Fun[[float], int],
                Fun[[complex], int],
                # Sized
                Fun[[Sized], int],
            ],
            return_range=interval.positive_values
        ),
        "all": ConstMethodIntr(
            signature=_numpy_unary_op_bool_axis_signature,
            return_range=interval.bool_values
        ),
        "allclose": ConstFunctionIntr(
            signature=_numpy_allclose_signature,
            return_range=interval.bool_values
        ),
        "alltrue": ConstFunctionIntr(
            signature=_numpy_unary_op_bool_axis_signature,
            return_range=interval.bool_values
        ),
        "amax": ConstFunctionIntr(signature=_numpy_unary_op_axis_signature),
        "amin": ConstFunctionIntr(signature=_numpy_unary_op_axis_signature),
        "angle": ConstFunctionIntr(signature=_numpy_unary_op_angle_signature),
        "any": ConstMethodIntr(
            signature=_numpy_unary_op_bool_axis_signature,
            return_range=interval.bool_values
        ),
        "append": ConstFunctionIntr(
            signature=Union[
                # no axis -> flattened output
                # scalar
                Fun[[bool, bool], NDArray[bool, :]],
                Fun[[int, int], NDArray[int, :]],
                Fun[[float, float], NDArray[float, :]],
                Fun[[complex, float], NDArray[float, :]],
                # 1D Array
                # FIXME: second argument could have a shape larger than first
                Fun[[Iterable[bool], bool], NDArray[bool, :]],
                Fun[[Iterable[int], int], NDArray[int, :]],
                Fun[[Iterable[float], float], NDArray[float, :]],
                Fun[[Iterable[complex], complex], NDArray[complex, :]],

                Fun[[Iterable[bool], Iterable[bool]], NDArray[bool, :]],
                Fun[[Iterable[int], Iterable[int]], NDArray[int, :]],
                Fun[[Iterable[float], Iterable[float]], NDArray[float, :]],
                Fun[[Iterable[complex], Iterable[complex]],
                    NDArray[complex, :]],

                # 2D Array
                Fun[[Iterable[Iterable[bool]], bool], NDArray[bool, :]],
                Fun[[Iterable[Iterable[int]], int], NDArray[int, :]],
                Fun[[Iterable[Iterable[float]], float], NDArray[float, :]],
                Fun[[Iterable[Iterable[complex]], complex],
                    NDArray[complex, :]],

                Fun[[Iterable[Iterable[bool]], Iterable[bool]],
                    NDArray[bool, :]],
                Fun[[Iterable[Iterable[int]], Iterable[int]], NDArray[int, :]],
                Fun[[Iterable[Iterable[float]], Iterable[float]],
                    NDArray[float, :]],
                Fun[[Iterable[Iterable[complex]], Iterable[
                    complex]], NDArray[complex, :]],

                Fun[[Iterable[Iterable[bool]], Iterable[
                    Iterable[bool]]], NDArray[bool, :]],
                Fun[[Iterable[Iterable[int]], Iterable[
                    Iterable[int]]], NDArray[int, :]],
                Fun[[Iterable[Iterable[float]], Iterable[
                    Iterable[float]]], NDArray[float, :]],
                Fun[[Iterable[Iterable[complex]], Iterable[
                    Iterable[complex]]], NDArray[complex, :]],

                Fun[[bool, Iterable[Iterable[bool]]], NDArray[bool, :]],
                Fun[[int, Iterable[Iterable[int]]], NDArray[int, :]],
                Fun[[float, Iterable[Iterable[float]]], NDArray[float, :]],
                Fun[[complex, Iterable[Iterable[complex]]],
                    NDArray[complex, :]],

                Fun[[Iterable[bool], Iterable[Iterable[bool]]],
                    NDArray[bool, :]],
                Fun[[Iterable[int], Iterable[Iterable[int]]], NDArray[int, :]],
                Fun[[Iterable[float], Iterable[Iterable[float]]],
                    NDArray[float, :]],
                Fun[[Iterable[complex], Iterable[Iterable[complex]]],
                    NDArray[complex, :]],

                Fun[[Iterable[Iterable[bool]], Iterable[
                    Iterable[bool]]], NDArray[bool, :]],
                Fun[[Iterable[Iterable[int]], Iterable[
                    Iterable[int]]], NDArray[int, :]],
                Fun[[Iterable[Iterable[float]], Iterable[
                    Iterable[float]]], NDArray[float, :]],
                Fun[[Iterable[Iterable[complex]], Iterable[
                    Iterable[complex]]], NDArray[complex, :]],

                # 3D Array FIXME: same as above
                Fun[[Iterable[Iterable[Iterable[bool]]], bool],
                    NDArray[bool, :]],
                Fun[[Iterable[Iterable[Iterable[int]]], int], NDArray[int, :]],
                Fun[[Iterable[Iterable[Iterable[float]]], float],
                    NDArray[float, :]],
                Fun[[Iterable[Iterable[Iterable[complex]]],
                     complex], NDArray[complex, :]],

                Fun[[Iterable[Iterable[Iterable[bool]]],
                     Iterable[bool]], NDArray[bool, :]],
                Fun[[Iterable[Iterable[Iterable[int]]],
                     Iterable[int]], NDArray[int, :]],
                Fun[[Iterable[Iterable[Iterable[float]]],
                     Iterable[float]], NDArray[float, :]],
                Fun[[Iterable[Iterable[Iterable[complex]]],
                     Iterable[complex]], NDArray[complex, :]],

                Fun[[Iterable[Iterable[Iterable[bool]]],
                     Iterable[Iterable[bool]]], NDArray[bool, :]],
                Fun[[Iterable[Iterable[Iterable[int]]],
                     Iterable[Iterable[int]]], NDArray[int, :]],
                Fun[[Iterable[Iterable[Iterable[float]]], Iterable[
                    Iterable[float]]], NDArray[float, :]],
                Fun[[Iterable[Iterable[Iterable[complex]]], Iterable[
                    Iterable[complex]]], NDArray[complex, :]],

                Fun[[Iterable[Iterable[Iterable[bool]]], Iterable[
                    Iterable[Iterable[bool]]]], NDArray[bool, :]],
                Fun[[Iterable[Iterable[Iterable[int]]], Iterable[
                    Iterable[Iterable[int]]]], NDArray[int, :]],
                Fun[[Iterable[Iterable[Iterable[float]]], Iterable[
                    Iterable[Iterable[float]]]], NDArray[float, :]],
                Fun[[Iterable[Iterable[Iterable[complex]]], Iterable[
                    Iterable[Iterable[complex]]]], NDArray[complex, :]],

                # 4D Array FIXME: same as above
                Fun[[Iterable[Iterable[Iterable[Iterable[bool]]]], bool],
                    NDArray[bool, :]],
                Fun[[Iterable[Iterable[Iterable[Iterable[int]]]], int],
                    NDArray[int, :]],
                Fun[[Iterable[Iterable[Iterable[Iterable[float]]]], float],
                    NDArray[float, :]],
                Fun[[Iterable[Iterable[Iterable[Iterable[complex]]]],
                     complex], NDArray[complex, :]],

                Fun[[Iterable[Iterable[Iterable[Iterable[bool]]]],
                     Iterable[bool]], NDArray[bool, :]],
                Fun[[Iterable[Iterable[Iterable[Iterable[int]]]],
                     Iterable[int]], NDArray[int, :]],
                Fun[[Iterable[Iterable[Iterable[Iterable[float]]]],
                     Iterable[float]], NDArray[float, :]],
                Fun[[Iterable[Iterable[Iterable[Iterable[complex]]]],
                     Iterable[complex]], NDArray[complex, :]],

                Fun[[Iterable[Iterable[Iterable[Iterable[bool]]]],
                     Iterable[Iterable[bool]]], NDArray[bool, :]],
                Fun[[Iterable[Iterable[Iterable[Iterable[int]]]],
                     Iterable[Iterable[int]]], NDArray[int, :]],
                Fun[[Iterable[Iterable[Iterable[Iterable[float]]]],
                     Iterable[Iterable[float]]], NDArray[float, :]],
                Fun[[Iterable[Iterable[Iterable[Iterable[complex]]]],
                     Iterable[Iterable[complex]]], NDArray[complex, :]],

                Fun[[Iterable[Iterable[Iterable[Iterable[bool]]]],
                     Iterable[Iterable[Iterable[bool]]]], NDArray[bool, :]],
                Fun[[Iterable[Iterable[Iterable[Iterable[int]]]],
                     Iterable[Iterable[Iterable[int]]]], NDArray[int, :]],
                Fun[[Iterable[Iterable[Iterable[Iterable[float]]]], Iterable[
                    Iterable[Iterable[float]]]], NDArray[float, :]],
                Fun[[Iterable[Iterable[Iterable[Iterable[complex]]]], Iterable[
                    Iterable[Iterable[complex]]]], NDArray[complex, :]],

                Fun[[Iterable[Iterable[Iterable[Iterable[bool]]]], Iterable[
                    Iterable[Iterable[Iterable[bool]]]]], NDArray[bool, :]],
                Fun[[Iterable[Iterable[Iterable[Iterable[int]]]], Iterable[
                    Iterable[Iterable[Iterable[int]]]]], NDArray[int, :]],
                Fun[[Iterable[Iterable[Iterable[Iterable[float]]]], Iterable[
                    Iterable[Iterable[Iterable[float]]]]], NDArray[float, :]],
                Fun[[Iterable[Iterable[Iterable[Iterable[complex]]]], Iterable[
                    Iterable[Iterable[Iterable[complex]]]]],
                    NDArray[complex, :]],

                # FIXME: same as above with None axis

                # axis -> same dims

                # 1D
                Fun[[Iterable[bool], Iterable[bool], int], Iterable[bool]],
                Fun[[Iterable[int], Iterable[int], int], Iterable[int]],
                Fun[[Iterable[float], Iterable[float], int], Iterable[float]],
                Fun[[Iterable[complex], Iterable[complex], int],
                    Iterable[complex]],

                # 2D
                Fun[[Iterable[Iterable[bool]], Iterable[
                    Iterable[bool]], int], Iterable[Iterable[bool]]],
                Fun[[Iterable[Iterable[int]], Iterable[
                    Iterable[int]], int], Iterable[Iterable[int]]],
                Fun[[Iterable[Iterable[float]], Iterable[
                    Iterable[float]], int], Iterable[Iterable[float]]],
                Fun[[Iterable[Iterable[complex]], Iterable[
                    Iterable[complex]], int], Iterable[Iterable[complex]]],

                # 3D
                Fun[[Iterable[Iterable[Iterable[bool]]], Iterable[
                    Iterable[Iterable[bool]]], int],
                    Iterable[Iterable[Iterable[bool]]]],
                Fun[[Iterable[Iterable[Iterable[int]]], Iterable[
                    Iterable[Iterable[int]]], int],
                    Iterable[Iterable[Iterable[int]]]],
                Fun[[Iterable[Iterable[Iterable[float]]], Iterable[
                    Iterable[Iterable[float]]], int],
                    Iterable[Iterable[Iterable[float]]]],
                Fun[[Iterable[Iterable[Iterable[complex]]], Iterable[
                    Iterable[Iterable[complex]]], int],
                    Iterable[Iterable[Iterable[complex]]]],

                # 4D
                Fun[[Iterable[Iterable[Iterable[Iterable[bool]]]],
                     Iterable[Iterable[Iterable[Iterable[bool]]]], int],
                    Iterable[Iterable[Iterable[Iterable[bool]]]]],
                Fun[[Iterable[Iterable[Iterable[Iterable[int]]]],
                     Iterable[Iterable[Iterable[Iterable[int]]]], int],
                    Iterable[Iterable[Iterable[Iterable[int]]]]],
                Fun[[Iterable[Iterable[Iterable[Iterable[float]]]],
                     Iterable[Iterable[Iterable[Iterable[float]]]], int],
                    Iterable[Iterable[Iterable[Iterable[float]]]]],
                Fun[[Iterable[Iterable[Iterable[Iterable[complex]]]],
                     Iterable[Iterable[Iterable[Iterable[complex]]]],
                     int],
                    Iterable[Iterable[Iterable[Iterable[complex]]]]],
            ]
        ),
        "arange": ConstFunctionIntr(
            signature=Union[
                Fun[[float], NDArray[float, :]],
                Fun[[float, float], NDArray[float, :]],
                Fun[[float, float, float], NDArray[float, :]],
                Fun[[float, float, float, None], NDArray[float, :]],
                Fun[[float, float, float, _bool_signature], NDArray[bool, :]],
                Fun[[float, float, float, _int_signature], NDArray[int, :]],
                Fun[[float, float, float, _float_signature],
                    NDArray[float, :]],
                Fun[[float, float, float, _complex_signature],
                    NDArray[complex, :]],
            ],
            return_range_content=interval.range_values,
            args=('start', 'stop', 'step', 'dtype'),
            defaults=(1, None)
        ),
        "arccos": ConstFunctionIntr(signature=_numpy_unary_op_float_signature),
        "arccosh": ConstFunctionIntr(
            signature=_numpy_unary_op_float_signature),
        "arcsin": ConstFunctionIntr(signature=_numpy_unary_op_float_signature),
        "arcsinh": ConstFunctionIntr(
            signature=_numpy_unary_op_float_signature),
        "arctan": ConstFunctionIntr(signature=_numpy_unary_op_float_signature),
        "arctan2": UFunc(
            BINARY_UFUNC,
            signature=_numpy_binary_op_float_no_complex_signature
        ),
        "arctanh": ConstFunctionIntr(
            signature=_numpy_unary_op_float_signature),
        "argmax": ConstMethodIntr(
            signature=_numpy_unary_op_int_axis_signature),
        "argmin": ConstMethodIntr(
            signature=_numpy_unary_op_int_axis_signature),
        "argsort": ConstFunctionIntr(
            signature=_numpy_unary_op_int_axis_signature),
        "argwhere": ConstFunctionIntr(signature=_numpy_unary_op_int_signature),
        "around": ConstFunctionIntr(signature=_numpy_around_signature),
        "array": ConstFunctionIntr(signature=_numpy_array_signature,
                                   args=('object', 'dtype'), defaults=(None,)),
        "array2string": ConstFunctionIntr(
            signature=_numpy_array_str_signature),
        "array_equal": ConstFunctionIntr(signature=Fun[[T0, T1], bool]),
        "array_equiv": ConstFunctionIntr(signature=Fun[[T0, T1], bool]),
        "array_split": ConstFunctionIntr(
            signature=Union[
                # int split
                Fun[[NDArray[T0, :], int], List[NDArray[T0, :]]],
                # array split
                Fun[[NDArray[T0, :], Iterable[int]], List[NDArray[T0, :]]],
            ]
        ),
        "array_str": ConstFunctionIntr(signature=_numpy_array_str_signature),
        "asarray": ConstFunctionIntr(signature=_numpy_array_signature),
        "asarray_chkfinite": ConstFunctionIntr(
            signature=_numpy_array_signature),
        "ascontiguousarray": ConstFunctionIntr(
            signature=_numpy_array_signature),
        "asfarray": ConstFunctionIntr(signature=_numpy_farray_signature),
        "asscalar": ConstFunctionIntr(
            signature=Union[
                Fun[[NDArray[bool, :]], bool],
                Fun[[NDArray[int, :]], int],
                Fun[[NDArray[float, :]], float],
                Fun[[NDArray[complex, :]], complex],
                Fun[[NDArray[bool, :, :]], bool],
                Fun[[NDArray[int, :, :]], int],
                Fun[[NDArray[float, :, :]], float],
                Fun[[NDArray[complex, :, :]], complex],
                Fun[[NDArray[bool, :, :, :]], bool],
                Fun[[NDArray[int, :, :, :]], int],
                Fun[[NDArray[float, :, :, :]], float],
                Fun[[NDArray[complex, :, :, :]], complex],
            ]
        ),
        "atleast_1d": ConstFunctionIntr(
            signature=Union[
                # scalar
                Fun[[bool], NDArray[bool, :]],
                Fun[[int], NDArray[int, :]],
                Fun[[float], NDArray[float, :]],
                Fun[[complex], NDArray[complex, :]],
                # 1d
                Fun[[Iterable[bool]], NDArray[bool, :]],
                Fun[[Iterable[int]], NDArray[int, :]],
                Fun[[Iterable[float]], NDArray[float, :]],
                Fun[[Iterable[complex]], NDArray[complex, :]],
                # 2d+
                Fun[[NDArray[T0, :, :]], NDArray[T0, :, :]],
                Fun[[Iterable[Iterable[bool]]], NDArray[bool, :, :]],
                Fun[[Iterable[Iterable[int]]], NDArray[int, :, :]],
                Fun[[Iterable[Iterable[float]]], NDArray[float, :, :]],
                Fun[[Iterable[Iterable[complex]]], NDArray[complex, :, :]],
                # 3d
                Fun[[Iterable[Iterable[Iterable[bool]]]],
                    NDArray[bool, :, :, :]],
                Fun[[Iterable[Iterable[Iterable[int]]]],
                    NDArray[int, :, :, :]],
                Fun[[Iterable[Iterable[Iterable[float]]]],
                    NDArray[float, :, :, :]],
                Fun[[Iterable[Iterable[Iterable[complex]]]],
                    NDArray[complex, :, :, :]],
                # 4d
                Fun[[Iterable[Iterable[Iterable[Iterable[bool]]]]],
                    NDArray[bool, :, :, :, :]],
                Fun[[Iterable[Iterable[Iterable[Iterable[int]]]]],
                    NDArray[int, :, :, :, :]],
                Fun[[Iterable[Iterable[Iterable[Iterable[float]]]]],
                    NDArray[float, :, :, :, :]],
                Fun[[Iterable[Iterable[Iterable[Iterable[complex]]]]],
                    NDArray[complex, :, :, :, :]],
            ]
        ),
        "atleast_2d": ConstFunctionIntr(
            signature=Union[
                # scalar
                Fun[[bool], NDArray[bool, :, :]],
                Fun[[int], NDArray[int, :, :]],
                Fun[[float], NDArray[float, :, :]],
                Fun[[complex], NDArray[complex, :, :]],
                # 1d
                Fun[[Iterable[bool]], NDArray[bool, :, :]],
                Fun[[Iterable[int]], NDArray[int, :, :]],
                Fun[[Iterable[float]], NDArray[float, :, :]],
                Fun[[Iterable[complex]], NDArray[complex, :, :]],
                # 2d+
                Fun[[NDArray[T0, :, :]], NDArray[T0, :, :]],
                Fun[[Iterable[Iterable[bool]]], NDArray[bool, :, :]],
                Fun[[Iterable[Iterable[int]]], NDArray[int, :, :]],
                Fun[[Iterable[Iterable[float]]], NDArray[float, :, :]],
                Fun[[Iterable[Iterable[complex]]], NDArray[complex, :, :]],
                # 3d
                Fun[[Iterable[Iterable[Iterable[bool]]]],
                    NDArray[bool, :, :, :]],
                Fun[[Iterable[Iterable[Iterable[int]]]],
                    NDArray[int, :, :, :]],
                Fun[[Iterable[Iterable[Iterable[float]]]],
                    NDArray[float, :, :, :]],
                Fun[[Iterable[Iterable[Iterable[complex]]]],
                    NDArray[complex, :, :, :]],
                # 4d
                Fun[[Iterable[Iterable[Iterable[Iterable[bool]]]]],
                    NDArray[bool, :, :, :, :]],
                Fun[[Iterable[Iterable[Iterable[Iterable[int]]]]],
                    NDArray[int, :, :, :, :]],
                Fun[[Iterable[Iterable[Iterable[Iterable[float]]]]],
                    NDArray[float, :, :, :, :]],
                Fun[[Iterable[Iterable[Iterable[Iterable[complex]]]]],
                    NDArray[complex, :, :, :, :]],
            ]
        ),
        "atleast_3d": ConstFunctionIntr(
            signature=Union[
                # scalar
                Fun[[bool], NDArray[bool, :, :, :]],
                Fun[[int], NDArray[int, :, :, :]],
                Fun[[float], NDArray[float, :, :, :]],
                Fun[[complex], NDArray[complex, :, :, :]],
                # 1d
                Fun[[Iterable[bool]], NDArray[bool, :, :, :]],
                Fun[[Iterable[int]], NDArray[int, :, :, :]],
                Fun[[Iterable[float]], NDArray[float, :, :, :]],
                Fun[[Iterable[complex]], NDArray[complex, :, :, :]],
                # 2d+
                Fun[[NDArray[T0, :, :]], NDArray[T0, :, :, :]],
                Fun[[Iterable[Iterable[bool]]], NDArray[bool, :, :, :]],
                Fun[[Iterable[Iterable[int]]], NDArray[int, :, :, :]],
                Fun[[Iterable[Iterable[float]]], NDArray[float, :, :, :]],
                Fun[[Iterable[Iterable[complex]]], NDArray[complex, :, :, :]],
                # 3d
                Fun[[Iterable[Iterable[Iterable[bool]]]],
                    NDArray[bool, :, :, :]],
                Fun[[Iterable[Iterable[Iterable[int]]]],
                    NDArray[int, :, :, :]],
                Fun[[Iterable[Iterable[Iterable[float]]]],
                    NDArray[float, :, :, :]],
                Fun[[Iterable[Iterable[Iterable[complex]]]],
                    NDArray[complex, :, :, :]],
                # 4d
                Fun[[Iterable[Iterable[Iterable[Iterable[bool]]]]],
                    NDArray[bool, :, :, :, :]],
                Fun[[Iterable[Iterable[Iterable[Iterable[int]]]]],
                    NDArray[int, :, :, :, :]],
                Fun[[Iterable[Iterable[Iterable[Iterable[float]]]]],
                    NDArray[float, :, :, :, :]],
                Fun[[Iterable[Iterable[Iterable[Iterable[complex]]]]],
                    NDArray[complex, :, :, :, :]],
            ]
        ),
        "average": ConstFunctionIntr(
            signature=_numpy_unary_op_average_axis_signature),
        "base_repr": ConstFunctionIntr(
            signature=Union[
                Fun[[bool], str],
                Fun[[bool, int], str],
                Fun[[bool, int, int], str],
                Fun[[int], str],
                Fun[[int, int], str],
                Fun[[int, int, int], str],
            ]
        ),
        "binary_repr": ConstFunctionIntr(
            signature=Union[
                Fun[[bool], str],
                Fun[[bool, int], str],
                Fun[[bool, None], str],
                Fun[[int], str],
                Fun[[int, int], str],
                Fun[[int, None], str],
            ]
        ),
        "bincount": ConstFunctionIntr(
            signature=Union[
                Fun[[Iterable[bool]], NDArray[int, :]],
                Fun[[Iterable[int]], NDArray[int, :]],
                #
                Fun[[Iterable[bool], Iterable[float]], NDArray[int, :]],
                Fun[[Iterable[int], Iterable[float]], NDArray[int, :]],
                #
                Fun[[Iterable[bool], Iterable[float], int], NDArray[int, :]],
                Fun[[Iterable[int], Iterable[float], int], NDArray[int, :]],
            ],
        ),
        "bitwise_and": UFunc(
            BINARY_UFUNC,
            signature=_numpy_int_binary_op_signature
        ),
        "bitwise_not": ConstFunctionIntr(
            signature=_numpy_int_unary_op_signature
        ),
        "bitwise_or": UFunc(
            BINARY_UFUNC,
            signature=_numpy_int_binary_op_signature
        ),
        "bitwise_xor": UFunc(
            BINARY_UFUNC,
            signature=_numpy_int_binary_op_signature
        ),
        "bool_": ConstFunctionIntr(signature=_bool_signature),
        "ceil": ConstFunctionIntr(signature=_numpy_float_unary_op_signature),
        "clip": ConstMethodIntr(signature=_numpy_ternary_op_signature),
        "concatenate": ConstFunctionIntr(
            args=('_', 'axis'),
            defaults=(0,),
            signature=Union[
                # 1D
                Fun[[Iterable[Iterable[bool]]], NDArray[bool, :]],
                Fun[[Tuple[Iterable[bool]]], NDArray[bool, :]],
                Fun[[Tuple[Iterable[bool], int]], NDArray[bool, :]],
                Fun[[Tuple[Iterable[bool], Iterable[bool]]], NDArray[bool, :]],
                Fun[[Tuple[Iterable[bool], Iterable[bool], int]],
                    NDArray[bool, :]],
                Fun[[Tuple[Iterable[bool], Iterable[bool],
                           Iterable[bool]]], NDArray[bool, :]],
                Fun[[Tuple[Iterable[bool], Iterable[bool],
                           Iterable[bool], int]], NDArray[bool, :]],
                Fun[[Tuple[Iterable[bool], Iterable[bool], Iterable[
                    bool], Iterable[bool]]], NDArray[bool, :]],
                Fun[[Tuple[Iterable[bool], Iterable[bool], Iterable[
                    bool], Iterable[bool], int]], NDArray[bool, :]],

                Fun[[Iterable[Iterable[int]]], NDArray[int, :]],
                Fun[[Tuple[Iterable[int]]], NDArray[int, :]],
                Fun[[Tuple[Iterable[int], int]], NDArray[int, :]],
                Fun[[Tuple[Iterable[int], Iterable[int]]], NDArray[int, :]],
                Fun[[Tuple[Iterable[int], Iterable[int], int]],
                    NDArray[int, :]],
                Fun[[Tuple[Iterable[int], Iterable[int], Iterable[int]]],
                    NDArray[int, :]],
                Fun[[Tuple[Iterable[int], Iterable[int],
                           Iterable[int], int]], NDArray[int, :]],
                Fun[[Tuple[Iterable[int], Iterable[int], Iterable[
                    int], Iterable[int]]], NDArray[int, :]],
                Fun[[Tuple[Iterable[int], Iterable[int], Iterable[
                    int], Iterable[int], int]], NDArray[int, :]],

                Fun[[Iterable[Iterable[float]]], NDArray[float, :]],
                Fun[[Tuple[Iterable[float]]], NDArray[float, :]],
                Fun[[Tuple[Iterable[float], int]], NDArray[float, :]],
                Fun[[Tuple[Iterable[float], Iterable[float]]],
                    NDArray[float, :]],
                Fun[[Tuple[Iterable[float], Iterable[float], int]],
                    NDArray[float, :]],
                Fun[[Tuple[Iterable[float], Iterable[float],
                           Iterable[float]]], NDArray[float, :]],
                Fun[[Tuple[Iterable[float], Iterable[float],
                           Iterable[float], int]], NDArray[float, :]],
                Fun[[Tuple[Iterable[float], Iterable[float], Iterable[
                    float], Iterable[float]]], NDArray[float, :]],
                Fun[[Tuple[Iterable[float], Iterable[float], Iterable[
                    float], Iterable[float], int]], NDArray[float, :]],

                Fun[[Iterable[Iterable[complex]]], NDArray[complex, :]],
                Fun[[Tuple[Iterable[complex]]], NDArray[complex, :]],
                Fun[[Tuple[Iterable[complex], int]], NDArray[complex, :]],
                Fun[[Tuple[Iterable[complex], Iterable[complex]]],
                    NDArray[complex, :]],
                Fun[[Tuple[Iterable[complex], Iterable[complex], int]],
                    NDArray[complex, :]],
                Fun[[Tuple[Iterable[complex], Iterable[complex],
                           Iterable[complex]]], NDArray[complex, :]],
                Fun[[Tuple[Iterable[complex], Iterable[complex],
                           Iterable[complex], int]], NDArray[complex, :]],
                Fun[[Tuple[Iterable[complex], Iterable[complex], Iterable[
                    complex], Iterable[complex]]], NDArray[complex, :]],
                Fun[[Tuple[Iterable[complex], Iterable[complex], Iterable[
                    complex], Iterable[complex], int]], NDArray[complex, :]],

                # 2D
                Fun[[Iterable[Iterable[Iterable[bool]]]], NDArray[bool, :, :]],
                Fun[[Tuple[Iterable[Iterable[bool]]]], NDArray[bool, :, :]],
                Fun[[Tuple[Iterable[Iterable[bool]], int]],
                    NDArray[bool, :, :]],
                Fun[[Tuple[Iterable[Iterable[bool]], Iterable[
                    Iterable[bool]]]], NDArray[bool, :, :]],
                Fun[[Tuple[Iterable[Iterable[bool]], Iterable[
                    Iterable[bool]], int]], NDArray[bool, :, :]],
                Fun[[Tuple[Iterable[Iterable[bool]], Iterable[Iterable[bool]],
                           Iterable[Iterable[bool]]]], NDArray[bool, :, :]],
                Fun[[Tuple[Iterable[Iterable[bool]], Iterable[Iterable[bool]],
                           Iterable[Iterable[bool]], int]],
                    NDArray[bool, :, :]],
                Fun[[Tuple[Iterable[Iterable[bool]], Iterable[Iterable[bool]],
                           Iterable[Iterable[bool]],
                           Iterable[Iterable[bool]]]],
                    NDArray[bool, :, :]],
                Fun[[Tuple[Iterable[Iterable[bool]],
                           Iterable[Iterable[bool]],
                           Iterable[Iterable[bool]],
                           Iterable[Iterable[bool]], int]],
                    NDArray[bool, :, :]],

                Fun[[Iterable[Iterable[Iterable[int]]]], NDArray[int, :, :]],
                Fun[[Tuple[Iterable[Iterable[int]]]], NDArray[int, :, :]],
                Fun[[Tuple[Iterable[Iterable[int]], int]], NDArray[int, :, :]],
                Fun[[Tuple[Iterable[Iterable[int]], Iterable[
                    Iterable[int]]]], NDArray[int, :, :]],
                Fun[[Tuple[Iterable[Iterable[int]], Iterable[
                    Iterable[int]], int]], NDArray[int, :, :]],
                Fun[[Tuple[Iterable[Iterable[int]], Iterable[Iterable[int]],
                           Iterable[Iterable[int]]]], NDArray[int, :, :]],
                Fun[[Tuple[Iterable[Iterable[int]], Iterable[Iterable[int]],
                           Iterable[Iterable[int]], int]], NDArray[int, :, :]],
                Fun[[Tuple[Iterable[Iterable[int]], Iterable[Iterable[int]],
                           Iterable[Iterable[int]], Iterable[Iterable[int]]]],
                    NDArray[int, :, :]],
                Fun[[Tuple[Iterable[Iterable[int]], Iterable[Iterable[int]],
                           Iterable[Iterable[int]], Iterable[Iterable[int]],
                           int]],
                    NDArray[int, :, :]],

                Fun[[Iterable[Iterable[Iterable[float]]]],
                    NDArray[float, :, :]],
                Fun[[Tuple[Iterable[Iterable[float]]]], NDArray[float, :, :]],
                Fun[[Tuple[Iterable[Iterable[float]], int]],
                    NDArray[float, :, :]],
                Fun[[Tuple[Iterable[Iterable[float]],
                           Iterable[Iterable[float]]]], NDArray[float, :, :]],
                Fun[[Tuple[Iterable[Iterable[float]],
                           Iterable[Iterable[float]], int]],
                    NDArray[float, :, :]],
                Fun[[Tuple[Iterable[Iterable[float]],
                           Iterable[Iterable[float]],
                           Iterable[Iterable[float]]]],
                    NDArray[float, :, :]],
                Fun[[Tuple[Iterable[Iterable[float]],
                           Iterable[Iterable[float]],
                           Iterable[Iterable[float]], int]],
                    NDArray[float, :, :]],
                Fun[[Tuple[Iterable[Iterable[float]],
                           Iterable[Iterable[float]],
                           Iterable[Iterable[float]],
                           Iterable[Iterable[float]]]], NDArray[float, :, :]],
                Fun[[Tuple[Iterable[Iterable[float]],
                           Iterable[Iterable[float]],
                           Iterable[Iterable[float]],
                           Iterable[Iterable[float]], int]],
                    NDArray[float, :, :]],

                Fun[[Iterable[Iterable[Iterable[complex]]]],
                    NDArray[complex, :, :]],
                Fun[[Tuple[Iterable[Iterable[complex]]]],
                    NDArray[complex, :, :]],
                Fun[[Tuple[Iterable[Iterable[complex]], int]],
                    NDArray[complex, :, :]],
                Fun[[Tuple[Iterable[Iterable[complex]],
                           Iterable[Iterable[complex]]]],
                    NDArray[complex, :, :]],
                Fun[[Tuple[Iterable[Iterable[complex]],
                           Iterable[Iterable[complex]], int]],
                    NDArray[complex, :, :]],
                Fun[[Tuple[Iterable[Iterable[complex]],
                           Iterable[Iterable[complex]],
                           Iterable[Iterable[complex]]]],
                    NDArray[complex, :, :]],
                Fun[[Tuple[Iterable[Iterable[complex]],
                           Iterable[Iterable[complex]],
                           Iterable[Iterable[complex]], int]],
                    NDArray[complex, :, :]],
                Fun[[Tuple[Iterable[Iterable[complex]],
                           Iterable[Iterable[complex]],
                           Iterable[Iterable[complex]],
                           Iterable[Iterable[complex]]]],
                    NDArray[complex, :, :]],
                Fun[[Tuple[Iterable[Iterable[complex]],
                           Iterable[Iterable[complex]],
                           Iterable[Iterable[complex]],
                           Iterable[Iterable[complex]], int]],
                    NDArray[complex, :, :]],
            ]
        ),
        "complex": ConstFunctionIntr(signature=_complex_signature),
        "complex64": ConstFunctionIntr(signature=_complex_signature),
        "complex128": ConstFunctionIntr(signature=_complex_signature),
        "conj": ConstMethodIntr(signature=_numpy_unary_op_signature),
        "conjugate": ConstMethodIntr(signature=_numpy_unary_op_signature),
        "copy": ConstMethodIntr(signature=_numpy_array_signature),
        "copyto": FunctionIntr(
            argument_effects=[UpdateEffect(), ReadEffect(),
                              ReadEffect(), ReadEffect()],
            signature=Union[
                # 1d
                Fun[[NDArray[bool, :], bool], None],
                Fun[[NDArray[bool, :], Iterable[bool]], None],
                Fun[[NDArray[int, :], int], None],
                Fun[[NDArray[int, :], Iterable[int]], None],
                Fun[[NDArray[float, :], float], None],
                Fun[[NDArray[float, :], Iterable[float]], None],
                Fun[[NDArray[complex, :], complex], None],
                Fun[[NDArray[complex, :], Iterable[complex]], None],

                # 2d
                Fun[[NDArray[bool, :, :], bool], None],
                Fun[[NDArray[bool, :, :], Iterable[bool]], None],
                Fun[[NDArray[bool, :, :], Iterable[Iterable[bool]]], None],
                Fun[[NDArray[int, :, :], int], None],
                Fun[[NDArray[int, :, :], Iterable[int]], None],
                Fun[[NDArray[int, :, :], Iterable[Iterable[int]]], None],
                Fun[[NDArray[float, :, :], float], None],
                Fun[[NDArray[float, :, :], Iterable[float]], None],
                Fun[[NDArray[float, :, :], Iterable[Iterable[float]]], None],
                Fun[[NDArray[complex, :, :], complex], None],
                Fun[[NDArray[complex, :, :], Iterable[complex]], None],
                Fun[[NDArray[complex, :, :],
                     Iterable[Iterable[complex]]], None],

                # 3d
                Fun[[NDArray[bool, :, :, :], bool], None],
                Fun[[NDArray[bool, :, :, :], Iterable[bool]], None],
                Fun[[NDArray[bool, :, :, :], Iterable[Iterable[bool]]], None],
                Fun[[NDArray[bool, :, :, :],
                     Iterable[Iterable[Iterable[bool]]]], None],
                Fun[[NDArray[int, :, :, :], int], None],
                Fun[[NDArray[int, :, :, :], Iterable[int]], None],
                Fun[[NDArray[int, :, :, :], Iterable[Iterable[int]]], None],
                Fun[[NDArray[int, :, :, :],
                     Iterable[Iterable[Iterable[int]]]], None],
                Fun[[NDArray[float, :, :, :], float], None],
                Fun[[NDArray[float, :, :, :],
                     Iterable[float]], None],
                Fun[[NDArray[float, :, :, :],
                     Iterable[Iterable[float]]], None],
                Fun[[NDArray[float, :, :, :],
                     Iterable[Iterable[Iterable[float]]]], None],
                Fun[[NDArray[complex, :, :, :],
                     complex], None],
                Fun[[NDArray[complex, :, :, :], Iterable[complex]], None],
                Fun[[NDArray[complex, :, :, :],
                     Iterable[Iterable[complex]]], None],
                Fun[[NDArray[complex, :, :, :],
                     Iterable[Iterable[Iterable[complex]]]], None],
            ]
        ),
        "copysign": ConstFunctionIntr(
            signature=_numpy_binary_op_float_signature
        ),
        "count_nonzero": ConstFunctionIntr(
            signature=Union[
                # scalar
                Fun[[bool], int],
                Fun[[int], int],
                Fun[[float], int],
                Fun[[complex], int],
                # 1d
                Fun[[Iterable[bool]], int],
                Fun[[Iterable[int]], int],
                Fun[[Iterable[float]], int],
                Fun[[Iterable[complex]], int],
                # 2d
                Fun[[Iterable[Iterable[bool]]], int],
                Fun[[Iterable[Iterable[int]]], int],
                Fun[[Iterable[Iterable[float]]], int],
                Fun[[Iterable[Iterable[complex]]], int],
                # 3d
                Fun[[Iterable[Iterable[Iterable[bool]]]], int],
                Fun[[Iterable[Iterable[Iterable[int]]]], int],
                Fun[[Iterable[Iterable[Iterable[float]]]], int],
                Fun[[Iterable[Iterable[Iterable[complex]]]], int],
                # 4d
                Fun[[Iterable[Iterable[Iterable[Iterable[bool]]]]], int],
                Fun[[Iterable[Iterable[Iterable[Iterable[int]]]]], int],
                Fun[[Iterable[Iterable[Iterable[Iterable[float]]]]], int],
                Fun[[Iterable[Iterable[Iterable[Iterable[complex]]]]], int],
            ]
        ),
        "cos": ConstFunctionIntr(
            signature=_numpy_unary_op_float_signature
        ),
        "cosh": ConstFunctionIntr(
            signature=_numpy_unary_op_float_signature
        ),
        "ctypeslib": {
            "as_array": ConstFunctionIntr()
        },
        "cumprod": ConstMethodIntr(
            signature=_numpy_unary_op_cumsum_axis_signature
        ),
        "cumproduct": ConstFunctionIntr(
            signature=_numpy_unary_op_cumsum_axis_signature
        ),
        "cumsum": ConstMethodIntr(
            signature=_numpy_unary_op_cumsum_axis_signature
        ),
        "deg2rad": ConstFunctionIntr(
            signature=_numpy_float_unary_op_float_signature
        ),
        "degrees": ConstFunctionIntr(
            signature=_numpy_float_unary_op_float_signature
        ),
        "delete_": ConstFunctionIntr(),
        "diag": ConstFunctionIntr(),
        "diagflat": ConstFunctionIntr(),
        "diagonal": ConstMethodIntr(),
        "diff": ConstFunctionIntr(),
        "digitize": ConstFunctionIntr(),
        "divide": UFunc(BINARY_UFUNC),
        "dot": ConstMethodIntr(),
        "double_": ConstFunctionIntr(signature=_float_signature),
        "e": ConstantIntr(),
        "ediff1d": ConstFunctionIntr(),
        "empty": ConstFunctionIntr(args=('shape', 'dtype'),
                                   defaults=("numpy.float64",),
                                   signature=_numpy_ones_signature,
                                   ),
        "empty_like": ConstFunctionIntr(
            args=('a', 'dtype'),
            defaults=("numpy.float64",),
            signature=_numpy_ones_like_signature
        ),
        "equal": UFunc(BINARY_UFUNC),
        "exp": ConstFunctionIntr(signature=_numpy_unary_op_float_signature),
        "expm1": ConstFunctionIntr(),
        "eye": ConstFunctionIntr(),
        "fabs": ConstFunctionIntr(),
        "fill_diagonal": FunctionIntr(
            argument_effects=[UpdateEffect(), ReadEffect()],
            signature=Union[
                Fun[[NDArray[T0, :], bool], None],
                Fun[[NDArray[T0, :], int], None],
                Fun[[NDArray[T0, :], float], None],
                Fun[[NDArray[T0, :], complex], None],
            ]
        ),
        "finfo": ClassWithConstConstructor(CLASSES['finfo']),
        "fix": ConstFunctionIntr(),
        "flatnonzero": ConstFunctionIntr(),
        "fliplr": ConstFunctionIntr(),
        "flip": ConstFunctionIntr(),
        "flipud": ConstFunctionIntr(),
        "float32": ConstFunctionIntr(signature=_float_signature),
        "float64": ConstFunctionIntr(signature=_float_signature),
        "float_": ConstFunctionIntr(signature=_float_signature),
        "floor": ConstFunctionIntr(signature=_numpy_float_unary_op_signature),
        "floor_divide": UFunc(BINARY_UFUNC),
        "fmax": UFunc(BINARY_UFUNC),
        "fmin": UFunc(BINARY_UFUNC),
        "fmod": UFunc(BINARY_UFUNC),
        "frexp": ConstFunctionIntr(),
        "fromfunction": ConstFunctionIntr(),
        "fromiter": ConstFunctionIntr(),
        "fromstring": ConstFunctionIntr(),
        "greater": UFunc(
            BINARY_UFUNC,
            signature=_numpy_binary_op_bool_signature,
        ),
        "greater_equal": UFunc(
            BINARY_UFUNC,
            signature=_numpy_binary_op_bool_signature,
        ),
        "hstack": ConstFunctionIntr(),
        "hypot": UFunc(BINARY_UFUNC),
        "identity": ConstFunctionIntr(),
        "imag": FunctionIntr(),
        "indices": ConstFunctionIntr(),
        "inf": ConstantIntr(),
        "inner": ConstFunctionIntr(),
        "insert": ConstFunctionIntr(),
        "intersect1d": ConstFunctionIntr(),
        "int16": ConstFunctionIntr(signature=_int_signature),
        "int32": ConstFunctionIntr(signature=_int_signature),
        "int64": ConstFunctionIntr(signature=_int_signature),
        "int8": ConstFunctionIntr(signature=_int_signature),
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
        "ldexp": UFunc(BINARY_UFUNC),
        "left_shift": UFunc(
            BINARY_UFUNC,
            signature=_numpy_int_binary_op_signature,
        ),
        "less": UFunc(
            BINARY_UFUNC,
            signature=_numpy_binary_op_bool_signature,
        ),
        "less_equal": UFunc(
            BINARY_UFUNC,
            signature=_numpy_binary_op_bool_signature,
        ),
        "lexsort": ConstFunctionIntr(),
        "linalg": {
            "norm": FunctionIntr(args=('x', 'ord', 'axis'),
                                 defaults=(None, None)),
            "matrix_power": ConstFunctionIntr(),
        },
        "linspace": ConstFunctionIntr(),
        "log": ConstFunctionIntr(),
        "log10": ConstFunctionIntr(),
        "log1p": ConstFunctionIntr(),
        "log2": ConstFunctionIntr(),
        "logaddexp": UFunc(BINARY_UFUNC),
        "logaddexp2": UFunc(BINARY_UFUNC),
        "logspace": ConstFunctionIntr(),
        "logical_and": UFunc(
            BINARY_UFUNC,
            signature=_numpy_int_binary_op_signature
        ),
        "logical_not": ConstFunctionIntr(),
        "logical_or": UFunc(
            BINARY_UFUNC,
            signature=_numpy_int_binary_op_signature
        ),
        "logical_xor": UFunc(
            BINARY_UFUNC,
            signature=_numpy_int_binary_op_signature
        ),
        "max": ConstMethodIntr(signature=_numpy_unary_op_axis_signature),
        "maximum": UFunc(
            BINARY_UFUNC,
            signature=_numpy_binary_op_signature
        ),
        "mean": ConstMethodIntr(),
        "median": ConstFunctionIntr(
            signature=_numpy_unary_op_sum_axis_signature
        ),
        "min": ConstMethodIntr(signature=_numpy_unary_op_axis_signature),
        "minimum": UFunc(
            BINARY_UFUNC,
            signature=_numpy_binary_op_signature
        ),
        "mod": UFunc(BINARY_UFUNC),
        "multiply": UFunc(
            BINARY_UFUNC,
            signature=_numpy_binary_op_signature,
        ),
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
        "ndim": ConstFunctionIntr(return_range=interval.positive_values),
        "negative": ConstFunctionIntr(signature=_numpy_unary_op_signature),
        "newaxis": ConstantIntr(),
        "nextafter": UFunc(BINARY_UFUNC),
        "NINF": ConstantIntr(),
        "nonzero": ConstMethodIntr(),
        "not_equal": UFunc(BINARY_UFUNC),
        "ones": ConstFunctionIntr(signature=_numpy_ones_signature),
        "ones_like": ConstFunctionIntr(signature=_numpy_ones_like_signature),
        "outer": ConstFunctionIntr(),
        "pi": ConstantIntr(),
        "place": FunctionIntr(),
        "power": UFunc(
            BINARY_UFUNC,
            signature=_numpy_binary_op_signature
        ),
        "prod": ConstMethodIntr(),
        "product": ConstFunctionIntr(),
        "ptp": ConstMethodIntr(),
        "put": MethodIntr(),
        "putmask": FunctionIntr(),
        "rad2deg": ConstFunctionIntr(
            signature=_numpy_float_unary_op_float_signature
        ),
        "radians": ConstFunctionIntr(
            signature=_numpy_float_unary_op_float_signature
        ),
        "random": {
            "binomial": FunctionIntr(args=('n', 'p', 'size'),
                                     global_effects=True),
            "bytes": FunctionIntr(args=('length',),
                                  global_effects=True),
            "choice": FunctionIntr(args=('a', 'size', 'replace', 'p'),
                                   global_effects=True),
            "poisson": FunctionIntr(args=('lam', 'size',),
                                    defaults=(1.0, None,),
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
            "seed": FunctionIntr(global_effects=True),
            "shuffle": FunctionIntr(global_effects=True),
            "standard_normal": FunctionIntr(args=('size',),
                                            global_effects=True),
        },
        "rank": ConstFunctionIntr(),
        "ravel": ConstMethodIntr(),
        "real": FunctionIntr(),
        "reciprocal": ConstFunctionIntr(),
        "remainder": UFunc(BINARY_UFUNC),
        "repeat": ConstMethodIntr(),
        "reshape": ConstMethodIntr(
            signature=Union[
                Fun[[NDArray[T0, :], int], NDArray[T1, :]],
                Fun[[NDArray[T0, :], Tuple[int]], NDArray[T1, :]],
                Fun[[NDArray[T0, :], int, int], NDArray[T1, :, :]],
                Fun[[NDArray[T0, :], Tuple[int, int]], NDArray[T1, :, :]],
                Fun[[NDArray[T0, :], int, int, int],
                    NDArray[T1, :, :, :]],
                Fun[[NDArray[T0, :], Tuple[int, int, int]],
                    NDArray[T1, :, :, :]],
                Fun[[NDArray[T0, :], int, int, int, int],
                    NDArray[T1, :, :, :, :]],
                Fun[[NDArray[T0, :], Tuple[int, int, int, int]],
                    NDArray[T1, :, :, :, :]],
            ]
        ),
        "resize": ConstMethodIntr(),
        "right_shift": UFunc(
            BINARY_UFUNC,
            signature=_numpy_int_binary_op_signature,
        ),
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
        "sin": ConstFunctionIntr(signature=_numpy_unary_op_float_signature),
        "sinh": ConstFunctionIntr(signature=_numpy_unary_op_float_signature),
        "size": ConstFunctionIntr(return_range=interval.positive_values),
        "sometrue": ConstFunctionIntr(),
        "sort": ConstFunctionIntr(),
        "sort_complex": ConstFunctionIntr(),
        "spacing": ConstFunctionIntr(),
        "split": ConstFunctionIntr(),
        "sqrt": ConstFunctionIntr(signature=_numpy_unary_op_float_signature),
        "square": ConstFunctionIntr(),
        "std_": ConstMethodIntr(args=('a', 'axis', 'dtype'),
                                defaults=(None, None)),
        "subtract": UFunc(
            BINARY_UFUNC,
            signature=_numpy_binary_op_signature,
        ),
        "sum": ConstMethodIntr(signature=_numpy_unary_op_sum_axis_signature),
        "swapaxes": ConstMethodIntr(),
        "take": ConstMethodIntr(),
        "tan": ConstFunctionIntr(signature=_numpy_unary_op_float_signature),
        "tanh": ConstFunctionIntr(signature=_numpy_unary_op_float_signature),
        "tile": ConstFunctionIntr(),
        "trace": ConstMethodIntr(),
        "transpose": ConstMethodIntr(),
        "tri": ConstMethodIntr(),
        "tril": ConstMethodIntr(),
        "trim_zeros": ConstMethodIntr(),
        "triu": ConstMethodIntr(),
        "true_divide": UFunc(BINARY_UFUNC),
        "trunc": ConstFunctionIntr(),
        "ubyte": ConstFunctionIntr(signature=_int_signature),
        "uint16": ConstFunctionIntr(signature=_int_signature),
        "uint32": ConstFunctionIntr(signature=_int_signature),
        "uint64": ConstFunctionIntr(signature=_int_signature),
        "uint8": ConstFunctionIntr(signature=_int_signature),
        "union1d": ConstFunctionIntr(),
        "unique": ConstFunctionIntr(),
        "unwrap": ConstFunctionIntr(),
        "var": ConstMethodIntr(),
        "vstack": ConstFunctionIntr(),
        "where": ConstFunctionIntr(),
        "zeros": ConstFunctionIntr(args=('shape', 'dtype'),
                                   defaults=("numpy.float64",),
                                   signature=_numpy_ones_signature,
                                   ),
        "zeros_like": ConstFunctionIntr(signature=_numpy_ones_like_signature),
    },
    "time": {
        "sleep": FunctionIntr(
            signature=Fun[[float], None],
            global_effects=True
        ),
        "time": FunctionIntr(
            signature=Fun[[], float],
            global_effects=True
        ),
    },
    "math": {
        "isinf": ConstFunctionIntr(signature=Fun[[float], bool]),
        "modf": ConstFunctionIntr(signature=Fun[[float], Tuple[float, float]]),
        "frexp": ConstFunctionIntr(signature=Fun[[float], Tuple[float, int]]),
        "factorial": ConstFunctionIntr(signature=Fun[[int], int]),
        "gamma": ConstFunctionIntr(signature=Fun[[float], float]),
        "lgamma": ConstFunctionIntr(signature=Fun[[float], float]),
        "trunc": ConstFunctionIntr(signature=Fun[[float], int]),
        "erf": ConstFunctionIntr(signature=Fun[[float], float]),
        "erfc": ConstFunctionIntr(signature=Fun[[float], float]),
        "asinh": ConstFunctionIntr(signature=Fun[[float], float]),
        "atanh": ConstFunctionIntr(signature=Fun[[float], float]),
        "acosh": ConstFunctionIntr(signature=Fun[[float], float]),
        "radians": ConstFunctionIntr(signature=Fun[[float], float]),
        "degrees": ConstFunctionIntr(signature=Fun[[float], float]),
        "hypot": ConstFunctionIntr(signature=Fun[[float, float], float]),
        "tanh": ConstFunctionIntr(signature=Fun[[float], float]),
        "cosh": ConstFunctionIntr(signature=Fun[[float], float]),
        "sinh": ConstFunctionIntr(signature=Fun[[float], float]),
        "atan": ConstFunctionIntr(signature=Fun[[float], float]),
        "atan2": ConstFunctionIntr(signature=Fun[[float, float], float]),
        "asin": ConstFunctionIntr(signature=Fun[[float], float]),
        "tan": ConstFunctionIntr(signature=Fun[[float], float]),
        "log": ConstFunctionIntr(signature=Fun[[float], float]),
        "log1p": ConstFunctionIntr(signature=Fun[[float], float]),
        "expm1": ConstFunctionIntr(signature=Fun[[float], float]),
        "ldexp": ConstFunctionIntr(signature=Fun[[float, int], float]),
        "fmod": ConstFunctionIntr(signature=Fun[[float, float], float]),
        "fabs": ConstFunctionIntr(signature=Fun[[float], float]),
        "copysign": UFunc(BINARY_UFUNC),
        "acos": ConstFunctionIntr(signature=Fun[[float], float]),
        "cos": ConstFunctionIntr(signature=Fun[[float], float]),
        "sin": ConstFunctionIntr(signature=Fun[[float], float]),
        "exp": ConstFunctionIntr(signature=Fun[[float], float]),
        "sqrt": ConstFunctionIntr(signature=Fun[[float], float]),
        "log10": ConstFunctionIntr(signature=Fun[[float], float]),
        "isnan": ConstFunctionIntr(signature=Fun[[float], bool]),
        "ceil": ConstFunctionIntr(signature=Fun[[float], float]),
        "floor": ConstFunctionIntr(signature=Fun[[float], float]),
        "pow": ConstFunctionIntr(signature=Fun[[float, float], float]),
        "pi": ConstantIntr(signature=float),
        "e": ConstantIntr(signature=float),
    },
    "functools": {
        "partial": FunctionIntr(
            signature=Union[
                # no arg
                Fun[[Fun[[], T0]], Fun[[], T0]],
                # 1 arg
                Fun[[Fun[[T0], T1]], Fun[[T0], T1]],
                Fun[[Fun[[T0], T1], T0], Fun[[], T1]],
                # 2 args
                Fun[[Fun[[T0, T1], T2]], Fun[[T0, T1], T2]],
                Fun[[Fun[[T0, T1], T2], T0], Fun[[T1], T2]],
                Fun[[Fun[[T0, T1], T2], T0, T1], Fun[[], T2]],
                # 3 args
                Fun[[Fun[[T0, T1, T2], T3]], Fun[[T0, T1, T2], T3]],
                Fun[[Fun[[T0, T1, T2], T3], T0], Fun[[T1, T2], T3]],
                Fun[[Fun[[T0, T1, T2], T3], T0, T1], Fun[[T2], T3]],
                Fun[[Fun[[T0, T1, T2], T3], T0, T1, T2], Fun[[], T3]],
                # 4 args
                Fun[[Fun[[T0, T1, T2, T3], T4]], Fun[[T0, T1, T2, T3], T4]],
                Fun[[Fun[[T0, T1, T2, T3], T4], T0], Fun[[T1, T2, T3], T4]],
                Fun[[Fun[[T0, T1, T2, T3], T4], T0, T1], Fun[[T2, T3], T4]],
                Fun[[Fun[[T0, T1, T2, T3], T4], T0, T1, T2], Fun[[T3], T4]],
                Fun[[Fun[[T0, T1, T2, T3], T4], T0, T1, T2, T3], Fun[[], T4]],
                # 5 args
                Fun[[Fun[[T0, T1, T2, T3, T4], T5]],
                    Fun[[T0, T1, T2, T3, T4], T5]],
                Fun[[Fun[[T0, T1, T2, T3, T4], T5], T0],
                    Fun[[T1, T2, T3, T4], T5]],
                Fun[[Fun[[T0, T1, T2, T3, T4], T5], T0, T1],
                    Fun[[T2, T3, T4], T5]],
                Fun[[Fun[[T0, T1, T2, T3, T4], T5], T0, T1, T2],
                    Fun[[T3, T4], T5]],
                Fun[[Fun[[T0, T1, T2, T3, T4], T5], T0, T1, T2, T3],
                    Fun[[T4], T5]],
                Fun[[Fun[[T0, T1, T2, T3, T4], T5], T0, T1, T2, T3, T4],
                    Fun[[], T5]],
                # 6 args
                Fun[[Fun[[T0, T1, T2, T3, T4, T5], T6]],
                    Fun[[T0, T1, T2, T3, T4, T5], T6]],
                Fun[[Fun[[T0, T1, T2, T3, T4, T5], T6],
                     T0], Fun[[T1, T2, T3, T4, T5], T6]],
                Fun[[Fun[[T0, T1, T2, T3, T4, T5], T6],
                     T0, T1], Fun[[T2, T3, T4, T5], T6]],
                Fun[[Fun[[T0, T1, T2, T3, T4, T5], T6],
                     T0, T1, T2], Fun[[T3, T4, T5], T6]],
                Fun[[Fun[[T0, T1, T2, T3, T4, T5], T6],
                     T0, T1, T2, T3], Fun[[T4, T5], T6]],
                Fun[[Fun[[T0, T1, T2, T3, T4, T5], T6],
                     T0, T1, T2, T3, T4], Fun[[T5], T6]],
                Fun[[Fun[[T0, T1, T2, T3, T4, T5], T6],
                     T0, T1, T2, T3, T4, T5], Fun[[], T6]],
            ]
        ),
        "reduce": ReadOnceFunctionIntr(signature=_functools_reduce_signature),
    },
    "bisect": {
        "bisect_left": ConstFunctionIntr(
            signature=Union[
                Fun[[List[T0], T0], int],
                Fun[[List[T0], T0, int], int],
                Fun[[List[T0], T0, int, int], int],
            ],
            return_range=interval.positive_values
        ),
        "bisect_right": ConstFunctionIntr(
            signature=Union[
                Fun[[List[T0], T0], int],
                Fun[[List[T0], T0, int], int],
                Fun[[List[T0], T0, int, int], int],
            ],
            return_range=interval.positive_values
        ),
        "bisect": ConstFunctionIntr(
            signature=Union[
                Fun[[List[T0], T0], int],
                Fun[[List[T0], T0, int], int],
                Fun[[List[T0], T0, int, int], int],
            ],
            return_range=interval.positive_values
        ),
    },
    "cmath": {
        "cos": FunctionIntr(
            signature=Union[
                Fun[[float], complex],
                Fun[[complex], complex],
            ],
        ),
        "sin": FunctionIntr(
            signature=Union[
                Fun[[float], complex],
                Fun[[complex], complex],
            ],
        ),
        "exp": FunctionIntr(
            signature=Union[
                Fun[[float], complex],
                Fun[[complex], complex],
            ],
        ),
        "sqrt": FunctionIntr(
            signature=Union[
                Fun[[float], complex],
                Fun[[complex], complex],
            ],
        ),
        "log10": FunctionIntr(
            signature=Union[
                Fun[[float], complex],
                Fun[[complex], complex],
            ],
        ),
        "isnan": FunctionIntr(
            signature=Union[
                Fun[[float], bool],
                Fun[[complex], bool],
            ],
        ),
        "pi": ConstantIntr(signature=float),
        "e": ConstantIntr(signature=float),
    },
    "itertools": {
        "count": ReadOnceFunctionIntr(
            signature=Union[
                Fun[[], Generator[int]],
                Fun[[int], Generator[int]],
                Fun[[int, int], Generator[int]],
            ]
        ),
        "imap": ReadOnceFunctionIntr(
            signature=Union[
                Fun[[None, Iterable[T0]], List[Tuple[T0]]],
                Fun[[None, Iterable[T0], Iterable[T1]], List[Tuple[T0, T1]]],
                Fun[[None, Iterable[T0], Iterable[T1], Iterable[T2]],
                    List[Tuple[T0, T1, T2]]],
                Fun[[None, Iterable[T0], Iterable[T1], Iterable[T2],
                     Iterable[T3]], List[Tuple[T0, T1, T2, T3]]],
                Fun[[Fun[[T0], T7], Iterable[T0]], List[T7]],
                Fun[[Fun[[T0, T1], T7], Iterable[T0], Iterable[T1]], List[T7]],
                Fun[[Fun[[T0, T1, T2], T7], Iterable[T0], Iterable[T1],
                     Iterable[T2]], List[T7]],
                Fun[[Fun[[T0, T1, T2, T3], T7], Iterable[T0], Iterable[T1],
                     Iterable[T2], Iterable[T3]], List[T7]],
            ]
        ),
        "ifilter": ReadOnceFunctionIntr(
            signature=Union[
                Fun[[None, Iterable[T0]], Generator[T0]],
                Fun[[Fun[[T0], bool], Iterable[T0]], Generator[T0]],
            ],
        ),
        "islice": ReadOnceFunctionIntr(),
        "product": ConstFunctionIntr(
            signature=Union[
                Fun[[], Generator[T0]],
                Fun[[Iterable[T0]], Generator[Tuple[T0]]],
                Fun[[Iterable[T0], Iterable[T1]], Generator[Tuple[T0, T1]]],
                Fun[[Iterable[T0], Iterable[T1], Iterable[T2]],
                    Generator[Tuple[T0, T1, T2]]],
                Fun[[Iterable[T0], Iterable[T1], Iterable[T2], Iterable[T3]],
                    Generator[Tuple[T0, T1, T2, T3]]],
            ],
        ),
        "izip": ReadOnceFunctionIntr(
            signature=Union[
                Fun[[], Generator[T0]],
                Fun[[Iterable[T0]], Generator[Tuple[T0]]],
                Fun[[Iterable[T0], Iterable[T1]], Generator[Tuple[T0, T1]]],
                Fun[[Iterable[T0], Iterable[T1], Iterable[T2]],
                    Generator[Tuple[T0, T1, T2]]],
                Fun[[Iterable[T0], Iterable[T1], Iterable[T2], Iterable[T3]],
                    Generator[Tuple[T0, T1, T2, T3]]],
            ]
        ),
        "combinations": ConstFunctionIntr(
            signature=Fun[[Iterable[T0], int], Generator[List[T0]]]),
        "permutations": ConstFunctionIntr(
            signature=Union[
                Fun[[Iterable[T0]], Generator[List[T0]]],
                Fun[[Iterable[T0], int], Generator[List[T0]]],
            ],
        ),
    },
    "random": {
        "seed": FunctionIntr(
            signature=Union[
                Fun[[], None],
                Fun[[T0], None],
            ],
            global_effects=True
        ),
        "random": FunctionIntr(
            signature=Fun[[], float],
            global_effects=True
        ),
        "randint": FunctionIntr(
            signature=Fun[[int, int], int],
            global_effects=True
        ),
        "randrange": FunctionIntr(
            signature=Union[
                Fun[[int], int],
                Fun[[int, int], int],
                Fun[[int, int, int], int]
            ],
            global_effects=True
        ),
        "gauss": FunctionIntr(
            signature=Fun[[float, float], float],
            global_effects=True
        ),
        "uniform": FunctionIntr(
            signature=Fun[[float, float], float],
            global_effects=True
        ),
        "expovariate": FunctionIntr(
            signature=Fun[[float], float],
            global_effects=True
        ),
        "sample": FunctionIntr(
            signature=Fun[[Iterable[T0], int], List[T0]],
            global_effects=True
        ),
        "choice": FunctionIntr(
            signature=Fun[[Iterable[T0]], T0],
            global_effects=True
        ),
        "shuffle": FunctionIntr(
            signature=Union[
                Fun[[List[T0]], None],
                Fun[[List[T0], Fun[[], float]], None],
            ],
            global_effects=True
        ),
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
        "lt": ConstFunctionIntr(signature=_operator_eq_signature),
        "le": ConstFunctionIntr(signature=_operator_eq_signature),
        "eq": ConstFunctionIntr(signature=_operator_eq_signature),
        "ne": ConstFunctionIntr(signature=_operator_eq_signature),
        "ge": ConstFunctionIntr(signature=_operator_eq_signature),
        "gt": ConstFunctionIntr(signature=_operator_eq_signature),
        "__lt__": ConstFunctionIntr(signature=_operator_eq_signature),
        "__le__": ConstFunctionIntr(signature=_operator_eq_signature),
        "__eq__": ConstFunctionIntr(signature=_operator_eq_signature),
        "__ne__": ConstFunctionIntr(signature=_operator_eq_signature),
        "__ge__": ConstFunctionIntr(signature=_operator_eq_signature),
        "__gt__": ConstFunctionIntr(signature=_operator_eq_signature),
        "not_": ConstFunctionIntr(),
        "__not__": ConstFunctionIntr(),
        "truth": ConstFunctionIntr(),
        "is_": ConstFunctionIntr(),
        "is_not": ConstFunctionIntr(),
        "abs": ConstFunctionIntr(),
        "__abs__": ConstFunctionIntr(),
        "add": ConstFunctionIntr(signature=_operator_add_signature),
        "__add__": ConstFunctionIntr(signature=_operator_add_signature),
        "and_": ConstFunctionIntr(),
        "__and__": ConstFunctionIntr(),
        "div": ConstFunctionIntr(signature=_numpy_binary_op_signature),
        "__div__": ConstFunctionIntr(signature=_numpy_binary_op_signature),
        "floordiv": ConstFunctionIntr(signature=_numpy_binary_op_signature),
        "__floordiv__": ConstFunctionIntr(
            signature=_numpy_binary_op_signature
        ),
        "inv": ConstFunctionIntr(),
        "invert": ConstFunctionIntr(),
        "__inv__": ConstFunctionIntr(),
        "__invert__": ConstFunctionIntr(),
        "lshift": ConstFunctionIntr(signature=_numpy_int_binary_op_signature),
        "__lshift__": ConstFunctionIntr(
            signature=_numpy_int_binary_op_signature
        ),
        "matmul": ConstFunctionIntr(signature=_operator_mul_signature),
        "__matmul__": ConstFunctionIntr(signature=_operator_mul_signature),
        "mod": ConstFunctionIntr(signature=_operator_mod_signature),
        "__mod__": ConstFunctionIntr(signature=_operator_mod_signature),
        "mul": ConstFunctionIntr(signature=_operator_mul_signature),
        "__mul__": ConstFunctionIntr(signature=_operator_mul_signature),
        "neg": ConstFunctionIntr(),
        "__neg__": ConstFunctionIntr(),
        "or_": ConstFunctionIntr(),
        "__or__": ConstFunctionIntr(),
        "pos": ConstFunctionIntr(signature=_numpy_unary_op_signature),
        "__pos__": ConstFunctionIntr(signature=_numpy_unary_op_signature),
        "rshift": ConstFunctionIntr(signature=_numpy_int_binary_op_signature),
        "__rshift__": ConstFunctionIntr(
            signature=_numpy_int_binary_op_signature
        ),
        "sub": ConstFunctionIntr(signature=_operator_sub_signature),
        "__sub__": ConstFunctionIntr(signature=_operator_sub_signature),
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
        "contains": MethodIntr(
            update_effects,
            signature=_operator_contains_signature
        ),
        "__contains__": MethodIntr(
            update_effects,
            signature=_operator_contains_signature
        ),
        "countOf": ConstFunctionIntr(),
        "delitem": FunctionIntr(
            argument_effects=[UpdateEffect(), ReadEffect()]),
        "__delitem__": FunctionIntr(
            argument_effects=[UpdateEffect(), ReadEffect()]),
        "getitem": ConstFunctionIntr(signature=_operator_getitem_signature),
        "__getitem__": ConstFunctionIntr(
            signature=_operator_getitem_signature
        ),
        "indexOf": ConstFunctionIntr(),
        "__theitemgetter__": ConstFunctionIntr(),
        "itemgetter": MethodIntr(
            return_alias=lambda _: {
                MODULES['operator_']['__theitemgetter__']}
        ),

    },
    "string": {
        "ascii_lowercase": ConstantIntr(signature=str),
        "ascii_uppercase": ConstantIntr(signature=str),
        "ascii_letters": ConstantIntr(signature=str),
        "digits": ConstantIntr(signature=str),
        "find": ConstFunctionIntr(
            signature=Union[
                Fun[[str, str], int],
                Fun[[str, str, Optional[int]], int],
                Fun[[str, str, Optional[int], Optional[int]], int],
            ],
        ),
        "hexdigits": ConstantIntr(signature=str),
        "octdigits": ConstantIntr(signature=str),
    },
    "os": {
        "path": {
            "join": ConstFunctionIntr(
                signature=Union[
                    Fun[[str], str],
                    Fun[[str, str], str],
                    Fun[[str, str, str], str],
                    Fun[[str, str, str, str], str],
                    Fun[[str, str, str, str, str], str],
                ]
            ),
        }
    },
    # conflicting method names must be listed here
    "__dispatch__": {
        "clear": MethodIntr(signature=Fun[[T0], None]),
        "conjugate": ConstMethodIntr(),
        "copy": ConstMethodIntr(signature=Fun[[T0], T0]),
        "count": ConstMethodIntr(
            signature=Union[
                Fun[[Iterable[T0], T0], int],
                Fun[[Iterable[T0], T0, int], int],
                Fun[[Iterable[T0], T0, int, int], int],
            ],
            return_range=interval.positive_values
        ),
        "next": MethodIntr(global_effects=True),  # because of file.next
        "pop": MethodIntr(),
        "remove": MethodIntr(),
        "update": MethodIntr(update_effects),
    },
}

if sys.version_info.major == 3:
    del MODULES['string']['find']
    del MODULES['itertools']['imap']
    del MODULES['itertools']['izip']
    del MODULES['itertools']['ifilter']
    del MODULES['operator_']['idiv']
    del MODULES['operator_']['__idiv__']
    del MODULES['operator_']['div']
    del MODULES['operator_']['__div__']
    del MODULES['__builtin__']['cmp']
    del MODULES['__builtin__']['file']
    del MODULES['__builtin__']['long_']
    del MODULES['__builtin__']['StandardError']
    MODULES['__builtin__']['print'] = FunctionIntr(global_effects=True)
    MODULES['io'] = {
        '_io': {
            "TextIOWrapper": ClassWithConstConstructor(
                CLASSES['file'], global_effects=True)
        }
    }
else:
    del MODULES['operator_']['matmul']
    del MODULES['operator_']['__matmul__']

# VMSError is only available on VMS
if 'VMSError' in sys.modules['__builtin__'].__dict__:
    MODULES['__builtin__']['VMSError'] = ConstExceptionIntr()

# WindowsError is only available on Windows
if 'WindowsError' in sys.modules['__builtin__'].__dict__:
    MODULES['__builtin__']['WindowsError'] = ConstExceptionIntr()

# detect and prune unsupported modules
for module_name in ["omp", "scipy.special", "scipy"]:
    try:
        __import__(module_name)
    except ImportError:
        logger.warn(
            "Pythran support disabled for module: {}".format(module_name)
        )
        parts = module_name.split(".")
        del reduce(lambda m, field: m[field], parts[:-1], MODULES)[parts[-1]]

# check and delete unimplemented numpy methods
for method in list(MODULES['numpy'].keys()):
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
                spec = getargspec(obj)
                assert not signature.args.args

                signature.args.args

                args = [ast.Name(arg, ast.Param(), None) for arg in spec.args]
                defaults = spec.defaults

                # Avoid use of comprehesion to fill "as much args/defauls" as
                # possible
                signature.args.args = args[:-len(defaults)]
                signature.args.defaults = []
                for arg, value in zip(args[-len(defaults):], defaults):
                    signature.args.defaults.append(to_ast(value))
                    signature.args.args.append(arg)
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
            intrinsic.signature = type(cst)

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
