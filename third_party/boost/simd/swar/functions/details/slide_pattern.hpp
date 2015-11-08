//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2014 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2014 MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_SWAR_FUNCTIONS_DETAILS_SLIDE_PATTERN_HPP_INCLUDED
#define BOOST_SIMD_SWAR_FUNCTIONS_DETAILS_SLIDE_PATTERN_HPP_INCLUDED

#include <boost/simd/include/functions/simd/slide.hpp>
#include <boost/dispatch/attributes.hpp>

#include <boost/preprocessor/arithmetic/dec.hpp>
#include <boost/preprocessor/arithmetic/sub.hpp>
#include <boost/preprocessor/repetition/enum.hpp>
#include <boost/preprocessor/repetition/repeat.hpp>

namespace boost { namespace simd { namespace details
{
  //============================================================================
  // slide pattern
  //============================================================================
  template<int N>
  struct slide_pattern
  {
    template<typename T, typename P>
    static BOOST_FORCEINLINE T process(T const& a0, P const&)
    {
      return slide<N>(a0);
    }

    template<typename T, typename P>
    static BOOST_FORCEINLINE T process(T const& a0, T const& a1, P const&)
    {
      return slide<N>(a0,a1);
    }
  };

#define M2(z,n,t) -1
#define M1(z,n,t) (t + n)

#define M0(z,n,t)                                                              \
template<typename Permutation>                                                 \
struct  default_matcher::match##t < BOOST_PP_ENUM(t,M1,BOOST_PP_INC(n))        \
                                  , Permutation                                \
                                  >                                            \
      : slide_pattern<BOOST_PP_INC(n)>                                         \
{};                                                                            \
                                                                               \
template<typename Permutation>                                                 \
struct  default_matcher::match##t< BOOST_PP_ENUM( BOOST_PP_SUB(t               \
                                                              ,BOOST_PP_INC(n) \
                                                              )                \
                                                , M1                           \
                                                , BOOST_PP_INC(n)              \
                                                )                              \
                              , BOOST_PP_ENUM ( BOOST_PP_INC(n)                \
                                              , M2                             \
                                              , BOOST_PP_INC(n)                \
                                              )                                \
                              , Permutation                                    \
                              >                                                \
      : slide_pattern<BOOST_PP_INC(n)>                                         \
{};                                                                            \
/**/

  //============================================================================
  // Cardinal 4 slide patterns
  //============================================================================
  BOOST_PP_REPEAT(3,M0,4)

  //============================================================================
  // Cardinal 8 slide patterns
  //============================================================================
  BOOST_PP_REPEAT(7,M0,8)

  //============================================================================
  // Cardinal 16 slide patterns
  //============================================================================
  BOOST_PP_REPEAT(15,M0,16)

#undef M0
#undef M1
#undef M2

} } }

#endif
