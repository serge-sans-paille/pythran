//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_COMMON_SCALAR_FUNCTION_NEGATE_HPP_INCLUDED
#define BOOST_SIMD_ARCH_COMMON_SCALAR_FUNCTION_NEGATE_HPP_INCLUDED

#include <boost/simd/function/is_nez.hpp>
#include <boost/simd/function/sign.hpp>
#include <boost/simd/detail/dispatch/function/overload.hpp>
#include <boost/config.hpp>

namespace boost { namespace simd { namespace ext
{
  namespace bd = boost::dispatch;
  BOOST_DISPATCH_OVERLOAD ( negate_
                          , (typename A0)
                          , bd::cpu_
                          , bd::scalar_< bd::signed_<A0> >
                          , bd::scalar_< bd::signed_<A0> >
                          )
  {
    BOOST_FORCEINLINE A0 operator() ( A0 a0, A0 a1) const BOOST_NOEXCEPT
    {
      return a0*sign(a1);
    }
  };

  BOOST_DISPATCH_OVERLOAD ( negate_
                          , (typename A0)
                          , bd::cpu_
                          , bd::scalar_< bd::unsigned_<A0> >
                          , bd::scalar_< bd::unsigned_<A0> >
                          )
  {
    BOOST_FORCEINLINE A0 operator() ( A0 a0, A0 a1) const BOOST_NOEXCEPT
    {
      return bool(is_nez(a1))*a0;
    }
  };
} } }


#endif
