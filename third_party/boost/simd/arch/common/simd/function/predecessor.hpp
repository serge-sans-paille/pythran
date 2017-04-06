//==================================================================================================
/**
  Copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
**/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_COMMON_SIMD_FUNCTION_PREDECESSOR_HPP_INCLUDED
#define BOOST_SIMD_ARCH_COMMON_SIMD_FUNCTION_PREDECESSOR_HPP_INCLUDED

#include <boost/simd/detail/overload.hpp>
#include <boost/simd/detail/assert_utils.hpp>
#include <boost/simd/constant/mone.hpp>
#include <boost/simd/constant/valmin.hpp>
#include <boost/simd/function/bitfloating.hpp>
#include <boost/simd/function/bitinteger.hpp>
#include <boost/simd/function/if_nan_else.hpp>
#include <boost/simd/function/is_gez.hpp>
#include <boost/simd/function/is_less.hpp>
#include <boost/simd/function/is_greater.hpp>
#include <boost/simd/function/is_nan.hpp>
#include <boost/simd/function/is_not_equal.hpp>
#include <boost/simd/function/dec.hpp>
#include <boost/simd/function/plus.hpp>
#include <boost/simd/function/if_dec.hpp>
#include <boost/simd/function/minus.hpp>
#include <boost/assert.hpp>

namespace boost { namespace simd { namespace ext
{
   namespace bd = boost::dispatch;
   namespace bs = boost::simd;
   BOOST_DISPATCH_OVERLOAD_IF(predecessor_
                          , (typename A0, typename X)
                          , (detail::is_native<X>)
                          , bd::cpu_
                          , bs::pack_<bd::arithmetic_<A0>, X>
                          )
   {
      BOOST_FORCEINLINE A0 operator()( const A0& a0) const BOOST_NOEXCEPT
      {
        return if_dec(is_not_equal(a0, Valmin<A0>()), a0);
      }
   };

   BOOST_DISPATCH_OVERLOAD_IF(predecessor_
                          , (typename A0, typename X)
                          , (detail::is_native<X>)
                          , bd::cpu_
                          , bs::pack_<bd::floating_<A0>, X>
                          )
   {
      BOOST_FORCEINLINE A0 operator()( const A0& a0) const BOOST_NOEXCEPT
      {
        return if_nan_else(is_nan(a0), bitfloating(saturated_(dec)(bitinteger(a0))));
      }
   };

   BOOST_DISPATCH_OVERLOAD_IF(predecessor_
                          , (typename A0, typename X)
                          , (detail::is_native<X>)
                          , bd::cpu_
                          , bs::pack_<bd::integer_<A0>, X>
                          , bs::pack_<bd::integer_<A0>, X>
                          )
   {
      BOOST_FORCEINLINE A0 operator()( const A0& a0, const A0& a1) const BOOST_NOEXCEPT
      {
        BOOST_ASSERT_MSG(assert_all(is_gez(a1)), "predecessor rank must be non negative");
        return if_else(  is_greater(Valmin<A0>()+a1, a0), Valmin<A0>(), a0-a1);
      }
   };

   BOOST_DISPATCH_OVERLOAD_IF(predecessor_
                          , (typename A0, typename A1, typename X)
                          , (detail::is_native<X>)
                          , bd::cpu_
                          , bs::pack_<bd::floating_<A0>, X>
                          , bs::pack_<bd::integer_<A1>, X>
                          )
   {
      BOOST_FORCEINLINE A0 operator()( const A0& a0, const  A1&  a1) const BOOST_NOEXCEPT
      {
        BOOST_ASSERT_MSG(assert_all(is_gez(a1)), "predecessor rank must be non negative");
        return if_allbits_else(is_nan(a0), bitfloating(saturated_(minus)(bitinteger(a0), a1)));
      }
   };
} } }

#endif
