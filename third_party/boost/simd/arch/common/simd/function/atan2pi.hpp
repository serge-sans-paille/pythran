//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_COMMON_SIMD_FUNCTION_ATAN2PI_HPP_INCLUDED
#define BOOST_SIMD_ARCH_COMMON_SIMD_FUNCTION_ATAN2PI_HPP_INCLUDED

#include <boost/simd/function/atan2.hpp>
#include <boost/simd/constant/invpi.hpp>
#include <boost/simd/detail/dispatch/function/overload.hpp>
#include <boost/config.hpp>

namespace boost { namespace simd { namespace ext
                                   {
  namespace bd = boost::dispatch;
  namespace bs = boost::simd;
  BOOST_DISPATCH_OVERLOAD_IF ( atan2pi_
                          , (typename A0, typename A1, typename X)
                          , (detail::is_native<X>)
                          , bd::cpu_
                          , bs::pack_< bd::floating_<A0>, X>
                          , bs::pack_< bd::floating_<A1>, X >
                          )
  {
     BOOST_FORCEINLINE A0 operator() ( A0 const& a0, A1 const& a1) const BOOST_NOEXCEPT
    {
      return Invpi<A0>()*(atan2(a0, a1));
    }
  };

   BOOST_DISPATCH_OVERLOAD_IF ( atan2pi_
                          , (typename A0, typename A1, typename X)
                          , (detail::is_native<X>)
                          , bd::cpu_
                          , bs::pedantic_tag
                          , bs::pack_< bd::floating_<A0>, X>
                          , bs::pack_< bd::floating_<A1>, X >
                          )
  {
     BOOST_FORCEINLINE A0 operator() (const pedantic_tag &,
                                      A0 const& a0, A1 const& a1) const BOOST_NOEXCEPT
    {
      return Invpi<A0>()*pedantic_(atan2)(a0, a1);
    }
  };
} } }


#endif
