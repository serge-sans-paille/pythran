//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_COMMON_SCALAR_FUNCTION_CLZ_HPP_INCLUDED
#define BOOST_SIMD_ARCH_COMMON_SCALAR_FUNCTION_CLZ_HPP_INCLUDED

#ifndef __GNUC__
#include <boost/simd/function/ffs.hpp>
#include <boost/simd/function/reversebits.hpp>
#endif
#ifdef BOOST_MSVC
#include <intrin.h>
#endif
#include <boost/simd/function/bitwise_cast.hpp>
#include <boost/simd/detail/dispatch/function/overload.hpp>
#include <boost/simd/detail/dispatch/meta/as_integer.hpp>
#include <boost/config.hpp>

namespace boost { namespace simd { namespace ext
{
  namespace bd = boost::dispatch;
  BOOST_DISPATCH_OVERLOAD ( clz_
                          , (typename A0)
                          , bd::cpu_
                          , bd::scalar_< bd::type64_<A0> >
                          )
  {
    using result_t = bd::as_integer_t<A0>;
    BOOST_FORCEINLINE result_t operator() ( A0 a0) const BOOST_NOEXCEPT
    {
      result_t t1 = bitwise_cast<result_t>(a0);
      BOOST_ASSERT_MSG( t1, "clz not defined for 0" );

    #ifdef __GNUC__
      return __builtin_clzll(t1);
    #else
      return ffs(reversebits(t1))-1;
    #endif
    }
  };

  BOOST_DISPATCH_OVERLOAD ( clz_
                          , (typename A0)
                          , bd::cpu_
                          , bd::scalar_< bd::type32_<A0> >
                          )
  {
    using result_t = bd::as_integer_t<A0>;
    BOOST_FORCEINLINE result_t operator() ( A0 a0) const BOOST_NOEXCEPT
    {
      result_t t1 = bitwise_cast<result_t>(a0);
      BOOST_ASSERT_MSG( t1, "clz not defined for 0" );

    #ifdef __GNUC__
      return __builtin_clz(t1);
    #else
      return ffs(reversebits(t1))-1;
    #endif
    }
  };

  BOOST_DISPATCH_OVERLOAD ( clz_
                          , (typename A0)
                          , bd::cpu_
                          , bd::scalar_< bd::type16_<A0> >
                          )
  {
    BOOST_FORCEINLINE  bd::as_integer_t<A0> operator() ( A0 a0) const BOOST_NOEXCEPT
    {
      using i_t = typename bd::as_integer_t<A0, unsigned>;
      i_t t1 = bitwise_cast<i_t>(a0);
      return clz(uint32_t(t1))-16;
    }
  };


  BOOST_DISPATCH_OVERLOAD ( clz_
                          , (typename A0)
                          , bd::cpu_
                          , bd::scalar_< bd::type8_<A0> >
                          )
  {
    BOOST_FORCEINLINE bd::as_integer_t<A0> operator() ( A0 a0) const BOOST_NOEXCEPT
    {
      using i_t = typename bd::as_integer_t<A0, unsigned>;
      i_t t1 = bitwise_cast<i_t>(a0);
      return clz(uint32_t(t1))-24;
    }
  };
} } }


#endif
