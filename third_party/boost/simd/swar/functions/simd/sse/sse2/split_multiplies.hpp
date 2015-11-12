//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_SWAR_FUNCTIONS_SIMD_SSE_SSE2_SPLIT_MULTIPLIES_HPP_INCLUDED
#define BOOST_SIMD_SWAR_FUNCTIONS_SIMD_SSE_SSE2_SPLIT_MULTIPLIES_HPP_INCLUDED
#ifdef BOOST_SIMD_HAS_SSE2_SUPPORT

#include <boost/simd/swar/functions/split_multiplies.hpp>
#include <boost/simd/include/functions/simd/interleave_first.hpp>
#include <boost/simd/include/functions/simd/interleave_second.hpp>
#include <boost/simd/include/functions/simd/deinterleave_first.hpp>
#include <boost/simd/include/functions/simd/deinterleave_second.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::split_multiplies_
                                   , boost::simd::tag::sse2_
                                   , (A0)(A1)
                                   , ((simd_<int16_<A0>,boost::simd::tag::sse_>))
                                     ((simd_<int16_<A0>,boost::simd::tag::sse_>))
                                     ((simd_<int32_<A1>,boost::simd::tag::sse_>))
                                     ((simd_<int32_<A1>,boost::simd::tag::sse_>))
                                   )
  {
    typedef void result_type;
    BOOST_FORCEINLINE result_type operator()(A0 const& a0, A0 const& a1, A1& a2, A1& a3) const
    {
      A0 lo = _mm_mullo_epi16(a0, a1);
      A0 hi = _mm_mulhi_epi16(a0, a1);

      a2 = interleave_first(lo, hi);
      a3 = interleave_second(lo, hi);
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::split_multiplies_
                                   , boost::simd::tag::sse2_
                                   , (A0)(A1)
                                   , ((simd_<uint16_<A0>,boost::simd::tag::sse_>))
                                     ((simd_<uint16_<A0>,boost::simd::tag::sse_>))
                                     ((simd_<uint32_<A1>,boost::simd::tag::sse_>))
                                     ((simd_<uint32_<A1>,boost::simd::tag::sse_>))
                                   )
  {
    typedef void result_type;
    BOOST_FORCEINLINE result_type operator()(A0 const& a0, A0 const& a1, A1& a2, A1& a3) const
    {
      A0 lo = _mm_mullo_epi16(a0, a1);
      A0 hi = _mm_mulhi_epu16(a0, a1);

      a2 = interleave_first(lo, hi);
      a3 = interleave_second(lo, hi);
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::split_multiplies_
                                   , boost::simd::tag::sse2_
                                   , (A0)(A1)
                                   , ((simd_<uint32_<A0>,boost::simd::tag::sse_>))
                                     ((simd_<uint32_<A0>,boost::simd::tag::sse_>))
                                     ((simd_<uint64_<A1>,boost::simd::tag::sse_>))
                                     ((simd_<uint64_<A1>,boost::simd::tag::sse_>))
                                   )
  {
    typedef void result_type;
    BOOST_FORCEINLINE result_type operator()(A0 const& a0, A0 const& a1, A1& a2, A1& a3) const
    {
      A1 lo = _mm_mul_epu32(a0, a1);
      A1 hi = _mm_mul_epu32(_mm_srli_si128(a0, 4), _mm_srli_si128(a1, 4));

      a2 = deinterleave_first(lo, hi);
      a3 = deinterleave_second(lo, hi);
    }
  };
} } }

#endif
#endif
