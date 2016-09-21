//==================================================================================================
/**
  Copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
**/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_COMMON_SIMD_FUNCTION_DIVCEIL_HPP_INCLUDED
#define BOOST_SIMD_ARCH_COMMON_SIMD_FUNCTION_DIVCEIL_HPP_INCLUDED

#include <boost/simd/detail/overload.hpp>
#include <boost/simd/meta/hierarchy/simd.hpp>
#include <boost/simd/function/ceil.hpp>
#include <boost/simd/function/group.hpp>
#include <boost/simd/function/split.hpp>
#include <boost/simd/function/tofloat.hpp>
#include <boost/simd/function/toint.hpp>
#include <boost/simd/function/touint.hpp>
#include <boost/simd/detail/dispatch/meta/upgrade.hpp>
#include <boost/simd/detail/brigand.hpp>
#include <utility>

namespace boost { namespace simd { namespace ext
{
  namespace bd = boost::dispatch;
  namespace bs = boost::simd;

  BOOST_DISPATCH_OVERLOAD_IF(div_
                            , (typename A0, typename X)
                            , (brigand::and_<bd::is_upgradable<A0>, detail::is_native<X>>)
                            , bd::cpu_
                            , bs::tag::ceil_
                            , bs::pack_<bd::int_<A0>, X>
                            , bs::pack_<bd::int_<A0>, X>
                            )
  {
    BOOST_FORCEINLINE A0 operator()( bd::functor<bs::tag::ceil_> const&
                                   , const A0& a0, const A0& a1) const BOOST_NOEXCEPT
    {
      auto s0 = bs::split(a0);
      auto s1 = bs::split(a1);
      auto d0 = saturated_(toint)(div(ceil, tofloat(s0[0]), tofloat(s1[0])));
      auto d1 = saturated_(toint)(div(ceil, tofloat(s0[1]), tofloat(s1[1])));
      return saturated_(group)(d0, d1);
    }
  };

  BOOST_DISPATCH_OVERLOAD_IF(div_
                            , (typename A0, typename X)
                            , (brigand::and_<bd::is_upgradable<A0>, detail::is_native<X>>)
                            , bd::cpu_
                            , bs::tag::ceil_
                            , bs::pack_<bd::uint_<A0>, X>
                            , bs::pack_<bd::uint_<A0>, X>
                            )
  {
    BOOST_FORCEINLINE A0 operator()( bd::functor<bs::tag::ceil_> const&
                                   , const A0& a0, const A0& a1) const BOOST_NOEXCEPT
    {
      auto s0 = bs::split(a0);
      auto s1 = bs::split(a1);
      auto d0 = saturated_(touint)(div(ceil, tofloat(s0[0]), tofloat(s1[0])));
      auto d1 = saturated_(touint)(div(ceil, tofloat(s0[1]), tofloat(s1[1])));
      return saturated_(group)(d0, d1);
    }
  };

  BOOST_DISPATCH_OVERLOAD_IF(div_
                         , (typename A0, typename X)
                         , (detail::is_native<X>)
                         , bd::cpu_
                         , bs::tag::ceil_
                         , bs::pack_<bd::ints8_<A0>, X>
                         , bs::pack_<bd::ints8_<A0>, X>
                         )
  {
    BOOST_FORCEINLINE A0 operator()( bd::functor<bs::tag::ceil_> const&
                                   , const A0& a0, const A0& a1) const BOOST_NOEXCEPT
    {
      auto s0 = bs::split(a0);
      auto s1 = bs::split(a1);
      auto d0 = div(ceil, s0[0], s1[0]);
      auto d1 = div(ceil, s0[1], s1[1]);
      return saturated_(group)(d0, d1);
    }
  };

  BOOST_DISPATCH_OVERLOAD_IF(div_
                         , (typename A0, typename X)
                         , (detail::is_native<X>)
                         , bd::cpu_
                         , bs::tag::ceil_
                         , bs::pack_<bd::floating_<A0>, X>
                         , bs::pack_<bd::floating_<A0>, X>
                         )
  {
    BOOST_FORCEINLINE A0 operator()( bd::functor<bs::tag::ceil_> const&
                                   , const A0& a0, const A0& a1) const BOOST_NOEXCEPT
    {
      return bs::ceil(a0/a1);
    }
  };
} } }

#endif
