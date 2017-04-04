//==================================================================================================
/*!
  @file

  @copyright 2017 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_COMMON_SIMD_FUNCTION_ILOGB_HPP_INCLUDED
#define BOOST_SIMD_ARCH_COMMON_SIMD_FUNCTION_ILOGB_HPP_INCLUDED
#include <boost/simd/detail/overload.hpp>

#include <boost/simd/meta/hierarchy/simd.hpp>
#include <boost/simd/function/bitwise_cast.hpp>
#include <boost/simd/function/exponent.hpp>
#include <boost/simd/function/group.hpp>
#include <boost/simd/function/if_else.hpp>
#include <boost/simd/function/is_inf.hpp>
#include <boost/simd/function/is_nan.hpp>
#include <boost/simd/function/pedantic.hpp>
#include <boost/simd/function/split.hpp>
#include <boost/simd/function/std.hpp>
#include <boost/simd/function/tofloat.hpp>
#include <boost/simd/constant/valmax.hpp>
#include <boost/simd/detail/dispatch/meta/as_integer.hpp>
#include <boost/simd/detail/dispatch/meta/as_floating.hpp>
#include <cmath>
namespace boost { namespace simd { namespace ext
{
  namespace bd = boost::dispatch;
  namespace bs = boost::simd;
  BOOST_DISPATCH_OVERLOAD_IF(ilogb_
                            , (typename A0, typename X)
                            , (detail::is_native<X>)
                            , bd::cpu_
                            , bs::pack_<bd::floating_<A0>, X>
                            )
  {
    using result_t = bd::as_integer_t<A0>;
    BOOST_FORCEINLINE result_t operator()( const A0& a0) const BOOST_NOEXCEPT
    {
      return if_else(is_inf(a0), Valmax<result_t>(), exponent(a0));
    }
  };

  BOOST_DISPATCH_OVERLOAD(ilogb_
                         , (typename A0, typename X)
                         , bd::cpu_
                         , bs::pedantic_tag
                         , bs::pack_<bd::floating_<A0>, X>
                         )
  {
    using result_t = bd::as_integer_t<A0>;
    BOOST_FORCEINLINE result_t operator()(const pedantic_tag &
                                         ,  const A0& a0) const BOOST_NOEXCEPT
    {
      result_t fp_ilogbnan(FP_ILOGBNAN);
      result_t fp_ilogb0(FP_ILOGB0);
      return if_else(is_nan(a0), fp_ilogbnan,
                            if_else(is_eqz(a0), fp_ilogb0
                                   , bs::ilogb(a0)));
    }
  };

  BOOST_DISPATCH_OVERLOAD_IF(ilogb_
                            , (typename A0, typename X)
                            , (detail::is_native<X>)
                            , bd::cpu_
                            , bs::pack_<bd::integer_<A0>, X>
                            )
  {
    BOOST_FORCEINLINE A0 operator()( const A0& a0) const BOOST_NOEXCEPT
    {
      return bitwise_cast<A0>(ilogb(tofloat(a0)));
    }
  };

  BOOST_DISPATCH_OVERLOAD_IF ( ilogb_
                             , (typename A0, typename X)
                             , (detail::is_native<X>)
                             , bd::cpu_
                             , bs::pack_<bd::ints16_<A0>, X>
                             )
  {
    BOOST_FORCEINLINE A0 operator() ( const A0 & a0)
    {
      auto s0 = split(a0);
      return bitwise_cast<A0>(group(ilogb(s0[0]), ilogb(s0[1])));
    }
  };

  BOOST_DISPATCH_OVERLOAD_IF ( ilogb_
                             , (typename A0, typename X)
                             , (detail::is_native<X>)
                             , bd::cpu_
                             , bs::pack_<bd::ints8_<A0>, X>
                             )
  {
    using result = bd::as_integer_t<A0>;
    BOOST_FORCEINLINE A0 operator() ( const A0 & a0)
    {
      auto s0 = split(a0);
      return bitwise_cast<A0>(group(ilogb(s0[0]), ilogb(s0[1])));
    }
  };
} } }

#endif

