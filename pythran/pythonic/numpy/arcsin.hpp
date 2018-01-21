#ifndef PYTHONIC_NUMPY_ARCSIN_HPP
#define PYTHONIC_NUMPY_ARCSIN_HPP

#include "pythonic/include/numpy/arcsin.hpp"

#include "pythonic/utils/functor.hpp"
#include "pythonic/types/ndarray.hpp"
#include "pythonic/utils/numpy_traits.hpp"

PYTHONIC_NS_BEGIN

namespace numpy
{
  namespace wrapper
  {
    double arcsin(long const &v)
    {
      return arcsin(static_cast<double>(v));
    }
    template <class T>
    auto arcsin(T const &v) -> decltype(boost::simd::asin(v))
    {
      return boost::simd::asin(v);
    }
  }
#define NUMPY_NARY_FUNC_NAME arcsin
#define NUMPY_NARY_FUNC_SYM wrapper::arcsin
#include "pythonic/types/numpy_nary_expr.hpp"
}
PYTHONIC_NS_END

#endif
