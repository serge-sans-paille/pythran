//==================================================================================================
/**
  Copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
**/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_COMMON_SCALAR_FUNCTION_RSQRT_HPP_INCLUDED
#define BOOST_SIMD_ARCH_COMMON_SCALAR_FUNCTION_RSQRT_HPP_INCLUDED

#include <boost/simd/function/raw.hpp>
#include <boost/simd/function/pedantic.hpp>
#include <boost/simd/function/rec.hpp>
#include <boost/simd/function/sqrt.hpp>
#include <boost/simd/function/bitwise_cast.hpp>
#include <boost/simd/detail/dispatch/function/overload.hpp>
#include <boost/simd/detail/dispatch/meta/as_integer.hpp>
#include <boost/config.hpp>

namespace boost { namespace simd { namespace ext
{
  namespace bd = boost::dispatch;
  namespace bs = boost::simd;

  BOOST_DISPATCH_OVERLOAD ( rsqrt_
                          , (typename A0)
                          , bd::cpu_
                          , bd::scalar_< bd::floating_<A0> >
                          )
  {
    BOOST_FORCEINLINE A0 operator() ( A0 const& a0) const BOOST_NOEXCEPT
    {
      return bs::rec(bs::sqrt(a0));
    }
  };

  BOOST_DISPATCH_OVERLOAD ( rsqrt_
                          , (typename A0)
                          , bd::cpu_
                          , boost::simd::raw_tag
                          , bd::scalar_< bd::single_<A0> >
                         )
  {
    BOOST_FORCEINLINE A0 operator() (const raw_tag &,  A0 a0) const BOOST_NOEXCEPT
    {
      typedef bd::as_integer_t<A0> i_t;

      // Quake III Arena RSQRT approximation
      i_t x = bitwise_cast<i_t>(a0);
      i_t y = 0x5f3759df - (x >> 1);

      // make negative values be NaN
      y |= x >> (sizeof(i_t)*CHAR_BIT-1);

      A0 x2 = a0 * 0.5f;
      A0 y2 = bitwise_cast<A0>(y);

      // Newton-Rhapson refinement steps: 2 NR steps for precision purpose
      y2    = y2 * ( 1.5f - ( x2 * y2 * y2 ) );
      return  y2 * ( 1.5f - ( x2 * y2 * y2 ) );
    }
  };
  BOOST_DISPATCH_OVERLOAD ( rsqrt_
                          , (typename A0)
                          , bd::cpu_
                          , boost::simd::raw_tag
                          , bd::scalar_< bd::double_<A0> >
                         )
  {
    BOOST_FORCEINLINE A0 operator() (const raw_tag &,  A0 a0) const BOOST_NOEXCEPT
    {
      return bs::rsqrt(a0);
    }
  };

   BOOST_DISPATCH_OVERLOAD ( rsqrt_
                          , (typename A0)
                          , bd::cpu_
                          , boost::simd::pedantic_tag
                          , bd::scalar_< bd::floating_<A0> >
                         )
  {
    BOOST_FORCEINLINE A0 operator() (const pedantic_tag &,  A0 a0) const BOOST_NOEXCEPT
    {
      return bs::rec(bs::sqrt(a0));
    }
  };

} } }

#endif
