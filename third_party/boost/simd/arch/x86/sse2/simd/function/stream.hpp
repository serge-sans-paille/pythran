//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_ARCH_X86_SSE2_SIMD_FUNCTION_STREAM_HPP_INCLUDED
#define BOOST_SIMD_ARCH_X86_SSE2_SIMD_FUNCTION_STREAM_HPP_INCLUDED
#ifdef BOOST_SIMD_HAS_SSE2_SUPPORT

#include <boost/simd/memory/functions/stream.hpp>
#include <boost/simd/memory/iterator_category.hpp>
#include <boost/simd/memory/functions/details/check_ptr.hpp>
#include <boost/simd/detail/dispatch/functor/preprocessor/call.hpp>
#include <boost/simd/detail/dispatch/attributes.hpp>

namespace boost { namespace simd { namespace ext
{
  /// INTERNAL ONLY - double SIMD stream with offset
  BOOST_DISPATCH_IMPLEMENT          ( stream_
                                    , boost::simd::tag::sse2_
                                    , (A0)(A1)(A2)
                                    , ((simd_ < double_<A0>
                                              , boost::simd::tag::sse_
                                              >
                                      ))
                                      (iterator_< scalar_< double_<A1> > >)
                                      (scalar_< integer_<A2> >)
                                    )
  {
    typedef void result_type;

    BOOST_FORCEINLINE result_type operator()(__m128d a0, A1 a1, A2 a2) const
    {
      BOOST_SIMD_DETAILS_CHECK_PTR(a1 + a2, sizeof(__m128d));
      _mm_stream_pd(a1+a2,a0);
    }
  };

  /// INTERNAL ONLY - double SIMD stream without offset
  BOOST_DISPATCH_IMPLEMENT          ( stream_
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

    BOOST_FORCEINLINE result_type operator()(__m128d a0, A1 a1 ) const
    {
      BOOST_SIMD_DETAILS_CHECK_PTR(a1, sizeof(__m128d));
      _mm_stream_pd(a1,a0);
    }
  };

  /// INTERNAL ONLY - single SIMD stream with offset
  BOOST_DISPATCH_IMPLEMENT          ( stream_
                                    , boost::simd::tag::sse2_
                                    , (A0)(A1)(A2)
                                    , ((simd_ < single_<A0>
                                              , boost::simd::tag::sse_
                                              >
                                      ))
                                      (iterator_< scalar_< single_<A1> > >)
                                      (scalar_< integer_<A2> >)
                                    )
  {
    typedef void result_type;

    BOOST_FORCEINLINE result_type operator()(__m128 a0, A1 a1, A2 a2) const
    {
      BOOST_SIMD_DETAILS_CHECK_PTR(a1 + a2, sizeof(__m128));
      _mm_stream_ps(a1+a2,a0);
    }
  };

  /// INTERNAL ONLY - single SIMD stream without offset
  BOOST_DISPATCH_IMPLEMENT          ( stream_
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
      _mm_stream_ps(a1,a0);
    }
  };

  /// INTERNAL ONLY - integers SIMD stream with offset
  BOOST_DISPATCH_IMPLEMENT          ( stream_
                                    , boost::simd::tag::sse2_
                                    , (A0)(A1)(A2)
                                    , ((simd_ < integer_<A0>
                                              , boost::simd::tag::sse_
                                              >
                                      ))
                                      (iterator_< scalar_< integer_<A1> > >)
                                      (scalar_< integer_<A2> >)
                                    )
  {
    typedef void result_type;

    BOOST_FORCEINLINE result_type operator()(__m128i a0, A1 a1, A2 a2) const
    {
      BOOST_SIMD_DETAILS_CHECK_PTR(a1 + a2, sizeof(__m128i));
      _mm_stream_si128(reinterpret_cast<__m128i*>(a1 + a2), a0);
    }
  };

  /// INTERNAL ONLY - integers SIMD stream without offset
  BOOST_DISPATCH_IMPLEMENT          ( stream_
                                    , boost::simd::tag::sse2_
                                    , (A0)(A1)
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
      _mm_stream_si128(reinterpret_cast<__m128i*>(a1), a0);
    }
  };
} } }

#endif
#endif
