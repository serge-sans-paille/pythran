#ifndef PYTHONIC_NUMPY_COS_HPP
#define PYTHONIC_NUMPY_COS_HPP

#include "pythonic/include/numpy/cos.hpp"

#include "pythonic/utils/functor.hpp"
#include "pythonic/types/ndarray.hpp"
#include "pythonic/utils/numpy_traits.hpp"

PYTHONIC_NS_BEGIN

namespace numpy
{
  namespace wrapper
  {
    double cos(long const &v)
    {
      return cos(static_cast<double>(v));
    }
    template <class T>
    auto cos(T const &v) -> decltype(boost::simd::cos(v))
    {
      return boost::simd::cos(v);
    }
  }

#define NUMPY_NARY_FUNC_NAME cos
#define NUMPY_NARY_FUNC_SYM wrapper::cos
#include "pythonic/types/numpy_nary_expr.hpp"
}
PYTHONIC_NS_END

#endif
