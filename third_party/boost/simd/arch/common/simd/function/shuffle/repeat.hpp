//==================================================================================================
/**
  Copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
**/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_COMMON_SIMD_FUNCTION_SHUFFLE_REPEAT_HPP_INCLUDED
#define BOOST_SIMD_ARCH_COMMON_SIMD_FUNCTION_SHUFFLE_REPEAT_HPP_INCLUDED

#include <boost/simd/function/repeat_lower_half.hpp>
#include <boost/simd/function/repeat_upper_half.hpp>
#include <boost/simd/detail/nsm.hpp>

namespace boost { namespace simd
{
  namespace detail
  {
    namespace tt = nsm::type_traits;
    // ---------------------------------------------------------------------------------------------
    // Is this a half-repeat pattern ?
    template<int P0, int... Ps>
    struct  is_repeat
          : tt::is_same< nsm::integral_list<int,P0,Ps...>
                        , nsm::append < nsm::range<int,P0,P0+int(sizeof...(Ps)+1)/2>
                                      , nsm::range<int,P0,P0+int(sizeof...(Ps)+1)/2>
                                      >
                        >

    {};

    // -1 disqualifies already
    template<int P1, int... Ps> struct is_repeat<-1,P1,Ps...> : tt::false_type {};

    // Don't overlap with other hierarchies
    template<int P0>          struct is_repeat<P0>    : tt::false_type {};
    template<int P0, int P1>  struct is_repeat<P0,P1> : tt::false_type {};
    template<int P1>          struct is_repeat<-1,P1> : tt::false_type {};
  }

  // -----------------------------------------------------------------------------------------------
  // Repeat patterns hierarchy
  template<bool Upper, typename P> struct repeat_ : P
  {
    using parent = P;
  };

  // -----------------------------------------------------------------------------------------------
  // Repeat matcher
  struct repeat_shuffle
  {
    template<typename T, typename P>
    static BOOST_FORCEINLINE T process(T const& a0, repeat_<false,P> const&)
    {
      return repeat_lower_half(a0);
    }

    template<typename T, typename P>
    static BOOST_FORCEINLINE T process(T const& a0, repeat_<true,P> const&)
    {
      return repeat_upper_half(a0);
    }
  };
} }

// -------------------------------------------------------------------------------------------------
// Hierarchize repeat patterns
namespace boost { namespace dispatch { namespace ext
{
  // repeat half patterns
  template<int P0, int... Ps,typename Origin>
  struct pattern_hierarchy< boost::simd::detail::pattern_<P0,Ps...>,Origin
                          , typename std::enable_if<simd::detail::is_repeat<P0,Ps...>::value>::type
                          >
  {
    using type = boost::simd::repeat_<P0 != 0, boost::simd::detail::pattern_<P0,Ps...> >;
  };
} } }

#endif
