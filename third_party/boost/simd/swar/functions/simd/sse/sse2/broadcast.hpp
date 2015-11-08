//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2014 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2014 MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_SWAR_FUNCTIONS_SIMD_SSE_SSE2_BROADCAST_HPP_INCLUDED
#define BOOST_SIMD_SWAR_FUNCTIONS_SIMD_SSE_SSE2_BROADCAST_HPP_INCLUDED
#ifdef BOOST_SIMD_HAS_SSE2_SUPPORT

#include <boost/simd/swar/functions/broadcast.hpp>
#include <boost/dispatch/attributes.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::broadcast_
                                    , boost::simd::tag::sse2_
                                    , (A0)(A1)
                                    , ((simd_ < double_<A0>
                                              , boost::simd::tag::sse_
                                              >
                                      ))
                                      (mpl_integral_< scalar_< integer_<A1> > >)
                                    )
  {
    typedef A0 result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& a0, A1 const&) const
    {
      return _mm_shuffle_pd(a0,a0,_MM_SHUFFLE2( A1::value, A1::value));
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::broadcast_
                                    , boost::simd::tag::sse2_
                                    , (A0)(A1)
                                    , ((simd_ < single_<A0>
                                              , boost::simd::tag::sse_
                                              >
                                      ))
                                      (mpl_integral_< scalar_< integer_<A1> > >)
                                    )
  {
    typedef A0 result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& a0, A1 const&) const
    {
      return _mm_shuffle_ps ( a0, a0, _MM_SHUFFLE ( A1::value, A1::value
                                                  , A1::value, A1::value
                                                  )
                            );
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::broadcast_
                                    , boost::simd::tag::sse2_
                                    , (A0)(A1)
                                    , ((simd_ < ints32_<A0>
                                              , boost::simd::tag::sse_
                                              >
                                      ))
                                      (mpl_integral_< scalar_< integer_<A1> > >)
                                    )
  {
    typedef A0 result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& a0, A1 const&) const
    {
      return _mm_shuffle_epi32( a0, _MM_SHUFFLE ( A1::value, A1::value
                                                , A1::value, A1::value
                                                )
                              );
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::broadcast_
                                    , boost::simd::tag::sse2_
                                    , (A0)(A1)
                                    , ((simd_ < ints16_<A0>
                                              , boost::simd::tag::sse_
                                              >
                                      ))
                                      (mpl_integral_< scalar_< integer_<A1> > >)
                                    )
  {
    typedef A0 result_type;

    // This shuffle the 32 bits packet of the broadcast so
    // we end up with [ In In+1 In In+1 In In+1 In In+1 ]
    typedef boost::mpl::int_< _MM_SHUFFLE ( A1::value / 2,A1::value / 2
                                          , A1::value / 2,A1::value / 2
                                          )
                            > partial_t;

    // This select either In or In+1 as 16 bits value and give us
    // [In In In In In In In In] or [In+1 In+1 In+1 In+1 In+1 In+1 In+1 In+1]
    typedef boost::mpl::int_< _MM_SHUFFLE ( A1::value % 2,A1::value % 2
                                          , A1::value % 2,A1::value % 2
                                          )
                            > fix_t;

#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wshadow"
#endif // __clang__

    BOOST_FORCEINLINE result_type operator()(A0 const& a0, A1 const&) const
    {
      return _mm_shufflehi_epi16( _mm_shufflelo_epi16
                                  ( _mm_shuffle_epi32( a0, partial_t::value)
                                  , fix_t::value
                                  )
                                , fix_t::value
                                );
    }

#ifdef __clang__
#pragma clang diagnostic pop
#endif // __clang__

  };
} } }

#endif
#endif
