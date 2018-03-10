#ifndef PYTHONIC_INCLUDE_NUMPY_TAN_HPP
#define PYTHONIC_INCLUDE_NUMPY_TAN_HPP

#include "pythonic/include/utils/functor.hpp"
#include "pythonic/include/types/ndarray.hpp"
#include "pythonic/include/utils/numpy_traits.hpp"

#include <boost/simd/function/tan.hpp>

PYTHONIC_NS_BEGIN

namespace numpy
{
  namespace wrapper
  {
    template <class T>
    auto tan(T const &v) -> decltype(boost::simd::tan(v))
    {
      return boost::simd::tan(v);
    }
    template <class T>
    std::complex<T> tan(std::complex<T> const &v)
    {
      return std::tan(v);
    }
  }
#define NUMPY_NARY_FUNC_NAME tan
#define NUMPY_NARY_FUNC_SYM wrapper::tan
#include "pythonic/include/types/numpy_nary_expr.hpp"
}
PYTHONIC_NS_END

#endif
