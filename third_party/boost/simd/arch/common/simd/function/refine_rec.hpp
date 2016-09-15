//==================================================================================================
/**
  Copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
**/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_COMMON_SIMD_FUNCTION_REFINE_REC_HPP_INCLUDED
#define BOOST_SIMD_ARCH_COMMON_SIMD_FUNCTION_REFINE_REC_HPP_INCLUDED

#include <boost/simd/detail/overload.hpp>
#include <boost/simd/detail/traits.hpp>
#include <boost/simd/function/fnms.hpp>
#include <boost/simd/function/fma.hpp>
#include <boost/simd/constant/one.hpp>

namespace boost { namespace simd { namespace ext
{
  namespace bd = boost::dispatch;
  namespace bs = boost::simd;

  BOOST_DISPATCH_OVERLOAD_IF( refine_rec_
                            , (typename T, typename X)
                            , (detail::is_native<X>)
                            , bd::cpu_
                            , bs::pack_<bd::floating_<T>,X>
                            , bs::pack_<bd::floating_<T>,X>
                            )
  {
    BOOST_FORCEINLINE T operator()(T const& a0, T const& x) const BOOST_NOEXCEPT
    {
      // Newton-Raphson: 1/X ~= x*(1-a0*x) + x
      return fma(fnms(x, a0, One<T>()), x, x);
    }
  };
} } }

#endif
