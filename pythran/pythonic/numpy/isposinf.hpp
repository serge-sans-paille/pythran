#ifndef PYTHONIC_NUMPY_ISPOSINF_HPP
#define PYTHONIC_NUMPY_ISPOSINF_HPP

#include "pythonic/include/numpy/isposinf.hpp"

#include "pythonic/utils/functor.hpp"
#include "pythonic/types/ndarray.hpp"
#include "pythonic/utils/numpy_traits.hpp"

#include <boost/simd/function/is_inf.hpp>
#include <boost/simd/function/is_positive.hpp>

PYTHONIC_NS_BEGIN

namespace numpy
{
  namespace wrapper
  {
    template <class T>
    bool isposinf(T const &t)
    {
      return boost::simd::is_inf(t) && boost::simd::is_positive(t);
    }
  }
#define NUMPY_NARY_FUNC_NAME isposinf
#define NUMPY_NARY_FUNC_SYM wrapper::isposinf
#include "pythonic/types/numpy_nary_expr.hpp"
}
PYTHONIC_NS_END

#endif
