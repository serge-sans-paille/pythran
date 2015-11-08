//==============================================================================
//         Copyright 2009 - 2014 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2014 MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_SWAR_FUNCTIONS_DETAILS_REVERSE_PATTERN_HPP_INCLUDED
#define BOOST_SIMD_SWAR_FUNCTIONS_DETAILS_REVERSE_PATTERN_HPP_INCLUDED

#include <boost/simd/swar/functions/details/default_matcher.hpp>
#include <boost/simd/include/functions/simd/reverse.hpp>
#include <boost/dispatch/attributes.hpp>

namespace boost { namespace simd { namespace details
{
  //============================================================================
  // Idempotent pattern
  //============================================================================
  struct reverse_pattern
  {
    template<typename T, typename P>
    static BOOST_FORCEINLINE T process(T const& a0, P const&)
    {
      return reverse(a0);
    }
  };

  //============================================================================
  // Forward to identify on a0/a1
  //============================================================================
  template<typename P> struct default_matcher::match2<1,0,P> : reverse_pattern {};

  template<typename P>
  struct default_matcher::match4<3,2,1,0,P> : reverse_pattern
  {};

  template<typename P>
  struct default_matcher::match8<7,6,5,4,3,2,1,0,P> : reverse_pattern
  {};

  template<typename P>
  struct  default_matcher::match16<15,14,13,12,11,10,9,8,7,6,5,4,3,2,1,0,P>
        : reverse_pattern
  {};

  template<typename P>
  struct  default_matcher::match32< 31,30,29,28,27,26,25,24,23,22,21,20,19,18,17,16
                                  , 15,14,13,12,11,10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0
                                  , P
                                  >
        : reverse_pattern
  {};
} } }

#endif
