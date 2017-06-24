//==================================================================================================
/**
  Copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
**/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_COMMON_SIMD_FUNCTION_SHUFFLE_SLIDE_HPP_INCLUDED
#define BOOST_SIMD_ARCH_COMMON_SIMD_FUNCTION_SHUFFLE_SLIDE_HPP_INCLUDED

#include <boost/simd/detail/overload.hpp>
#include <boost/simd/detail/shuffle.hpp>
#include <boost/simd/detail/nsm.hpp>
#include <boost/simd/function/slide.hpp>

namespace boost { namespace simd
{
  namespace tt = nsm::type_traits;

  // -----------------------------------------------------------------------------------------------
  // Repeat patterns hierarchy
  template<int Offset, typename P> struct slide_pattern : P
  {
    using parent = P;
  };

  namespace detail
  {
    // ---------------------------------------------------------------------------------------------
    // Generate a bunch of -1
    template<typename L> struct make_zero;

    template<typename... T>
    struct make_zero<nsm::list<T...>>
    {
      using type = nsm::integral_list<int, (sizeof(T)!=0?-1:1)...>;
    };

    // ---------------------------------------------------------------------------------------------
    // Generate a forward slide pattern of index N
    template<int N, int Sz> struct make_forward_slide
    {
      using type = nsm::append< nsm::range<int,N,Sz>
                                  , typename make_zero< nsm::range<int,0,N> >::type
                                  >;
    };

    // ---------------------------------------------------------------------------------------------
    // Generate a backward slide pattern of index N
    template<int N, int Sz>
    struct make_backward_slide
    {
      using type = nsm::append< typename make_zero< nsm::range<int,0,N> >::type
                                  , nsm::range<int,0,(Sz-N)>
                                  >;
    };

    // ---------------------------------------------------------------------------------------------
    // Generate a relative slide pattern for all indexes
    template<typename S, typename L> struct make_slides;

    template<typename S, typename... T>
    struct make_slides<S,nsm::list<T...>>
    {
      template<int X, bool Fwd> struct do_          : make_forward_slide<X,S::value>    {};
      template<int X>           struct do_<X,false> : make_backward_slide<-X,S::value>  {};

       using type = nsm::list<typename do_<T::value,(T::value>0)>::type...>;
    };

    // ---------------------------------------------------------------------------------------------
    // Locate proper sliding index
    template<int N, int... Ps> struct find_slide
    {
      using checks = typename make_slides < tt::integral_constant<int,sizeof...(Ps)>
                                          , nsm::range<int,-(N-1),N>
                                          >::type;

      using found = nsm::find < checks
                                  , std::is_same<nsm::_1,nsm::integral_list<int,Ps...>>
                                  >;

      using idx   = tt::integral_constant<int, N-int(nsm::size<found>::value)>;

      using type = typename std::conditional< idx::value && (idx::value<N)
                                            , slide_pattern<idx::value,pattern_<Ps...>>
                                            , nsm::no_such_type_
                                            >::type;
    };

    // ---------------------------------------------------------------------------------------------
    // Is this a slide pattern ?
    template<int... Ps>
    struct is_slide : nsm::bool_< !std::is_same < nsm::no_such_type_
                                                    , typename find_slide<sizeof...(Ps),Ps...>::type
                                                    >::value
                                    >
    {
      using mode = typename find_slide<sizeof...(Ps),Ps...>::type;
    };

    // Don't overlap with other hierarchies
    template<int N, int P0> struct is_slide<N,P0>     : tt::false_type {};
  }

  // -----------------------------------------------------------------------------------------------
  // Repeat matcher
  struct slide_shuffle
  {
    // Unary slide
    template<typename T, int N, typename P>
    static BOOST_FORCEINLINE T process(T const& a0, slide_pattern<N,P> const&)
    {
      return slide<N>(a0);
    }
  };
} }

// -------------------------------------------------------------------------------------------------
// Hierarchize slide patterns
namespace boost { namespace dispatch { namespace ext
{
  // slide patterns
  template<int... Ps,typename Origin>
  struct pattern_hierarchy< boost::simd::detail::pattern_<Ps...>,Origin
                          , typename std::enable_if<simd::detail::is_slide<Ps...>::value>::type
                          >
  {
    using type = typename simd::detail::is_slide<Ps...>::mode;
  };
} } }

#endif
