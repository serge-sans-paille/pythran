//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_COMMON_SCALAR_FUNCTION_ILOGB_HPP_INCLUDED
#define BOOST_SIMD_ARCH_COMMON_SCALAR_FUNCTION_ILOGB_HPP_INCLUDED

#include <boost/simd/constant/zero.hpp>
#include <boost/simd/detail/brigand.hpp>
#include <boost/simd/function/exponent.hpp>
#include <boost/simd/function/is_gtz.hpp>
#include <boost/simd/detail/math.hpp>
#include <boost/simd/detail/dispatch/function/overload.hpp>
#include <boost/simd/detail/dispatch/meta/as_floating.hpp>
#include <boost/simd/detail/dispatch/meta/as_integer.hpp>
#include <boost/config.hpp>

namespace boost { namespace simd { namespace ext
{
  namespace bd = boost::dispatch;
  namespace bs = boost::simd;
  BOOST_DISPATCH_OVERLOAD ( ilogb_
                          , (typename A0)
                          , bd::cpu_
                          , bd::scalar_< bd::integer_<A0> >
                          )
  {
    BOOST_FORCEINLINE A0 operator() ( A0 a0 ) const BOOST_NOEXCEPT
    {
      return static_cast<A0>(bs::ilogb(static_cast<bd::as_floating_t<A0>>(a0)));
    }
  };

#ifdef BOOST_SIMD_HAS_ILOGB
  BOOST_DISPATCH_OVERLOAD ( ilogb_
                          , (typename A0)
                          , bd::cpu_
                          , bd::scalar_< bd::double_<A0> >
                          )
  {
    using result_t = bd::as_integer_t<A0, signed>;
    BOOST_FORCEINLINE result_t operator() ( A0 a0 ) const BOOST_NOEXCEPT
    {
      return is_gtz(a0) ? ::ilogb(a0) : Zero<result_t>();
    }
  };
#endif

#ifdef BOOST_SIMD_HAS_ILOGBF
  BOOST_DISPATCH_OVERLOAD ( ilogb_
                          , (typename A0)
                          , bd::cpu_
                          , bd::scalar_< bd::single_<A0> >
                          )
  {
    using result_t = bd::as_integer_t<A0, signed>;
    BOOST_FORCEINLINE result_t operator() ( A0 a0 ) const BOOST_NOEXCEPT
    {
      return is_gtz(a0) ? ::ilogbf(a0) : Zero<result_t>();
    }
  };
#endif

  BOOST_DISPATCH_OVERLOAD ( ilogb_
                          , (typename A0)
                          , bd::cpu_
                          , bd::scalar_< bd::floating_<A0> >
                          )
  {
    using result_t = bd::as_integer_t<A0, signed>;
    BOOST_FORCEINLINE result_t operator() ( A0 a0 ) const BOOST_NOEXCEPT
    {
      return is_gtz(a0) ? bs::exponent(a0) : Zero<result_t>();
    }
  };
} } }


#endif
