//==============================================================================
//         Copyright 2009 - 2013 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_SWAR_FUNCTIONS_SIMD_SSE_SSE2_SPLIT_LOW_HPP_INCLUDED
#define BOOST_SIMD_SWAR_FUNCTIONS_SIMD_SSE_SSE2_SPLIT_LOW_HPP_INCLUDED
#ifdef BOOST_SIMD_HAS_SSE2_SUPPORT

#include <boost/simd/swar/functions/split_low.hpp>
#include <boost/simd/include/constants/zero.hpp>
#include <boost/dispatch/meta/upgrade.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::split_low_
                                    , boost::simd::tag::sse2_
                                    , (A0)
                                    , ((simd_ < single_<A0>
                                              , boost::simd::tag::sse_
                                              >
                                      ))
                                    )
  {
    typedef typename dispatch::meta::upgrade<A0>::type  result_type;

    BOOST_FORCEINLINE result_type operator()(const A0& a0) const
    {
      return _mm_cvtps_pd(a0);
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::split_low_
                                    , boost::simd::tag::sse2_
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
      return _mm_unpacklo_epi8(a0, is_ltz(a0));
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::split_low_
                                    , boost::simd::tag::sse2_
                                    , (A0)
                                    , ((simd_ < uint8_<A0>
                                              , boost::simd::tag::sse_
                                              >
                                      ))
                                    )
  {
    typedef typename dispatch::meta::upgrade<A0>::type  result_type;

    BOOST_FORCEINLINE result_type operator()(const A0& a0) const
    {
      return _mm_unpacklo_epi8(a0, Zero<A0>());
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::split_low_
                                    , boost::simd::tag::sse2_
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
      return _mm_unpacklo_epi16(a0, is_ltz(a0));
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::split_low_
                                    , boost::simd::tag::sse2_
                                    , (A0)
                                    , ((simd_ < uint16_<A0>
                                              , boost::simd::tag::sse_
                                              >
                                      ))
                                    )
  {
    typedef typename dispatch::meta::upgrade<A0>::type  result_type;

    BOOST_FORCEINLINE result_type operator()(const A0& a0) const
    {
      return _mm_unpacklo_epi16(a0, Zero<A0>());
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::split_low_
                                    , boost::simd::tag::sse2_
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
      return _mm_unpacklo_epi32(a0, is_ltz(a0));
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::split_low_
                                    , boost::simd::tag::sse2_
                                    , (A0)
                                    , ((simd_ < uint32_<A0>
                                              , boost::simd::tag::sse_
                                              >
                                      ))
                                    )
  {
    typedef typename dispatch::meta::upgrade<A0>::type  result_type;

    BOOST_FORCEINLINE result_type operator()(const A0& a0) const
    {
      return _mm_unpacklo_epi32(a0, Zero<A0>());
    }
  };
} } }

#endif
#endif
