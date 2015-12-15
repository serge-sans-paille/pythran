""" Module to convert Python type to Pythonic type. """

import sys

from numpy import ndarray, int8, int16, int32, int64, uint8, uint16, uint32
from numpy import float64, float32, complex64, complex128, uint64

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

if sys.version_info[0] < 3:
    PYTYPE_TO_CTYPE_TABLE[long] = 'pythran_long_t'
    TYPE_TO_SUFFIX[long] = "LL"


def pytype_to_ctype(t):
    """ Python -> pythonic type binding. """
    if isinstance(t, list):
        return 'pythonic::types::list<{0}>'.format(pytype_to_ctype(t[0]))
    elif isinstance(t, set):
        return 'pythonic::types::set<{0}>'.format(pytype_to_ctype(list(t)[0]))
    elif isinstance(t, dict):
        tkey, tvalue = t.items()[0]
        return 'pythonic::types::dict<{0},{1}>'.format(pytype_to_ctype(tkey),
                                                       pytype_to_ctype(tvalue))
    elif isinstance(t, tuple):
        return 'decltype(pythonic::types::make_tuple({0}))'.format(
            ", ".join('std::declval<{}>()'.format(
                pytype_to_ctype(_)) for _ in t))
    elif isinstance(t, ndarray):
        dtype = pytype_to_ctype(t.flat[0])
        ndim = t.ndim
        arr = 'pythonic::types::ndarray<{0},{1}>'.format(dtype, ndim)
        # cannot use f_contiguous as one element arrays are both c_ and f_
        # the trick is to use transposed array of two elements for texpr
        if t.flags.f_contiguous and not t.flags.c_contiguous and ndim == 2:
            return 'pythonic::types::numpy_texpr<{0}>'.format(arr)
        elif any(x < 0 for x in t.strides):
            slices = ", ".join(['pythonic::types::slice'] * ndim)
            return 'pythonic::types::numpy_gexpr<{0},{1}>'.format(arr, slices)
        else:
            return arr
    elif t in PYTYPE_TO_CTYPE_TABLE:
        return PYTYPE_TO_CTYPE_TABLE[t]
    else:
        raise NotImplementedError("{0}:{1}".format(type(t), t))


def pytype_to_pretty_type(t):
    """ Python -> docstring type. """
    if isinstance(t, list):
        return '{0} list'.format(pytype_to_pretty_type(t[0]))
    elif isinstance(t, set):
        return '{0} set'.format(pytype_to_pretty_type(list(t)[0]))
    elif isinstance(t, dict):
        tkey, tvalue = t.items()[0]
        return '{0}:{1} dict'.format(pytype_to_pretty_type(tkey),
                                     pytype_to_pretty_type(tvalue))
    elif isinstance(t, tuple):
        return '({0})'.format(
            ", ".join(map(pytype_to_pretty_type, t)))
    elif isinstance(t, ndarray):
        dtype = pytype_to_pretty_type(t.flat[0])
        ndim = t.ndim
        arr = '{0}{1}'.format(dtype, '[]' * ndim)
        # cannot use f_contiguous as one element arrays are both c_ and f_
        # the trick is to use transposed array of two elements for texpr
        if t.flags.f_contiguous and not t.flags.c_contiguous and ndim == 2:
            return '{}.T'.format(arr)
        elif any(x < 0 for x in t.strides):
            return '{0}{1}'.format(dtype, '[::]' * ndim)
        else:
            return arr
    elif t in PYTYPE_TO_CTYPE_TABLE:
        return t.__name__
    else:
        raise NotImplementedError("{0}:{1}".format(type(t), t))
