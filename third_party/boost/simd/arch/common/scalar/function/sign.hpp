//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_COMMON_SCALAR_FUNCTION_SIGN_HPP_INCLUDED
#define BOOST_SIMD_ARCH_COMMON_SCALAR_FUNCTION_SIGN_HPP_INCLUDED

#ifndef BOOST_SIMD_NO_NANS
#include <boost/simd/function/is_nan.hpp>
#endif
#include <boost/simd/function/is_gtz.hpp>
#include <boost/simd/function/is_ltz.hpp>
#include <boost/simd/function/shift_right.hpp>
#include <boost/simd/detail/dispatch/function/overload.hpp>
#include <boost/config.hpp>

namespace boost { namespace simd { namespace ext
{
  namespace bd = boost::dispatch;
  BOOST_DISPATCH_OVERLOAD ( sign_
                          , (typename A0)
                          , bd::cpu_
                          , bd::scalar_< bd::signed_<A0> >
                          )
  {
    BOOST_FORCEINLINE A0 operator() ( A0 a0) const BOOST_NOEXCEPT
    {
      return shift_right(a0, (sizeof(A0)*8-1)) - shift_right(-a0, (sizeof(A0)*8-1));
    }
  };

  BOOST_DISPATCH_OVERLOAD ( sign_
                          , (typename A0)
                          , bd::cpu_
                          , bd::scalar_< bd::unsigned_<A0> >
                          )
  {
    BOOST_FORCEINLINE A0 operator() ( A0 a0) const BOOST_NOEXCEPT
    {
      return !!a0;
    }
  };


  BOOST_DISPATCH_OVERLOAD ( sign_
                          , (typename A0)
                          , bd::cpu_
                          , bd::scalar_< bd::floating_<A0> >
                          )
  {
    BOOST_FORCEINLINE A0 operator() ( A0 a0) const BOOST_NOEXCEPT
    {
      A0 r = bool(is_gtz(a0))-bool(is_ltz(a0));
#ifdef BOOST_SIMD_NO_NANS
      return r;
#else
      return is_nan(a0) ? a0 : r;
#endif
    }
  };
} } }


#endif
