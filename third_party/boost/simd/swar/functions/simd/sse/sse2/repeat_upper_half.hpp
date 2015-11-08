//==============================================================================
//         Copyright 2003 - 2012 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_SWAR_FUNCTIONS_SIMD_SSE_SSE2_REPEAT_UPPER_HALF_HPP_INCLUDED
#define BOOST_SIMD_SWAR_FUNCTIONS_SIMD_SSE_SSE2_REPEAT_UPPER_HALF_HPP_INCLUDED
#ifdef BOOST_SIMD_HAS_SSE2_SUPPORT

#include <boost/simd/swar/functions/repeat_upper_half.hpp>
#include <boost/simd/include/functions/simd/interleave_second.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::repeat_upper_half_
                                   , boost::simd::tag::sse2_
                                   , (A0)
                                   , ((simd_<type64_<A0>,boost::simd::tag::sse_>))
                                   )
  {
    typedef A0 result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& a0) const
    {
      return interleave_second(a0,a0);
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::repeat_upper_half_
                                   , boost::simd::tag::sse2_
                                   , (A0)
                                   , ((simd_<single_<A0>,boost::simd::tag::sse_>))
                                   )
  {
    typedef A0 result_type;

    BOOST_FORCEINLINE result_type operator()(__m128 a0) const
    {
      return _mm_movehl_ps(a0,a0);
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::repeat_upper_half_
                                   , boost::simd::tag::sse2_
                                   , (A0)
                                   , ((simd_<ints32_<A0>,boost::simd::tag::sse_>))
                                   )
  {
    typedef A0 result_type;

    BOOST_FORCEINLINE result_type operator()(__m128i a0) const
    {
      return _mm_shuffle_epi32(a0, _MM_SHUFFLE(3,2,3,2) );
    }
  };
} } }

#endif
#endif
