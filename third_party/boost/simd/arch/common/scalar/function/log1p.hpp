//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_COMMON_SCALAR_FUNCTION_LOG1P_HPP_INCLUDED
#define BOOST_SIMD_ARCH_COMMON_SCALAR_FUNCTION_LOG1P_HPP_INCLUDED
#include <boost/simd/function/std.hpp>

#include <boost/simd/detail/enforce_precision.hpp>
#include <boost/simd/function/log.hpp>
#include <boost/simd/function/dec.hpp>
#include <boost/simd/function/inc.hpp>
#include <boost/simd/detail/dispatch/function/overload.hpp>
#include <boost/config.hpp>
#include <cmath>

namespace boost { namespace simd { namespace ext
{
  namespace bd = boost::dispatch;
  namespace bs = boost::simd;
  BOOST_DISPATCH_OVERLOAD ( log1p_
                          , (typename A0)
                          , bd::cpu_
                          , bd::scalar_< bd::floating_<A0> >
                          )
  {
    BOOST_FORCEINLINE A0 operator() ( A0 const& a0) const BOOST_NOEXCEPT
    {
      detail::enforce_precision<A0> enforcer;

      if (Mone<A0>() > a0)   return Nan<A0>();
      #ifndef BOOST_SIMD_NO_INFINITIES
      if (a0 == Inf<A0>())   return Inf<A0>();
      #endif
      if (a0 == Mone<A0>())   return Minf<A0>();
      A0 u = inc(a0);
      return log(u)+(a0-dec(u))/u;
    }
  };
  BOOST_DISPATCH_OVERLOAD ( log1p_
                          , (typename A0)
                          , bd::cpu_
                          , bs::std_tag
                          , bd::scalar_< bd::floating_<A0> >
                          )
  {
    BOOST_FORCEINLINE A0 operator() (const std_tag &, A0 a0) const BOOST_NOEXCEPT
    {
      return std::log1p(a0);
    }
  };
} } }


#endif
