//==================================================================================================
/**
  Copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
**/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_COMMON_SIMD_FUNCTION_MULTIPLIES_HPP_INCLUDED
#define BOOST_SIMD_ARCH_COMMON_SIMD_FUNCTION_MULTIPLIES_HPP_INCLUDED

#include <boost/simd/detail/overload.hpp>
#include <boost/simd/function/saturated.hpp>
#include <boost/simd/function/group.hpp>
#include <boost/simd/function/multiplies.hpp>
#include <boost/simd/function/split_multiplies.hpp>
#include <boost/simd/detail/dispatch/meta/upgrade.hpp>

namespace boost { namespace simd { namespace ext
{
  namespace bd = boost::dispatch;
  namespace bs = boost::simd;

  BOOST_DISPATCH_OVERLOAD ( multiplies_
                          , (typename A0, typename X)
                          , bd::cpu_
                          , bs::saturated_tag
                          , bs::pack_<bd::floating_<A0>, X>
                          , bs::pack_<bd::floating_<A0>, X>
                          )
  {
    BOOST_FORCEINLINE
    A0 operator()(const saturated_tag&, const A0& a0, const A0& a1) const BOOST_NOEXCEPT
    {
      return a0*a1;
    }
  };

  BOOST_DISPATCH_OVERLOAD_IF( multiplies_
                            , (typename A0, typename X)
                            , (bd::is_upgradable<A0>)
                            , bd::cpu_
                            , bs::saturated_tag
                            , bs::pack_<bd::integer_<A0>, X>
                            , bs::pack_<bd::integer_<A0>, X>
                            )
  {
    BOOST_FORCEINLINE
    A0 operator()(const saturated_tag &, const A0& a0, const A0& a1) const BOOST_NOEXCEPT
    {
      auto sm = split_multiplies(a0, a1);
      return saturated_(group)(sm.first, sm.second);
    }
  };
} } }

#endif
