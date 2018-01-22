#ifndef PYTHONIC_INCLUDE_NUMPY_LOGADDEXP2_HPP
#define PYTHONIC_INCLUDE_NUMPY_LOGADDEXP2_HPP

#include "pythonic/include/utils/functor.hpp"
#include "pythonic/include/types/ndarray.hpp"
#include "pythonic/include/types/numpy_broadcast.hpp"
#include "pythonic/include/utils/numpy_traits.hpp"

#include <boost/simd/function/log2.hpp>
#include <boost/simd/function/pow.hpp>
PYTHONIC_NS_BEGIN

namespace numpy
{
  namespace wrapper
  {
    template <class T0, class T1>
    auto logaddexp2(T0 const &t0, T1 const &t1)
        -> decltype(boost::simd::log2(boost::simd::pow(T0(2), t0) +
                                      boost::simd::pow(T1(2), t1)));
  }

#define NUMPY_NARY_FUNC_NAME logaddexp2
#define NUMPY_NARY_FUNC_SYM wrapper::logaddexp2
#include "pythonic/include/types/numpy_nary_expr.hpp"
}
PYTHONIC_NS_END

#endif
