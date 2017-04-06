//==================================================================================================
/**
  Copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
**/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_COMMON_SIMD_FUNCTION_REFINE_RSQRT_HPP_INCLUDED
#define BOOST_SIMD_ARCH_COMMON_SIMD_FUNCTION_REFINE_RSQRT_HPP_INCLUDED

#include <boost/simd/detail/overload.hpp>
#include <boost/simd/detail/traits.hpp>
#include <boost/simd/function/fnms.hpp>
#include <boost/simd/function/fma.hpp>
#include <boost/simd/function/sqr.hpp>
#include <boost/simd/constant/one.hpp>
#include <boost/simd/constant/half.hpp>
#include <boost/simd/constant/three.hpp>

namespace boost { namespace simd { namespace ext
{
  namespace bd = boost::dispatch;
  namespace bs = boost::simd;

  BOOST_DISPATCH_OVERLOAD_IF( refine_rsqrt_
                            , (typename T, typename X)
                            , (detail::is_native<X>)
                            , bd::cpu_
                            , bs::pack_<bd::floating_<T>,X>
                            , bs::pack_<bd::floating_<T>,X>
                            )
  {
    BOOST_FORCEINLINE T operator()(T const& a0, T const& x) const BOOST_NOEXCEPT
    {
      // Newton-Raphson
      //      return fma( fnms(a0, sqr(x), One<T>()), x*Half<T>(), x);
      return x * Half<T>() * fnms(a0, sqr(x), Three<T>());
    }
  };
} } }

#endif
