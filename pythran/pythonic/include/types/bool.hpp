#ifndef PYTHONIC_INCLUDE_TYPES_BOOL_HPP
#define PYTHONIC_INCLUDE_TYPES_BOOL_HPP

#ifdef ENABLE_PYTHON_MODULE

#include "pythonic/python/core.hpp"

namespace pythonic
{
  template <>
  struct to_python<bool> {
    static PyObject *convert(bool b);
  };
  template <>
  struct from_python<bool> {
    static bool is_convertible(PyObject *obj);
    static bool convert(PyObject *obj);
  };
}

#endif

#endif
