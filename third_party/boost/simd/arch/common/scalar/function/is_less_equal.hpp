//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_COMMON_SCALAR_FUNCTION_IS_LESS_EQUAL_HPP_INCLUDED
#define BOOST_SIMD_ARCH_COMMON_SCALAR_FUNCTION_IS_LESS_EQUAL_HPP_INCLUDED
#include <boost/simd/function/std.hpp>

#include <boost/simd/logical.hpp>
#include <boost/simd/detail/dispatch/adapted/std/integral_constant.hpp>
#include <boost/simd/detail/dispatch/function/overload.hpp>
#include <boost/config.hpp>
#include <cmath>

namespace boost { namespace simd { namespace ext
{
  namespace bd = boost::dispatch;
  namespace bs = boost::simd;
  BOOST_DISPATCH_OVERLOAD ( is_less_equal_
                          , (typename A0)
                          , bd::cpu_
                          , bd::scalar_< bd::bool_<A0> >
                          , bd::scalar_< bd::bool_<A0> >
                          )
  {
    BOOST_FORCEINLINE bool operator() ( A0 a0, A0 a1) const BOOST_NOEXCEPT
    {
      return (a0 <=  a1);
    }
  };
  BOOST_DISPATCH_OVERLOAD ( is_less_equal_
                          , (typename A0)
                          , bd::cpu_
                          , bd::scalar_< bd::fundamental_<A0> >
                          , bd::scalar_< bd::fundamental_<A0> >
                          )
  {
    BOOST_FORCEINLINE logical<A0> operator() ( A0 a0, A0 a1) const BOOST_NOEXCEPT
    {
      return (a0 <= a1);
    }
  };
  BOOST_DISPATCH_OVERLOAD ( is_less_equal_
                          , (typename A0, typename A1)
                          , bd::cpu_
                          , bd::scalar_< bd::fundamental_<A0> >
                          , bd::constant_< bd::fundamental_<A1> >
                          )
  {
    BOOST_FORCEINLINE logical<A0> operator() ( A0 a0, A1 const&) const BOOST_NOEXCEPT
    {
      return (a0 <= A1::value);
    }
  };
  BOOST_DISPATCH_OVERLOAD ( is_less_equal_
                          , (typename A0, typename A1)
                          , bd::cpu_
                          , bd::constant_< bd::fundamental_<A0> >
                          , bd::scalar_< bd::fundamental_<A1> >
                          )
  {
    BOOST_FORCEINLINE logical<A1> operator() ( A0, A1 a1) const BOOST_NOEXCEPT
    {
      return (A0::value <= a1);
    }
  };
  BOOST_DISPATCH_OVERLOAD ( is_less_equal_
                          , (typename A0)
                          , bd::cpu_
                          , bd::constant_< bd::fundamental_<A0> >
                          , bd::constant_< bd::fundamental_<A0> >
                          )
  {
    BOOST_FORCEINLINE logical<typename A0::value_type> operator() ( A0 , A0 ) const BOOST_NOEXCEPT
    {
      return {true};
    }
  };
  BOOST_DISPATCH_OVERLOAD ( is_less_equal_
                          , (typename T)
                          ,  bd::cpu_
                          ,  bd::scalar_<bd::unspecified_<T>>
                          ,  bd::scalar_<bd::unspecified_<T>>
                          )
  {
    BOOST_FORCEINLINE auto operator()(T const& a, T const& b) const BOOST_NOEXCEPT -> decltype(a <= b)
    {
      return a <= b;
    }
  };
} } }

#endif
