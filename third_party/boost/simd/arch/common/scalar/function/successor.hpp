//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_COMMON_SCALAR_FUNCTION_SUCCESSOR_HPP_INCLUDED
#define BOOST_SIMD_ARCH_COMMON_SCALAR_FUNCTION_SUCCESSOR_HPP_INCLUDED

#include <boost/simd/constant/valmax.hpp>
#include <boost/simd/function/abs.hpp>
#include <boost/simd/function/plus.hpp>
#include <boost/simd/function/bitfloating.hpp>
#include <boost/simd/function/bitinteger.hpp>
#include <boost/simd/function/is_gez.hpp>
#include <boost/simd/function/is_nan.hpp>
#include <boost/simd/function/inc.hpp>
#include <boost/simd/detail/dispatch/function/overload.hpp>
#include <boost/assert.hpp>
#include <boost/config.hpp>

namespace boost { namespace simd { namespace ext
{
  namespace bd = boost::dispatch;
  BOOST_DISPATCH_OVERLOAD ( successor_
                          , (typename A0)
                          , bd::cpu_
                          , bd::scalar_< bd::arithmetic_<A0> >
                          )
  {
    BOOST_FORCEINLINE A0 operator() ( A0 a0) const BOOST_NOEXCEPT
    {
       return saturated_(inc)(a0);
    }
  };

  BOOST_DISPATCH_OVERLOAD ( successor_
                          , (typename A0)
                             , bd::cpu_
                                    , bd::scalar_< bd::floating_<A0> >
                                    )
  {
    BOOST_FORCEINLINE A0 operator() ( A0 a0) const BOOST_NOEXCEPT
    {
      if (is_nan(a0)) return a0;
      return bitfloating(saturated_(inc)(bitinteger(a0)));
    }
  };

  BOOST_DISPATCH_OVERLOAD ( successor_
                          , (typename A0)
                          , bd::cpu_
                          , bd::scalar_< bd::arithmetic_<A0> >
                          , bd::scalar_< bd::integer_<A0> >
                          )
  {
    BOOST_FORCEINLINE A0 operator() ( A0 a0, A0 a1) const BOOST_NOEXCEPT
    {
      BOOST_ASSERT_MSG(is_gez(a1), "predecessor rank must be non negative");
      if (Valmax<A0>()-a1 < a0) return Valmax<A0>();
      return a0+a1;
    }
  };

  BOOST_DISPATCH_OVERLOAD ( successor_
                          , (typename A0, typename A1)
                          , bd::cpu_
                          , bd::scalar_< bd::floating_<A0> >
                          , bd::scalar_< bd::integer_<A1> >
                          )
  {
    BOOST_FORCEINLINE A0 operator() ( A0 a0, A1 a1) const BOOST_NOEXCEPT
    {
      BOOST_ASSERT_MSG(is_gez(a1), "predecessor rank must be non negative");
      using itype = bd::as_integer_t<A0, signed>;
      if (is_nan(a0)) return a0;
      return bitfloating(saturated_(plus)(bitinteger(a0), itype(a1)));
    }
  };
} } }


#endif
