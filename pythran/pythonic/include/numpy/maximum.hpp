#ifndef PYTHONIC_INCLUDE_NUMPY_MAXIMUM_HPP
#define PYTHONIC_INCLUDE_NUMPY_MAXIMUM_HPP

#include "pythonic/include/utils/functor.hpp"
#include "pythonic/include/types/ndarray.hpp"
#include "pythonic/include/types/numpy_broadcast.hpp"
#include "pythonic/include/utils/numpy_traits.hpp"

#include <boost/simd/function/max.hpp>

PYTHONIC_NS_BEGIN

namespace numpy
{
  namespace wrapper
  {
    template <class T>
    auto max(T const &self, T const &other) ->
        typename std::enable_if<!types::is_complex<T>::value,
                                decltype(boost::simd::max(self, other))>::type
    {
      return boost::simd::max(self, other);
    }
    template <class T0, class T1>
    auto max(T0 const &self, T1 const &other) ->
        typename std::decay<decltype(self < other ? other : self)>::type
    {
      return self < other ? other : self;
    }
  }
#define NUMPY_NARY_FUNC_NAME maximum
#define NUMPY_NARY_FUNC_SYM wrapper::max
#include "pythonic/include/types/numpy_nary_expr.hpp"
}
PYTHONIC_NS_END

#endif
