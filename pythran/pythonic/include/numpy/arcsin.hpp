#ifndef PYTHONIC_INCLUDE_NUMPY_ARCSIN_HPP
#define PYTHONIC_INCLUDE_NUMPY_ARCSIN_HPP

#include "pythonic/include/utils/functor.hpp"
#include "pythonic/include/types/ndarray.hpp"
#include "pythonic/include/utils/numpy_traits.hpp"

#include <boost/simd/function/asin.hpp>

PYTHONIC_NS_BEGIN

namespace numpy
{

  namespace wrapper
  {
    double arcsin(long const &v);
    template <class T>
    auto arcsin(T const &v) -> decltype(boost::simd::asin(v));
  }
#define NUMPY_NARY_FUNC_NAME arcsin
#define NUMPY_NARY_FUNC_SYM wrapper::arcsin
#include "pythonic/include/types/numpy_nary_expr.hpp"
}
PYTHONIC_NS_END

#endif
