#ifndef PYTHONIC_INCLUDE_NUMPY_COSH_HPP
#define PYTHONIC_INCLUDE_NUMPY_COSH_HPP

#include "pythonic/include/utils/functor.hpp"
#include "pythonic/include/types/ndarray.hpp"
#include "pythonic/include/utils/numpy_traits.hpp"

#include <boost/simd/function/cosh.hpp>

PYTHONIC_NS_BEGIN

namespace numpy
{
  namespace wrapper
  {
    template <class T>
    auto cosh(T const &v) -> decltype(boost::simd::cosh(v))
    {
      return boost::simd::cosh(v);
    }
    template <class T>
    std::complex<T> cosh(std::complex<T> const &v)
    {
      return std::cosh(v);
    }
  }
#define NUMPY_NARY_FUNC_NAME cosh
#define NUMPY_NARY_FUNC_SYM wrapper::cosh
#include "pythonic/include/types/numpy_nary_expr.hpp"
}
PYTHONIC_NS_END

#endif
