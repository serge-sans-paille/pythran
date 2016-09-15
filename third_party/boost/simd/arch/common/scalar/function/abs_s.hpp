//==================================================================================================
/**
  Copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
**/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_COMMON_SCALAR_FUNCTION_ABS_S_HPP_INCLUDED
#define BOOST_SIMD_ARCH_COMMON_SCALAR_FUNCTION_ABS_S_HPP_INCLUDED

#include <boost/simd/function/abs.hpp>
#include <boost/simd/function/saturated.hpp>
#include <boost/simd/detail/dispatch/function/overload.hpp>
#include <boost/config.hpp>

namespace boost { namespace simd { namespace ext
{
  namespace bd = boost::dispatch;
  namespace bs = boost::simd;

  BOOST_DISPATCH_OVERLOAD ( abs_
                          , (typename T)
                          , bd::cpu_
                          , bs::saturated_tag
                          , bd::scalar_<bd::unsigned_<T>>
                          )
  {
    BOOST_FORCEINLINE T operator()(const saturated_tag &, T a) const BOOST_NOEXCEPT
    {
      return a;
    }
  };

  BOOST_DISPATCH_OVERLOAD ( abs_
                          , (typename T)
                          , bd::cpu_
                          , bs::saturated_tag
                          , bd::scalar_<bd::floating_<T>>
                          )
  {
    BOOST_FORCEINLINE T operator()(const saturated_tag &, T a) const BOOST_NOEXCEPT
    {
      return bs::abs(a);
    }
  };
} } }

#endif
