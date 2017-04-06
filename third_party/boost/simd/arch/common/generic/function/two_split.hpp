//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_COMMON_GENERIC_FUNCTION_TWO_SPLIT_HPP_INCLUDED
#define BOOST_SIMD_ARCH_COMMON_GENERIC_FUNCTION_TWO_SPLIT_HPP_INCLUDED

#include <boost/simd/detail/constant/splitfactor.hpp>
#include <boost/simd/detail/enforce_precision.hpp>
#include <boost/simd/function/minus.hpp>
#include <boost/simd/function/multiplies.hpp>
#include <boost/simd/detail/dispatch/function/overload.hpp>
#include <boost/config.hpp>
#include <utility>

namespace boost { namespace simd { namespace ext
{
  namespace bd = boost::dispatch;

  BOOST_DISPATCH_OVERLOAD ( two_split_
                          , (typename A0)
                          , bd::cpu_
                          , bd::generic_< bd::floating_<A0> >
                          )
  {
    using result_t = std::pair<A0,A0>;
    BOOST_FORCEINLINE result_t operator() ( A0 const& a) const BOOST_NOEXCEPT
    {
      detail::enforce_precision<A0> enforcer;
      A0 const c = Splitfactor<A0>()*a;
      A0 const c1 = c-a;
      A0 r0 = c-c1;
      return {r0, a-r0};
    }
  };
} } }


#endif
