//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_COMMON_SIMD_FUNCTION_NEGATE_HPP_INCLUDED
#define BOOST_SIMD_ARCH_COMMON_SIMD_FUNCTION_NEGATE_HPP_INCLUDED
#include <boost/simd/detail/overload.hpp>

#include <boost/simd/meta/hierarchy/simd.hpp>
#include <boost/simd/function/is_nez.hpp>
#include <boost/simd/function/multiplies.hpp>
#include <boost/simd/function/sign.hpp>

namespace boost { namespace simd { namespace ext
{
   namespace bd = boost::dispatch;
   namespace bs = boost::simd;
   BOOST_DISPATCH_OVERLOAD_IF(negate_
                          , (typename A0, typename X)
                          , (detail::is_native<X>)
                          , bd::cpu_
                          , bs::pack_<bd::signed_<A0>, X>
                          , bs::pack_<bd::signed_<A0>, X>
                          )
   {
      BOOST_FORCEINLINE A0 operator()( const A0& a0, const A0& a1) const BOOST_NOEXCEPT
      {
        return a0*sign(a1);
      }
   };

   BOOST_DISPATCH_OVERLOAD_IF(negate_
                          , (typename A0, typename X)
                          , (detail::is_native<X>)
                          , bd::cpu_
                          , bs::pack_<bd::unsigned_<A0>, X>
                          , bs::pack_<bd::unsigned_<A0>, X>
                          )
   {
      BOOST_FORCEINLINE A0 operator()( const A0& a0, const A0& a1) const BOOST_NOEXCEPT
      {
        return if_else_zero(is_nez(a1), a0);
      }
   };


} } }

#endif

