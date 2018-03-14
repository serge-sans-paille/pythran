#ifndef PYTHONIC_INCLUDE_NUMPY_ARCTANH_HPP
#define PYTHONIC_INCLUDE_NUMPY_ARCTANH_HPP

#include "pythonic/include/utils/functor.hpp"
#include "pythonic/include/types/ndarray.hpp"
#include "pythonic/include/utils/numpy_traits.hpp"

#include <boost/simd/function/atanh.hpp>

PYTHONIC_NS_BEGIN

namespace numpy
{
  namespace wrapper
  {
    template <class T>
    auto atanh(T const &v) -> decltype(boost::simd::atanh(v))
    {
      return boost::simd::atanh(v);
    }
    template <class T>
    std::complex<T> atanh(std::complex<T> const &v)
    {
      return std::atanh(v);
    }
  }
#define NUMPY_NARY_FUNC_NAME arctanh
#define NUMPY_NARY_FUNC_SYM wrapper::atanh
#include "pythonic/include/types/numpy_nary_expr.hpp"
}
PYTHONIC_NS_END

#endif
