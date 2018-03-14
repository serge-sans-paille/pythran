#ifndef PYTHONIC_INCLUDE_NUMPY_ARCTAN_HPP
#define PYTHONIC_INCLUDE_NUMPY_ARCTAN_HPP

#include "pythonic/include/utils/functor.hpp"
#include "pythonic/include/types/ndarray.hpp"
#include "pythonic/include/utils/numpy_traits.hpp"

#include <boost/simd/function/atan.hpp>

PYTHONIC_NS_BEGIN

namespace numpy
{
  namespace wrapper
  {
    template <class T>
    auto atan(T const &v) -> decltype(boost::simd::atan(v))
    {
      return boost::simd::atan(v);
    }
    template <class T>
    std::complex<T> atan(std::complex<T> const &v)
    {
      return std::atan(v);
    }
  }
#define NUMPY_NARY_FUNC_NAME arctan
#define NUMPY_NARY_FUNC_SYM wrapper::atan
#include "pythonic/include/types/numpy_nary_expr.hpp"
}
PYTHONIC_NS_END

#endif
