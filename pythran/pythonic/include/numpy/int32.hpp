#ifndef PYTHONIC_INCLUDE_NUMPY_INT32_HPP
#define PYTHONIC_INCLUDE_NUMPY_INT32_HPP

#include "pythonic/include/types/numpy_op_helper.hpp"
#include "pythonic/include/utils/functor.hpp"
#include "pythonic/include/utils/numpy_traits.hpp"

PYTHONIC_NS_BEGIN

namespace numpy
{

  namespace details
  {

    int32_t int32();
    template <class V>
    int32_t int32(V v);
  } // namespace details

#define NUMPY_NARY_FUNC_NAME int32
#define NUMPY_NARY_FUNC_SYM details::int32
#define NUMPY_NARY_EXTRA_METHOD using type = int32_t;
#include "pythonic/include/types/numpy_nary_expr.hpp"
} // namespace numpy

namespace builtins
{
  inline numpy::functor::int32 getattr(types::attr::DTYPE, int32_t const &);
} // namespace builtins

PYTHONIC_NS_END
#ifdef ENABLE_PYTHON_MODULE

#include "pythonic/python/core.hpp"

PYTHONIC_NS_BEGIN

template <>
struct to_python<numpy::functor::int32> {
  static PyObject *convert(numpy::functor::int32 const &c);
};

template <>
struct from_python<numpy::functor::int32> {
  static bool is_convertible(PyObject *obj);
  static numpy::functor::int32 convert(PyObject *obj);
};
PYTHONIC_NS_END
#endif

#endif
