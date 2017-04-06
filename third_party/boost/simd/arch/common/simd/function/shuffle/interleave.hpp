//==================================================================================================
/**
  Copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
**/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_COMMON_SIMD_FUNCTION_SHUFFLE_INTERLEAVE_HPP_INCLUDED
#define BOOST_SIMD_ARCH_COMMON_SIMD_FUNCTION_SHUFFLE_INTERLEAVE_HPP_INCLUDED

#include <boost/simd/detail/overload.hpp>
#include <boost/simd/function/interleave_second.hpp>
#include <boost/simd/function/interleave_first.hpp>
#include <boost/simd/function/interleave_even.hpp>
#include <boost/simd/function/interleave_odd.hpp>
#include <boost/simd/detail/nsm.hpp>
#include <boost/simd/detail/shuffle.hpp>

namespace boost { namespace simd
{
  // -----------------------------------------------------------------------------------------------
  // Interleaving pattern hierarchy
  template<int OE, bool D, bool HZ, typename P>
  struct interleave_pattern : P
  {
    using parent = P;
  };

  namespace detail
  {
    namespace tt = nsm::type_traits;

    // ---------------------------------------------------------------------------------------------
    // Generate various interleave_* based pattern for later comparison
    template<int C, int Base, bool Direct, bool HasZero, typename R>
    struct make_oepattern;

    template<int C, int Base, bool Direct, bool HasZero, typename R>
    struct make_fspattern;

    template<int C, int Base, bool Direct, bool HasZero, typename... N>
    struct make_oepattern<C, Base, Direct, HasZero, nsm::list<N...>>
    {
      template<int I>
      using a_value = tt::integral_constant<int, Direct ? Base+I : (HasZero ? -1 : Base+I+C)>;

      template<int I>
      using b_value = tt::integral_constant<int, Direct ? (HasZero ? -1 : Base+I+C-1) : Base+I-1>;

      using type = boost::simd::detail::pattern_< ( N::value%2  ? b_value<N::value>::value
                                                                : a_value<N::value>::value
                                                  )...
                                                >;
    };

    template<int C, int Base, bool Direct, bool HasZero, typename... N>
    struct make_fspattern<C, Base, Direct, HasZero, nsm::list<N...>>
    {
      template<int I>
      using f_value = tt::integral_constant
                                          < int
                                          , Direct  ? ( (I%2) ? (HasZero ? -1 : (I%2)*C+I/2)
                                                              : (I%2)*C+I/2
                                                      )
                                                    : ( (I%2) ? ((I+1)%2)*C+I/2
                                                              : (HasZero ? -1 : ((I+1)%2)*C+I/2)
                                                      )
                                          >;

      template<int I>
      using s_value = tt::integral_constant
                                      < int
                                      , Direct  ? ( (I%2) ? (HasZero ? -1 : ((I%2)*C+I/2)+C/2)
                                                          : ((I%2)*C+I/2)+C/2
                                                  )
                                                : ( (I%2) ? ((I+1)%2)*C+I/2+C/2
                                                          : (HasZero  ? -1 : ((I+1)%2)*C+I/2+C/2)
                                                  )
                                      >;

      using type = boost::simd::detail::pattern_< ( Base  ? s_value<N::value>::value
                                                          : f_value<N::value>::value
                                                  )...
                                                >;
    };

    // ---------------------------------------------------------------------------------------------
    // Find the correct interleaving pattern among all possible
    template<int C, typename EntryPattern>
    struct which_interleave
    {
      template<int OE, bool D, bool HZ>
      using p_ = nsm::pair< typename make_oepattern<C,OE,D,HZ,nsm::range<int,0,C>>::type
                              , interleave_pattern<OE,D,HZ,EntryPattern>
                              >;
      template<int OE, bool D, bool HZ>
      using r_ = nsm::pair< typename make_oepattern<0,OE,D,HZ,nsm::range<int,0,C>>::type
                              , interleave_pattern<OE,D,HZ,EntryPattern>
                              >;

      template<int OE, bool D, bool HZ>
      using q_ = nsm::pair< typename make_fspattern<C,OE,D,HZ,nsm::range<int,0,C>>::type
                              , interleave_pattern<2+OE,D,HZ,EntryPattern>
                              >;

      using omap = nsm::map < // Odd/Even patterns
                                  p_<0,true ,false>, p_<0,true ,true >
                                , p_<0,false,false>, p_<0,false,true >
                                , p_<1,true ,false>, p_<1,true ,true >
                                , p_<1,false,false>, p_<1,false,true >
                                , r_<0,true ,false>, r_<1,true ,false>
                                >;

      using fmap = nsm::map < // First/Second patterns
                                  q_<0,true ,false>, q_<0,true ,true >
                                , q_<0,false,false>, q_<0,false,true >
                                , q_<1,true ,false>, q_<1,true ,true >
                                , q_<1,false,false>, q_<1,false,true >
                                >;

      using otype = nsm::at<omap,EntryPattern>;
      using ftype = nsm::at<fmap,EntryPattern>;
      using type  = typename std::conditional < std::is_same<nsm::no_such_type_,otype>::value
                                              , ftype
                                              , otype
                                              >::type;
    };

    // ---------------------------------------------------------------------------------------------
    // Check if pattern performs some interleaving operations
    template<int... Ps>
    struct  is_interleave
          : nsm::bool_< !tt::is_same
                                  < nsm::no_such_type_
                                  , typename which_interleave < sizeof...(Ps)
                                                              , boost::simd::detail::pattern_<Ps...>
                                                              >::type
                                  >::value
                          >
    {
      using mode = typename which_interleave< sizeof...(Ps)
                                            , boost::simd::detail::pattern_<Ps...>
                                            >::type;
    };

    // Do not step on other hierarchies
    template<int P0>          struct is_interleave<P0>    : tt::false_type {};
    template<int P0, int P1>  struct is_interleave<P0,P1> : tt::false_type {};
  }

  // -----------------------------------------------------------------------------------------------
  // Interleave matcher
  struct interleave_shuffle
  {
    // All interleave_even
    template<typename T, typename P> static BOOST_FORCEINLINE
    T process(T const& a0, T const& a1, interleave_pattern<0,true,false,P> const&)
    {
      return interleave_even(a0,a1);
    }

    template<typename T, typename P> static BOOST_FORCEINLINE
    T process(T const& a0, interleave_pattern<0,true,false,P> const&)
    {
      return interleave_even(a0,a0);
    }

    template<typename T, typename P> static BOOST_FORCEINLINE
    T process(T const& a0, T const& a1, interleave_pattern<0,false,false,P> const&)
    {
      return interleave_even(a1,a0);
    }

    template<typename T, typename P> static BOOST_FORCEINLINE
    T process(T const& a0, interleave_pattern<0,true,true,P> const&)
    {
      return interleave_even(a0,Zero<T>());
    }

    template<typename T, typename P> static BOOST_FORCEINLINE
    T process(T const& a0, interleave_pattern<0,false,true,P> const&)
    {
      return interleave_even(Zero<T>(),a0);
    }

    // All interleave_odd
    template<typename T, typename P> static BOOST_FORCEINLINE
    T process(T const& a0, T const& a1, interleave_pattern<1,true,false,P> const&)
    {
      return interleave_odd(a0,a1);
    }

    template<typename T, typename P> static BOOST_FORCEINLINE
    T process(T const& a0, interleave_pattern<1,true,false,P> const&)
    {
      return interleave_odd(a0,a0);
    }

    template<typename T, typename P> static BOOST_FORCEINLINE
    T process(T const& a0, T const& a1, interleave_pattern<1,false,false,P> const&)
    {
      return interleave_odd(a1,a0);
    }

    template<typename T, typename P> static BOOST_FORCEINLINE
    T process(T const& a0, interleave_pattern<1,true,true,P> const&)
    {
      return interleave_odd(a0,Zero<T>());
    }

    template<typename T, typename P> static BOOST_FORCEINLINE
    T process(T const& a0, interleave_pattern<1,false,true,P> const&)
    {
      return interleave_odd(Zero<T>(),a0);
    }

    // All interleave_first
    template<typename T, typename P> static BOOST_FORCEINLINE
    T process(T const& a0, T const& a1, interleave_pattern<2,true,false,P> const&)
    {
      return interleave_first(a0,a1);
    }

    template<typename T, typename P> static BOOST_FORCEINLINE
    T process(T const& a0, T const& a1, interleave_pattern<2,false,false,P> const&)
    {
      return interleave_first(a1,a0);
    }

    template<typename T, typename P> static BOOST_FORCEINLINE
    T process(T const& a0, interleave_pattern<2,true,true,P> const&)
    {
      return interleave_first(a0,Zero<T>());
    }

    template<typename T, typename P> static BOOST_FORCEINLINE
    T process(T const& a0, interleave_pattern<2,false,true,P> const&)
    {
      return interleave_first(Zero<T>(),a0);
    }

    // All interleave_second
    template<typename T, typename P> static BOOST_FORCEINLINE
    T process(T const& a0, T const& a1, interleave_pattern<3,true,false,P> const&)
    {
      return interleave_second(a0,a1);
    }

    template<typename T, typename P> static BOOST_FORCEINLINE
    T process(T const& a0, T const& a1, interleave_pattern<3,false,false,P> const&)
    {
      return interleave_second(a1,a0);
    }

    template<typename T, typename P> static BOOST_FORCEINLINE
    T process(T const& a0, interleave_pattern<3,true,true,P> const&)
    {
      return interleave_second(a0,Zero<T>());
    }

    template<typename T, typename P> static BOOST_FORCEINLINE
    T process(T const& a0, interleave_pattern<3,false,true,P> const&)
    {
      return interleave_second(Zero<T>(),a0);
    }
  };
} }

// -------------------------------------------------------------------------------------------------
// Hierarchize interleaving patterns
namespace boost { namespace dispatch { namespace ext
{
  // interleave patterns
  template<int... Ps,typename Origin>
  struct pattern_hierarchy< boost::simd::detail::pattern_<Ps...>,Origin
                          , typename std::enable_if<simd::detail::is_interleave<Ps...>::value>::type
                          >
  {
    using type = typename simd::detail::is_interleave<Ps...>::mode;
  };
} } }

#endif
