//==================================================================================================
/*!
    @file

    @Copyright 2016 Numscale SAS

    Distributed under the Boost Software License, Version 1.0.
    (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_X86_SSE2_SIMD_FUNCTION_ILOGB_HPP_INCLUDED
#define BOOST_SIMD_ARCH_X86_SSE2_SIMD_FUNCTION_ILOGB_HPP_INCLUDED

#include <boost/simd/detail/overload.hpp>
#include <boost/simd/function/abs.hpp>
#include <boost/simd/function/bitwise_and.hpp>
#include <boost/simd/function/bitwise_cast.hpp>
#include <boost/simd/function/dec.hpp>
#include <boost/simd/function/exponent.hpp>
#include <boost/simd/function/group.hpp>
#include <boost/simd/function/if_inc.hpp>
#include <boost/simd/function/split.hpp>
#include <boost/simd/function/if_else.hpp>
#include <boost/simd/function/if_zero_else.hpp>
#include <boost/simd/function/is_lez.hpp>
#include <boost/simd/function/is_nez.hpp>
#include <boost/simd/function/shift_right.hpp>
#include <boost/simd/function/tofloat.hpp>
#include <boost/simd/constant/one.hpp>
#include <boost/simd/constant/constant.hpp>
#include <boost/simd/constant/zero.hpp>
#include <boost/simd/detail/dispatch/meta/upgrade.hpp>

namespace boost { namespace simd { namespace ext
{
  namespace bd =  boost::dispatch;
  namespace bs =  boost::simd;

  BOOST_DISPATCH_OVERLOAD ( ilogb_
                          , (typename A0)
                          , bs::sse2_
                          , bs::pack_<bd::uint8_<A0>, bs::sse_>
                          )
  {

    BOOST_FORCEINLINE A0 operator() ( const A0 & a0)
    {
      using ui16_t =  bd::upgrade_t<A0>;
      const A0 mask =  Constant<A0, 0x7f>();
      A0 n = a0;
      A0 i = One<A0>();
      n = bitwise_and(mask, shift_right(bitwise_cast<ui16_t>(n), 1));
      i = if_inc(is_nez(n), i);
      n = bitwise_and(mask, shift_right(bitwise_cast<ui16_t>(n), 1));
      i = if_inc(is_nez(n), i);
      n = bitwise_and(mask, shift_right(bitwise_cast<ui16_t>(n), 1));
      i = if_inc(is_nez(n), i);
      n = bitwise_and(mask, shift_right(bitwise_cast<ui16_t>(n), 1));
      i = if_inc(is_nez(n), i);
      n = bitwise_and(mask, shift_right(bitwise_cast<ui16_t>(n), 1));
      i = if_inc(is_nez(n), i);
      n = bitwise_and(mask, shift_right(bitwise_cast<ui16_t>(n), 1));
      i = if_inc(is_nez(n), i);
      n = bitwise_and(mask, shift_right(bitwise_cast<ui16_t>(n), 1));
      i = if_inc(is_nez(n), i);
      return dec(i);
    }
  };
  BOOST_DISPATCH_OVERLOAD ( ilogb_
                          , (typename A0)
                          , bs::sse2_
                          , bs::pack_<bd::int8_<A0>, bs::sse_>
                          )
  {

    BOOST_FORCEINLINE A0 operator() ( const A0 & a0)
    {
      using uA0 = bd::as_integer_t<A0, unsigned>;
      return bitwise_cast<A0>(ilogb(bitwise_cast<uA0>(saturated_(abs)(a0))));
    }
  };

} } }

#endif
