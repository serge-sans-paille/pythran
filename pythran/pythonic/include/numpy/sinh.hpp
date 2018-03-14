#ifndef PYTHONIC_INCLUDE_NUMPY_SINH_HPP
#define PYTHONIC_INCLUDE_NUMPY_SINH_HPP

#include "pythonic/include/utils/functor.hpp"
#include "pythonic/include/types/ndarray.hpp"
#include "pythonic/include/utils/numpy_traits.hpp"

#include <boost/simd/function/sinh.hpp>

PYTHONIC_NS_BEGIN

namespace numpy
{
  namespace wrapper
  {
    template <class T>
    std::complex<T> sinh(std::complex<T> const &val)
    {
      return std::sinh(val);
    }
    template <class T>
    auto sinh(T const &val) -> decltype(boost::simd::sinh(val))
    {
      return boost::simd::sinh(val);
    }
  }
#define NUMPY_NARY_FUNC_NAME sinh
#define NUMPY_NARY_FUNC_SYM wrapper::sinh
#include "pythonic/include/types/numpy_nary_expr.hpp"
}
PYTHONIC_NS_END

#endif
