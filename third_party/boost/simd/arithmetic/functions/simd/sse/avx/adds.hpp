//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2014 MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_ARITHMETIC_FUNCTIONS_SIMD_SSE_AVX_ADDS_HPP_INCLUDED
#define BOOST_SIMD_ARITHMETIC_FUNCTIONS_SIMD_SSE_AVX_ADDS_HPP_INCLUDED
#ifdef BOOST_SIMD_HAS_AVX_SUPPORT

#include <boost/simd/arithmetic/functions/adds.hpp>
#include <boost/simd/include/functions/simd/bitwise_and.hpp>
#include <boost/simd/include/functions/simd/minus.hpp>
#include <boost/dispatch/meta/scalar_of.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::adds_, boost::simd::tag::avx_
                                    , (A0)
                                    , ((simd_<int_<A0>,boost::simd::tag::avx_>))
                                      ((simd_<int_<A0>,boost::simd::tag::avx_>))
                                    )
  {
    typedef A0 result_type;
    BOOST_SIMD_FUNCTOR_CALL_REPEAT(2)
    {
      typedef typename meta::scalar_of<A0>::type             sctype;
      typedef simd::native<sctype, boost::simd::tag::sse_ >  svtype;
      svtype a00 = _mm256_extractf128_si256(a0, 0);
      svtype a10 = _mm256_extractf128_si256(a1, 0);
      svtype  r0 = adds(a00,a10);
      result_type that  = _mm256_castsi128_si256(r0);
      svtype a01 = _mm256_extractf128_si256(a0, 1);
      svtype a11 = _mm256_extractf128_si256(a1, 1);
      svtype r1 = adds(a01,a11);
      that = _mm256_insertf128_si256(that, r1, 1);
      return that;
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::adds_, boost::simd::tag::avx_
                                    , (A0)
                                    , ((simd_<uint_<A0>,boost::simd::tag::avx_>))
                                      ((simd_<uint_<A0>,boost::simd::tag::avx_>))
                                    )
  {
    typedef A0 result_type;
    BOOST_SIMD_FUNCTOR_CALL_REPEAT(2)
    {
      typedef typename meta::scalar_of<A0>::type             sctype;
      typedef simd::native<sctype, boost::simd::tag::sse_ >  svtype;
      svtype a00 = _mm256_extractf128_si256(a0, 0);
      svtype a10 = _mm256_extractf128_si256(a1, 0);
      svtype  r0 = adds(a00,a10);
      result_type that  = _mm256_castsi128_si256(r0);
      svtype a01 = _mm256_extractf128_si256(a0, 1);
      svtype a11 = _mm256_extractf128_si256(a1, 1);
      svtype r1 = adds(a01,a11);
      that = _mm256_insertf128_si256(that, r1, 1);
      return that;
    }
  };
} } }

#endif
#endif
