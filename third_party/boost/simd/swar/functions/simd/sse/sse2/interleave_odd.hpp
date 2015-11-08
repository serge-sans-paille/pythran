//==============================================================================
//         Copyright 2003 - 2012 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_SWAR_FUNCTIONS_SIMD_SSE_SSE2_INTERLEAVE_ODD_HPP_INCLUDED
#define BOOST_SIMD_SWAR_FUNCTIONS_SIMD_SSE_SSE2_INTERLEAVE_ODD_HPP_INCLUDED
#ifdef BOOST_SIMD_HAS_SSE2_SUPPORT

#include <boost/simd/swar/functions/interleave_odd.hpp>
#include <boost/simd/swar/functions/details/shuffle.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::interleave_odd_
                                   , boost::simd::tag::sse2_
                                   , (A0)(A1)
                                   , ((simd_<single_<A0>,boost::simd::tag::sse_>))
                                     ((simd_<single_<A1>,boost::simd::tag::sse_>))
                                   )
  {
    typedef A0 result_type;

    BOOST_FORCEINLINE result_type operator()(__m128 const a0, __m128 const a1) const
    {
      return _mm_unpackhi_ps( details::shuffle<1, 3, 1, 3>(a0,a0)
                            , details::shuffle<1, 3, 1, 3>(a1,a1)
                            );
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::interleave_odd_
                                   , boost::simd::tag::sse2_
                                   , (A0)(A1)
                                   , ((simd_<double_<A0>,boost::simd::tag::sse_>))
                                     ((simd_<double_<A1>,boost::simd::tag::sse_>))
                                   )
  {
    typedef A0 result_type;

    BOOST_FORCEINLINE result_type operator()(__m128d const a0, __m128d const a1) const
    {
      return _mm_unpackhi_pd(a0,a1);
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::interleave_odd_
                                   , boost::simd::tag::sse2_
                                   , (A0)(A1)
                                   , ((simd_<type32_<A0>,boost::simd::tag::sse_>))
                                     ((simd_<type32_<A1>,boost::simd::tag::sse_>))
                                   )
  {
    typedef A0 result_type;

    BOOST_FORCEINLINE result_type operator()(__m128i const a0, __m128i const a1) const
    {
      return _mm_unpackhi_epi32 ( details::shuffle<1, 3, 1, 3>(a0,a0)
                                , details::shuffle<1, 3, 1, 3>(a1,a1)
                                );
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::interleave_odd_
                                   , boost::simd::tag::sse2_
                                   , (A0)(A1)
                                   , ((simd_<type64_<A0>,boost::simd::tag::sse_>))
                                     ((simd_<type64_<A1>,boost::simd::tag::sse_>))
                                   )
  {
    typedef A0 result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& a0, A1 const& a1) const
    {
      return _mm_unpackhi_epi64(a0,a1);
    }
  };
} } }

#endif
#endif
