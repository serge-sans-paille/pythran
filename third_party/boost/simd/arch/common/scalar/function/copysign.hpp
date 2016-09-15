//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_COMMON_SCALAR_FUNCTION_COPYSIGN_HPP_INCLUDED
#define BOOST_SIMD_ARCH_COMMON_SCALAR_FUNCTION_COPYSIGN_HPP_INCLUDED

#include <boost/simd/function/abs.hpp>
#include <boost/simd/function/bitwise_notand.hpp>
#include <boost/simd/function/bitofsign.hpp>
#include <boost/simd/function/signnz.hpp>
#include <boost/simd/constant/signmask.hpp>
#include <boost/simd/detail/math.hpp>
#include <boost/simd/detail/dispatch/function/overload.hpp>
#include <boost/config.hpp>


namespace boost { namespace simd { namespace ext
{
  namespace bd = boost::dispatch;
  BOOST_DISPATCH_OVERLOAD ( copysign_
                          , (typename A0)
                          , bd::cpu_
                          , bd::scalar_< bd::arithmetic_<A0> >
                          , bd::scalar_< bd::arithmetic_<A0> >
                          )
  {
    BOOST_FORCEINLINE A0 operator() ( A0 a0, A0 a1) const BOOST_NOEXCEPT
    {
      return saturated_(abs)(a0)*signnz(a1);
    }
  };

  BOOST_DISPATCH_OVERLOAD ( copysign_
                          , (typename A0)
                          , bd::cpu_
                          , bd::scalar_< bd::double_<A0> >
                          , bd::scalar_< bd::double_<A0> >
                          )
  {
    BOOST_FORCEINLINE A0 operator() ( A0 a0, A0 a1) const BOOST_NOEXCEPT
    {
    #ifdef BOOST_SIMD_HAS_COPYSIGN
      return ::copysign(a0, a1);
      // _copysign appears to be bogus for a1 = -0 in old MSVCRT
    #elif defined(BOOST_SIMD_HAS__COPYSIGN) && !defined(__MSVCRT__)
      return ::_copysign(a0, a1);
    #else
      return bitwise_or(bitofsign(a1), bitwise_notand(Signmask<A0>(), a0));
    #endif
    }
  };

  BOOST_DISPATCH_OVERLOAD ( copysign_
                          , (typename A0)
                          , bd::cpu_
                          , bd::scalar_< bd::single_<A0> >
                          , bd::scalar_< bd::single_<A0> >
                                    )
  {
    BOOST_FORCEINLINE A0 operator() ( A0 a0, A0 a1) const BOOST_NOEXCEPT
    {
    #ifdef BOOST_SIMD_HAS_COPYSIGNF
      return ::copysignf(a0, a1);
    #elif defined(BOOST_SIMD_HAS__COPYSIGNF)
      return ::_copysignf(a0, a1);
    #else
       return bitwise_or(bitofsign(a1), bitwise_notand(Signmask<A0>(), a0));
    #endif
    }
  };
} } }


#endif
