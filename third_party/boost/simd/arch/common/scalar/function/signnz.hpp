//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_COMMON_SCALAR_FUNCTION_SIGNNZ_HPP_INCLUDED
#define BOOST_SIMD_ARCH_COMMON_SCALAR_FUNCTION_SIGNNZ_HPP_INCLUDED

#include <boost/simd/constant/one.hpp>
#include <boost/simd/constant/signmask.hpp>
#include <boost/simd/function/bitwise_and.hpp>
#include <boost/simd/function/bitwise_or.hpp>
#include <boost/simd/function/is_nan.hpp>
#include <boost/simd/detail/dispatch/function/overload.hpp>
#include <boost/config.hpp>

namespace boost { namespace simd { namespace ext
{
  namespace bd = boost::dispatch;
  BOOST_DISPATCH_OVERLOAD ( signnz_
                          , (typename A0)
                          , bd::cpu_
                          , bd::scalar_< bd::signed_<A0> >
                          )
  {
    BOOST_FORCEINLINE A0 operator() ( A0 a0) const BOOST_NOEXCEPT
    {
      return (a0>>(sizeof(A0)*8-2)) | 1;
    }
  };

  BOOST_DISPATCH_OVERLOAD ( signnz_
                          , (typename A0)
                          , bd::cpu_
                          , bd::scalar_< bd::unsigned_<A0> >
                          )
  {
    BOOST_FORCEINLINE A0 operator() ( A0 const&) const BOOST_NOEXCEPT
    {
      return One<A0>();
    }
  };

  BOOST_DISPATCH_OVERLOAD ( signnz_
                          , (typename A0)
                          , bd::cpu_
                          , bd::scalar_< bd::floating_<A0> >
                          )
  {
    BOOST_FORCEINLINE A0 operator() ( A0 a0) const BOOST_NOEXCEPT
    {
      #ifndef BOOST_SIMD_NO_NANS
      return simd::is_nan(a0) ? a0 : bitwise_or(One<A0>(), bitwise_and(Signmask<A0>(), a0));
      #else
      return bitwise_or(One<A0>(), bitwise_and(Signmask<A0>(), a0));
      #endif
    }
  };
} } }


#endif
