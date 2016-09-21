//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_COMMON_SCALAR_FUNCTION_IF_ZERO_ELSE_HPP_INCLUDED
#define BOOST_SIMD_ARCH_COMMON_SCALAR_FUNCTION_IF_ZERO_ELSE_HPP_INCLUDED

#include <boost/simd/constant/zero.hpp>
#include <boost/simd/function/is_eqz.hpp>
#include <boost/simd/logical.hpp>
#include <boost/simd/detail/dispatch/function/overload.hpp>
#include <boost/config.hpp>

namespace boost { namespace simd { namespace ext
{
  namespace bd = boost::dispatch;
  BOOST_DISPATCH_OVERLOAD ( if_zero_else_
                          , (typename A0, typename A1)
                          , bd::cpu_
                          , bd::scalar_< logical_<A0> >
                          , bd::scalar_< bd::unspecified_<A1> >
                          )
  {
    BOOST_FORCEINLINE A1 operator() ( A0 a0, A1 const& a1) const BOOST_NOEXCEPT
    {
      return is_eqz(a0) ? a1 : Zero<A1>();
    }
  };

  BOOST_DISPATCH_OVERLOAD ( if_zero_else_
                          , (typename A0, typename A1)
                          , bd::cpu_
                          , bd::scalar_< bd::arithmetic_<A0> >
                          , bd::scalar_< bd::arithmetic_<A1> >
                          )
  {
    BOOST_FORCEINLINE A1 operator() ( A0 a0, A1  a1) const BOOST_NOEXCEPT
    {
      return a0 ? Zero<A1>() : a1;
    }
  };

  BOOST_DISPATCH_OVERLOAD ( if_zero_else_
                          , (typename A0)
                          , bd::cpu_
                          , bd::scalar_< bd::bool_<A0> >
                          , bd::scalar_< bd::bool_<A0> >
                          )
  {
    BOOST_FORCEINLINE bool operator() ( A0 a0, A0  a1) const BOOST_NOEXCEPT
    {
      return a0 ? false : a1;
    }
  };
} } }


#endif
