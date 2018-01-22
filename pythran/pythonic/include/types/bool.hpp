#ifndef PYTHONIC_INCLUDE_TYPES_BOOL_HPP
#define PYTHONIC_INCLUDE_TYPES_BOOL_HPP

#ifdef ENABLE_PYTHON_MODULE

#include "pythonic/python/core.hpp"

#include "boost/simd/logical.hpp"

PYTHONIC_NS_BEGIN
template <>
struct to_python<bool> {
  static PyObject *convert(bool b);
};
template <>
struct from_python<bool> {
  static bool is_convertible(PyObject *obj);
  static bool convert(PyObject *obj);
};

template <class T>
struct to_python<boost::simd::logical<T>> {
  static PyObject *convert(boost::simd::logical<T> b);
};
PYTHONIC_NS_END

#endif

#endif
