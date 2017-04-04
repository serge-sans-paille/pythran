//==================================================================================================
/*!
  @file

  @copyright 2015 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_COMMON_SCALAR_FUNCTION_TWO_PROD_HPP_INCLUDED
#define BOOST_SIMD_ARCH_COMMON_SCALAR_FUNCTION_TWO_PROD_HPP_INCLUDED

#include <boost/simd/detail/enforce_precision.hpp>
#include <boost/simd/function/if_zero_else.hpp>
#include <boost/simd/function/is_invalid.hpp>
#include <boost/simd/function/minus.hpp>
#include <boost/simd/function/multiplies.hpp>
#include <boost/simd/function/two_split.hpp>
#include <boost/simd/detail/dispatch/function/overload.hpp>
#include <boost/config.hpp>
#include <utility>

namespace boost { namespace simd { namespace ext
{
  namespace bd = boost::dispatch;

  BOOST_DISPATCH_OVERLOAD ( two_prod_
                          , (typename A0)
                          , bd::cpu_
                          , bd::scalar_< bd::floating_<A0> >
                          , bd::scalar_< bd::floating_<A0> >
                          )
  {
    using result_t = std::pair<A0,A0>;
    BOOST_FORCEINLINE
      result_t operator() ( A0 a,A0 b) const BOOST_NOEXCEPT
    {
      detail::enforce_precision<A0> enforcer;
      A0 a1, a2, b1, b2;
      std::tie(a1, a2) = two_split(a);
      std::tie(b1, b2) = two_split(b);
      A0 r0 = a*b;
#if defined(BOOST_SIMD_NO_INVALIDS)
      return {r0, a2*b2 -(((r0-a1*b1)-a2*b1)-a1*b2)};
#else
      return {r0, if_zero_else(is_invalid(r0), a2*b2 -(((r0-a1*b1)-a2*b1)-a1*b2))};
#endif

    }
  };
} } }


#endif
