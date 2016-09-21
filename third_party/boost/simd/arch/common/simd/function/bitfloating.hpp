//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_COMMON_SIMD_FUNCTION_BITFLOATING_HPP_INCLUDED
#define BOOST_SIMD_ARCH_COMMON_SIMD_FUNCTION_BITFLOATING_HPP_INCLUDED
#include <boost/simd/detail/overload.hpp>

#include <boost/simd/meta/hierarchy/simd.hpp>
#include <boost/simd/constant/signmask.hpp>
#include <boost/simd/function/bitwise_cast.hpp>
#include <boost/simd/function/if_else.hpp>
#include <boost/simd/function/is_gez.hpp>
#include <boost/simd/function/minus.hpp>
#include <boost/simd/detail/dispatch/meta/as_floating.hpp>

namespace boost { namespace simd { namespace ext
{
   namespace bd = boost::dispatch;
   namespace bs = boost::simd;
   BOOST_DISPATCH_OVERLOAD_IF(bitfloating_
                          , (typename A0, typename X)
                          , (detail::is_native<X>)
                          , bd::cpu_
                          , bs::pack_<bd::arithmetic_<A0>, X>
                          )
   {
      using result = bd::as_floating_t<A0>;
      BOOST_FORCEINLINE result operator()( const A0& a0) const BOOST_NOEXCEPT
      {
        A0 s = bitwise_cast<A0>(Signmask<result>());
        return bitwise_cast<result>(if_else(is_gez(a0) , a0, s-a0));
      }
   };

   BOOST_DISPATCH_OVERLOAD_IF(bitfloating_
                          , (typename A0, typename X)
                          , (detail::is_native<X>)
                          , bd::cpu_
                          , bs::pack_<bd::unsigned_<A0>, X>
                          )
   {
      using result = bd::as_floating_t<A0>;
      BOOST_FORCEINLINE result operator()( const A0& a0) const BOOST_NOEXCEPT
      {
        return simd::bitwise_cast<result>(a0);
      }
   };

} } }

#endif

