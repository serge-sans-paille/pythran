//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_REDUCTION_FUNCTIONS_SIMD_SSE_AVX_SUM_HPP_INCLUDED
#define BOOST_SIMD_REDUCTION_FUNCTIONS_SIMD_SSE_AVX_SUM_HPP_INCLUDED
#ifdef BOOST_SIMD_HAS_AVX_SUPPORT

#include <boost/simd/reduction/functions/sum.hpp>
#include <boost/simd/include/constants/one.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::sum_, tag::cpu_
                                    , (A0)
                                    , ((simd_<double_<A0>,boost::simd::tag::avx_>))
                                    )
  {
    typedef typename A0::value_type result_type;

    BOOST_FORCEINLINE result_type operator()(__m256d a0) const
    {
      __m256d half_sum  = _mm256_hadd_pd( a0, a0 );
      __m128d sum       = _mm_add_pd( _mm256_extractf128_pd( half_sum, 0 )
                                    , _mm256_extractf128_pd( half_sum, 1 )
                                    );
      return _mm_cvtsd_f64(sum);
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::sum_, tag::cpu_
                                    , (A0)
                                    , ((simd_<single_<A0>,boost::simd::tag::avx_>))
                                    )
  {
    typedef typename meta::scalar_of<A0>::type result_type;
    BOOST_FORCEINLINE result_type operator()(__m256 a0) const
    {
      A0 r = _mm256_dp_ps(a0, One<A0>(), 0xFF);
      return r[0]+r[4];
    }
  };

} } }

#endif
#endif
