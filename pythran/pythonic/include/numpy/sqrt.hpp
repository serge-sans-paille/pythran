#ifndef PYTHONIC_INCLUDE_NUMPY_SQRT_HPP
#define PYTHONIC_INCLUDE_NUMPY_SQRT_HPP

#include "pythonic/include/utils/functor.hpp"
#include "pythonic/include/types/ndarray.hpp"
#include "pythonic/include/utils/numpy_traits.hpp"

#include <boost/simd/function/sqrt.hpp>
#include <cmath>

PYTHONIC_NS_BEGIN

namespace numpy
{
  namespace wrapper
  {
    template <class T>
    std::complex<T> sqrt(std::complex<T> const &val)
    {
      return std::sqrt(val);
    }
    template <class T>
    auto sqrt(T const &val) -> decltype(boost::simd::sqrt(val))
    {
      return boost::simd::sqrt(val);
    }
  }

#define NUMPY_NARY_FUNC_NAME sqrt
#define NUMPY_NARY_FUNC_SYM wrapper::sqrt
#include "pythonic/include/types/numpy_nary_expr.hpp"
}
PYTHONIC_NS_END

#endif
