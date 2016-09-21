//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_COMMON_SCALAR_FUNCTION_PREDECESSOR_HPP_INCLUDED
#define BOOST_SIMD_ARCH_COMMON_SCALAR_FUNCTION_PREDECESSOR_HPP_INCLUDED

#include <boost/simd/constant/valmin.hpp>
#include <boost/simd/function/bitfloating.hpp>
#include <boost/simd/function/bitinteger.hpp>
#include <boost/simd/function/is_gez.hpp>
#include <boost/simd/function/is_nan.hpp>
#include <boost/simd/function/dec.hpp>
#include <boost/simd/function/minus.hpp>
#include <boost/simd/detail/dispatch/function/overload.hpp>
#include <boost/assert.hpp>
#include <boost/config.hpp>

namespace boost { namespace simd { namespace ext
{
  namespace bd = boost::dispatch;
  BOOST_DISPATCH_OVERLOAD ( predecessor_
                          , (typename A0)
                          , bd::cpu_
                          , bd::scalar_< bd::arithmetic_<A0> >
                          , bd::scalar_< bd::integer_<A0> >
                          )
  {
    BOOST_FORCEINLINE A0 operator() ( A0 a0, A0 a1) const BOOST_NOEXCEPT
    {
      BOOST_ASSERT_MSG(is_gez(a1), "predecessor rank must be non negative");
      if (Valmin<A0>()+a1 > a0) return Valmin<A0>();
      return a0-a1;
    }
  };

  BOOST_DISPATCH_OVERLOAD ( predecessor_
                          , (typename A0)
                          , bd::cpu_
                          , bd::scalar_< bd::arithmetic_<A0> >
                          )
  {
    BOOST_FORCEINLINE A0 operator() ( A0 a0) const BOOST_NOEXCEPT
    {
      return saturated_(dec)(a0);
    }
  };

  BOOST_DISPATCH_OVERLOAD ( predecessor_
                          , (typename A0, typename A1)
                          , bd::cpu_
                          , bd::scalar_< bd::floating_<A0> >
                          , bd::scalar_< bd::integer_<A1> >
                          )
  {
    BOOST_FORCEINLINE A0 operator() ( A0 a0, A1 a1) const BOOST_NOEXCEPT
    {
      using i_t = bd::as_integer_t<A0>;
      BOOST_ASSERT_MSG(is_gez(a1), "predecessor rank must be non negative");
      if (is_nan(a0)) return a0;
      return bitfloating(saturated_(minus)(bitinteger(a0), i_t(a1)));
    }
  };

  BOOST_DISPATCH_OVERLOAD ( predecessor_
                          , (typename A0)
                          , bd::cpu_
                          , bd::scalar_< bd::floating_<A0> >
                          )
  {
    BOOST_FORCEINLINE A0 operator() ( A0 a0) const BOOST_NOEXCEPT
    {
      if (is_nan(a0)) return a0;
      return bitfloating(saturated_(dec)(bitinteger(a0)));
    }
  };
} } }


#endif
