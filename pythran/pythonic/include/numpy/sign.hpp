#ifndef PYTHONIC_INCLUDE_NUMPY_SIGN_HPP
#define PYTHONIC_INCLUDE_NUMPY_SIGN_HPP

#include "pythonic/include/utils/functor.hpp"
#include "pythonic/include/types/ndarray.hpp"
#include "pythonic/include/utils/numpy_traits.hpp"
#include <boost/simd/function/sign.hpp>

PYTHONIC_NS_BEGIN

namespace numpy
{
  namespace wrapper
  {
    template <class T>
    auto sign(T const &v) -> decltype(boost::simd::sign(v))
    {
      return boost::simd::sign(v);
    }

    template <class T>
    std::complex<T> sign(std::complex<T> const &v)
    {
      if (v.real())
        return {boost::simd::sign(v.real()), 0};
      else
        return {boost::simd::sign(v.imag()), 0};
    }
  }
#define NUMPY_NARY_FUNC_NAME sign
#define NUMPY_NARY_FUNC_SYM wrapper::sign
#include "pythonic/include/types/numpy_nary_expr.hpp"
}
PYTHONIC_NS_END

#endif
