//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2014 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2014 MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_SWAR_FUNCTIONS_SIMD_SSE_SSE2_REVERSE_HPP_INCLUDED
#define BOOST_SIMD_SWAR_FUNCTIONS_SIMD_SSE_SSE2_REVERSE_HPP_INCLUDED
#ifdef BOOST_SIMD_HAS_SSE2_SUPPORT

#include <boost/simd/swar/functions/reverse.hpp>
#include <boost/simd/include/functions/simd/bitwise_cast.hpp>
#include <boost/dispatch/meta/as_floating.hpp>
#include <boost/dispatch/attributes.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::reverse_
                                    , boost::simd::tag::sse2_
                                    , (A0)
                                    , ((simd_ < single_<A0>
                                              , boost::simd::tag::sse_
                                              >
                                      ))
                                    )
  {
    typedef A0 result_type;

    BOOST_FORCEINLINE BOOST_SIMD_FUNCTOR_CALL(1)
    {
      return _mm_shuffle_ps(a0,a0, _MM_SHUFFLE(0,1,2,3));
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::reverse_
                                    , boost::simd::tag::sse2_
                                    , (A0)
                                    , ((simd_ < double_<A0>
                                              , boost::simd::tag::sse_
                                              >
                                      ))
                                    )
  {
    typedef A0 result_type;

    BOOST_FORCEINLINE BOOST_SIMD_FUNCTOR_CALL(1)
    {
      return _mm_shuffle_pd(a0, a0, _MM_SHUFFLE2(0,1));
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::reverse_
                                    , boost::simd::tag::sse2_
                                    , (A0)
                                    , ((simd_ < ints32_<A0>
                                              , boost::simd::tag::sse_
                                              >
                                      ))
                                    )
  {
    typedef A0 result_type;
    BOOST_FORCEINLINE BOOST_SIMD_FUNCTOR_CALL(1)
    {
      return _mm_shuffle_epi32(a0, _MM_SHUFFLE(0,1,2,3));
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::reverse_
                                    , boost::simd::tag::sse2_
                                    , (A0)
                                    , ((simd_ < ints64_<A0>
                                              , boost::simd::tag::sse_
                                              >
                                      ))
                                    )
  {
    typedef A0 result_type;

    BOOST_FORCEINLINE BOOST_SIMD_FUNCTOR_CALL(1)
    {
      typedef typename dispatch::meta::as_floating<A0>::type f_t;
      return  simd::bitwise_cast<A0>(reverse( simd::bitwise_cast<f_t>(a0)));
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::reverse_
                                    , boost::simd::tag::sse2_
                                    , (A0)
                                    , ((simd_ < ints16_<A0>
                                              , boost::simd::tag::sse_
                                              >
                                      ))
                                    )
  {
    typedef A0 result_type;

    BOOST_FORCEINLINE BOOST_SIMD_FUNCTOR_CALL(1)
    {
      A0  that = _mm_shuffle_epi32  (a0  , _MM_SHUFFLE(0,1,2,3));
          that = _mm_shufflelo_epi16(that, _MM_SHUFFLE(2,3,0,1));

      return _mm_shufflehi_epi16(that, _MM_SHUFFLE(2,3,0,1));
    }
  };
} } }

#endif
#endif
