//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2013 MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_SWAR_FUNCTIONS_SIMD_SSE_AVX_COMBINE_HPP_INCLUDED
#define BOOST_SIMD_SWAR_FUNCTIONS_SIMD_SSE_AVX_COMBINE_HPP_INCLUDED
#ifdef BOOST_SIMD_HAS_AVX_SUPPORT

#include <boost/simd/swar/functions/combine.hpp>
#include <boost/simd/sdk/simd/meta/retarget.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::combine_
                                    , boost::simd::tag::avx_
                                    , (A0)
                                    , ((simd_ < double_<A0>
                                              , boost::simd::tag::sse_
                                              >
                                      ))
                                      ((simd_ < double_<A0>
                                              , boost::simd::tag::sse_
                                              >
                                      ))
                                    )
  {
    typedef typename  meta::retarget<A0,boost::simd::tag::avx_>::type result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& a0, A0 const& a1) const
    {
      result_type that = _mm256_castpd128_pd256(a0());
                  that = _mm256_insertf128_pd(that(), a1(), 1);
      return that;
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::combine_
                                    , boost::simd::tag::avx_
                                    , (A0)
                                    , ((simd_ < single_<A0>
                                              , boost::simd::tag::sse_
                                              >
                                      ))
                                      ((simd_ < single_<A0>
                                              , boost::simd::tag::sse_
                                              >
                                      ))
                                    )
  {
    typedef typename  meta::retarget<A0,boost::simd::tag::avx_>::type result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& a0, A0 const& a1) const
    {
      result_type that = _mm256_castps128_ps256(a0());
                  that = _mm256_insertf128_ps(that(), a1(), 1);
      return that;
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::combine_
                                    , boost::simd::tag::avx_
                                    , (A0)
                                    , ((simd_ < integer_<A0>
                                              , boost::simd::tag::sse_
                                              >
                                      ))
                                      ((simd_ < integer_<A0>
                                              , boost::simd::tag::sse_
                                              >
                                      ))
                                    )
  {
    typedef typename  meta::retarget<A0,boost::simd::tag::avx_>::type result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& a0, A0 const& a1) const
    {
      result_type that = _mm256_castsi128_si256(a0());
                  that = _mm256_insertf128_si256(that(), a1(), 1);
      return that;
    }
  };
} } }

#endif
#endif
