//==================================================================================================
/**
  Copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
**/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_COMMON_SIMD_FUNCTION_SHUFFLE_REVERSE_HPP_INCLUDED
#define BOOST_SIMD_ARCH_COMMON_SIMD_FUNCTION_SHUFFLE_REVERSE_HPP_INCLUDED

#include <boost/simd/detail/overload.hpp>
#include <boost/simd/function/reverse.hpp>
#include <boost/simd/detail/nsm.hpp>
#include <boost/simd/detail/shuffle.hpp>

namespace boost { namespace simd
{
  namespace detail
  {
    // ---------------------------------------------------------------------------------------------
    // Check if pattern is [B B+1 ... B+C]
    template<int... Ps> struct is_reverse
    {
      using type = nsm::all < nsm::transform< nsm::range<int,0,sizeof...(Ps)>
                                                    , nsm::reverse<nsm::integral_list<int,Ps...>>
                                                    , nsm::equal_to<nsm::_1,nsm::_2>
                                                    >
                                >;
    };

    template<int P0> struct is_reverse<P0> : tt::false_type {};
  }

  // -----------------------------------------------------------------------------------------------
  // Identity pattern hierarchy
  template<typename P> struct reverse_pattern : P
  {
    using parent = P;
  };

  // -----------------------------------------------------------------------------------------------
  // Reverse matcher
  struct reverse_shuffle
  {
    template<typename T, typename P> static BOOST_FORCEINLINE
    T process(T const& a0, reverse_pattern<P> const&) { return reverse(a0); }
  };
} }

// -------------------------------------------------------------------------------------------------
// Hierarchize reverse patterns
namespace boost { namespace dispatch { namespace ext
{
  template<int... Ps,typename Origin>
  struct pattern_hierarchy< boost::simd::detail::pattern_<Ps...>,Origin
                          , typename std::enable_if<simd::detail::is_reverse<Ps...>::type::value>::type
                          >
  {
    using type = boost::simd::reverse_pattern<bsd::pattern_<Ps...>>;
  };
} } }

#endif
