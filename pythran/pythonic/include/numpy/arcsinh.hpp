#ifndef PYTHONIC_INCLUDE_NUMPY_ARCSINH_HPP
#define PYTHONIC_INCLUDE_NUMPY_ARCSINH_HPP

#include "pythonic/include/utils/functor.hpp"
#include "pythonic/include/types/ndarray.hpp"
#include "pythonic/include/utils/numpy_traits.hpp"
#include <boost/simd/function/asinh.hpp>

PYTHONIC_NS_BEGIN

namespace numpy
{
  namespace wrapper
  {
    template <class T>
    std::complex<T> asinh(std::complex<T> const &val)
    {
      return std::asinh(val);
    }
    template <class T>
    auto asinh(T const &val) -> decltype(boost::simd::asinh(val))
    {
      return boost::simd::asinh(val);
    }
  }
#define NUMPY_NARY_FUNC_NAME arcsinh
#define NUMPY_NARY_FUNC_SYM wrapper::asinh
#include "pythonic/include/types/numpy_nary_expr.hpp"
}
PYTHONIC_NS_END

#endif
