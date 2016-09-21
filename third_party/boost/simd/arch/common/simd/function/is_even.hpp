//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_COMMON_SIMD_FUNCTION_IS_EVEN_HPP_INCLUDED
#define BOOST_SIMD_ARCH_COMMON_SIMD_FUNCTION_IS_EVEN_HPP_INCLUDED
#include <boost/simd/detail/overload.hpp>

#include <boost/simd/meta/hierarchy/simd.hpp>
#include <boost/simd/meta/as_logical.hpp>
#include <boost/simd/meta/as_logical.hpp>
#include <boost/simd/constant/half.hpp>
#include <boost/simd/constant/one.hpp>
#include <boost/simd/function/bitwise_and.hpp>
#include <boost/simd/function/is_eqz.hpp>
#include <boost/simd/function/is_flint.hpp>
#include <boost/simd/function/multiplies.hpp>

namespace boost { namespace simd { namespace ext
{
   namespace bd = boost::dispatch;
   namespace bs = boost::simd;
   BOOST_DISPATCH_OVERLOAD_IF(is_even_
                          , (typename A0, typename X)
                          , (detail::is_native<X>)
                          , bd::cpu_
                          , bs::pack_<bd::arithmetic_<A0>, X>
                          )
   {
      BOOST_FORCEINLINE bs::as_logical_t<A0>  operator()( const A0& a0) const BOOST_NOEXCEPT
      {
        return is_eqz(bitwise_and(a0, One<A0>()));
      }
   };

   BOOST_DISPATCH_OVERLOAD_IF(is_even_
                          , (typename A0, typename X)
                          , (detail::is_native<X>)
                          , bd::cpu_
                          , bs::pack_<bd::floating_<A0>, X>
                          )
   {
      BOOST_FORCEINLINE bs::as_logical_t<A0>  operator()( const A0& a0) const BOOST_NOEXCEPT
      {
        return is_flint(a0*Half<A0>());
      }
   };

} } }
#endif

