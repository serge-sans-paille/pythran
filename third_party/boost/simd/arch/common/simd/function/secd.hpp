//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_COMMON_SIMD_FUNCTION_SECD_HPP_INCLUDED
#define BOOST_SIMD_ARCH_COMMON_SIMD_FUNCTION_SECD_HPP_INCLUDED

#include <boost/simd/function/restricted.hpp>
#include <boost/simd/constant/ratio.hpp>
#include <boost/simd/function/cosd.hpp>
#include <boost/simd/function/if_nan_else.hpp>
#include <boost/simd/function/is_flint.hpp>
#include <boost/simd/function/rec.hpp>
#include <boost/simd/detail/dispatch/function/overload.hpp>
#include <boost/config.hpp>

namespace boost { namespace simd { namespace ext
{
  namespace bd = boost::dispatch;
  namespace bs = boost::simd;
  BOOST_DISPATCH_OVERLOAD_IF ( secd_
                          , (typename A0, typename X)
                          , (detail::is_native<X>)
                          , bd::cpu_
                          , bs::pack_< bd::floating_<A0>, X>
                          )
  {
    BOOST_FORCEINLINE A0 operator() ( A0 const& a0) const BOOST_NOEXCEPT
    {
      return secd(a0, tag::big_);
    }
  };
  BOOST_DISPATCH_OVERLOAD ( secd_
                          , (typename A0, typename A1, typename X)
                          , bd::cpu_
                          , bs::pack_< bd::floating_<A0>, X>
                          , bd::scalar_ < bd::unspecified_<A1>>
                          )
  {
    BOOST_FORCEINLINE A0 operator() ( A0 const& a0, A1 const&) const BOOST_NOEXCEPT
    {
      return if_nan_else(is_flint((a0- Ratio<A0,90>())*Ratio<A0,1,180>())
                        , rec(cosd(a0,A1())));
    }
  };
  BOOST_DISPATCH_OVERLOAD_IF ( secd_
                          , (typename A0, typename X)
                          , (detail::is_native<X>)
                          , bd::cpu_
                          , bs::restricted_tag
                          , bs::pack_< bd::floating_<A0>, X>
                          )
  {
    BOOST_FORCEINLINE A0 operator() (const restricted_tag &,  A0 const& a0) const BOOST_NOEXCEPT
    {
      return rec(restricted_(cosd)(a0));
    }
  };
} } }


#endif
