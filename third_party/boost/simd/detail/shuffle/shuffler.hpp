//==================================================================================================
/**
  Copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
**/
//==================================================================================================
#ifndef BOOST_SIMD_DETAIL_SHUFFLE_SHUFFLER_HPP_INCLUDED
#define BOOST_SIMD_DETAIL_SHUFFLE_SHUFFLER_HPP_INCLUDED

#include <boost/simd/config.hpp>
#include <boost/simd/detail/nsm.hpp>
#include <boost/simd/constant/zero.hpp>

namespace boost { namespace simd { namespace detail
{
  // -----------------------------------------------------------------------------------------------
  // Shuffler entry point
  template<typename Matcher, typename Permutation> struct shuffler;

  // -----------------------------------------------------------------------------------------------
  // General cases - perform reinsertion of correct values via make(...)
  template<typename Matcher, int P0, int P1, int... Ps>
  struct shuffler<Matcher,pattern_<P0,P1,Ps...>>
  {
    // Unary permutation handler
    template<typename T> static BOOST_FORCEINLINE T process(T const& a0)
    {
      return Matcher::process(a0, dispatch::hierarchy_of_t<pattern_<P0,P1,Ps...>>{});
    }

    // Binary permutation handler
    template<typename T> static BOOST_FORCEINLINE T process(T const& a0,T const& a1)
    {
      return switch_(a0,a1,side_t<pattern_<P0,P1,Ps...>>{});
    }

    template<typename T>
    static BOOST_FORCEINLINE T switch_(T const& a0,T const&, a0_side const&)
    {
      return boost::simd::shuffle<P0,P1,Ps...>(a0);
    }

    template<typename T>
    static BOOST_FORCEINLINE T switch_(T const&,T const& a1, a1_side const&)
    {
      static int const pattern_size = 2 + int(sizeof...(Ps));
      return boost::simd::shuffle < remap<P0,-pattern_size>::value
                                  , remap<P1,-pattern_size>::value
                                  , remap<Ps,-pattern_size>::value...
                                  >(a1);
    }

    template<typename T>
    static BOOST_FORCEINLINE T switch_(T const& a0,T const& a1, both_side const&)
    {
      return Matcher::process(a0,a1, dispatch::hierarchy_of_t<pattern_<P0,P1,Ps...>>{});
    }

    template<typename T>
    static BOOST_FORCEINLINE T switch_(T const&,T const&, zero_side const&)
    {
      return Zero<T>();
    }
  };

  // -----------------------------------------------------------------------------------------------
  // Default matcher for permutation of size 1
  template<typename Matcher> struct shuffler<Matcher,pattern_<0>>
  {
    // Unary permutation handler
    template<typename T> static BOOST_FORCEINLINE T process(T const& a0)
    {
      return a0;
    }

    // Binary permutation handler
    template<typename T> static BOOST_FORCEINLINE T process(T const& a0,T const&)
    {
      return a0;
    }
  };

  template<typename Matcher> struct shuffler<Matcher,pattern_<1>>
  {
    // Binary permutation handler
    template<typename T> static BOOST_FORCEINLINE T process(T const&, T const& a1)
    {
      return a1;
    }
  };

  template<typename Matcher> struct shuffler<Matcher,pattern_<-1>>
  {
    // Unary permutation handler
    template<typename T> static BOOST_FORCEINLINE T process(T const&)
    {
      return Zero<T>();
    }

    // Binary permutation handler
    template<typename T> static BOOST_FORCEINLINE T process(T const&,T const&)
    {
      return Zero<T>();
    }
  };
} } }

#endif
