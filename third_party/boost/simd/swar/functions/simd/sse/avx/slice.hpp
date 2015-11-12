//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_SWAR_FUNCTIONS_SIMD_SSE_AVX_SLICE_HPP_INCLUDED
#define BOOST_SIMD_SWAR_FUNCTIONS_SIMD_SSE_AVX_SLICE_HPP_INCLUDED
#ifdef BOOST_SIMD_HAS_AVX_SUPPORT

#include <boost/simd/swar/functions/slice.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::slice_
                                    , boost::simd::tag::avx_
                                    , (A0)(A1)
                                    , ((simd_<double_<A0>,boost::simd::tag::avx_>))
                                      ((simd_<double_<A1>,boost::simd::tag::sse_>))
                                      ((simd_<double_<A1>,boost::simd::tag::sse_>))
                                    )
  {
    typedef void result_type;

    BOOST_FORCEINLINE
    result_type operator()(const A0 & a0,  A1& a1, A1& a2) const
    {
      a1 = _mm256_extractf128_pd(a0, 0);
      a2 = _mm256_extractf128_pd(a0, 1);
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::slice_
                                    , boost::simd::tag::avx_
                                    , (A0)(A1)
                                    , ((simd_<single_<A0>,boost::simd::tag::avx_>))
                                      ((simd_<single_<A1>,boost::simd::tag::sse_>))
                                      ((simd_<single_<A1>,boost::simd::tag::sse_>))
                                    )
  {
    typedef void result_type;

    BOOST_FORCEINLINE
    result_type operator()(const A0 & a0,  A1& a1, A1& a2) const
    {
      a1 = _mm256_extractf128_ps(a0, 0);
      a2 = _mm256_extractf128_ps(a0, 1);
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::slice_
                                    , boost::simd::tag::avx_
                                    , (A0)(A1)
                                    , ((simd_<integer_<A0>,boost::simd::tag::avx_>))
                                      ((simd_<integer_<A1>,boost::simd::tag::sse_>))
                                      ((simd_<integer_<A1>,boost::simd::tag::sse_>))
                                    )
  {
    typedef void result_type;

    BOOST_FORCEINLINE
    result_type operator()(const A0 & a0,  A1& a1, A1& a2) const
    {
      a1 = _mm256_extractf128_si256(a0, 0);
      a2 = _mm256_extractf128_si256(a0, 1);
    }
  };
} } }

#endif
#endif
