//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2014               MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_MEMORY_FUNCTIONS_SIMD_SSE_AVX_ALIGNED_STORE_HPP_INCLUDED
#define BOOST_SIMD_MEMORY_FUNCTIONS_SIMD_SSE_AVX_ALIGNED_STORE_HPP_INCLUDED
#ifdef BOOST_SIMD_HAS_AVX_SUPPORT

#include <boost/simd/memory/functions/aligned_store.hpp>
#include <boost/simd/memory/functions/details/check_ptr.hpp>
#include <boost/simd/memory/iterator_category.hpp>
#include <boost/dispatch/functor/preprocessor/call.hpp>
#include <boost/dispatch/attributes.hpp>
#include <boost/simd/meta/is_pointing_to.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::aligned_store_
                                    , boost::simd::tag::avx_
                                    , (A0)(A1)(A2)
                                    , ((simd_ < double_<A0>
                                              , boost::simd::tag::sse_
                                              >
                                      ))
                                      (iterator_< scalar_< double_<A1> > >)
                                      ((simd_< logical_<A2>
                                             , boost::simd::tag::sse_
                                             >
                                      ))
                                    )
  {
    typedef void result_type;

    BOOST_FORCEINLINE result_type operator()(__m128d a0, A1 a1, const A2& a2) const
    {
      BOOST_SIMD_DETAILS_CHECK_PTR(a1, sizeof(__m128d));
      _mm_maskstore_pd(a1,_mm_castpd_si128(a2),a0);
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::aligned_store_
                                    , boost::simd::tag::avx_
                                    , (A0)(A1)(A2)
                                    , ((simd_ < single_<A0>
                                              , boost::simd::tag::sse_
                                              >
                                      ))
                                      (iterator_< scalar_< single_<A1> > >)
                                      ((simd_< logical_<A2>
                                             , boost::simd::tag::sse_
                                             >
                                      ))
                                    )
  {
    typedef void result_type;

    BOOST_FORCEINLINE result_type operator()(__m128 a0, A1 a1, const A2& a2) const
    {
      BOOST_SIMD_DETAILS_CHECK_PTR(a1, sizeof(__m128));
      _mm_maskstore_ps(a1,_mm_castps_si128(a2),a0);
    }
  };

  /// INTERNAL ONLY - masked AVX double SIMD store without offset
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::aligned_store_
                                    , boost::simd::tag::avx_
                                    , (A0)(A1)(A2)
                                    , ((simd_ < double_<A0>
                                              , boost::simd::tag::avx_
                                              >
                                      ))
                                      (iterator_< scalar_< double_<A1> > >)
                                      ((simd_< logical_<A2>
                                             , boost::simd::tag::avx_
                                             >
                                      ))
                                    )
  {
    typedef void result_type;

    BOOST_FORCEINLINE result_type operator()(__m256d a0, A1 a1, const A2& a2) const
    {
      BOOST_SIMD_DETAILS_CHECK_PTR(a1, sizeof(__m256d));
      _mm256_maskstore_pd(a1,_mm256_castpd_si256(a2),a0);
    }
  };

  /// INTERNAL ONLY - AVX double SIMD store without offset
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::aligned_store_
                                    , boost::simd::tag::avx_
                                    , (A0)(A1)
                                    , ((simd_ < double_<A0>
                                              , boost::simd::tag::avx_
                                              >
                                      ))
                                      (iterator_< scalar_< double_<A1> > >)
                                    )
  {
    typedef void result_type;

    BOOST_FORCEINLINE result_type operator()(__m256d a0, A1 a1) const
    {
      BOOST_SIMD_DETAILS_CHECK_PTR(a1, sizeof(__m256d));
      _mm256_store_pd(a1,a0);
    }
  };

  /// INTERNAL ONLY - masked AVX single SIMD store without offset
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::aligned_store_
                                    , boost::simd::tag::avx_
                                    , (A0)(A1)(A2)
                                    , ((simd_ < single_<A0>
                                              , boost::simd::tag::avx_
                                              >
                                      ))
                                      (iterator_< scalar_< single_<A1> > >)
                                      ((simd_< logical_<A2>
                                             , boost::simd::tag::avx_
                                             >
                                      ))
                                    )
  {
    typedef void result_type;

    BOOST_FORCEINLINE result_type operator()(__m256 a0, A1 a1, const A2& a2) const
    {
      BOOST_SIMD_DETAILS_CHECK_PTR(a1, sizeof(__m256));
      _mm256_maskstore_ps(a1,_mm256_castps_si256(a2),a0);
    }
  };

  /// INTERNAL ONLY - AVX single SIMD store without offset
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::aligned_store_
                                    , boost::simd::tag::avx_
                                    , (A0)(A1)
                                    , ((simd_ < single_<A0>
                                              , boost::simd::tag::avx_
                                              >
                                      ))
                                      (iterator_< scalar_< single_<A1> > >)
                                    )
  {
    typedef void result_type;

    BOOST_FORCEINLINE result_type operator()(__m256 a0, A1 a1) const
    {
      BOOST_SIMD_DETAILS_CHECK_PTR(a1, sizeof(__m256));
      _mm256_store_ps(a1,a0);
    }
  };

  /// INTERNAL ONLY - AVX integral SIMD store without offset
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION_IF( boost::simd::tag::aligned_store_
                                      , boost::simd::tag::avx_
                                      , (A0)(A1)
                                       , ( simd::meta::is_pointing_to
                                          < A1
                                          , typename  dispatch::meta
                                                    ::scalar_of<A0>::type
                                          >
                                        )
                                      , ((simd_ < integer_<A0>
                                                , boost::simd::tag::avx_
                                                >
                                        ))
                                        (iterator_< scalar_< integer_<A1> > >)
                                      )
  {
    typedef void result_type;

    BOOST_FORCEINLINE result_type operator()(__m256i a0, A1 a1) const
    {
      BOOST_SIMD_DETAILS_CHECK_PTR(a1, sizeof(__m256i));
      _mm256_store_si256(reinterpret_cast<__m256i*>(a1), a0);
    }
  };
} } }

#endif
#endif
