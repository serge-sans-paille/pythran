#ifndef PYTHONIC_INCLUDE_NUMPY_EXPM1_HPP
#define PYTHONIC_INCLUDE_NUMPY_EXPM1_HPP

#include "pythonic/include/utils/functor.hpp"
#include "pythonic/include/types/ndarray.hpp"
#include "pythonic/include/utils/numpy_traits.hpp"

#include <boost/simd/function/expm1.hpp>

PYTHONIC_NS_BEGIN

namespace numpy
{

  namespace wrapper
  {
    template <class T>
    std::complex<T> expm1(std::complex<T> const &val)
    {
      return exp(val) - 1;
    }
    template <class T>
    auto expm1(T const &val) -> decltype(boost::simd::expm1(val))
    {
      return boost::simd::expm1(val);
    }
  }

#define NUMPY_NARY_FUNC_NAME expm1
#define NUMPY_NARY_FUNC_SYM wrapper::expm1
#include "pythonic/include/types/numpy_nary_expr.hpp"
}
PYTHONIC_NS_END

#endif
