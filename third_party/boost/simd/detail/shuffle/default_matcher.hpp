//==================================================================================================
/**
  Copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
**/
//==================================================================================================
#ifndef BOOST_SIMD_DETAIL_SHUFFLE_DEFAULT_MATCHER_HPP_INCLUDED
#define BOOST_SIMD_DETAIL_SHUFFLE_DEFAULT_MATCHER_HPP_INCLUDED

#include <boost/simd/config.hpp>
#include <boost/simd/detail/nsm.hpp>
#include <boost/simd/function/extract.hpp>
#include <boost/simd/function/combine.hpp>
#include <boost/simd/function/slice.hpp>
#include <boost/simd/arch/common/simd/function/shuffle/identity.hpp>
#include <boost/simd/arch/common/simd/function/shuffle/broadcast.hpp>

namespace boost { namespace simd { namespace detail
{
  namespace tt = nsm::type_traits;

  // -----------------------------------------------------------------------------------------------
  // Half-permutation snatcher
  template<bool isUpper, int... Ps> struct half_
  {
    using perm = nsm::integral_list<int,Ps...>;
    template<typename I, typename C>
    struct apply : nsm::at_c < perm, isUpper ? I::value+C::value : I::value>
    {};
  };

  // -----------------------------------------------------------------------------------------------
  // Default matcher - don't do anything special but shuffle manually
  struct  default_matcher
        : identity_shuffle
        , broadcast_shuffle
  {
    // please, trigger on identity & broadcast pattern to do the correct thing
    using identity_shuffle::process;
    using broadcast_shuffle::process;

    // Unary helpers
    template<typename T, int N> BOOST_FORCEINLINE static typename T::value_type
    fill_( const T& a0, tt::integral_constant<int,N> const& )
    {
      return boost::simd::extract<N>(a0);
    }

    template<typename T> BOOST_FORCEINLINE static typename T::value_type
    fill_(const T&, tt::integral_constant<int,-1> const&)
    {
      return typename T::value_type{0};
    }

    // Unary permutation handler
    template<typename T, int... P>
    static BOOST_FORCEINLINE T process(T const& a0, pattern_<P...> const& p)
    {
      return process(a0, p, typename T::storage_kind{});
    }

    template<typename T, int... P>
    static BOOST_FORCEINLINE T process(T const& a0, pattern_<P...> const&, aggregate_storage const&)
    {
      // Aggregate storage has a chance to be the combination of two regular shuffles
      auto s = slice(a0);
      return combine( shuffle<half_<false,P...>>(s[0],s[1])
                    , shuffle<half_<true ,P...>>(s[0],s[1])
                    );
    }

    template<typename K, typename T, int... P>
    static BOOST_FORCEINLINE T process(T const& a0, pattern_<P...> const&, K const&)
    { return T( fill_ (a0 , tt::integral_constant<int,P>{} )... );
    }

    // Binary permutation handler
    template<typename T, int... P>
    static BOOST_FORCEINLINE T process(T const& a0, T const& a1, pattern_<P...> const&)
    {
      return T( fill_ (a0 ,a1 , tt::integral_constant<int,P>{}
                              , nsm::bool_<(P<T::static_size)>{}
                      )...
              );
    }

    // Binary helpers
    template<typename T, int N>
    BOOST_FORCEINLINE static typename T::value_type
    fill_ ( const T& a0, const T&
          , tt::integral_constant<int,N> const&, tt::true_type const&
          )
    {
      return  boost::simd::extract<N>(a0);
    }

    template<typename T>
    BOOST_FORCEINLINE static typename T::value_type
    fill_ ( const T&, const T&
          , tt::integral_constant<int,-1> const&, tt::true_type const&
          )
    {
      return 0;
    }

    template<typename T, int N>
    BOOST_FORCEINLINE static typename T::value_type
    fill_ (const T&, const T & a1
          , tt::integral_constant<int,N> const&, tt::false_type const&
          )
    {
      return  boost::simd::extract<N-T::static_size>(a1);
    }
  };
} } }

#endif
