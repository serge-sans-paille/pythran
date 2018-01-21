#ifndef PYTHONIC_NUMPY_LOGADDEXP_HPP
#define PYTHONIC_NUMPY_LOGADDEXP_HPP

#include "pythonic/include/numpy/logaddexp.hpp"

#include "pythonic/utils/functor.hpp"
#include "pythonic/types/ndarray.hpp"
#include "pythonic/utils/numpy_traits.hpp"

PYTHONIC_NS_BEGIN

namespace numpy
{
  namespace wrapper
  {
    template <class T0, class T1>
    auto logaddexp(T0 const &t0, T1 const &t1)
        -> decltype(boost::simd::log(boost::simd::exp(t0) +
                                     boost::simd::exp(t1)))
    {
      return boost::simd::log(boost::simd::exp(t0) + boost::simd::exp(t1));
    }
  }

#define NUMPY_NARY_FUNC_NAME logaddexp
#define NUMPY_NARY_FUNC_SYM wrapper::logaddexp
#include "pythonic/types/numpy_nary_expr.hpp"
}
PYTHONIC_NS_END

#endif
