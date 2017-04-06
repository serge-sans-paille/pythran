//==================================================================================================
/**
  Copyright 2016 Numscale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
**/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_X86_AVX2_SIMD_FUNCTION_SUM_HPP_INCLUDED
#define BOOST_SIMD_ARCH_X86_AVX2_SIMD_FUNCTION_SUM_HPP_INCLUDED

#include <boost/simd/detail/overload.hpp>
#include <boost/simd/function/slice.hpp>
#include <boost/simd/function/extract.hpp>
#include <boost/simd/detail/dispatch/meta/upgrade.hpp>

namespace boost { namespace simd { namespace ext
{
  namespace bd =  boost::dispatch;
  namespace bs =  boost::simd;

  BOOST_DISPATCH_OVERLOAD ( sum_
                          , (typename A0)
                          , bs::avx2_
                          , bs::pack_<bd::ints64_<A0>, bs::avx_>
                         )
  {
    BOOST_FORCEINLINE typename A0::value_type operator()(const A0 & a0) const BOOST_NOEXCEPT
    {
      return sum(slice_low(a0) + slice_high(a0));
    }
  };

  BOOST_DISPATCH_OVERLOAD ( sum_
                          , (typename A0)
                          , bs::avx2_
                          , bs::pack_<bd::ints32_<A0>, bs::avx_>
                         )
  {
    BOOST_FORCEINLINE typename A0::value_type operator()(const A0 & a0) const BOOST_NOEXCEPT
    {
      A0  acc = _mm256_add_epi32(a0, _mm256_srli_si256(a0, 8));
          acc = _mm256_add_epi32(acc, _mm256_srli_si256(acc, 4));
      return extract<0>(acc) +  extract<4>(acc);
    }
  };

  BOOST_DISPATCH_OVERLOAD ( sum_
                          , (typename A0)
                          , bs::avx2_
                          , bs::pack_<bd::ints16_<A0>, bs::avx_>
                         )
  {
    BOOST_FORCEINLINE typename A0::value_type operator()(const A0 & a0) const BOOST_NOEXCEPT
    {
      A0  s = _mm256_hadd_epi16(a0, a0);
          s = _mm256_hadd_epi16(s, s);
          s = _mm256_hadd_epi16(s, s);
      return extract<0>(s) + extract<15>(s);
    }
  };

  BOOST_DISPATCH_OVERLOAD ( sum_
                          , (typename A0)
                          , bs::avx2_
                          , bs::pack_<bd::ints8_<A0>, bs::avx_>
                         )
  {
    BOOST_FORCEINLINE typename A0::value_type operator()(const A0 & a0) const BOOST_NOEXCEPT
    {
      __m256i z = _mm256_set1_epi8(0);
      bd::upgrade_t<A0> s = _mm256_add_epi16( _mm256_unpacklo_epi8(a0, z)
                                            , _mm256_unpackhi_epi8(a0, z)
                                            );
      return static_cast<typename A0::value_type>(sum(s));
    }
  };
} } }

#endif
