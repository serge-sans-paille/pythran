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
                          , bs::pack_<bd::ints8_<A0>, bs::avx_>
                          , bs::pack_<bd::ints8_<A0>, bs::avx_>
                         )
  {
    BOOST_FORCEINLINE std::array<A0,2> operator()(A0 const& a0, A0 const& a1) const BOOST_NOEXCEPT
    {
      auto l    = _mm256_unpacklo_epi8(a0,a1);
      auto h    = _mm256_unpackhi_epi8(a0,a1);

      auto u0 = _mm256_unpacklo_epi8(l,h);
      auto u1 = _mm256_unpackhi_epi8(l,h);

      auto lh0  = _mm256_unpacklo_epi8(u0,u1);
      auto lh1  = _mm256_unpackhi_epi8(u0,u1);

      std::array<A0,2> that { _mm256_permute4x64_epi64(_mm256_unpacklo_epi8(lh0, lh1), 0xD8)
                            , _mm256_permute4x64_epi64(_mm256_unpackhi_epi8(lh0, lh1), 0xD8)
                            };
      return that;
    }
  };

  BOOST_DISPATCH_OVERLOAD ( deinterleave_
                          , (typename A0)
                          , bs::avx2_
                          , bs::pack_<bd::ints16_<A0>, bs::avx_>
                          , bs::pack_<bd::ints16_<A0>, bs::avx_>
                         )
  {
    BOOST_FORCEINLINE std::array<A0,2> operator()(A0 const& a0, A0 const& a1) const BOOST_NOEXCEPT
    {
      auto l = _mm256_unpacklo_epi16(a0,a1);
      auto h = _mm256_unpackhi_epi16(a0,a1);

      auto u0 = _mm256_unpacklo_epi16(l,h);
      auto u1 = _mm256_unpackhi_epi16(l,h);

      l = _mm256_unpacklo_epi16(u0, u1);
      h = _mm256_unpackhi_epi16(u0, u1);

      std::array<A0,2> that { _mm256_permute4x64_epi64(l, 0xD8 )
                            , _mm256_permute4x64_epi64(h, 0xD8 )
                            };

      return that;
    }
  };

  BOOST_DISPATCH_OVERLOAD ( deinterleave_
                          , (typename A0)
                          , bs::avx2_
                          , bs::pack_<bd::ints32_<A0>, bs::avx_>
                          , bs::pack_<bd::ints32_<A0>, bs::avx_>
                         )
  {
    BOOST_FORCEINLINE std::array<A0,2> operator()(A0 const& a0, A0 const& a1) const BOOST_NOEXCEPT
    {
      auto l = _mm256_unpacklo_epi32(a0,a1);
      auto h = _mm256_unpackhi_epi32(a0,a1);
      A0   idx(0,1,4,5,2,3,6,7);

      std::array<A0,2> that { _mm256_permutevar8x32_epi32(_mm256_unpacklo_epi32(l, h), idx)
                            , _mm256_permutevar8x32_epi32(_mm256_unpackhi_epi32(l, h), idx)
                            };

      return that;
    }
  };

  BOOST_DISPATCH_OVERLOAD ( deinterleave_
                          , (typename A0)
                          , bs::avx2_
                          , bs::pack_<bd::ints64_<A0>, bs::avx_>
                          , bs::pack_<bd::ints64_<A0>, bs::avx_>
                         )
  {
    BOOST_FORCEINLINE std::array<A0,2> operator()(A0 const& a0, A0 const& a1) const BOOST_NOEXCEPT
    {
      std::array<A0,2> that { _mm256_permute4x64_epi64(_mm256_unpacklo_epi64(a0,a1), 0xD8)
                            , _mm256_permute4x64_epi64(_mm256_unpackhi_epi64(a0,a1), 0xD8)
                            };

      return that;
    }
  };
} } }

#endif
