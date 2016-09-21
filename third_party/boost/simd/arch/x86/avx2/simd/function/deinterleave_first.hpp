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
#include <boost/simd/function/slice.hpp>
#include <boost/simd/function/bitwise_cast.hpp>

namespace boost { namespace simd { namespace ext
{
  namespace bd =  boost::dispatch;
  namespace bs =  boost::simd;

  BOOST_DISPATCH_OVERLOAD ( deinterleave_first_
                          , (typename A0)
                          , bs::avx2_
                          , bs::pack_<bd::ints16_<A0>, bs::avx_>
                          , bs::pack_<bd::ints16_<A0>, bs::avx_>
                         )
  {
    BOOST_FORCEINLINE A0 operator()(const A0 & a0, const A0 & a1 ) const BOOST_NOEXCEPT
    {
      auto lo = _mm256_unpacklo_epi16(a0,a1);
      auto hi = _mm256_unpackhi_epi16(a0,a1);

      // this gives everything but the two middle qword are permuted
      lo = _mm256_unpacklo_epi16( _mm256_unpacklo_epi16(lo,hi)
                                , _mm256_unpackhi_epi16(lo,hi)
                                );

      // 0xD8 = 0b11011000 = [3][1][2][0] to permute them back
      return _mm256_permute4x64_epi64(lo, 0xD8 );
    }
  };
} } }

#endif
