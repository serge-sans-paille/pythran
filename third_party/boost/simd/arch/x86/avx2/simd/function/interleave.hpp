//==================================================================================================
/**
  Copyright 2017 Numscale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
**/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_X86_AVX2_SIMD_FUNCTION_INTERLEAVE_HPP_INCLUDED
#define BOOST_SIMD_ARCH_X86_AVX2_SIMD_FUNCTION_INTERLEAVE_HPP_INCLUDED

#include <boost/simd/detail/overload.hpp>
#include <array>

namespace boost { namespace simd { namespace ext
{
  namespace bd =  boost::dispatch;
  namespace bs =  boost::simd;

  BOOST_DISPATCH_OVERLOAD ( interleave_
                          , (typename A0)
                          , bs::avx2_
                          , bs::pack_<bd::integer_<A0>, bs::avx_>
                          , bs::pack_<bd::integer_<A0>, bs::avx_>
                         )
  {
    BOOST_FORCEINLINE A0 get_low(A0 const& a0, A0 const& a1, nsm::size_t<32> const& ) const
    {
      return _mm256_unpacklo_epi8(a0, a1);
    }

    BOOST_FORCEINLINE A0 get_low(A0 const& a0, A0 const& a1, nsm::size_t<16> const& ) const
    {
      return _mm256_unpacklo_epi16(a0, a1);
    }

    BOOST_FORCEINLINE A0 get_low(A0 const& a0, A0 const& a1, nsm::size_t< 8> const& ) const
    {
      return _mm256_unpacklo_epi32(a0, a1);
    }

    BOOST_FORCEINLINE A0 get_low(A0 const& a0, A0 const& a1, nsm::size_t< 4> const& ) const
    {
      return _mm256_unpacklo_epi64(a0, a1);
    }

    BOOST_FORCEINLINE A0 get_high(A0 const& a0, A0 const& a1, nsm::size_t<32> const& ) const
    {
      return _mm256_unpackhi_epi8(a0, a1);
    }

    BOOST_FORCEINLINE A0 get_high(A0 const& a0, A0 const& a1, nsm::size_t<16> const& ) const
    {
      return _mm256_unpackhi_epi16(a0, a1);
    }

    BOOST_FORCEINLINE A0 get_high(A0 const& a0, A0 const& a1, nsm::size_t< 8> const& ) const
    {
      return _mm256_unpackhi_epi32(a0, a1);
    }

    BOOST_FORCEINLINE A0 get_high(A0 const& a0, A0 const& a1, nsm::size_t< 4> const& ) const
    {
      return _mm256_unpackhi_epi64(a0, a1);
    }

    BOOST_FORCEINLINE std::array<A0,2> operator()(A0 const& a0, A0 const& a1 ) const BOOST_NOEXCEPT
    {
      using sz_t = nsm::size_t<A0::static_size>;
      A0 l = get_low(a0, a1, sz_t{}), h = get_high(a0, a1, sz_t{});

      std::array<A0,2> that{_mm256_permute2x128_si256(l, h, 0x20),_mm256_permute2x128_si256(l, h, 0x31)};
      return that;
    }
  };
} } }

#endif
