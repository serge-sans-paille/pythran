//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_MEMORY_FUNCTIONS_SIMD_SSE_SSE2_ALIGNED_STORE_HPP_INCLUDED
#define BOOST_SIMD_MEMORY_FUNCTIONS_SIMD_SSE_SSE2_ALIGNED_STORE_HPP_INCLUDED
#ifdef BOOST_SIMD_HAS_SSE2_SUPPORT

#include <boost/simd/memory/functions/aligned_store.hpp>
#include <boost/simd/memory/functions/details/check_ptr.hpp>
#include <boost/simd/memory/iterator_category.hpp>
#include <boost/dispatch/functor/preprocessor/call.hpp>
#include <boost/dispatch/attributes.hpp>
#include <boost/simd/meta/is_pointing_to.hpp>

namespace boost { namespace simd { namespace ext
{
  /// INTERNAL ONLY - SSE double SIMD store without offset
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::aligned_store_
                                    , boost::simd::tag::sse2_
                                    , (A0)(A1)
                                    , ((simd_ < double_<A0>
                                              , boost::simd::tag::sse_
                                              >
                                      ))
                                      (iterator_< scalar_< double_<A1> > >)
                                    )
  {
    typedef void result_type;

    BOOST_FORCEINLINE result_type operator()(__m128d a0, A1 a1) const
    {
      BOOST_SIMD_DETAILS_CHECK_PTR(a1, sizeof(__m128d));
      _mm_store_pd(a1,a0);
    }
  };

  /// INTERNAL ONLY - SSE single SIMD store without offset
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::aligned_store_
                                    , boost::simd::tag::sse2_
                                    , (A0)(A1)
                                    , ((simd_ < single_<A0>
                                              , boost::simd::tag::sse_
                                              >
                                      ))
                                      (iterator_< scalar_< single_<A1> > >)
                                    )
  {
    typedef void result_type;

    BOOST_FORCEINLINE result_type operator()(__m128 a0, A1 a1) const
    {
      BOOST_SIMD_DETAILS_CHECK_PTR(a1, sizeof(__m128));
      _mm_store_ps(a1,a0);
    }
  };

  /// INTERNAL ONLY - SSE integral SIMD store without offset
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION_IF( boost::simd::tag::aligned_store_
                                      , boost::simd::tag::sse2_
                                      , (A0)(A1)
                                      , ( simd::meta::is_pointing_to
                                          < A1
                                          , typename  dispatch::meta
                                                    ::scalar_of<A0>::type
                                          >
                                        )
                                      , ((simd_ < integer_<A0>
                                                , boost::simd::tag::sse_
                                                >
                                        ))
                                        (iterator_< scalar_< integer_<A1> > >)
                                      )
  {
    typedef void result_type;

    BOOST_FORCEINLINE result_type operator()(__m128i a0, A1 a1) const
    {
      BOOST_SIMD_DETAILS_CHECK_PTR(a1, sizeof(__m128i));
      _mm_store_si128(reinterpret_cast<__m128i*>(a1), a0);
    }
  };
} } }

#endif
#endif
