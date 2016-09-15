//==================================================================================================
/**
  Copyright 2016 Numscale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
**/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_X86_SSE2_SIMD_FUNCTION_SUM_HPP_INCLUDED
#define BOOST_SIMD_ARCH_X86_SSE2_SIMD_FUNCTION_SUM_HPP_INCLUDED

#include <boost/simd/detail/overload.hpp>

namespace boost { namespace simd { namespace ext
{
  namespace bd =  boost::dispatch;
  namespace bs =  boost::simd;

  BOOST_DISPATCH_OVERLOAD ( sum_
                          , (typename A0)
                          , bs::sse2_
                          , bs::pack_<bd::double_<A0>, bs::sse_>
                         )
  {
    BOOST_FORCEINLINE double operator()(const A0& a0) const BOOST_NOEXCEPT
    {
      // Limit pressure on the shuffle port by using store port
      double tmp;
      _mm_storeh_pd(&tmp, a0);
      return _mm_cvtsd_f64(a0)+tmp;
    }
  };

  BOOST_DISPATCH_OVERLOAD ( sum_
                          , (typename A0)
                          , bs::sse2_
                          , bs::pack_<bd::ints32_<A0>, bs::sse_>
                         )
  {
    BOOST_FORCEINLINE typename A0::value_type operator()(const A0& a0) const BOOST_NOEXCEPT
    {
      __m128i sum64 = _mm_add_epi32 (_mm_shuffle_epi32(a0, _MM_SHUFFLE(1, 0, 3, 2))
                                    , a0
                                    );

      __m128i sum32 = _mm_add_epi32 ( sum64
                                    , _mm_shufflelo_epi16(sum64, _MM_SHUFFLE(1, 0, 3, 2))
                                    );

      return _mm_cvtsi128_si32(sum32);
    }
  };

  BOOST_DISPATCH_OVERLOAD ( sum_
                          , (typename A0)
                          , bs::sse2_
                          , bs::pack_<bd::ints8_<A0>, bs::sse_>
                         )
  {
    BOOST_FORCEINLINE typename A0::value_type operator()(const A0& a0) const BOOST_NOEXCEPT
    {
      // no int8 shuffle, so we optimize using other ways
      __m128i r  = _mm_set1_epi32(0);
      __m128i z  = _mm_set1_epi8(0);
      __m128i o  = _mm_set1_epi16(1);

      r = _mm_add_epi32(r, _mm_madd_epi16(_mm_unpacklo_epi8(a0, z), o));
      r = _mm_add_epi32(r, _mm_madd_epi16(_mm_unpackhi_epi8(a0, z), o));
      r = _mm_add_epi32(r, _mm_srli_si128(r, 8));
      r = _mm_add_epi32(r, _mm_srli_si128(r, 4));

      return typename A0::value_type(_mm_cvtsi128_si32(r));
    }
  };

  BOOST_DISPATCH_OVERLOAD ( sum_
                          , (typename A0)
                          , bs::sse2_
                          , bs::pack_<bd::ints16_<A0>, bs::sse_>
                         )
  {
    BOOST_FORCEINLINE typename A0::value_type operator()(const A0& a0) const BOOST_NOEXCEPT
    {
      // no int16 shuffle, so we optimize using other ways
      __m128i r  = _mm_set1_epi32(0);
      r = _mm_add_epi32(r, _mm_madd_epi16(a0, _mm_set1_epi16(1)));
      r = _mm_add_epi32(r, _mm_srli_si128(r, 8));
      r = _mm_add_epi32(r, _mm_srli_si128(r, 4));

      return typename A0::value_type(_mm_cvtsi128_si32(r));
    }
  };
} } }

#endif
