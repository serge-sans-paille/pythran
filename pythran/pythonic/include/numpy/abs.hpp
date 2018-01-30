#ifndef PYTHONIC_INCLUDE_NUMPY_ABS_HPP
#define PYTHONIC_INCLUDE_NUMPY_ABS_HPP

#include "pythonic/include/types/numpy_op_helper.hpp"
#include "pythonic/include/utils/meta.hpp"
#include "pythonic/include/utils/numpy_traits.hpp"
#include "pythonic/include/utils/functor.hpp"

#include <boost/simd/function/abs.hpp>

PYTHONIC_NS_BEGIN

namespace numpy
{
  namespace wrapper
  {
    // boost simd does ! handle bool specialization, which is indeed a
    // corner case...
    template <class T>
    auto abs(T const &v) -> decltype(boost::simd::abs(v))
    {
      return boost::simd::abs(v);
    }
    constexpr bool abs(bool const &v)
    {
      return v;
    }
    template <class T>
    T abs(std::complex<T> const v)
    {
      return std::abs(v);
    }
  }

#define NUMPY_NARY_FUNC_NAME abs
#ifdef USE_BOOST_SIMD
#define NUMPY_NARY_FUNC_SYM wrapper::abs
#else
#define NUMPY_NARY_FUNC_SYM std::abs
#endif
#include "pythonic/include/types/numpy_nary_expr.hpp"
}
PYTHONIC_NS_END

#endif
