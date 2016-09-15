//==================================================================================================
/**
  Copyright 2016 Numscale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
**/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_X86_AVX2_SIMD_FUNCTION_DEINTERLEAVE_HPP_INCLUDED
#define BOOST_SIMD_ARCH_X86_AVX2_SIMD_FUNCTION_DEINTERLEAVE_HPP_INCLUDED

#include <boost/simd/detail/overload.hpp>
#include <boost/simd/function/deinterleave_first.hpp>
#include <boost/simd/function/deinterleave_second.hpp>
#include <array>

namespace boost { namespace simd { namespace ext
{
  namespace bd =  boost::dispatch;
  namespace bs =  boost::simd;

  BOOST_DISPATCH_OVERLOAD ( deinterleave_
                          , (typename A0)
                          , bs::avx2_
                          , bs::pack_<bd::ints16_<A0>, bs::avx_>
                          , bs::pack_<bd::ints16_<A0>, bs::avx_>
                         )
  {
    BOOST_FORCEINLINE std::array<A0,2> operator()(A0 const& a0, A0 const& a1) const BOOST_NOEXCEPT
    {
      auto lo = _mm256_unpacklo_epi16(a0,a1);
      auto hi = _mm256_unpackhi_epi16(a0,a1);

      auto u0 = _mm256_unpacklo_epi16(lo,hi);
      auto u1 = _mm256_unpackhi_epi16(lo,hi);

      lo = _mm256_unpacklo_epi16(u0, u1);
      hi = _mm256_unpackhi_epi16(u0, u1);

      return  { _mm256_permute4x64_epi64(lo, 0xD8 )
              , _mm256_permute4x64_epi64(hi, 0xD8 )
              };
    }
  };
} } }

#endif
