//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_COMMON_SIMD_FUNCTION_DIVIDES_HPP_INCLUDED
#define BOOST_SIMD_ARCH_COMMON_SIMD_FUNCTION_DIVIDES_HPP_INCLUDED

#include <boost/simd/detail/overload.hpp>
#include <boost/simd/constant/one.hpp>
#include <boost/simd/constant/valmax.hpp>
#include <boost/simd/constant/valmin.hpp>
#include <boost/simd/function/bitwise_or.hpp>
#include <boost/simd/function/bitwise_xor.hpp>
#include <boost/simd/function/divides.hpp>
#include <boost/simd/function/genmask.hpp>
#include <boost/simd/function/if_else.hpp>
#include <boost/simd/function/if_zero_else_one.hpp>
#include <boost/simd/function/inc.hpp>
#include <boost/simd/function/is_eqz.hpp>
#include <boost/simd/function/is_nez.hpp>
#include <boost/simd/function/logical_and.hpp>
#include <boost/simd/function/plus.hpp>
#include <boost/simd/function/shift_right.hpp>
#include <boost/simd/detail/dispatch/meta/scalar_of.hpp>

namespace boost { namespace simd { namespace ext
{
   namespace bd = boost::dispatch;
   namespace bs = boost::simd;
   BOOST_DISPATCH_OVERLOAD(divides_
                          , (typename A0, typename X)
                          , bd::cpu_
                          , bs::saturated_tag
                          , bs::pack_<bd::floating_<A0>, X>
                          , bs::pack_<bd::floating_<A0>, X>
                          )
   {
      BOOST_FORCEINLINE A0 operator()(const saturated_tag &
                                     , const A0& a0, const A0& a1) const BOOST_NOEXCEPT
      {
        return a0/a1;
      }
   };

   BOOST_DISPATCH_OVERLOAD(divides_
                          , (typename A0, typename X)
                          , bd::cpu_
                          , bs::saturated_tag
                          , bs::pack_<bd::uint_<A0>, X>
                          , bs::pack_<bd::uint_<A0>, X>
                          )
   {
      BOOST_FORCEINLINE A0 operator()(const saturated_tag &
                                     , const A0& a0, const A0& a1) const BOOST_NOEXCEPT
      {
        auto iseqza1 = is_eqz(a1);
        const A0 aa1 = if_else(iseqza1, One<A0>(), a1);
        const A0 aa0 = if_else(iseqza1, genmask(a0), a0);
        return aa0/aa1;
      }
   };

   BOOST_DISPATCH_OVERLOAD(divides_
                          , (typename A0, typename X)
                          , bd::cpu_
                          , bs::saturated_tag
                          , bs::pack_<bd::int_<A0>, X>
                          , bs::pack_<bd::int_<A0>, X>
                          )
   {
      BOOST_FORCEINLINE A0 operator()(const saturated_tag &
                                     , const A0& a0, const A0& a1) const BOOST_NOEXCEPT
      {
        using sA0 = bd::scalar_of_t<A0>;
        auto iseqza1 = is_eqz(a1);
        // replace valmin/-1 by (valmin+1)/-1
        A0 x = a0 + if_zero_else_one(inc(a1) | (a0 + Valmin<A0>()));
        // negative -> valmin
        // positive -> valmax
        const A0 x2 = bitwise_xor(Valmax<A0>(), shift_right(x, sizeof(sA0)*CHAR_BIT-1));
        x = if_else(logical_and(iseqza1, is_nez(x)), x2, x);
        const A0 y = if_else(iseqza1, One<A0>(), a1);
        return x/y;
      }
   };

   BOOST_DISPATCH_OVERLOAD ( divides_
                          , (typename T)
                          ,  bd::cpu_
                          ,  bs::saturated_tag
                          ,  bd::generic_<bd::fundamental_<T>>
                          ,  bd::generic_<bd::fundamental_<T>>
                          )
  {
    BOOST_FORCEINLINE T operator()(const saturated_tag &, const T& a, const T& b) const BOOST_NOEXCEPT
    {
      return saturated_(divides)(a, b);
    }
  };

} } }

#endif
