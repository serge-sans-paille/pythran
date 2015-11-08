//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_MEMORY_FUNCTIONS_SIMD_SSE_SSE2_MAKE_HPP_INCLUDED
#define BOOST_SIMD_MEMORY_FUNCTIONS_SIMD_SSE_SSE2_MAKE_HPP_INCLUDED
#ifdef BOOST_SIMD_HAS_SSE2_SUPPORT

#include <boost/simd/memory/functions/make.hpp>
#include <boost/simd/preprocessor/make_helper.hpp>
#include <boost/dispatch/attributes.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::make_
                                    , boost::simd::tag::sse2_
                                    , (A0)
                                    , ((target_ < simd_ < double_<A0>
                                                        , boost::simd::tag::sse_
                                                        >
                                                >
                                      ))
                                    )
  {
    BOOST_SIMD_MAKE_BODY(2) { return _mm_setr_pd(a0, a1); }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::make_
                                    , boost::simd::tag::sse2_
                                    , (A0)
                                    , ((target_ < simd_ < ints64_<A0>
                                                        , boost::simd::tag::sse_
                                                        >
                                                >
                                      ))
                                    )
  {
    BOOST_SIMD_MAKE_BODY(2)
    {
#ifdef BOOST_SIMD_ARCH_X86_64
      return _mm_set_epi64x(a1, a0);
#else
      return _mm_setr_epi32( (uint64_t(a0) & 0x00000000FFFFFFFFULL)
                           , (uint64_t(a0) & 0xFFFFFFFF00000000ULL) >> 32
                           , (uint64_t(a1) & 0x00000000FFFFFFFFULL)
                           , (uint64_t(a1) & 0xFFFFFFFF00000000ULL) >> 32
                           );
#endif
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::make_
                                    , boost::simd::tag::sse2_
                                    , (A0)
                                    , ((target_ < simd_ < single_<A0>
                                                        , boost::simd::tag::sse_
                                                        >
                                                >
                                      ))
                                    )
  {
    BOOST_SIMD_MAKE_BODY(4) { return _mm_setr_ps(a0, a1, a2, a3); }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::make_
                                    , boost::simd::tag::sse2_
                                    , (A0)
                                    , ((target_ < simd_ < ints32_<A0>
                                                        , boost::simd::tag::sse_
                                                        >
                                                >
                                      ))
                                    )
  {
    BOOST_SIMD_MAKE_BODY(4) { return _mm_setr_epi32(a0, a1, a2, a3); }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::make_
                                    , boost::simd::tag::sse2_
                                    , (A0)
                                    , ((target_ < simd_ < ints16_<A0>
                                                        , boost::simd::tag::sse_
                                                        >
                                                >
                                      ))
                                    )
  {
    BOOST_SIMD_MAKE_BODY(8)
    {
      return _mm_setr_epi16(a0, a1, a2, a3 , a4, a5, a6, a7 );
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::make_
                                    , boost::simd::tag::sse2_
                                    , (A0)
                                    , ((target_ < simd_ < ints8_<A0>
                                                        , boost::simd::tag::sse_
                                                        >
                                                >
                                      ))
                                    )
  {
    BOOST_SIMD_MAKE_BODY(16)
    {
      return _mm_setr_epi8 ( a0, a1 , a2,  a3 ,  a4,  a5,  a6,  a7
                           , a8, a9, a10, a11 , a12, a13, a14, a15 );
    }
  };
} } }

#endif
#endif
