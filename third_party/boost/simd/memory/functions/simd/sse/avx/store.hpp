//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_MEMORY_FUNCTIONS_SIMD_SSE_AVX_STORE_HPP_INCLUDED
#define BOOST_SIMD_MEMORY_FUNCTIONS_SIMD_SSE_AVX_STORE_HPP_INCLUDED
#ifdef BOOST_SIMD_HAS_AVX_SUPPORT

#include <boost/simd/memory/functions/store.hpp>
#include <boost/simd/memory/iterator_category.hpp>
#include <boost/dispatch/functor/preprocessor/call.hpp>
#include <boost/dispatch/meta/scalar_of.hpp>
#include <boost/simd/meta/is_pointing_to.hpp>

namespace boost { namespace simd { namespace ext
{
  /// INTERNAL ONLY - SIMD store double without offset
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::store_
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
      _mm256_storeu_pd(a1,a0);
    }
  };

  /// INTERNAL ONLY - SIMD store float without offset
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::store_
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
      _mm256_storeu_ps(a1,a0);
    }
  };

  /// INTERNAL ONLY - SIMD store integers without offset
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION_IF( boost::simd::tag::store_
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
      _mm256_storeu_si256(reinterpret_cast<__m256i*>(a1), a0);
    }
  };
} } }

#endif
#endif
