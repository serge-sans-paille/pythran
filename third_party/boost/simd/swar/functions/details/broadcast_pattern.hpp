//==============================================================================
//         Copyright 2009 - 2014 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2014 MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_SWAR_FUNCTIONS_DETAILS_BROADCAST_PATTERN_HPP_INCLUDED
#define BOOST_SIMD_SWAR_FUNCTIONS_DETAILS_BROADCAST_PATTERN_HPP_INCLUDED

#include <boost/simd/swar/functions/details/default_matcher.hpp>
#include <boost/simd/include/functions/simd/broadcast.hpp>
#include <boost/dispatch/attributes.hpp>

namespace boost { namespace simd { namespace details
{
  //============================================================================
  // Idempotent pattern
  //============================================================================
  template<int N>
  struct broadcast_pattern
  {
    template<typename T, typename P>
    static BOOST_FORCEINLINE T process(T const& a0, P const&)
    {
      return boost::simd::broadcast<N>(a0);
    }
  };

  //============================================================================
  // Forward to identify on a0/a1
  //============================================================================
  template<int N, typename P>
  struct default_matcher::match2<N,N,P> : broadcast_pattern<N>
  {};

  template<int N, typename P>
  struct default_matcher::match4<N,N,N,N,P> : broadcast_pattern<N>
  {};

  template<int N, typename P>
  struct default_matcher::match8<N,N,N,N,N,N,N,N,P> : broadcast_pattern<N>
  {};

  template<int N, typename P>
  struct  default_matcher::match16<N,N,N,N,N,N,N,N,N,N,N,N,N,N,N,N,P>
        : broadcast_pattern<N>
  {};

  template<int N, typename P>
  struct  default_matcher::match32
          < N,N,N,N,N,N,N,N,N,N,N,N,N,N,N,N,N,N,N,N,N,N,N,N,N,N,N,N,N,N,N,N,P>
        : broadcast_pattern<N>
  {};
} } }

#endif
