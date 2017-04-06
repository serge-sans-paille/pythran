//==================================================================================================
/**
  Copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
**/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_COMMON_SIMD_FUNCTION_SHUFFLE_BROADCAST_HPP_INCLUDED
#define BOOST_SIMD_ARCH_COMMON_SIMD_FUNCTION_SHUFFLE_BROADCAST_HPP_INCLUDED

#include <boost/simd/detail/overload.hpp>
#include <boost/simd/detail/nsm.hpp>
#include <boost/simd/detail/shuffle.hpp>
#include <boost/simd/function/broadcast.hpp>

namespace boost { namespace simd
{
  namespace detail
  {
    namespace tt = nsm::type_traits;

    // ---------------------------------------------------------------------------------------------
    // Check if pattern is [N ... N]
    template<int P, int... Ps>
    struct is_broadcast : nsm::all< nsm::integral_list<int,Ps...>
                                      , nsm::equal_to<nsm::_1,tt::integral_constant<int,P>>
                                      >
    {};

    template<int P0> struct is_broadcast<P0> : tt::false_type {};
  }

  // -----------------------------------------------------------------------------------------------
  // Broadcast pattern hierarchy
  template<int P0, typename P>
  struct  broadcast_pattern : P
  {
    using parent = P;
  };

  // -----------------------------------------------------------------------------------------------
  // Identity matcher - do nothing but return its argument
  struct broadcast_shuffle
  {
    template<typename T, int Idx, typename P>
    static BOOST_FORCEINLINE T process(T const& a0, broadcast_pattern<Idx,P> const&)
    {
      return broadcast<Idx>(a0);
    }
  };
} }

namespace boost { namespace dispatch { namespace ext
{
  namespace bsd = boost::simd::detail;

  // -----------------------------------------------------------------------------------------------
  // Hierarchize broadcast patterns
  template<int P0, int... Ps,typename Origin>
  struct pattern_hierarchy< bsd::pattern_<P0,Ps...>,Origin
                          , typename std::enable_if<bsd::is_broadcast<P0,Ps...>::type::value>::type
                          >
  {
    using type = boost::simd::broadcast_pattern<P0, bsd::pattern_<P0,Ps...>>;
  };
} } }

#endif
