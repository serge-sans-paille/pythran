#ifndef PYTHONIC_NUMPY_RINT_HPP
#define PYTHONIC_NUMPY_RINT_HPP

#include "pythonic/include/numpy/rint.hpp"

#include "pythonic/utils/functor.hpp"
#include "pythonic/types/ndarray.hpp"
#include "pythonic/utils/numpy_traits.hpp"
#include <boost/simd/function/inearbyint.hpp>

PYTHONIC_NS_BEGIN

namespace numpy
{
  namespace wrapper
  {
    template <class T>
    T rint(T const &v)
    {
      return boost::simd::inearbyint(v);
    }
  }
#define NUMPY_NARY_FUNC_NAME rint
#define NUMPY_NARY_FUNC_SYM wrapper::rint
#include "pythonic/types/numpy_nary_expr.hpp"
}
PYTHONIC_NS_END

#endif
