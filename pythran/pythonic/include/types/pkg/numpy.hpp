#ifndef PYTHONIC_INCLUDE_TYPES_PKG_NUMPY_HPP
#define PYTHONIC_INCLUDE_TYPES_PKG_NUMPY_HPP

PYTHONIC_NS_BEGIN

namespace types
{

  namespace pkg {

    struct numpy {};

  }

}
PYTHONIC_NS_END

#ifdef ENABLE_PYTHON_MODULE

#include "pythonic/python/core.hpp"

PYTHONIC_NS_BEGIN
template <>
struct from_python<types::pkg::numpy> {

  static bool is_convertible(PyObject *obj);

  static types::pkg::numpy convert(PyObject *obj) { return {}; }
};
PYTHONIC_NS_END

#endif
#endif
