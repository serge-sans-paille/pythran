//==================================================================================================
/**
  Copyright 2016 Numscale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
**/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_X86_AVX2_SIMD_FUNCTION_DEINTERLEAVE_FIRST_HPP_INCLUDED
#define BOOST_SIMD_ARCH_X86_AVX2_SIMD_FUNCTION_DEINTERLEAVE_FIRST_HPP_INCLUDED

#include <boost/simd/detail/overload.hpp>
#include <boost/simd/function/lookup.hpp>

namespace boost { namespace simd { namespace ext
{
  namespace bd =  boost::dispatch;
  namespace bs =  boost::simd;

  BOOST_DISPATCH_OVERLOAD ( deinterleave_first_
                          , (typename A0)
                          , bs::avx2_
                          , bs::pack_<bd::ints8_<A0>, bs::avx_>
                          , bs::pack_<bd::ints8_<A0>, bs::avx_>
                         )
  {
    BOOST_FORCEINLINE A0 operator()(const A0 & a0, const A0 & a1 ) const BOOST_NOEXCEPT
    {
      auto l    = _mm256_unpacklo_epi8(a0,a1);
      auto h    = _mm256_unpackhi_epi8(a0,a1);
      auto lh0  = _mm256_unpacklo_epi8(_mm256_unpacklo_epi8(l, h), _mm256_unpackhi_epi8(l, h));
      auto lh1  = _mm256_unpackhi_epi8(_mm256_unpacklo_epi8(l, h), _mm256_unpackhi_epi8(l, h));
      return _mm256_permute4x64_epi64(_mm256_unpacklo_epi8(lh0, lh1), 0xD8);
    }
  };

  BOOST_DISPATCH_OVERLOAD ( deinterleave_first_
                          , (typename A0)
                          , bs::avx2_
                          , bs::pack_<bd::ints16_<A0>, bs::avx_>
                          , bs::pack_<bd::ints16_<A0>, bs::avx_>
                         )
  {
    BOOST_FORCEINLINE A0 operator()(const A0 & a0, const A0 & a1 ) const BOOST_NOEXCEPT
    {
      auto l = _mm256_unpacklo_epi16(a0,a1);
      auto h = _mm256_unpackhi_epi16(a0,a1);
           l = _mm256_unpacklo_epi16(_mm256_unpacklo_epi16(l,h), _mm256_unpackhi_epi16(l,h));
      return _mm256_permute4x64_epi64(l, 0xD8);
    }
  };

  BOOST_DISPATCH_OVERLOAD ( deinterleave_first_
                          , (typename A0)
                          , bs::avx2_
                          , bs::pack_<bd::ints32_<A0>, bs::avx_>
                          , bs::pack_<bd::ints32_<A0>, bs::avx_>
                         )
  {
    BOOST_FORCEINLINE A0 operator()(const A0 & a0, const A0 & a1 ) const BOOST_NOEXCEPT
    {
      auto l = _mm256_unpacklo_epi32(a0,a1);
      auto h = _mm256_unpackhi_epi32(a0,a1);
           l = _mm256_unpacklo_epi32(l, h);
      return _mm256_permutevar8x32_epi32(l, A0(0,1,4,5,2,3,6,7));
    }
  };

  BOOST_DISPATCH_OVERLOAD ( deinterleave_first_
                          , (typename A0)
                          , bs::avx2_
                          , bs::pack_<bd::ints64_<A0>, bs::avx_>
                          , bs::pack_<bd::ints64_<A0>, bs::avx_>
                         )
  {
    BOOST_FORCEINLINE A0 operator()(const A0 & a0, const A0 & a1 ) const BOOST_NOEXCEPT
    {
      auto l = _mm256_unpacklo_epi64(a0,a1);
      return _mm256_permute4x64_epi64(l, 0xD8);
    }
  };
} } }

#endif
