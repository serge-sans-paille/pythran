#ifndef PYTHONIC_TYPES_PKG_NUMPY_HPP
#define PYTHONIC_TYPES_PKG_NUMPY_HPP

#include "pythonic/include/types/pkg/numpy.hpp"

#ifdef ENABLE_PYTHON_MODULE

PYTHONIC_NS_BEGIN
inline bool from_python<types::pkg::numpy>::is_convertible(PyObject *obj)
{
  if (!PyModule_Check(obj)) {
    return false;
  }
  const char * pkg_name = PyModule_GetName(obj);
  const size_t pkg_name_len = strlen(pkg_name);
  const size_t numpy_len = sizeof("numpy") - 1;
  if (pkg_name_len == numpy_len) {
    return strcmp(pkg_name, "numpy") == 0;
  } else if (pkg_name_len >= numpy_len + 1) {
    return strcmp(pkg_name + pkg_name_len - numpy_len - 1, ".numpy") == 0;
  } else {
    return false;
  }
}
PYTHONIC_NS_END

#endif
#endif
