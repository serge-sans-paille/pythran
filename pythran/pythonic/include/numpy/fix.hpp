#ifndef PYTHONIC_INCLUDE_NUMPY_FIX_HPP
#define PYTHONIC_INCLUDE_NUMPY_FIX_HPP

#include "pythonic/include/utils/functor.hpp"
#include "pythonic/include/types/ndarray.hpp"
#include "pythonic/include/utils/numpy_traits.hpp"
#include <boost/simd/function/trunc.hpp>

PYTHONIC_NS_BEGIN

namespace numpy
{
  namespace wrapper
  {
    template <class T>
    double fix(T const &v)
    {
      return boost::simd::trunc(v);
    }
  }
#define NUMPY_NARY_FUNC_NAME fix
#define NUMPY_NARY_FUNC_SYM wrapper::fix
#include "pythonic/include/types/numpy_nary_expr.hpp"
}
PYTHONIC_NS_END

#endif
