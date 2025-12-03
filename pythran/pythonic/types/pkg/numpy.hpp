#ifndef PYTHONIC_TYPES_PKG_NUMPY_HPP
#define PYTHONIC_TYPES_PKG_NUMPY_HPP

#include "pythonic/include/types/pkg/numpy.hpp"

#ifdef ENABLE_PYTHON_MODULE

PYTHONIC_NS_BEGIN
inline bool from_python<types::pkg::numpy>::is_convertible(PyObject *obj) {
  return PyModule_Check(obj) && strcmp(PyModule_GetName(obj), "numpy") == 0;
}
PYTHONIC_NS_END

#endif
#endif
