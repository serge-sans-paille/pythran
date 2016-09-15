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
#include <boost/simd/function/fast.hpp>
#include <boost/simd/function/fast.hpp>
#include <boost/simd/function/std.hpp>

#include <boost/simd/function/is_gez.hpp>
#include <boost/simd/function/rsqrt.hpp>
#include <boost/simd/detail/math.hpp>
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
      #ifdef BOOST_SIMD_HAS_SQRTF
      return ::sqrtf(a0);
      #else
      return std::sqrt(a0);
      #endif
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
                          , boost::simd::fast_tag
                          , bd::scalar_< bd::single_<A0> >
                          )
  {
    BOOST_FORCEINLINE A0 operator() (const fast_tag &,  A0  a0) const BOOST_NOEXCEPT
    {
      return if_else_zero(a0, a0 * fast_(rsqrt)(a0));
    }
  };

   BOOST_DISPATCH_OVERLOAD ( sqrt_
                          , (typename A0)
                          , bd::cpu_
                          , boost::simd::fast_tag
                          , bd::scalar_< bd::double_<A0> >
                          )
  {
    BOOST_FORCEINLINE A0 operator() (const fast_tag &,  A0  a0) const BOOST_NOEXCEPT
    {
      return ::sqrt(a0);
    }
  };

  BOOST_DISPATCH_OVERLOAD ( sqrt_
                          , (typename A0)
                          , bd::cpu_
                          , boost::simd::fast_tag
                          , bd::scalar_< bd::integer_<A0> >
                          )
  {
    BOOST_FORCEINLINE A0 operator() (const fast_tag &,  A0 a0) const BOOST_NOEXCEPT
    {
      BOOST_ASSERT_MSG( is_positive(a0)
                      , "sqrt integer domain is restricted to positive integer."
                      );
      return sqrt(a0);
    }
  };

} } }


#endif
