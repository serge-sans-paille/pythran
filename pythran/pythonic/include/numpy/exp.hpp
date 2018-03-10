#ifndef PYTHONIC_INCLUDE_NUMPY_EXP_HPP
#define PYTHONIC_INCLUDE_NUMPY_EXP_HPP

#include "pythonic/include/utils/functor.hpp"
#include "pythonic/include/types/ndarray.hpp"
#include "pythonic/include/utils/numpy_traits.hpp"

#include <boost/simd/function/exp.hpp>
#include <cmath>

PYTHONIC_NS_BEGIN

namespace numpy
{
  namespace wrapper
  {
    template <class T>
    std::complex<T> exp(std::complex<T> const &val)
    {
      return std::exp(val);
    }
    template <class T>
    auto exp(T const &val) -> decltype(boost::simd::exp(val))
    {
      return boost::simd::exp(val);
    }
  }
#define NUMPY_NARY_FUNC_NAME exp
#define NUMPY_NARY_FUNC_SYM wrapper::exp
#include "pythonic/include/types/numpy_nary_expr.hpp"
}
PYTHONIC_NS_END

#endif
