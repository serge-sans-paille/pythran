#ifndef PYTHONIC_INCLUDE_NUMPY_COS_HPP
#define PYTHONIC_INCLUDE_NUMPY_COS_HPP

#include "pythonic/include/utils/functor.hpp"
#include "pythonic/include/types/ndarray.hpp"
#include "pythonic/include/utils/numpy_traits.hpp"
#include <boost/simd/function/cos.hpp>

PYTHONIC_NS_BEGIN

namespace numpy
{
  namespace wrapper
  {
    double cos(long const &v);
    template <class T>
    auto cos(T const &v) -> decltype(boost::simd::cos(v));
  }
#define NUMPY_NARY_FUNC_NAME cos
#define NUMPY_NARY_FUNC_SYM wrapper::cos
#include "pythonic/include/types/numpy_nary_expr.hpp"
}
PYTHONIC_NS_END

#endif
