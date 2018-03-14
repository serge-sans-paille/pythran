#ifndef PYTHONIC_INCLUDE_NUMPY_SIN_HPP
#define PYTHONIC_INCLUDE_NUMPY_SIN_HPP

#include "pythonic/include/utils/functor.hpp"
#include "pythonic/include/types/ndarray.hpp"
#include "pythonic/include/utils/numpy_traits.hpp"

#include <boost/simd/function/sin.hpp>
#include <cmath>

PYTHONIC_NS_BEGIN

namespace numpy
{
  namespace wrapper
  {
    double sin(long const &v);
    template <class T>
    auto sin(T const &v) -> decltype(boost::simd::sin(v));
    template <class T>
    std::complex<T> sin(std::complex<T> const &v)
    {
      return std::sin(v);
    }
  }
#define NUMPY_NARY_FUNC_NAME sin
#define NUMPY_NARY_FUNC_SYM wrapper::sin
#include "pythonic/include/types/numpy_nary_expr.hpp"
}
PYTHONIC_NS_END

#endif
