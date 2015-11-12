//==============================================================================
//         Copyright 2009 - 2014 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2014 MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_SWAR_FUNCTIONS_DETAILS_IDENTITY_PATTERN_HPP_INCLUDED
#define BOOST_SIMD_SWAR_FUNCTIONS_DETAILS_IDENTITY_PATTERN_HPP_INCLUDED

#include <boost/simd/swar/functions/details/default_matcher.hpp>
#include <boost/dispatch/attributes.hpp>

namespace boost { namespace simd { namespace details
{
  //============================================================================
  // Idempotent pattern
  //============================================================================
  struct identity_pattern
  {
    template<typename T, typename P>
    static BOOST_FORCEINLINE T process(T const& a0, P const&)
    {
      return a0;
    }
  };

  //============================================================================
  // Forward to identify on a0/a1
  //============================================================================
  template<typename P>
  struct default_matcher::match2<0,1,P> : identity_pattern
  {};

  template<typename P>
  struct default_matcher::match4<0,1,2,3,P> : identity_pattern
  {};

  template<typename P>
  struct default_matcher::match8<0,1,2,3,4,5,6,7,P> : identity_pattern
  {};

  template<typename P>
  struct  default_matcher::match16<0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,P>
        : identity_pattern
  {};

  template<typename P>
  struct  default_matcher::match32
          < 0 ,1 ,2 ,3 ,4 ,5 ,6 ,7 ,8 ,9 ,10,11,12,13,14,15
          , 16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31
          , P
          > : identity_pattern
  {};
} } }

#endif
