#ifndef PYTHONIC_INCLUDE_NUMPY_LOG10_HPP
#define PYTHONIC_INCLUDE_NUMPY_LOG10_HPP

#include "pythonic/include/utils/functor.hpp"
#include "pythonic/include/types/ndarray.hpp"
#include "pythonic/include/utils/numpy_traits.hpp"

#include <boost/simd/function/log10.hpp>

PYTHONIC_NS_BEGIN

namespace numpy
{
  namespace wrapper
  {
    template <class T>
    std::complex<T> log10(std::complex<T> const &val)
    {
      return std::log10(val);
    }
    template <class T>
    auto log10(T const &val) -> decltype(boost::simd::log10(val))
    {
      return boost::simd::log10(val);
    }
  }
#define NUMPY_NARY_FUNC_NAME log10
#define NUMPY_NARY_FUNC_SYM wrapper::log10
#include "pythonic/include/types/numpy_nary_expr.hpp"
}
PYTHONIC_NS_END

#endif
