#ifndef PYTHONIC_NUMPY_SIN_HPP
#define PYTHONIC_NUMPY_SIN_HPP

#include "pythonic/include/numpy/sin.hpp"

#include "pythonic/utils/functor.hpp"
#include "pythonic/types/ndarray.hpp"
#include "pythonic/utils/numpy_traits.hpp"

PYTHONIC_NS_BEGIN

namespace numpy
{
  namespace wrapper
  {
    double sin(long const &v)
    {
      return sin(static_cast<double>(v));
    }
    template <class T>
    auto sin(T const &v) -> decltype(boost::simd::sin(v))
    {
      return boost::simd::sin(v);
    }
  }
#define NUMPY_NARY_FUNC_NAME sin
#define NUMPY_NARY_FUNC_SYM wrapper::sin
#include "pythonic/types/numpy_nary_expr.hpp"
}
PYTHONIC_NS_END

#endif
