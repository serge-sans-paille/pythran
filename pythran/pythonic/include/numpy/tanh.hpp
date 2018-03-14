#ifndef PYTHONIC_INCLUDE_NUMPY_TANH_HPP
#define PYTHONIC_INCLUDE_NUMPY_TANH_HPP

#include "pythonic/include/utils/functor.hpp"
#include "pythonic/include/types/ndarray.hpp"
#include "pythonic/include/utils/numpy_traits.hpp"

#include <boost/simd/function/tanh.hpp>

PYTHONIC_NS_BEGIN

namespace numpy
{
  namespace wrapper
  {
    template <class T>
    auto tanh(T const &v) -> decltype(boost::simd::tanh(v))
    {
      return boost::simd::tanh(v);
    }
    template <class T>
    std::complex<T> tanh(std::complex<T> const &v)
    {
      return std::tanh(v);
    }
  }
#define NUMPY_NARY_FUNC_NAME tanh
#define NUMPY_NARY_FUNC_SYM wrapper::tanh
#include "pythonic/include/types/numpy_nary_expr.hpp"
}
PYTHONIC_NS_END

#endif
