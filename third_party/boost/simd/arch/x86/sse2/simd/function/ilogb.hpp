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

#include <boost/simd/function/bitwise_and.hpp>
#include <boost/simd/function/bitwise_cast.hpp>
#include <boost/simd/function/dec.hpp>
#include <boost/simd/function/exponent.hpp>
#include <boost/simd/function/group.hpp>
#include <boost/simd/function/if_plus.hpp>
#include <boost/simd/function/split.hpp>
#include <boost/simd/function/if_else.hpp>
#include <boost/simd/function/if_zero_else.hpp>
#include <boost/simd/function/is_eqz.hpp>
#include <boost/simd/function/is_lez.hpp>
#include <boost/simd/function/is_nez.hpp>
#include <boost/simd/function/minus.hpp>
#include <boost/simd/function/plus.hpp>
#include <boost/simd/function/tofloat.hpp>
#include <boost/simd/constant/one.hpp>
#include <boost/simd/constant/constant.hpp>
#include <boost/simd/constant/zero.hpp>


namespace boost { namespace simd { namespace ext
{
  namespace bd =  boost::dispatch;
  namespace bs =  boost::simd;
  BOOST_DISPATCH_OVERLOAD ( ilogb_
                          , (typename A0)
                          , bs::sse2_
                          , bs::pack_<bd::int_<A0>, bs::sse_>
                         )
  {
    using result = bd::as_integer_t<A0>;
    BOOST_FORCEINLINE result operator() ( const A0 & a0)
    {
      using vtype = bd::as_integer_t<A0,unsigned>;
      return simd::bitwise_cast<A0>(if_zero_else( is_lez(a0)
                                                , ilogb(simd::bitwise_cast<vtype>(a0))
                                                )
                                   );
    }
  };
  BOOST_DISPATCH_OVERLOAD ( ilogb_
                          , (typename A0)
                          , bs::sse2_
                          , bs::pack_<bd::uint8_<A0>, bs::sse_>
                          )
  {

    BOOST_FORCEINLINE A0 operator() ( const A0 & a0)
    {
#define MKN8 simd::bitwise_cast<A0>
      const A0 mask =  Constant<A0, 0x7f>();
      A0 n = a0;
      A0 i = One<A0>();
      n = bitwise_and(MKN8(_mm_srli_epi16(n, 1)), mask);
      i = if_plus(is_nez(n), i, One<A0>());
      n = bitwise_and(MKN8(_mm_srli_epi16(n, 1)), mask);
      i = if_plus(is_nez(n), i, One<A0>());
      n = bitwise_and(MKN8(_mm_srli_epi16(n, 1)), mask);
      i = if_plus(is_nez(n), i, One<A0>());
      n = bitwise_and(MKN8(_mm_srli_epi16(n, 1)), mask);
      i = if_plus(is_nez(n), i, One<A0>());
      n = bitwise_and(MKN8(_mm_srli_epi16(n, 1)), mask);
      i = if_plus(is_nez(n), i, One<A0>());
      n = bitwise_and(MKN8(_mm_srli_epi16(n, 1)), mask);
      i = if_plus(is_nez(n), i, One<A0>());
      n = bitwise_and(MKN8(_mm_srli_epi16(n, 1)), mask);
      i = if_plus(is_nez(n), i, One<A0>());
      return dec(i);
    }
#undef MKN8
  };

  BOOST_DISPATCH_OVERLOAD ( ilogb_
                          , (typename A0)
                          , bs::sse2_
                          , bs::pack_<bd::ints16_<A0>, bs::sse_>
                          )
  {
    using result = bd::as_integer_t<A0>;
    BOOST_FORCEINLINE result operator() ( const A0 & a0)
    {
      auto s0 = split(a0);
      return bitwise_cast<result>(group(ilogb(s0[0]), ilogb(s0[1])));
    }
  };
  BOOST_DISPATCH_OVERLOAD ( ilogb_
                          , (typename A0)
                          , bs::sse2_
                          , bs::pack_<bd::unsigned_<A0>, bs::sse_>
                          )
  {
    using result = bd::as_integer_t<A0>;
    BOOST_FORCEINLINE result operator() ( const A0 & a0)
    {
      return simd::bitwise_cast<A0>(bs::exponent(tofloat(a0)));
    }
  };
} } }

#endif
