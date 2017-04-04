//==================================================================================================
/*!
  @file

  @copyright 2015 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_COMMON_SCALAR_FUNCTION_SAFE_MAX_HPP_INCLUDED
#define BOOST_SIMD_ARCH_COMMON_SCALAR_FUNCTION_SAFE_MAX_HPP_INCLUDED

#include <boost/simd/constant/inf.hpp>
#include <boost/simd/constant/sqrtvalmax.hpp>
#include <boost/simd/function/abs.hpp>
#include <boost/simd/function/divides.hpp>
#include <boost/simd/function/if_else.hpp>
#include <boost/simd/function/is_nez.hpp>
#include <boost/simd/detail/dispatch/function/overload.hpp>
#include <boost/config.hpp>

namespace boost { namespace simd { namespace ext
{
  namespace bd = boost::dispatch;
  BOOST_DISPATCH_OVERLOAD ( safe_max_
                          , (typename A0)
                          , bd::cpu_
                          , bd::scalar_< bd::floating_<A0> >
                          )
  {
    BOOST_FORCEINLINE A0 operator() ( A0 a0) const BOOST_NOEXCEPT
    {
      return (is_nez(a0)? Sqrtvalmax<A0>()/bs::abs(a0): Inf<A0>());
    }
  };
} } }


#endif
