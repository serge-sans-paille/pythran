//==================================================================================================
/**
  Copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
**/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_DETAIL_SLIDE_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_DETAIL_SLIDE_HPP_INCLUDED

#include <boost/simd/config.hpp>
#include <boost/simd/constant/zero.hpp>
#include <boost/simd/detail/nsm.hpp>

namespace boost { namespace simd { namespace detail
{
  namespace tt = nsm::type_traits;

  template<typename T,int N, int Card, bool isFwd> struct slider;

  // We add a small trampoline so MSVC is happy with the cardinal_of call
  template<typename T,int N, typename Card, bool isFwd>
  struct slider_ : slider<T,N,Card::value,isFwd>
  {};

  // General case dispatch to arch-specific implementation
  template<typename T,int N, int Card, bool isFwd> struct slider
  {
    static BOOST_FORCEINLINE auto call(T const& a0, T const& a1)
    BOOST_NOEXCEPT_DECLTYPE_BODY(detail::slide(a0,a1,tt::integral_constant<int, N>{}));

    static BOOST_FORCEINLINE auto call(T const& a0)
    BOOST_NOEXCEPT_DECLTYPE_BODY(detail::slide(a0,tt::integral_constant<int, N>{}));
  };

  // Backward slide slides the swapped inputs by the complement of the offset except for
  // unary case which may be optimized by the architecture except for slide<-Card>
  template<typename T,int N, int Card> struct slider<T,N,Card,false>
  {
    //static BOOST_FORCEINLINE auto call(T const& a0, T const& a1)
    //BOOST_NOEXCEPT_DECLTYPE_BODY(detail::slide(a1,a0,tt::integral_constant<int, Card+N>{}));

    static BOOST_FORCEINLINE auto call(T const& a0, tt::false_type const&)
    BOOST_NOEXCEPT_DECLTYPE_BODY(detail::slide(a0,tt::integral_constant<int, N>{}));

    static BOOST_FORCEINLINE T call(T const&, tt::true_type const&)
    { return Zero<T>(); }

    static BOOST_FORCEINLINE auto call(T const& a0)
    BOOST_NOEXCEPT_DECLTYPE_BODY( call(a0, nsm::bool_<(N==-Card)>{}) );

    static BOOST_FORCEINLINE auto call(T const& a0, T const& a1, tt::false_type const&)
    BOOST_NOEXCEPT_DECLTYPE_BODY(detail::slide(a1, a0, tt::integral_constant<int, Card+N>{}));

    static BOOST_FORCEINLINE T call(T const&, T const& a1, tt::true_type const&)
    { return a1; }

    static BOOST_FORCEINLINE auto call(T const& a0, T const& a1)
    BOOST_NOEXCEPT_DECLTYPE_BODY(call(a0, a1, nsm::bool_<(N == -Card)>{}));
  };

  // Scalar-like value returns a0 in backward mode
  template<typename T,int N> struct slider<T,N,1,false>
  {
    static BOOST_FORCEINLINE T call(T const&, T const& a1)  BOOST_NOEXCEPT { return a1;        }
    static BOOST_FORCEINLINE T call(T const&)               BOOST_NOEXCEPT { return Zero<T>(); }
  };

  // Sliding by 0 is identity
  template<typename T, int Card> struct slider<T,0,Card,true>
  {
    static BOOST_FORCEINLINE T call(T const& a0, T const&)  BOOST_NOEXCEPT  { return a0; }
    static BOOST_FORCEINLINE T call(T const& a0)            BOOST_NOEXCEPT  { return a0; }
  };

  // Sliding by cardinal is the 2nd parameter (or zero if lack thereof)
  template<int N,typename T> struct slider<T, N, N, true>
  {
    static BOOST_FORCEINLINE T call(T const&, T const& a1)  BOOST_NOEXCEPT  { return a1;        }
    static BOOST_FORCEINLINE T call(T const& )              BOOST_NOEXCEPT  { return Zero<T>(); }
  };
} } }

#endif
