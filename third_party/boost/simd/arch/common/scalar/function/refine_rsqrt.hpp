//==================================================================================================
/**
  Copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
**/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_COMMON_SCALAR_FUNCTION_REFINE_RSQRT_HPP_INCLUDED
#define BOOST_SIMD_ARCH_COMMON_SCALAR_FUNCTION_REFINE_RSQRT_HPP_INCLUDED

#include <boost/simd/detail/overload.hpp>
#include <boost/simd/function/fnms.hpp>
#include <boost/simd/function/fma.hpp>
#include <boost/simd/function/sqr.hpp>
#include <boost/simd/constant/one.hpp>
#include <boost/simd/constant/half.hpp>

namespace boost { namespace simd { namespace ext
{
  namespace bd = boost::dispatch;
  namespace bs = boost::simd;

  BOOST_DISPATCH_OVERLOAD ( refine_rsqrt_
                          , (typename T)
                          , bd::cpu_
                          , bd::scalar_<bd::floating_<T>>
                          , bd::scalar_<bd::floating_<T>>
                          )
  {
    BOOST_FORCEINLINE T operator()(T a0, T x) const BOOST_NOEXCEPT
    {
      // Newton-Raphson
      return fma( fnms(a0, sqr(x), One<T>()), x*Half<T>(), x);
    }
  };
} } }

#endif
