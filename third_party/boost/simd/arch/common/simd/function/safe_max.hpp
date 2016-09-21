//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_COMMON_SIMD_FUNCTION_SAFE_MAX_HPP_INCLUDED
#define BOOST_SIMD_ARCH_COMMON_SIMD_FUNCTION_SAFE_MAX_HPP_INCLUDED

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
  BOOST_DISPATCH_OVERLOAD_IF ( safe_max_
                          , (typename A0, typename X)
                          , (detail::is_native<X>)
                          , bd::cpu_
                          , bs::pack_< bd::floating_<A0>, X>
                          )
  {
    BOOST_FORCEINLINE A0 operator() ( A0 const& a0) const BOOST_NOEXCEPT
    {
      return if_else(is_nez(a0), Sqrtvalmax<A0>()/bs::abs(a0),
                     Inf<A0>());
    }
  };
} } }


#endif
