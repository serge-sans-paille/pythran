//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_COMMON_SIMD_FUNCTION_IS_NOT_LESS_HPP_INCLUDED
#define BOOST_SIMD_ARCH_COMMON_SIMD_FUNCTION_IS_NOT_LESS_HPP_INCLUDED
#include <boost/simd/detail/overload.hpp>

#include <boost/simd/meta/hierarchy/simd.hpp>
#include <boost/simd/function/is_greater_equal.hpp>
#include <boost/simd/function/is_less.hpp>
#include <boost/simd/function/is_ord.hpp>
#include <boost/simd/function/logical_not.hpp>
#include <boost/simd/function/logical_and.hpp>

namespace boost { namespace simd { namespace ext
{
   namespace bd = boost::dispatch;
   namespace bs = boost::simd;
   BOOST_DISPATCH_OVERLOAD_IF(is_not_less_
                          , (typename A0, typename X)
                          , (detail::is_native<X>)
                          , bd::cpu_
                          , bs::pack_<bd::floating_<A0>, X>
                          , bs::pack_<bd::floating_<A0>, X>
                          )
   {
      BOOST_FORCEINLINE bs::as_logical_t<A0> operator()( const A0& a0, const A0& a1) const BOOST_NOEXCEPT
      {
        auto r = logical_not(is_less(a0,a1));
        #ifndef BOOST_SIMD_NO_NANS
        r = logical_and(r, is_ord(a0, a1));
        #endif
        return r;
      }
   };

   BOOST_DISPATCH_OVERLOAD_IF(is_not_less_
                          , (typename A0, typename X)
                          , (detail::is_native<X>)
                          , bd::cpu_
                          , bs::pack_<bd::integer_<A0>, X>
                          , bs::pack_<bd::integer_<A0>, X>
                          )
   {
      BOOST_FORCEINLINE bs::as_logical_t<A0>  operator()( const A0& a0, const A0& a1) const BOOST_NOEXCEPT
      {
        return is_greater_equal(a0,a1);
      }
   };

} } }

#endif

