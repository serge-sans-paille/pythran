//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_SWAR_FUNCTIONS_SIMD_SSE_SSSE3_REVERSE_HPP_INCLUDED
#define BOOST_SIMD_SWAR_FUNCTIONS_SIMD_SSE_SSSE3_REVERSE_HPP_INCLUDED
#ifdef BOOST_SIMD_HAS_SSSE3_SUPPORT

#include <boost/simd/swar/functions/reverse.hpp>
#include <boost/dispatch/attributes.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::reverse_
                                    , boost::simd::tag::ssse3_
                                    , (A0)
                                    , ((simd_ < ints8_<A0>
                                              , boost::simd::tag::sse_
                                              >
                                      ))
                                    )
  {
    typedef A0 result_type;

    BOOST_FORCEINLINE BOOST_SIMD_FUNCTOR_CALL(1)
    {
      return _mm_shuffle_epi8 ( a0
                              , _mm_set_epi8( 0, 1, 2, 3, 4, 5, 6, 7
                                            , 8, 9,10,11,12,13,14,15
                                            )
                              );
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::reverse_
                                    , boost::simd::tag::ssse3_
                                    , (A0)
                                    , ((simd_ < ints16_<A0>
                                              , boost::simd::tag::sse_
                                              >
                                      ))
                                    )
  {
    typedef A0 result_type;

    BOOST_FORCEINLINE BOOST_SIMD_FUNCTOR_CALL(1)
    {
      return _mm_shuffle_epi8 ( a0
                              , _mm_set_epi8( 1, 0, 3, 2, 5, 4, 7, 6
                                            , 9, 8,11,10,13,12,15,14
                                            )
                              );
    }
  };
} } }

#endif
#endif
