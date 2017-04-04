//==================================================================================================
/**
  Copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
**/
//==================================================================================================
#ifndef BOOST_SIMD_DETAIL_SHUFFLE_PATTERN_HPP_INCLUDED
#define BOOST_SIMD_DETAIL_SHUFFLE_PATTERN_HPP_INCLUDED

#include <boost/simd/config.hpp>
#include <boost/simd/meta/cardinal_of.hpp>
#include <boost/simd/detail/nsm.hpp>
#include <boost/simd/detail/dispatch/hierarchy/unspecified.hpp>
#include <boost/simd/detail/dispatch/hierarchy_of.hpp>

namespace boost { namespace simd
{
  // -----------------------------------------------------------------------------------------------
  // normalized const-expr pattern holder - prevent MSVC 2016 shenanigans with 0
  template<int (*M)(int,int)> struct pattern {};

  namespace detail
  {
    namespace tt = nsm::type_traits;

    // -----------------------------------------------------------------------------------------------
    // normalized permutation pattern holder - also acts as its own hierarchy
    template<int... Ps> struct pattern_ : boost::dispatch::unspecified_<pattern_<Ps...>>
    {
      static const std::size_t static_size = sizeof...(Ps);
      using size_type = tt::integral_constant<std::size_t,static_size>;
      using parent = boost::dispatch::unspecified_<pattern_<Ps...>>;
    };

    // -----------------------------------------------------------------------------------------------
    // take a meta-function class and build a pattern
    template<typename M, typename C, typename L> struct make_meta_pattern;

    template<typename M, typename C, typename P>
    struct idx : nsm::apply<M, P, C>::type {};

    template<typename M, typename C, typename... Ps>
    struct make_meta_pattern<M, C, nsm::list<Ps...> >
    {
      using type = pattern_< idx<M,C,Ps>::value... >;
    };

    template<typename M, typename T>
    struct meta_pattern
    {
      using card = cardinal_of<T>;
      using type = typename make_meta_pattern<M, card, nsm::range<int,0,card::value>>::type;
    };

    // -----------------------------------------------------------------------------------------------
    // take a constexpr function and build a pattern
    template<int (*M)(int,int), typename C, typename L> struct make_const_pattern;

    template<int (*M)(int,int), typename C, typename... Ps>
    struct make_const_pattern<M, C, nsm::list<Ps...> >
    {
      using type = pattern_< M(Ps::value,C::value)... >;
    };

    template<int (*M)(int,int), typename T>
    struct meta_pattern<pattern<M>,T>
    {
      using card = cardinal_of<T>;
      using type = typename make_const_pattern<M, card, nsm::range<int,0,card::value>>::type;
    };
  } }
}

namespace boost { namespace dispatch
{
  namespace ext
  {
    template<typename Ps,typename Origin, typename Enable = void> struct pattern_hierarchy
    {
      using type = Ps;
    };
  }

  // ---------------------------------------------------------------------------------------------
  // Give a proper hierarchy to identify pattern
  template<int... Ps,typename Origin>
  struct  hierarchy_of < boost::simd::detail::pattern_<Ps...>,Origin>
        : ext::pattern_hierarchy<boost::simd::detail::pattern_<Ps...>,Origin>
  {};
} }

#endif
