//==================================================================================================
/*!
  @file
  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_COMMON_SCALAR_FUNCTION_IS_LESSGREATER_HPP_INCLUDED
#define BOOST_SIMD_ARCH_COMMON_SCALAR_FUNCTION_IS_LESSGREATER_HPP_INCLUDED

#include <boost/simd/function/std.hpp>
#include <boost/config.hpp>
#include <boost/simd/function/is_ord.hpp>
#include <boost/simd/logical.hpp>
#include <boost/simd/detail/dispatch/function/overload.hpp>
#include <cmath>

namespace boost { namespace simd { namespace ext
{
  namespace bd = boost::dispatch;
  namespace bs = boost::simd;
  BOOST_DISPATCH_OVERLOAD ( is_lessgreater_
                          , (typename A0)
                          , bd::cpu_
                          , bd::scalar_< bd::bool_<A0> >
                          , bd::scalar_< bd::bool_<A0> >
                          )
  {
    BOOST_FORCEINLINE bool operator() ( A0 a0 , A0 a1 ) const BOOST_NOEXCEPT
    {
      return  a0!=a1;
    }
  };
  BOOST_DISPATCH_OVERLOAD ( is_lessgreater_
                          , (typename A0)
                          , bd::cpu_
                          , bd::scalar_< bd::arithmetic_<A0> >
                          , bd::scalar_< bd::arithmetic_<A0> >
                          )
  {
    BOOST_FORCEINLINE logical<A0> operator() ( A0 a0 , A0 a1 ) const BOOST_NOEXCEPT
    {
      return a0!=a1;
    }
  };
  BOOST_DISPATCH_OVERLOAD ( is_lessgreater_
                          , (typename A0)
                          , bd::cpu_
                          , bd::scalar_< bd::floating_<A0> >
                          , bd::scalar_< bd::floating_<A0> >
                          )
  {
    BOOST_FORCEINLINE logical<A0> operator() ( A0 a0, A0 a1) const BOOST_NOEXCEPT
    {
      return is_ord(a0,a1)&&(a0!=a1);
    }
  };

  BOOST_DISPATCH_OVERLOAD ( is_lessgreater_
                          , (typename A0)
                          , bd::cpu_
                          , bs::std_tag
                          , bd::scalar_< bd::arithmetic_<A0> >
                          , bd::scalar_< bd::arithmetic_<A0> >
                          )
  {
    BOOST_FORCEINLINE logical<A0> operator() (const std_tag &,  A0 a0, A0 a1
                                             ) const BOOST_NOEXCEPT
    {
      return std::islessgreater(a0, a1);
    }
  };


} } }


#endif
