#ifndef PYTHONIC_INCLUDE_NUMPY_ARCCOSH_HPP
#define PYTHONIC_INCLUDE_NUMPY_ARCCOSH_HPP

#include "pythonic/include/utils/functor.hpp"
#include "pythonic/include/types/ndarray.hpp"
#include "pythonic/include/utils/numpy_traits.hpp"
#include <boost/simd/function/acosh.hpp>

PYTHONIC_NS_BEGIN

namespace numpy
{
  namespace wrapper
  {
    template <class T>
    auto acosh(T const &v) -> decltype(boost::simd::acosh(v))
    {
      return boost::simd::acosh(v);
    }
    template <class T>
    std::complex<T> acosh(std::complex<T> const &v)
    {
      return std::acosh(v);
    }
  }
#define NUMPY_NARY_FUNC_NAME arccosh
#define NUMPY_NARY_FUNC_SYM wrapper::acosh
#include "pythonic/include/types/numpy_nary_expr.hpp"
}
PYTHONIC_NS_END

#endif
