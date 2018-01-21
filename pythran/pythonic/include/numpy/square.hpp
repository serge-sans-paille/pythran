#ifndef PYTHONIC_INCLUDE_NUMPY_SQUARE_HPP
#define PYTHONIC_INCLUDE_NUMPY_SQUARE_HPP

#include "pythonic/include/types/numpy_op_helper.hpp"
#include "pythonic/include/utils/numpy_traits.hpp"
#include "pythonic/include/utils/functor.hpp"

#include <complex>
#include <boost/simd/function/sqr.hpp>

#ifdef USE_GMP
#include "pythonic/include/types/long.hpp"
#endif

namespace wrapper
{
}

PYTHONIC_NS_BEGIN

namespace numpy
{

  namespace wrapper
  {
#ifdef USE_GMP
    template <class T, class U>
    auto square(__gmp_expr<T, U> const &a) -> decltype(a *a)
    {
      return a * a;
    }
#endif
    template <class T>
    std::complex<T> square(std::complex<T> const &arg)
    {
      return arg * arg;
    }
    template <class T>
    auto square(T const &arg) -> decltype(boost::simd::sqr(arg))
    {
      return boost::simd::sqr(arg);
    }
  }

#define NUMPY_NARY_FUNC_NAME square
#define NUMPY_NARY_FUNC_SYM wrapper::square
#include "pythonic/include/types/numpy_nary_expr.hpp"
}
PYTHONIC_NS_END

#endif
