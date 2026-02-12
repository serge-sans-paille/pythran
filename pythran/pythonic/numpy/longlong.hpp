#ifndef PYTHONIC_NUMPY_LONGLONG_HPP
#define PYTHONIC_NUMPY_LONGLONG_HPP

#include "pythonic/include/numpy/longlong.hpp"

#include "pythonic/types/numpy_op_helper.hpp"
#include "pythonic/utils/functor.hpp"
#include "pythonic/utils/meta.hpp"
#include "pythonic/utils/numpy_traits.hpp"

PYTHONIC_NS_BEGIN

namespace numpy
{

  namespace details
  {

    inline long long longlong()
    {
      return {};
    }

    template <class V>
    long long longlong(V v)
    {
      return v;
    }
  } // namespace details

#define NUMPY_NARY_FUNC_NAME longlong
#define NUMPY_NARY_FUNC_SYM details::longlong
#include "pythonic/types/numpy_nary_expr.hpp"
} // namespace numpy
PYTHONIC_NS_END

#ifdef ENABLE_PYTHON_MODULE

#include "pythonic/python/core.hpp"
#include "numpy/arrayscalars.h"

PYTHONIC_NS_BEGIN

inline PyObject *
to_python<numpy::functor::longlong>::convert(numpy::functor::longlong const &c)
{
  return (PyObject*)&PyLongLongArrType_Type;
}

inline bool from_python<numpy::functor::longlong>::is_convertible(PyObject *obj)
{
  return obj == (PyObject*)&PyLongLongArrType_Type;
}

inline numpy::functor::longlong
from_python<numpy::functor::longlong>::convert(PyObject *obj)
{
  return {};
}

PYTHONIC_NS_END
#endif

#endif
