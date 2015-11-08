//==============================================================================
//         Copyright 2003 - 2012 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_SWAR_FUNCTIONS_SIMD_SSE_SSE2_INTERLEAVE_FIRST_HPP_INCLUDED
#define BOOST_SIMD_SWAR_FUNCTIONS_SIMD_SSE_SSE2_INTERLEAVE_FIRST_HPP_INCLUDED
#ifdef BOOST_SIMD_HAS_SSE2_SUPPORT

#include <boost/simd/swar/functions/interleave_first.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::interleave_first_
                                   , boost::simd::tag::sse2_
                                   , (A0)(A1)
                                   , ((simd_<single_<A0>,boost::simd::tag::sse_>))
                                     ((simd_<single_<A1>,boost::simd::tag::sse_>))
                                   )
  {
    typedef A0 result_type;

    BOOST_FORCEINLINE result_type operator()(__m128 const a0, __m128 const a1) const
    {
      return _mm_unpacklo_ps(a0,a1);
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::interleave_first_
                                   , boost::simd::tag::sse2_
                                   , (A0)(A1)
                                   , ((simd_<double_<A0>,boost::simd::tag::sse_>))
                                     ((simd_<double_<A1>,boost::simd::tag::sse_>))
                                   )
  {
    typedef A0 result_type;

    BOOST_FORCEINLINE result_type operator()(__m128d const a0, __m128d const a1) const
    {
      return _mm_unpacklo_pd(a0,a1);
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::interleave_first_
                                   , boost::simd::tag::sse2_
                                   , (A0)(A1)
                                   , ((simd_<type8_<A0>,boost::simd::tag::sse_>))
                                     ((simd_<type8_<A1>,boost::simd::tag::sse_>))
                                   )
  {
    typedef A0 result_type;

    BOOST_FORCEINLINE result_type operator()(__m128i const a0, __m128i const a1) const
    {
      return _mm_unpacklo_epi8(a0,a1);
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::interleave_first_
                                   , boost::simd::tag::sse2_
                                   , (A0)(A1)
                                   , ((simd_<type16_<A0>,boost::simd::tag::sse_>))
                                     ((simd_<type16_<A1>,boost::simd::tag::sse_>))
                                   )
  {
    typedef A0 result_type;

    BOOST_FORCEINLINE result_type operator()(__m128i const a0, __m128i const a1) const
    {
      return _mm_unpacklo_epi16(a0,a1);
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::interleave_first_
                                   , boost::simd::tag::sse2_
                                   , (A0)(A1)
                                   , ((simd_<type32_<A0>,boost::simd::tag::sse_>))
                                     ((simd_<type32_<A1>,boost::simd::tag::sse_>))
                                   )
  {
    typedef A0 result_type;

    BOOST_FORCEINLINE result_type operator()(__m128i const a0, __m128i const a1) const
    {
      return _mm_unpacklo_epi32(a0,a1);
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::interleave_first_
                                   , boost::simd::tag::sse2_
                                   , (A0)(A1)
                                   , ((simd_<type64_<A0>,boost::simd::tag::sse_>))
                                     ((simd_<type64_<A1>,boost::simd::tag::sse_>))
                                   )
  {
    typedef A0 result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& a0, A1 const& a1) const
    {
      return _mm_unpacklo_epi64(a0,a1);
    }
  };
} } }

#endif
#endif
