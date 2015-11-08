//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_SWAR_FUNCTIONS_SIMD_SSE_AVX_CUMSUM_HPP_INCLUDED
#define BOOST_SIMD_SWAR_FUNCTIONS_SIMD_SSE_AVX_CUMSUM_HPP_INCLUDED
#ifdef BOOST_SIMD_HAS_AVX_SUPPORT

#include <boost/simd/swar/functions/cumsum.hpp>
#include <boost/simd/include/functions/simd/splat.hpp>
#include <boost/simd/include/functions/simd/extract.hpp>
#include <boost/simd/include/functions/simd/plus.hpp>
#include <boost/simd/sdk/meta/scalar_of.hpp>

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is arithmetic_
/////////////////////////////////////////////////////////////////////////////
namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION(boost::simd::tag::cumsum_, boost::simd::tag::avx_,
                                    (A0),
                                    ((simd_<arithmetic_<A0>,boost::simd::tag::avx_>))
                                   )
  {
    typedef A0 result_type;
    BOOST_SIMD_FUNCTOR_CALL_REPEAT(1)
    {
      typedef typename meta::scalar_of<A0>::type sctype;
      typedef simd::native<sctype, boost::simd::tag::sse_ >  svtype;
      svtype a000 = _mm256_extractf128_si256(a0, 0);
      svtype a011 = _mm256_extractf128_si256(a0, 1);
      svtype a00 =  cumsum(a000);
      svtype a01 =  cumsum(a011);
      svtype z = splat<svtype>(a00[meta::cardinal_of<svtype>::value-1]);
      __m256i that = _mm256_castsi128_si256(a00);
      return _mm256_insertf128_si256(that, a01+z, 1);
    }
  };

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is double
/////////////////////////////////////////////////////////////////////////////


  BOOST_SIMD_FUNCTOR_IMPLEMENTATION(boost::simd::tag::cumsum_, boost::simd::tag::avx_,
                                    (A0),
                                    ((simd_<double_<A0>,boost::simd::tag::avx_>))
                                   )
  {
    typedef A0 result_type;
    BOOST_SIMD_FUNCTOR_CALL_REPEAT(1)
    {
      typedef typename meta::scalar_of<A0>::type sctype;
      typedef simd::native<sctype, boost::simd::tag::sse_ >  svtype;
      svtype a000 = _mm256_extractf128_pd(a0, 0);
      svtype a011 = _mm256_extractf128_pd(a0, 1);
      svtype a00 =  cumsum(a000);
      svtype a01 =  cumsum(a011);
      svtype z = splat<svtype>(a00[meta::cardinal_of<svtype>::value-1]);
      __m256d that = _mm256_castpd128_pd256(a00);
      return _mm256_insertf128_pd(that, a01+z, 1);
    }
  };

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is float
/////////////////////////////////////////////////////////////////////////////


  BOOST_SIMD_FUNCTOR_IMPLEMENTATION(boost::simd::tag::cumsum_, boost::simd::tag::avx_,
                                    (A0),
                                    ((simd_<single_<A0>,boost::simd::tag::avx_>))
                                   )
  {
    typedef A0 result_type;
    BOOST_SIMD_FUNCTOR_CALL_REPEAT(1)
    {
      typedef typename meta::scalar_of<A0>::type sctype;
      typedef simd::native<sctype, boost::simd::tag::sse_ >  svtype;
      svtype a011;
      a011=  _mm256_extractf128_ps(a0, 1);
      svtype a000;
      a000 =  _mm256_extractf128_ps(a0, 0);
      svtype a00 =  cumsum(a000);
      svtype a01 =  cumsum(a011);
      svtype z = splat<svtype>(a00[meta::cardinal_of<svtype>::value-1]);
      __m256 that = _mm256_castps128_ps256(a00);
      return _mm256_insertf128_ps(that, a01+z, 1);
    }
  };
} } }
#endif
#endif
