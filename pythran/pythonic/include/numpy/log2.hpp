#ifndef PYTHONIC_INCLUDE_NUMPY_LOG2_HPP
#define PYTHONIC_INCLUDE_NUMPY_LOG2_HPP

#include "pythonic/include/utils/functor.hpp"
#include "pythonic/include/types/ndarray.hpp"
#include "pythonic/include/utils/numpy_traits.hpp"
#include <boost/simd/function/log2.hpp>

PYTHONIC_NS_BEGIN

namespace numpy
{
  namespace wrapper
  {
    template <class T>
    std::complex<T> log2(std::complex<T> const &val)
    {
      return std::log(val) / std::log(2);
    }
    template <class T>
    auto log2(T const &val) -> decltype(boost::simd::log2(val))
    {
      return boost::simd::log2(val);
    }
  }
#define NUMPY_NARY_FUNC_NAME log2
#define NUMPY_NARY_FUNC_SYM wrapper::log2
#include "pythonic/include/types/numpy_nary_expr.hpp"
}
PYTHONIC_NS_END

#endif
