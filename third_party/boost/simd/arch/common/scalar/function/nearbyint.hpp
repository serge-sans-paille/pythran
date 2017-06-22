//==================================================================================================
/*
  Copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_COMMON_SCALAR_FUNCTION_NEARBYINT_HPP_INCLUDED
#define BOOST_SIMD_ARCH_COMMON_SCALAR_FUNCTION_NEARBYINT_HPP_INCLUDED

#include <boost/simd/constant/twotonmb.hpp>
#include <boost/simd/constant/zero.hpp>
#include <boost/simd/detail/enforce_precision.hpp>
#include <boost/simd/function/abs.hpp>
#include <boost/simd/detail/dispatch/function/overload.hpp>
#include <boost/config.hpp>
#include <boost/simd/function/std.hpp>
#include <boost/simd/function/raw.hpp>
#include <boost/simd/function/is_negative.hpp>
#include <cmath>

namespace boost { namespace simd { namespace ext
{
  namespace bd = boost::dispatch;
  namespace bs = boost::simd;
  BOOST_DISPATCH_OVERLOAD ( nearbyint_
                          , (typename A0)
                          , bd::cpu_
                          , bd::scalar_< bd::floating_<A0> >
                          )
  {
    BOOST_FORCEINLINE A0 operator() ( A0 a0) const BOOST_NOEXCEPT
    {
      detail::enforce_precision<A0> enforcer;
      const A0 v = bs::abs(a0);
      const A0 t2n = Twotonmb<A0>();
      A0 d0 = (v+t2n);
      A0 d = (d0-t2n);
      d = (v < t2n)?d:v;
      return is_negative(a0) ? -d : d;
    }
  };

  BOOST_DISPATCH_OVERLOAD ( nearbyint_
                          , (typename A0)
                          , bd::cpu_
                          , bd::scalar_< bd::integer_<A0> >
                          )
  {
    BOOST_FORCEINLINE A0 operator() ( A0 a0) const BOOST_NOEXCEPT
    {
      return a0;
    }
  };

  BOOST_DISPATCH_OVERLOAD ( nearbyint_
                          , (typename A0)
                          , bd::cpu_
                          , bs::raw_tag
                          , bd::scalar_< bd::floating_<A0> >
                          )
  {
    BOOST_FORCEINLINE A0 operator()( raw_tag const&, A0 a0) const BOOST_NOEXCEPT
    {
      return nearbyint(a0);
    }
  };

  BOOST_DISPATCH_OVERLOAD ( nearbyint_
                          , (typename A0)
                          , bd::cpu_
                          , bs::raw_tag
                          , bd::scalar_< bd::integer_<A0> >
                          )
  {
    BOOST_FORCEINLINE A0 operator()( raw_tag const&, A0 a0) const BOOST_NOEXCEPT
    {
      return a0;
    }
  };

  BOOST_DISPATCH_OVERLOAD ( nearbyint_
                          , (typename A0)
                          , bd::cpu_
                          , bs::std_tag
                          , bd::scalar_< bd::floating_<A0> >
                          )
  {
    BOOST_FORCEINLINE A0 operator() (const std_tag&, A0 a0) const BOOST_NOEXCEPT
    {
      return std::nearbyint(a0);
    }
  };
} } }

#endif
