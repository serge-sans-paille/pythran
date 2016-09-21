//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_COMMON_SIMD_FUNCTION_SIGN_HPP_INCLUDED
#define BOOST_SIMD_ARCH_COMMON_SIMD_FUNCTION_SIGN_HPP_INCLUDED
#include <boost/simd/detail/overload.hpp>

#include <boost/simd/meta/hierarchy/simd.hpp>
#include <boost/simd/constant/valmin.hpp>
#include <boost/simd/function/if_allbits_else.hpp>
#include <boost/simd/function/if_one_else_zero.hpp>
// #include <boost/simd/function/is_equal.hpp>
#include <boost/simd/function/is_gtz.hpp>
#include <boost/simd/function/is_ltz.hpp>
#include <boost/simd/function/is_nan.hpp>
#include <boost/simd/function/minus.hpp>


namespace boost { namespace simd { namespace ext
{
   namespace bd = boost::dispatch;
   namespace bs = boost::simd;
   BOOST_DISPATCH_OVERLOAD_IF(sign_
                          , (typename A0, typename X)
                          , (detail::is_native<X>)
                          , bd::cpu_
                          , bs::pack_<bd::arithmetic_<A0>, X>
                          )
   {
      BOOST_FORCEINLINE A0 operator()( const A0& a0) const BOOST_NOEXCEPT
      {
        return if_one_else_zero(is_gtz(a0))-if_one_else_zero(is_ltz(a0));
      }
   };

   BOOST_DISPATCH_OVERLOAD_IF(sign_
                          , (typename A0, typename X)
                          , (detail::is_native<X>)
                          , bd::cpu_
                          , bs::pack_<bd::unsigned_<A0>, X>
                          )
   {
      BOOST_FORCEINLINE A0 operator()( const A0& a0) const BOOST_NOEXCEPT
      {
        return if_one_else_zero(a0);
      }
   };

   BOOST_DISPATCH_OVERLOAD_IF(sign_
                          , (typename A0, typename X)
                          , (detail::is_native<X>)
                          , bd::cpu_
                          , bs::pack_<bd::floating_<A0>, X>
                          )
   {
      BOOST_FORCEINLINE A0 operator()( const A0& a0) const BOOST_NOEXCEPT
      {
         A0 r = if_one_else_zero(is_gtz(a0))-if_one_else_zero(is_ltz(a0));
         #ifdef BOOST_SIMD_NO_NANS
         return r;
         #else
         return if_allbits_else(is_nan(a0), r);
         #endif
      }
   };

} } }
#endif

