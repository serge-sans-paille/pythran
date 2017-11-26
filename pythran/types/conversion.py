""" Module to convert Python type to Pythonic type. """

import sys

from numpy import int8, int16, int32, int64, uint8, uint16, uint32
from numpy import float64, float32, complex64, complex128, uint64
from pythran.typing import List, Dict, Set, Tuple, NDArray, NDArray, Pointer
from pythran.typing import Fun

PYTYPE_TO_CTYPE_TABLE = {
    complex: 'std::complex<double>',
    bool: 'bool',
    int: 'long',
    float: 'double',
    str: 'pythonic::types::str',
    type(None): 'pythonic::types::none_type',
    int8: 'int8_t',
    int16: 'int16_t',
    int32: 'int32_t',
    int64: 'int64_t',
    uint8: 'uint8_t',
    uint16: 'uint16_t',
    uint32: 'uint32_t',
    uint64: 'uint64_t',
    float32: 'float',
    float64: 'double',
    complex64: 'std::complex<float>',
    complex128: 'std::complex<double>',
}

TYPE_TO_SUFFIX = {
    int: "L",
    }

if sys.version_info.major == 2:
    PYTYPE_TO_CTYPE_TABLE[long] = 'pythran_long_t'
    TYPE_TO_SUFFIX[long] = "LL"


def pytype_to_ctype(t):
    """ Python -> pythonic type binding. """
    if isinstance(t, List):
        return 'pythonic::types::list<{0}>'.format(
            pytype_to_ctype(t.__args__[0])
        )
    elif isinstance(t, Set):
        return 'pythonic::types::set<{0}>'.format(
            pytype_to_ctype(t.__args__[0])
        )
    elif isinstance(t, Dict):
        tkey, tvalue = t.__args__
        return 'pythonic::types::dict<{0},{1}>'.format(pytype_to_ctype(tkey),
                                                       pytype_to_ctype(tvalue))
    elif isinstance(t, Tuple):
        return 'decltype(pythonic::types::make_tuple({0}))'.format(
            ", ".join('std::declval<{}>()'.format(pytype_to_ctype(p))
                      for p in t.__args__)
        )
    elif isinstance(t, NDArray):
        dtype = pytype_to_ctype(t.__args__[0])
        ndim = len(t.__args__) - 1
        arr = 'pythonic::types::ndarray<{0},{1}>'.format(dtype, ndim)
        if t.__args__[1].start == -1:
            return 'pythonic::types::numpy_texpr<{0}>'.format(arr)
        elif any(s.step is not None and s.step < 0 for s in t.__args__[1:]):
            slices = ", ".join(['pythonic::types::slice'] * ndim)
            return 'pythonic::types::numpy_gexpr<{0},{1}>'.format(arr, slices)
        else:
            return arr
    elif isinstance(t, Pointer):
        return 'pythonic::types::pointer<{0}>'.format(
            pytype_to_ctype(t.__args__[0])
        )
    elif isinstance(t, Fun):
        return 'pythonic::types::cfun<{0}({1})>'.format(
            pytype_to_ctype(t.__args__[-1]),
            ", ".join(pytype_to_ctype(arg) for arg in t.__args__[:-1]),
        )
    elif t in PYTYPE_TO_CTYPE_TABLE:
        return PYTYPE_TO_CTYPE_TABLE[t]
    else:
        raise NotImplementedError("{0}:{1}".format(type(t), t))


def pytype_to_pretty_type(t):
    """ Python -> docstring type. """
    if isinstance(t, List):
        return '{0} list'.format(pytype_to_pretty_type(t.__args__[0]))
    elif isinstance(t, Set):
        return '{0} set'.format(pytype_to_pretty_type(t.__args__[0]))
    elif isinstance(t, Dict):
        tkey, tvalue = t.__args__
        return '{0}:{1} dict'.format(pytype_to_pretty_type(tkey),
                                     pytype_to_pretty_type(tvalue))
    elif isinstance(t, Tuple):
        return '({0})'.format(
            ", ".join(pytype_to_pretty_type(p) for p in t.__args__)
        )
    elif isinstance(t, NDArray):
        dtype = pytype_to_pretty_type(t.__args__[0])
        ndim = len(t.__args__) - 1
        arr = '{0}{1}'.format(dtype, '[]' * ndim)
        # it's a transpose!
        if t.__args__[1].start == -1:
            return '{}.T'.format(arr)
        elif any(s.step is not None and s.step < 0 for s in t.__args__[1:]):
            return '{0}{1}'.format(dtype, '[::]' * ndim)
        else:
            return arr
    elif isinstance(t, Pointer):
        dtype = pytype_to_pretty_type(t.__args__[0])
        return '{}*'.format(dtype)
    elif isinstance(t, Fun):
        rtype = pytype_to_pretty_type(t.__args__[-1])
        argtypes = [pytype_to_pretty_type(arg) for arg in t.__args__[:-1]]
        return '{}({})'.format(rtype, ", ".join(argtypes))
    elif t in PYTYPE_TO_CTYPE_TABLE:
        return t.__name__
    else:
        raise NotImplementedError("{0}:{1}".format(type(t), t))
