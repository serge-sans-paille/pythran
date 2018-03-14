#ifndef PYTHONIC_INCLUDE_NUMPY_ARCCOS_HPP
#define PYTHONIC_INCLUDE_NUMPY_ARCCOS_HPP

#include "pythonic/include/utils/functor.hpp"
#include "pythonic/include/types/ndarray.hpp"
#include "pythonic/include/utils/numpy_traits.hpp"

#include <boost/simd/function/acos.hpp>

PYTHONIC_NS_BEGIN

namespace numpy
{

  namespace wrapper
  {
    double arccos(long const &v);
    template <class T>
    auto arccos(T const &v) -> decltype(boost::simd::acos(v));
    template <class T>
    std::complex<T> arccos(std::complex<T> const &v)
    {
      return std::acos(v);
    }
  }

#define NUMPY_NARY_FUNC_NAME arccos
#define NUMPY_NARY_FUNC_SYM wrapper::arccos
#include "pythonic/include/types/numpy_nary_expr.hpp"
}
PYTHONIC_NS_END

#endif
