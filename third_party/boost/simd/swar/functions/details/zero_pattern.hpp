//==============================================================================
//         Copyright 2009 - 2014 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2014 MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_SWAR_FUNCTIONS_DETAILS_ZERO_PATTERN_HPP_INCLUDED
#define BOOST_SIMD_SWAR_FUNCTIONS_DETAILS_ZERO_PATTERN_HPP_INCLUDED

#include <boost/simd/swar/functions/details/default_matcher.hpp>
#include <boost/simd/include/constants/zero.hpp>

namespace boost { namespace simd { namespace details
{
  //============================================================================
  // Zeroing pattern
  //============================================================================
  struct zero_pattern
  {
    // By default, nothing is optimized
    template<typename T, typename P>
    static BOOST_FORCEINLINE T process(T const&, P const&)
    {
      return Zero<T>();
    }
  };

  //============================================================================
  // Forward to 0-ing
  //============================================================================
  template<typename P>
  struct  default_matcher::match2<-1,-1,P> : zero_pattern
  {};

  template<typename P>
  struct  default_matcher::match4<-1,-1,-1,-1,P> : zero_pattern
  {};

  template<typename P>
  struct  default_matcher::match8<-1,-1,-1,-1,-1,-1,-1,-1,P> : zero_pattern
  {};

  template<typename P>
  struct  default_matcher
        ::match16<-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,P>
        : zero_pattern
  {};

  template<typename P>
  struct  default_matcher
        ::match32 <-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1
                  ,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,P>
        : zero_pattern
  {};
} } }

#endif
