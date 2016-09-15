//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_COMMON_SCALAR_FUNCTION_CTZ_HPP_INCLUDED
#define BOOST_SIMD_ARCH_COMMON_SCALAR_FUNCTION_CTZ_HPP_INCLUDED

#ifndef __GNUC__
#include <boost/simd/function/ffs.hpp>
#endif
#include <boost/simd/function/bitwise_cast.hpp>
#include <boost/simd/detail/dispatch/function/overload.hpp>
#include <boost/simd/detail/dispatch/meta/as_integer.hpp>
#include <boost/config.hpp>
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
  BOOST_DISPATCH_OVERLOAD ( ctz_
                          , (typename A0)
                          , bd::cpu_
                          , bd::scalar_< bd::type64_<A0> >
                          )
  {
    using result_t = bd::as_integer_t<A0>;
    BOOST_FORCEINLINE result_t operator() ( A0 a0) const
    {
      result_t that = bitwise_cast<result_t>(a0);
      if(!that) return result_t(64);

    #if defined __GNUC__
      return __builtin_ctzll(that);
    #else
      return ffs(that)-1;
    #endif
    }
  };

  BOOST_DISPATCH_OVERLOAD ( ctz_
                          , (typename A0)
                          , bd::cpu_
                          , bd::scalar_< bd::type32_<A0> >
                          )
  {
    using result_t = bd::as_integer_t<A0>;
    BOOST_FORCEINLINE result_t operator() ( A0 a0) const
    {
      result_t that = bitwise_cast<result_t>(a0);
      if(!that) return result_t(32);

    #if defined __GNUC__
      return __builtin_ctz(that);
    #else
      return ffs(that)-1;
    #endif
    }
  };

  BOOST_DISPATCH_OVERLOAD ( ctz_
                          , (typename A0)
                          , bd::cpu_
                          , bd::scalar_< bd::arithmetic_<A0> >
                          )
  {
    BOOST_FORCEINLINE bd::as_integer_t<A0> operator() ( A0 a0) const
    {
      return ctz(uint32_t(a0));
    }
  };
} } }


#endif
