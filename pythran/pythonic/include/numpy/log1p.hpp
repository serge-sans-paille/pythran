#ifndef PYTHONIC_INCLUDE_NUMPY_LOG1P_HPP
#define PYTHONIC_INCLUDE_NUMPY_LOG1P_HPP

#include "pythonic/include/utils/functor.hpp"
#include "pythonic/include/types/ndarray.hpp"
#include "pythonic/include/utils/numpy_traits.hpp"
#include <boost/simd/function/log1p.hpp>

PYTHONIC_NS_BEGIN

namespace numpy
{

  namespace wrapper
  {
    template <class T>
    std::complex<T> log1p(std::complex<T> const &val)
    {
      return std::log(val + 1);
    }
    template <class T>
    auto log1p(T const &val) -> decltype(boost::simd::log1p(val))
    {
      return boost::simd::log1p(val);
    }
  }

#define NUMPY_NARY_FUNC_NAME log1p
#define NUMPY_NARY_FUNC_SYM wrapper::log1p
#include "pythonic/include/types/numpy_nary_expr.hpp"
}
PYTHONIC_NS_END

#endif
