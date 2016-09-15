//==================================================================================================
/*!
  @file
  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_COMMON_SCALAR_FUNCTION_IS_NORMAL_HPP_INCLUDED
#define BOOST_SIMD_ARCH_COMMON_SCALAR_FUNCTION_IS_NORMAL_HPP_INCLUDED

#include <boost/simd/function/is_nez.hpp>
#include <boost/simd/function/is_not_denormal.hpp>
#include <boost/simd/function/is_finite.hpp>
#include <boost/simd/function/std.hpp>
#include <boost/simd/detail/dispatch/function/overload.hpp>
#include <boost/config.hpp>
#include <cmath>

namespace boost { namespace simd { namespace ext
{
  namespace bd = boost::dispatch;
  namespace bs = boost::simd;
  BOOST_DISPATCH_OVERLOAD ( is_normal_
                          , (typename A0)
                          , bd::cpu_
                          , bd::scalar_< bd::bool_<A0> >
                          )
  {
    BOOST_FORCEINLINE bool operator() (A0 a0 ) const BOOST_NOEXCEPT
    {
      return a0;
    }
  };
  BOOST_DISPATCH_OVERLOAD ( is_normal_
                          , (typename A0)
                          , bd::cpu_
                          , bd::scalar_< bd::fundamental_<A0> >
                          )
  {
    BOOST_FORCEINLINE bs::as_logical_t<A0> operator() ( A0 a0) const BOOST_NOEXCEPT
    {
      return is_nez(a0);
    }
  };
  BOOST_DISPATCH_OVERLOAD ( is_normal_
                          , (typename A0)
                          , bd::cpu_
                          , bd::scalar_< bd::floating_<A0> >
                          )
  {
    BOOST_FORCEINLINE  bs::as_logical_t<A0> operator() ( A0 a0) const BOOST_NOEXCEPT
    {
      return   is_finite(a0)&&is_nez(a0)&&is_not_denormal(a0);
    }
  };
  BOOST_DISPATCH_OVERLOAD ( is_normal_
                          , (typename A0)
                          , bd::cpu_
                          , bs::std_tag
                          , bd::scalar_< bd::floating_<A0> >
                          )
  {
    BOOST_FORCEINLINE logical<A0> operator() (const std_tag &, A0 a0) const BOOST_NOEXCEPT
    {
      return std::isnormal(a0);
    }
  };
  BOOST_DISPATCH_OVERLOAD ( is_normal_
                          , (typename A0)
                          , bd::cpu_
                          , bs::std_tag
                          , bd::scalar_< bd::integer_<A0> >
                          )
  {
    BOOST_FORCEINLINE logical<A0> operator() (const std_tag &, A0 a0) const BOOST_NOEXCEPT
    {
      return {a0 != 0};
    }
  };
} } }


#endif
