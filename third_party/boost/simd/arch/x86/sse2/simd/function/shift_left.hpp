//==================================================================================================
/*!
    @file

    @Copyright 2016 Numscale SAS

    Distributed under the Boost Software License, Version 1.0.
    (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_X86_SSE2_SIMD_FUNCTION_SHIFT_LEFT_HPP_INCLUDED
#define BOOST_SIMD_ARCH_X86_SSE2_SIMD_FUNCTION_SHIFT_LEFT_HPP_INCLUDED
#include <boost/simd/detail/overload.hpp>

#include <boost/simd/function/bitwise_and.hpp>
#include <boost/simd/function/bitwise_or.hpp>
#include <boost/simd/function/bitwise_ornot.hpp>
#include <boost/simd/function/bitwise_cast.hpp>
#include <boost/simd/function/if_else_allbits.hpp>
#include <boost/simd/function/is_ltz.hpp>
#include <boost/simd/function/group.hpp>
#include <boost/simd/function/split.hpp>
#include <boost/simd/function/splat.hpp>
#include <boost/simd/constant/signmask.hpp>
#include <boost/simd/constant/allbits.hpp>
#include <boost/simd/constant/constant.hpp>
#include <boost/simd/detail/make_dependent.hpp>

namespace boost { namespace simd { namespace ext
{
  namespace bd =  boost::dispatch;
  namespace bs =  boost::simd;
  BOOST_DISPATCH_OVERLOAD ( shift_left_
                          , (typename A0,typename A1 )
                          , bs::sse2_
                          , bs::pack_<bd::ints8_<A0>, bs::sse_>
                          , bd::scalar_<bd::integer_<A1>>
                          )
  {
    BOOST_FORCEINLINE A0 operator() ( const A0 & a0
                                    , const A1 & a1 ) const BOOST_NOEXCEPT
    {
      using int_t =  detail::make_dependent_t<std::uint16_t,A0>;
      using gen_t = pack<int_t, A0::static_size/2>;
      BOOST_ASSERT_MSG(assert_good_shift<A0>(a1), "shift_left ints8 sse2: a shift is out of range");
      A0 const Mask1 = bitwise_cast<A0>( gen_t(0x00ff));
      A0 const Mask2 = bitwise_cast<A0>( gen_t(0xff00));
      A0 tmp  = bitwise_and(a0, Mask1);
      A0 tmp1 = _mm_slli_epi16(tmp, int(a1));
      tmp1 = bitwise_and(tmp1, Mask1);
      tmp = bitwise_and(a0, Mask2);
      A0 tmp3 = _mm_slli_epi16(tmp, int(a1));
      return bitwise_or(tmp1, bitwise_and(tmp3, Mask2));
    }
  };

  BOOST_DISPATCH_OVERLOAD ( shift_left_
                          , (typename A0,typename A1 )
                          , bs::sse2_
                          , bs::pack_<bd::ints16_<A0>, bs::sse_>
                          , bd::scalar_<bd::integer_<A1>>
                         )
  {
    BOOST_FORCEINLINE A0 operator() ( const A0 & a0
                                    , const A1 & a1 ) const BOOST_NOEXCEPT
    {
      BOOST_ASSERT_MSG(assert_good_shift<A0>(a1), "shift_left ints16 sse2: a shift is out of range");
      return _mm_slli_epi16(a0, a1);
    }
  };

  BOOST_DISPATCH_OVERLOAD ( shift_left_
                          , (typename A0,typename A1 )
                          , bs::sse2_
                          , bs::pack_<bd::ints32_<A0>, bs::sse_>
                          , bd::scalar_<bd::integer_<A1>>
                         )
  {
    BOOST_FORCEINLINE A0 operator() ( const A0 & a0
                                    , const A1 & a1 ) const BOOST_NOEXCEPT
    {
      BOOST_ASSERT_MSG(assert_good_shift<A0>(a1), "shift_left ints32 sse2: a shift is out of range");
      return _mm_slli_epi32(a0, a1);
    }
  };

  BOOST_DISPATCH_OVERLOAD ( shift_left_
                          , (typename A0,typename A1 )
                          , bs::sse2_
                          , bs::pack_<bd::ints64_<A0>, bs::sse_>
                          , bd::scalar_<bd::integer_<A1>>
                         )
  {
    BOOST_FORCEINLINE A0 operator() ( const A0 & a0
                                    , const A1 & a1 ) const BOOST_NOEXCEPT
    {
      BOOST_ASSERT_MSG(assert_good_shift<A0>(a1), "shift_left ints64 sse2: a shift is out of range");
      return _mm_slli_epi64(a0, int(a1));
    }
  };
} } }

#endif
