#ifndef PYTHONIC_INCLUDE_NUMPY_LOG_HPP
#define PYTHONIC_INCLUDE_NUMPY_LOG_HPP

#include "pythonic/include/utils/functor.hpp"
#include "pythonic/include/types/ndarray.hpp"
#include "pythonic/include/utils/numpy_traits.hpp"

#include <boost/simd/function/log.hpp>

PYTHONIC_NS_BEGIN

namespace numpy
{
  namespace wrapper
  {
    template <class T>
    std::complex<T> log(std::complex<T> const &val)
    {
      return std::log(val);
    }

    template <class T>
    typename std::enable_if<std::is_integral<T>::value, double>::type
    log(T const &val)
    {
      return std::log(val);
    }

    template <class T>
    auto log(T const &val) ->
        typename std::enable_if<!std::is_integral<T>::value,
                                decltype(boost::simd::log(val))>::type
    {
      return boost::simd::log(val);
    }
  }
#define NUMPY_NARY_FUNC_NAME log
#define NUMPY_NARY_FUNC_SYM wrapper::log
#include "pythonic/include/types/numpy_nary_expr.hpp"
}
PYTHONIC_NS_END

#endif
