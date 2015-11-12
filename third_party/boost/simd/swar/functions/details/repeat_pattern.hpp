//==============================================================================
//         Copyright 2009 - 2014 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2014 MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_SWAR_FUNCTIONS_DETAILS_REPEAT_PATTERN_HPP_INCLUDED
#define BOOST_SIMD_SWAR_FUNCTIONS_DETAILS_REPEAT_PATTERN_HPP_INCLUDED

#include <boost/simd/swar/functions/details/default_matcher.hpp>
#include <boost/simd/include/functions/simd/repeat_lower_half.hpp>
#include <boost/simd/include/functions/simd/repeat_upper_half.hpp>
#include <boost/dispatch/attributes.hpp>

namespace boost { namespace simd { namespace details
{
  //============================================================================
  // Repear lower/upper pattern
  //============================================================================
  struct repeat_lower
  {
    template<typename T, typename P>
    static BOOST_FORCEINLINE T process(T const& a0, P const&)
    {
      return repeat_lower_half(a0);
    }
  };

  struct repeat_upper
  {
    template<typename T, typename P>
    static BOOST_FORCEINLINE T process(T const& a0, P const&)
    {
      return repeat_upper_half(a0);
    }
  };

  //============================================================================
  // Forward to repeating on a0/a1
  // Not that for cardinal 2, this is already done by broadcast
  //============================================================================
  template<typename P>
  struct default_matcher::match4<0,1,0,1,P> : repeat_lower
  {};

  template<typename P>
  struct default_matcher::match4<2,3,2,3,P> : repeat_upper
  {};

  template<typename P>
  struct default_matcher::match8<0,1,2,3,0,1,2,3,P> : repeat_lower
  {};

  template<typename P>
  struct default_matcher::match8<4,5,6,7,4,5,6,7,P> : repeat_upper
  {};
} } }

#endif
