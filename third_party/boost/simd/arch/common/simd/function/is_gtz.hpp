//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_COMMON_SIMD_FUNCTION_IS_GTZ_HPP_INCLUDED
#define BOOST_SIMD_ARCH_COMMON_SIMD_FUNCTION_IS_GTZ_HPP_INCLUDED
#include <boost/simd/detail/overload.hpp>

#include <boost/simd/meta/hierarchy/simd.hpp>
#include <boost/simd/meta/as_logical.hpp>
#include <boost/simd/meta/as_logical.hpp>
#include <boost/simd/constant/zero.hpp>
#include <boost/simd/function/is_greater.hpp>
#include <boost/simd/function/is_nez.hpp>

namespace boost { namespace simd { namespace ext
{
   namespace bd = boost::dispatch;
   namespace bs = boost::simd;
   BOOST_DISPATCH_OVERLOAD_IF(is_gtz_
                          , (typename A0, typename X)
                          , (detail::is_native<X>)
                          , bd::cpu_
                          , bs::pack_<bd::signed_<A0>, X>
                          )
   {
      BOOST_FORCEINLINE bs::as_logical_t<A0>  operator()( const A0& a0) const BOOST_NOEXCEPT
      {
         return is_greater(a0, Zero<A0>());
      }
   };

   BOOST_DISPATCH_OVERLOAD_IF(is_gtz_
                          , (typename A0, typename X)
                          , (detail::is_native<X>)
                          , bd::cpu_
                          , bs::pack_<bd::unsigned_<A0>, X>
                          )
   {
      BOOST_FORCEINLINE bs::as_logical_t<A0> operator()( const A0& a0) const BOOST_NOEXCEPT
      {
         return is_nez(a0);
      }
   };

} } }

#endif

