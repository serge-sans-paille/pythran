//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_COMMON_SCALAR_FUNCTION_POPCNT_HPP_INCLUDED
#define BOOST_SIMD_ARCH_COMMON_SCALAR_FUNCTION_POPCNT_HPP_INCLUDED

#ifdef BOOST_MSVC
#include <intrin.h>
#endif
#include <boost/simd/function/hi.hpp>
#include <boost/simd/function/lo.hpp>
#include <boost/simd/function/sbits.hpp>
#include <boost/simd/detail/dispatch/function/overload.hpp>
#include <boost/config.hpp>

namespace boost { namespace simd { namespace ext
{
  namespace bd = boost::dispatch;
  BOOST_DISPATCH_OVERLOAD ( popcnt_
                          ,(typename A0)
                          , bd::cpu_
                          , bd::scalar_< bd::floating_<A0> >
                          )
  {
    BOOST_FORCEINLINE bd::as_integer_t<A0, unsigned> operator() ( A0 a0) const BOOST_NOEXCEPT
    {
      return simd::popcnt(sbits(a0));
    }
  };

  BOOST_DISPATCH_OVERLOAD  ( popcnt_
                           ,(typename A0)
                           , bd::cpu_
                           , bd::scalar_< bd::ints8_<A0> >
                           )
  {
    BOOST_FORCEINLINE bd::as_integer_t<A0, unsigned> operator() ( A0 a0) const BOOST_NOEXCEPT
    {
#ifdef BOOST_MSVC
      return __popcnt16(int16_t(a0) & 0xFF);
#else
      return __builtin_popcount(int32_t(a0) & 0xFF);
#endif
    }
  };

  BOOST_DISPATCH_OVERLOAD  ( popcnt_
                          ,(typename A0)
                           , bd::cpu_
                           , bd::scalar_< bd::ints16_<A0> >
                           )
  {
    BOOST_FORCEINLINE bd::as_integer_t<A0, unsigned> operator() ( A0 a0) const BOOST_NOEXCEPT
    {
    #ifdef BOOST_MSVC
      return __popcnt16(a0);
    #else
      return __builtin_popcount(int32_t(a0) & 0xFFFF);
    #endif
    }
  };

  BOOST_DISPATCH_OVERLOAD ( popcnt_
                          ,(typename A0)
                          , bd::cpu_
                          , bd::scalar_< bd::ints32_<A0> >
                          )
  {
    BOOST_FORCEINLINE bd::as_integer_t<A0, unsigned> operator() ( A0 a0) const BOOST_NOEXCEPT
    {
    #ifdef BOOST_MSVC
      return __popcnt(a0);
    #else
      return __builtin_popcount(a0);
    #endif
    }
  };

  BOOST_DISPATCH_OVERLOAD ( popcnt_
                          ,(typename A0)
                          , bd::cpu_
                          , bd::scalar_< bd::ints64_<A0> >
                          )
  {
    BOOST_FORCEINLINE bd::as_integer_t<A0, unsigned> operator() ( A0 a0) const BOOST_NOEXCEPT
    {
    #if defined BOOST_MSVC && defined _WIN64
      return __popcnt64(a0);
    #elif defined BOOST_MSVC
      return  __popcnt( hi(a0) )
            + __popcnt( lo(a0) );
    #else
      return  __builtin_popcount( hi(a0) )
            + __builtin_popcount( lo(a0) );
    #endif
    }
  };
} } }


#endif
