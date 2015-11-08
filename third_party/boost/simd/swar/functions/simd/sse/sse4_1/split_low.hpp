//==============================================================================
//         Copyright 2014        LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2014        LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2014        NumScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_SWAR_FUNCTIONS_SIMD_SSE_SSE4_1_SPLIT_LOW_HPP_INCLUDED
#define BOOST_SIMD_SWAR_FUNCTIONS_SIMD_SSE_SSE4_1_SPLIT_LOW_HPP_INCLUDED
#ifdef BOOST_SIMD_HAS_SSE4_1_SUPPORT

#include <boost/simd/swar/functions/split_low.hpp>
#include <boost/dispatch/meta/upgrade.hpp>
#include <boost/dispatch/attributes.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::split_low_
                                    , boost::simd::tag::sse4_1_
                                    , (A0)
                                    , ((simd_ < int8_<A0>
                                              , boost::simd::tag::sse_
                                              >
                                      ))
                                    )
  {
    typedef typename dispatch::meta::upgrade<A0>::type  result_type;

    BOOST_FORCEINLINE result_type operator()(const A0& a0) const
    {
      return _mm_cvtepi8_epi16(a0);
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::split_low_
                                    , boost::simd::tag::sse4_1_
                                    , (A0)
                                    , ((simd_ < int16_<A0>
                                              , boost::simd::tag::sse_
                                              >
                                      ))
                                    )
  {
    typedef typename dispatch::meta::upgrade<A0>::type  result_type;

    BOOST_FORCEINLINE result_type operator()(const A0& a0) const
    {
      return _mm_cvtepi16_epi32(a0);
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::split_low_
                                    , boost::simd::tag::sse4_1_
                                    , (A0)
                                    , ((simd_ < int32_<A0>
                                              , boost::simd::tag::sse_
                                              >
                                      ))
                                    )
  {
    typedef typename dispatch::meta::upgrade<A0>::type  result_type;

    BOOST_FORCEINLINE result_type operator()(const A0& a0) const
    {
      return _mm_cvtepi32_epi64(a0);
    }
  };
} } }

#endif
#endif
