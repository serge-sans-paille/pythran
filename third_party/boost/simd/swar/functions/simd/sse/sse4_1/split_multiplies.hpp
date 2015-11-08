//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_SWAR_FUNCTIONS_SIMD_SSE_SSE4_1_SPLIT_MULTIPLIES_HPP_INCLUDED
#define BOOST_SIMD_SWAR_FUNCTIONS_SIMD_SSE_SSE4_1_SPLIT_MULTIPLIES_HPP_INCLUDED
#ifdef BOOST_SIMD_HAS_SSE4_1_SUPPORT

#include <boost/simd/swar/functions/split_multiplies.hpp>
#include <boost/simd/include/functions/simd/interleave_first.hpp>
#include <boost/simd/include/functions/simd/interleave_second.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::split_multiplies_
                                   , boost::simd::tag::sse4_1_
                                   , (A0)(A1)
                                   , ((simd_<int32_<A0>,boost::simd::tag::sse_>))
                                     ((simd_<int32_<A0>,boost::simd::tag::sse_>))
                                     ((simd_<int64_<A1>,boost::simd::tag::sse_>))
                                     ((simd_<int64_<A1>,boost::simd::tag::sse_>))
                                   )
  {
    typedef void result_type;
    BOOST_FORCEINLINE result_type operator()(A0 const& a0, A0 const& a1, A1& a2, A1& a3) const
    {
      A1 lo = _mm_mul_epi32(a0, a1);
      A1 hi = _mm_mul_epi32(_mm_srli_si128(a0, 4), _mm_srli_si128(a1, 4));

      a2 = interleave_first(lo, hi);
      a3 = interleave_second(lo, hi);
    }
  };
} } }

#endif
#endif
