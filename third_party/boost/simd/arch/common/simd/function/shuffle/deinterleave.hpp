//==================================================================================================
/**
  Copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
**/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_COMMON_SIMD_FUNCTION_SHUFFLE_DEINTERLEAVE_HPP_INCLUDED
#define BOOST_SIMD_ARCH_COMMON_SIMD_FUNCTION_SHUFFLE_DEINTERLEAVE_HPP_INCLUDED

#include <boost/simd/function/deinterleave_first.hpp>
#include <boost/simd/function/deinterleave_second.hpp>
#include <boost/simd/detail/nsm.hpp>
#include <boost/simd/detail/shuffle.hpp>

namespace boost { namespace simd
{
  // -----------------------------------------------------------------------------------------------
  // Deinterleaving pattern hierarchy
  template<int FirstSecond, bool HasZero, bool Forward, typename P>
  struct deinterleave_pattern : P
  {
    using parent = P;
  };

  namespace detail
  {
    namespace tt = nsm::type_traits;

    // ---------------------------------------------------------------------------------------------
    // generate pattern for deinterleaving shuffle
    template<int I, bool SZ, typename Range> struct deinter_;

    template<int I, bool SZ, typename... Ps>
    struct deinter_<I,SZ, nsm::list<Ps...>>
    {
      using sz    = tt::integral_constant<int,sizeof...(Ps)/2>;
      using type  = detail::pattern_< ((SZ && Ps::value>=sz::value) ? -1 :  2*Ps::value+I)...>;
    };

    template<int I, bool SZ, typename Range>
    using deinter_t = typename deinter_<I,SZ,Range>::type;

    // ---------------------------------------------------------------------------------------------
    // Generate proper deinterleave_pattern hierarchy from a pattern
    template<int... Ps> struct find_deinterleave
    {
      using ref = boost::simd::detail::pattern_<Ps...>;
      using sz  = tt::integral_constant<int,sizeof...(Ps)/2>;
      using lo  = nsm::range<int,0,sz::value>;
      using hi  = nsm::range<int,sz::value,2*sz::value>;
      using fwd = nsm::append<lo,hi>;
      using bwd = nsm::append<hi,lo>;

      template<int FS, bool SZ, typename Rng>
      using case_ = nsm::pair < deinter_t<FS,SZ,Rng>
                                  , deinterleave_pattern<FS,SZ,std::is_same<Rng,fwd>::value,ref>
                                  >;

      using dmap  = nsm::map
                  < case_<0,false,fwd>, case_<0,true ,fwd>, case_<0,false,bwd>, case_<0,true ,bwd>
                  , case_<1,false,fwd>, case_<1,true ,fwd>, case_<1,false,bwd>, case_<1,true ,bwd>
                  >;

      using type = nsm::at<dmap,ref>;
    };

    // MSVC provision - MSVC seems to eagerly instantiate find_deinterleave even for cardinal-1
    template<int P0> struct find_deinterleave<P0>
    {
      using type = nsm::no_such_type_;
    };

    // ---------------------------------------------------------------------------------------------
    // Check if pattern performs some deinterleaving operations (0=first,1=second)
    template<int... Ps>
    struct  is_deinterleave
          : nsm::bool_<   !std::is_same < nsm::no_such_type_
                                            , typename find_deinterleave<Ps...>::type
                                            >::value
                          >
    {
      using mode = typename find_deinterleave<Ps...>::type;
    };

    template<int P0>         struct is_deinterleave<P0>    : tt::false_type {};
    template<int P0, int P1> struct is_deinterleave<P0,P1> : tt::false_type {};
  }

  // -----------------------------------------------------------------------------------------------
  // Deinterleave matcher
  struct deinterleave_shuffle
  {
    // All deinterleave_first
    template<typename T, typename P> static BOOST_FORCEINLINE
    T process(T const& a0, T const& a1, deinterleave_pattern<0,false,true,P> const&)
    {
      return deinterleave_first(a0,a1);
    }

    template<typename T, typename P> static BOOST_FORCEINLINE
    T process(T const& a0, T const& a1, deinterleave_pattern<0,false,false,P> const&)
    {
      return deinterleave_first(a1,a0);
    }

    template<typename T, typename P> static BOOST_FORCEINLINE
    T process(T const& a0, deinterleave_pattern<0,true,false,P> const&)
    {
      return deinterleave_first(Zero<T>(),a0);
    }

    template<typename T, typename P> static BOOST_FORCEINLINE
    T process(T const& a0, deinterleave_pattern<0,true,true,P> const&)
    {
      return deinterleave_first(a0,Zero<T>());
    }

    // All deinterleave_second
    template<typename T, typename P>
    static BOOST_FORCEINLINE
    T process(T const& a0, T const& a1, deinterleave_pattern<1,false,true,P> const&)
    {
      return deinterleave_second(a0,a1);
    }

    template<typename T, typename P>
    static BOOST_FORCEINLINE
    T process(T const& a0, T const& a1, deinterleave_pattern<1,false,false,P> const&)
    {
      return deinterleave_second(a1,a0);
    }

    template<typename T, typename P> static BOOST_FORCEINLINE
    T process(T const& a0, deinterleave_pattern<1,true,true,P> const&)
    {
      return deinterleave_second(a0,Zero<T>());
    }

    template<typename T, typename P> static BOOST_FORCEINLINE
    T process(T const& a0, deinterleave_pattern<1,true,false,P> const&)
    {
      return deinterleave_second(Zero<T>(),a0);
    }
  };
} }

namespace boost { namespace dispatch { namespace ext
{
  // -----------------------------------------------------------------------------------------------
  // Hierarchize deinterleaving patterns
  template<int... Ps,typename Origin>
  struct pattern_hierarchy< boost::simd::detail::pattern_<Ps...>,Origin
                          , typename std::enable_if < simd::detail
                                                          ::is_deinterleave<Ps...>::type::value
                                                    >::type
                          >
  {
    using type = typename simd::detail::is_deinterleave<Ps...>::mode;
  };
} } }

#endif
