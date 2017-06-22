//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_COMMON_SCALAR_FUNCTION_SQRT_HPP_INCLUDED
#define BOOST_SIMD_ARCH_COMMON_SCALAR_FUNCTION_SQRT_HPP_INCLUDED
#include <boost/simd/function/raw.hpp>
#include <boost/simd/function/std.hpp>

#include <boost/simd/function/is_eqz.hpp>
#include <boost/simd/function/is_gez.hpp>
#include <boost/simd/function/is_ngez.hpp>
#include <boost/simd/function/rsqrt.hpp>
#include <boost/simd/constant/nan.hpp>
#include <boost/simd/constant/zero.hpp>
#include <boost/simd/function/std.hpp>
#include <boost/simd/detail/dispatch/function/overload.hpp>
#include <boost/assert.hpp>
#include <boost/config.hpp>
#include <cmath>

namespace boost { namespace simd { namespace ext
{
  namespace bd = boost::dispatch;
  namespace bs = boost::simd;
  BOOST_DISPATCH_OVERLOAD ( sqrt_
                          , (typename A0)
                          , bd::cpu_
                          , bd::scalar_< bd::double_<A0> >
                          )
  {
    BOOST_FORCEINLINE A0 operator() ( A0  a0) const BOOST_NOEXCEPT
    {
      return ::sqrt(a0);
    }
  };
  BOOST_DISPATCH_OVERLOAD ( sqrt_
                          , (typename A0)
                          , bd::cpu_
                          , bd::scalar_< bd::single_<A0> >
                          )
  {
    BOOST_FORCEINLINE A0 operator() ( A0 a0) const BOOST_NOEXCEPT
    {
      return std::sqrt(a0);
    }
  };
  BOOST_DISPATCH_OVERLOAD ( sqrt_
                          , (typename A0)
                          , bd::cpu_
                          , bd::scalar_< bd::integer_<A0> >
                          )
  {
    BOOST_FORCEINLINE A0 operator() ( A0 a0) const BOOST_NOEXCEPT
    {
      BOOST_ASSERT_MSG(is_gez(a0), "sqrt input is negative");

      return A0(bs::sqrt(double(a0)));
    }
  };
  BOOST_DISPATCH_OVERLOAD ( sqrt_
                          , (typename A0)
                          , bd::cpu_
                          , bs::std_tag
                          , bd::scalar_< bd::floating_<A0> >
                          )
  {
    BOOST_FORCEINLINE A0 operator() (const std_tag &,  A0  a0) const BOOST_NOEXCEPT
    {
      return std::sqrt(a0);
    }
  };

  BOOST_DISPATCH_OVERLOAD ( sqrt_
                          , (typename A0)
                          , bd::cpu_
                          , boost::simd::raw_tag
                          , bd::scalar_< bd::floating_<A0> >
                          )
  {
    BOOST_FORCEINLINE A0 operator() (const raw_tag &,  A0  a0) const BOOST_NOEXCEPT
    {
      if (is_ngez(a0)) return Nan<A0>();
      if (is_eqz(a0)) return Zero<A0>();
      return a0 * raw_(rsqrt)(a0);
    }
  };

  BOOST_DISPATCH_OVERLOAD ( sqrt_
                          , (typename A0)
                          , bd::cpu_
                          , boost::simd::raw_tag
                          , bd::scalar_< bd::integer_<A0> >
                          )
  {
    BOOST_FORCEINLINE A0 operator() (const raw_tag &,  A0 a0) const BOOST_NOEXCEPT
    {
      BOOST_ASSERT_MSG( is_positive(a0)
                      , "sqrt integer domain is restricted to positive integer."
                      );
      return sqrt(a0);
    }
  };
} } }

#endif
