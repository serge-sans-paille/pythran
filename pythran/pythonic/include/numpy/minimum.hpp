#ifndef PYTHONIC_INCLUDE_NUMPY_MINIMUM_HPP
#define PYTHONIC_INCLUDE_NUMPY_MINIMUM_HPP

#include "pythonic/include/utils/functor.hpp"
#include "pythonic/include/types/ndarray.hpp"
#include "pythonic/include/types/numpy_broadcast.hpp"
#include "pythonic/include/utils/numpy_traits.hpp"

#include <boost/simd/function/min.hpp>

PYTHONIC_NS_BEGIN

namespace numpy
{
  namespace wrapper
  {
    template <class T>
    auto min(T const &self, T const &other) ->
        typename std::enable_if<!types::is_complex<T>::value,
                                decltype(boost::simd::min(self, other))>::type
    {
      return boost::simd::min(self, other);
    }
    template <class T0, class T1>
    auto min(T0 const &self, T1 const &other) ->
        typename std::decay<decltype(self > other ? other : self)>::type
    {
      return self > other ? other : self;
    }
  }
#define NUMPY_NARY_FUNC_NAME minimum
#define NUMPY_NARY_FUNC_SYM wrapper::min
#include "pythonic/include/types/numpy_nary_expr.hpp"
}
PYTHONIC_NS_END

#endif
