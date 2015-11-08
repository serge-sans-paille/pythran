//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_MEMORY_FUNCTIONS_SIMD_SSE_AVX_MAKE_HPP_INCLUDED
#define BOOST_SIMD_MEMORY_FUNCTIONS_SIMD_SSE_AVX_MAKE_HPP_INCLUDED
#ifdef BOOST_SIMD_HAS_AVX_SUPPORT

#include <boost/simd/memory/functions/make.hpp>
#include <boost/simd/preprocessor/make_helper.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::make_
                                    , boost::simd::tag::avx_
                                    , (A0)
                                    , ((target_ < simd_ < double_<A0>
                                                        , boost::simd::tag::avx_
                                                        >
                                                >
                                      ))
                                    )
  {
    BOOST_SIMD_MAKE_BODY(4)
    {
      return _mm256_setr_pd(a0, a1, a2, a3);
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::make_
                                    , boost::simd::tag::avx_
                                    , (A0)
                                    , ((target_ < simd_ < ints64_<A0>
                                                        , boost::simd::tag::avx_
                                                        >
                                                >
                                      ))
                                    )
  {
    BOOST_SIMD_MAKE_BODY(4)
    {
#ifndef BOOST_MSVC
      return _mm256_setr_epi64x(a0, a1, a2, a3);
#else
      return _mm256_setr_epi32( (uint64_t(a0) & 0x00000000FFFFFFFFULL)
                              , (uint64_t(a0) & 0xFFFFFFFF00000000ULL) >> 32
                              , (uint64_t(a1) & 0x00000000FFFFFFFFULL)
                              , (uint64_t(a1) & 0xFFFFFFFF00000000ULL) >> 32
                              , (uint64_t(a2) & 0x00000000FFFFFFFFULL)
                              , (uint64_t(a2) & 0xFFFFFFFF00000000ULL) >> 32
                              , (uint64_t(a3) & 0x00000000FFFFFFFFULL)
                              , (uint64_t(a3) & 0xFFFFFFFF00000000ULL) >> 32
                              );
#endif
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::make_
                                    , boost::simd::tag::avx_
                                    , (A0)
                                    , ((target_ < simd_ < single_<A0>
                                                        , boost::simd::tag::avx_
                                                        >
                                                >
                                      ))
                                    )
  {
    BOOST_SIMD_MAKE_BODY(8)
    {
      return _mm256_setr_ps(a0, a1, a2, a3, a4, a5, a6, a7);
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::make_
                                    , boost::simd::tag::avx_
                                    , (A0)
                                    , ((target_ < simd_ < ints32_<A0>
                                                        , boost::simd::tag::avx_
                                                        >
                                                >
                                      ))
                                    )
  {
    BOOST_SIMD_MAKE_BODY(8)
    {
      return _mm256_setr_epi32(a0, a1, a2, a3, a4, a5, a6, a7);
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::make_
                                    , boost::simd::tag::avx_
                                    , (A0)
                                    , ((target_ < simd_ < ints16_<A0>
                                                        , boost::simd::tag::avx_
                                                        >
                                                >
                                      ))
                                    )
  {
    BOOST_SIMD_MAKE_BODY(16)
    {
      return _mm256_setr_epi16( a0, a1,  a2,  a3,  a4,  a5,  a6,  a7
                              , a8, a9, a10, a11, a12, a13, a14, a15
                              );
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::make_
                                    , boost::simd::tag::avx_
                                    , (A0)
                                    , ((target_ < simd_ < ints8_<A0>
                                                        , boost::simd::tag::avx_
                                                        >
                                                >
                                      ))
                                    )
  {
    BOOST_SIMD_MAKE_BODY(32)
    {
      return _mm256_setr_epi8(  a0,  a1,  a2,  a3,  a4,  a5,  a6,  a7
                             ,  a8,  a9, a10, a11, a12, a13, a14, a15
                             , a16, a17, a18, a19, a20, a21, a22, a23
                             , a24, a25, a26, a27, a28, a29, a30, a31
                             );
    }
  };
} } }

#endif
#endif
