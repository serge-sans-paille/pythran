//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_SWAR_FUNCTIONS_SIMD_SSE_AVX_SPLIT_MULTIPLIES_HPP_INCLUDED
#define BOOST_SIMD_SWAR_FUNCTIONS_SIMD_SSE_AVX_SPLIT_MULTIPLIES_HPP_INCLUDED
#ifdef BOOST_SIMD_HAS_AVX_SUPPORT

#include <boost/simd/swar/functions/split_multiplies.hpp>
#include <boost/simd/sdk/simd/meta/retarget.hpp>
#include <boost/simd/sdk/meta/is_upgradable.hpp>

namespace boost { namespace simd { namespace ext
{
  //============================================================================
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION_IF( boost::simd::tag::split_multiplies_
                                      , boost::simd::tag::avx_
                                      , (A0)(A1)
                                      , (simd::meta::is_upgradable_to<A0,A1>)
                                      , ((simd_<integer_<A0>,boost::simd::tag::avx_>))
                                        ((simd_<integer_<A0>,boost::simd::tag::avx_>))
                                        ((simd_<integer_<A1>,boost::simd::tag::avx_>))
                                        ((simd_<integer_<A1>,boost::simd::tag::avx_>))
                                      )
  {
    typedef void result_type;
    typedef typename meta::retarget<A0,tag::sse_>::type A0_sse_;
    typedef typename meta::retarget<A1,tag::sse_>::type A1_sse_;

    BOOST_FORCEINLINE
    result_type operator()(const A0 & a0, const A0 & a1, A1& a2, A1& a3)const
    {
      A0_sse_ a00 = _mm256_extractf128_si256(a0, 0);
      A0_sse_ a01 = _mm256_extractf128_si256(a0, 1);
      A0_sse_ a10 = _mm256_extractf128_si256(a1, 0);
      A0_sse_ a11 = _mm256_extractf128_si256(a1, 1);

      A1_sse_ ha000, ha001;
      split_multiplies(a00, a10, ha000, ha001);
      a2 = _mm256_castsi128_si256(ha000);
      a2 = _mm256_insertf128_si256(a2, ha001, 1);

      A1_sse_ ha010, ha011;
      split_multiplies(a01, a11, ha010, ha011);
      a3 = _mm256_castsi128_si256(ha010);
      a3 = _mm256_insertf128_si256(a3, ha011, 1);
    }
  };
} } }

#endif
#endif
