#ifndef PYTHONIC_INCLUDE_NUMPY_FLOORDIVIDE_HPP
#define PYTHONIC_INCLUDE_NUMPY_FLOORDIVIDE_HPP

#include "pythonic/include/utils/functor.hpp"
#include "pythonic/include/types/ndarray.hpp"
#include "pythonic/include/types/numpy_broadcast.hpp"
#include "pythonic/include/utils/numpy_traits.hpp"

#ifdef USE_GMP
#include "pythonic/include/types/long.hpp"
#endif

#include <boost/simd/function/div.hpp>

PYTHONIC_NS_BEGIN

namespace numpy
{
  namespace wrapper
  {
    template <class Arg0, class Arg1>
    auto divfloor(Arg0 const &arg0, Arg1 const &arg1) ->
        typename std::enable_if<(std::is_integral<Arg0>::value &&
                                 std::is_floating_point<Arg1>::value),
                                Arg1>::type
    {
      return std::floor(arg0 / arg1);
    }

    template <class Arg0, class Arg1>
    auto divfloor(Arg0 const &arg0, Arg1 const &arg1) ->
        typename std::enable_if<(std::is_integral<Arg1>::value &&
                                 std::is_floating_point<Arg0>::value),
                                Arg0>::type
    {
      return std::floor(arg0 / arg1);
    }
    template <class T0, class T1>
    auto divfloor(T0 const &arg0, T1 const &arg1) ->
        typename std::enable_if<std::is_same<T0, T1>::value,
                                decltype(boost::simd::div(boost::simd::floor,
                                                          arg0, arg1))>::type
    {
      return boost::simd::div(boost::simd::floor, arg0, arg1);
    }
#ifdef USE_GMP
    template <class T0, class U0, class T>
    auto divfloor(__gmp_expr<T0, U0> const &arg0, T const &arg1)
        -> decltype(arg0 / arg1)
    {
      return arg0 / arg1;
    }
#endif
  }
#define NUMPY_NARY_FUNC_NAME floor_divide
#define NUMPY_NARY_FUNC_SYM wrapper::divfloor
#include "pythonic/include/types/numpy_nary_expr.hpp"
}
PYTHONIC_NS_END

#endif
