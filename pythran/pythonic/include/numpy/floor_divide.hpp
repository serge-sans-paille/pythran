#ifndef PYTHONIC_INCLUDE_NUMPY_FLOORDIVIDE_HPP
#define PYTHONIC_INCLUDE_NUMPY_FLOORDIVIDE_HPP

#include "pythonic/include/utils/functor.hpp"
#include "pythonic/include/types/ndarray.hpp"
#include "pythonic/include/types/numpy_broadcast.hpp"
#include "pythonic/include/utils/numpy_traits.hpp"

#include <boost/simd/function/div.hpp>

PYTHONIC_NS_BEGIN

namespace numpy
{
  namespace wrapper
  {
    template <class Arg0, class Arg1>
    std::complex<typename __combined<Arg0, Arg1>::type>
    divfloor(std::complex<Arg0> const &arg0, std::complex<Arg1> const &arg1)
    {
      auto tmp = arg0 / arg1;
      return {std::floor(tmp.real()), std::floor(tmp.imag())};
    }

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
  }
#define NUMPY_NARY_FUNC_NAME floor_divide
#define NUMPY_NARY_FUNC_SYM wrapper::divfloor
#include "pythonic/include/types/numpy_nary_expr.hpp"
}
PYTHONIC_NS_END

#endif
