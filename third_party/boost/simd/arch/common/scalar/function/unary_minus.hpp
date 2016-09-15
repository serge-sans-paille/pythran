//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_COMMON_SCALAR_FUNCTION_UNARY_MINUS_HPP_INCLUDED
#define BOOST_SIMD_ARCH_COMMON_SCALAR_FUNCTION_UNARY_MINUS_HPP_INCLUDED

#ifdef BOOST_MSVC
  #pragma warning(disable: 4146) // unary minus applied to unsigned
  #pragma warning(push)
#endif
#include <boost/config.hpp>
#include <boost/simd/meta/as_logical.hpp>
#include <boost/simd/constant/valmax.hpp>
#include <boost/simd/constant/valmin.hpp>
#include <boost/simd/function/unary_minus.hpp>
#include <boost/simd/function/saturated.hpp>
#
namespace boost { namespace simd { namespace ext
{
  namespace bd = boost::dispatch;
  BOOST_DISPATCH_OVERLOAD ( unary_minus_
                          , (typename A0)
                          , bd::cpu_
                          , bd::scalar_< bd::arithmetic_<A0> >
                          )
  {
    BOOST_FORCEINLINE A0 operator() ( A0 a0) const { return -a0; }
  };

  BOOST_DISPATCH_OVERLOAD ( unary_minus_
                          , (typename T)
                          , bd::cpu_
                          , bs::saturated_tag
                          , bd::scalar_<bd::signed_<T>>
                           )
  {
    BOOST_FORCEINLINE T operator()(const saturated_tag &, T a0) const BOOST_NOEXCEPT
    {
      return a0 == Valmin<T>() ? Valmax<T>() : bs::unary_minus(a0);
    }
  };

  BOOST_DISPATCH_OVERLOAD ( unary_minus_
                          , (typename T)
                          , bd::cpu_
                          , bs::saturated_tag
                          , bd::scalar_<bd::unspecified_<T>>
                          )
  {
    BOOST_FORCEINLINE T operator()(const saturated_tag &, T a) const BOOST_NOEXCEPT
    {
      return unary_minus(a);
    }
  };

} } }

#ifdef BOOST_MSVC
  #pragma warning(pop)
#endif

#endif
