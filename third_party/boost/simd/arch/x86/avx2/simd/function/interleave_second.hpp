//==================================================================================================
/**
  Copyright 2017 Numscale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_X86_AVX2_SIMD_FUNCTION_INTERLEAVE_SECOND_HPP_INCLUDED
#define BOOST_SIMD_ARCH_X86_AVX2_SIMD_FUNCTION_INTERLEAVE_SECOND_HPP_INCLUDED

#include <boost/simd/detail/overload.hpp>

namespace boost { namespace simd { namespace ext
{
  namespace bd =  boost::dispatch;
  namespace bs =  boost::simd;

  BOOST_DISPATCH_OVERLOAD ( interleave_second_
                          , (typename A0)
                          , bs::avx2_
                          , bs::pack_<bd::ints8_<A0>, bs::avx_>
                          , bs::pack_<bd::ints8_<A0>, bs::avx_>
                         )
  {
    BOOST_FORCEINLINE A0 operator()(const A0 & a0, const A0 & a1 ) const BOOST_NOEXCEPT
    {
      auto l = _mm256_unpacklo_epi8(a0, a1);
      auto h = _mm256_unpackhi_epi8(a0, a1);
      return A0(_mm256_permute2x128_si256(l, h, 0x31));
    }
  };

  BOOST_DISPATCH_OVERLOAD ( interleave_second_
                          , (typename A0)
                          , bs::avx2_
                          , bs::pack_<bd::ints16_<A0>, bs::avx_>
                          , bs::pack_<bd::ints16_<A0>, bs::avx_>
                         )
  {
    BOOST_FORCEINLINE A0 operator()(const A0 & a0,  const A0 & a1 ) const BOOST_NOEXCEPT
    {
      auto l = _mm256_unpacklo_epi16(a0, a1);
      auto h = _mm256_unpackhi_epi16(a0, a1);
      return A0(_mm256_permute2x128_si256(l, h, 0x31));
    }
  };

  BOOST_DISPATCH_OVERLOAD ( interleave_second_
                          , (typename A0)
                          , bs::avx2_
                          , bs::pack_<bd::ints32_<A0>, bs::avx_>
                          , bs::pack_<bd::ints32_<A0>, bs::avx_>
                         )
  {
    BOOST_FORCEINLINE A0 operator()(const A0 & a0,  const A0 & a1 ) const BOOST_NOEXCEPT
    {
      auto l = _mm256_unpacklo_epi32(a0, a1);
      auto h = _mm256_unpackhi_epi32(a0, a1);
      return A0(_mm256_permute2x128_si256(l, h, 0x31));
    }
  };

  BOOST_DISPATCH_OVERLOAD ( interleave_second_
                          , (typename A0)
                          , bs::avx2_
                          , bs::pack_<bd::ints64_<A0>, bs::avx_>
                          , bs::pack_<bd::ints64_<A0>, bs::avx_>
                         )
  {
    BOOST_FORCEINLINE A0 operator()(const A0 & a0,  const A0 & a1 ) const BOOST_NOEXCEPT
    {
      auto l = _mm256_unpacklo_epi64(a0, a1);
      auto h = _mm256_unpackhi_epi64(a0, a1);
      return A0(_mm256_permute2x128_si256(l, h, 0x31));
    }
  };
} } }

#endif
