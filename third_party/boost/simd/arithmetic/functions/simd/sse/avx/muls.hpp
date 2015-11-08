//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2014 MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_ARITHMETIC_FUNCTIONS_SIMD_SSE_AVX_MULS_HPP_INCLUDED
#define BOOST_SIMD_ARITHMETIC_FUNCTIONS_SIMD_SSE_AVX_MULS_HPP_INCLUDED
#ifdef BOOST_SIMD_HAS_AVX_SUPPORT

#include <boost/simd/arithmetic/functions/muls.hpp>
#include <boost/simd/sdk/simd/meta/retarget.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::muls_
                                    , boost::simd::tag::avx_
                                    , (A0)
                                    , ((simd_<ints32_<A0>
                                            , boost::simd::tag::avx_
                                            >
                                            ))
                                      ((simd_<ints32_<A0>
                                            , boost::simd::tag::avx_
                                            >
                                            ))
                                    )
  {

    typedef A0 result_type;
    BOOST_SIMD_FUNCTOR_CALL_REPEAT(2)
    {
      typedef typename meta::retarget<A0,simd::tag::sse_>::type htype;

      htype a00 = _mm256_extractf128_si256(a0, 0);
      htype a10 = _mm256_extractf128_si256(a1, 0);
      htype v0 = muls(a00, a10);
      htype a01 = _mm256_extractf128_si256(a0, 1);
      htype a11 = _mm256_extractf128_si256(a1, 1);
      htype v1 = muls(a01, a11);
      __m256i r = _mm256_castsi128_si256(v0);
      return _mm256_insertf128_si256(r, v1, 1);
    }
  };
} } }

#endif
#endif
