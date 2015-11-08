//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_REDUCTION_FUNCTIONS_SIMD_SSE_AVX_ALL_HPP_INCLUDED
#define BOOST_SIMD_REDUCTION_FUNCTIONS_SIMD_SSE_AVX_ALL_HPP_INCLUDED
#ifdef BOOST_SIMD_HAS_AVX_SUPPORT

#include <boost/simd/reduction/functions/all.hpp>
#include <boost/simd/include/constants/false.hpp>
#include <boost/simd/sdk/meta/as_logical.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION(boost::simd::tag::all_, boost::simd::tag::avx_,
                              (A0),
                              ((simd_<type16_<A0>,boost::simd::tag::avx_>))
                            )
  {
    typedef typename meta::scalar_of<A0>::type sA0;
    typedef typename meta::as_logical<sA0>::type result_type;
    BOOST_SIMD_FUNCTOR_CALL(1)
    {
      typedef typename meta::scalar_of<A0>::type             sctype;
      typedef simd::native<sctype, boost::simd::tag::sse_ >  svtype;
      svtype a00 = _mm256_extractf128_si256(a0, 0);
      if  (!simd::all(a00)) return False<result_type>();
      svtype a01 = _mm256_extractf128_si256(a0, 1);
      return simd::all(a01);
    }
  };

} } }
#endif
#endif
