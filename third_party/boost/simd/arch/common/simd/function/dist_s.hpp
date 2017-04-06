//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_COMMON_SIMD_FUNCTION_DIST_S_HPP_INCLUDED
#define BOOST_SIMD_ARCH_COMMON_SIMD_FUNCTION_DIST_S_HPP_INCLUDED
#include <boost/simd/detail/overload.hpp>

#include <boost/simd/meta/hierarchy/simd.hpp>
#include <boost/simd/constant/valmax.hpp>
#include <boost/simd/constant/zero.hpp>
#include <boost/simd/function/dist.hpp>
#include <boost/simd/function/if_else.hpp>
#include <boost/simd/detail/dispatch/function/overload.hpp>
#include <boost/config.hpp>

namespace boost { namespace simd { namespace ext
{
  namespace bd = boost::dispatch;
  namespace bs = boost::simd;
  BOOST_DISPATCH_OVERLOAD_IF ( dist_
                          , (typename A0, typename X)
                          , (detail::is_native<X>)
                          , bd::cpu_
                          , bs::saturated_tag
                          , bs::pack_< bd::signed_<A0>, X>
                          , bs::pack_< bd::signed_<A0>, X>
                          )
  {
    BOOST_FORCEINLINE A0 operator() (const saturated_tag &
                                    , A0 const& a0, A0 const& a1
                                    ) const BOOST_NOEXCEPT
    {
      A0 tmp = dist(a0, a1);
      return if_else(is_ltz(tmp), Valmax<A0>(), tmp);
    }
  };
  BOOST_DISPATCH_OVERLOAD_IF ( dist_
                          , (typename A0, typename X)
                          , (detail::is_native<X>)
                          , bd::cpu_
                          , bs::saturated_tag
                          , bs::pack_< bd::unsigned_<A0>, X >
                          , bs::pack_< bd::unsigned_<A0>, X >
                          )
  {
    BOOST_FORCEINLINE A0 operator() (const saturated_tag &
                                    , A0 const& a0, A0 const& a1
                                    ) const BOOST_NOEXCEPT
    {
      return dist(a0, a1);
    }
  };
  BOOST_DISPATCH_OVERLOAD_IF ( dist_
                          , (typename A0, typename X)
                          , (detail::is_native<X>)
                          , bd::cpu_
                          , bs::saturated_tag
                          , bs::pack_<bd::floating_<A0>, X >
                          , bs::pack_<bd::floating_<A0>, X >
                          )
  {
    BOOST_FORCEINLINE A0 operator() (const saturated_tag &
                                    , A0 const& a0, A0 const& a1
                                    ) const BOOST_NOEXCEPT
    {
      return dist(a0, a1);
    }
  };
} } }


#endif
