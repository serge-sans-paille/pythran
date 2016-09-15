//==================================================================================================
/**
  Copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
**/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_COMMON_SIMD_FUNCTION_ABS_S_HPP_INCLUDED
#define BOOST_SIMD_ARCH_COMMON_SIMD_FUNCTION_ABS_S_HPP_INCLUDED

#include <boost/simd/function/abs.hpp>
#include <boost/simd/function/saturated.hpp>
#include <boost/simd/detail/dispatch/function/overload.hpp>
#include <boost/config.hpp>

namespace boost { namespace simd { namespace ext
{
  namespace bd = boost::dispatch;
  namespace bs = boost::simd;

  BOOST_DISPATCH_OVERLOAD_IF ( abs_
                          , (typename T, typename X)
                          , (detail::is_native<X>)
                          , bd::cpu_
                          , bs::saturated_tag
                          , bs::pack_<bd::unsigned_<T>, X>
                          )
  {
    BOOST_FORCEINLINE T operator()(const saturated_tag &, T const& a) const BOOST_NOEXCEPT
    {
      return a;
    }
  };

  BOOST_DISPATCH_OVERLOAD_IF ( abs_
                          , (typename T, typename X)
                          , (detail::is_native<X>)
                          , bd::cpu_
                          , bs::saturated_tag
                          , bs::pack_<bd::floating_<T>, X>
                          )
  {
    BOOST_FORCEINLINE T operator()(const saturated_tag &, T const& a) const BOOST_NOEXCEPT
    {
      return bs::abs(a);
    }
  };
} } }

#endif
