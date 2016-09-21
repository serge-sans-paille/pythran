//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_COMMON_SIMD_FUNCTION_IS_INCLUDED_HPP_INCLUDED
#define BOOST_SIMD_ARCH_COMMON_SIMD_FUNCTION_IS_INCLUDED_HPP_INCLUDED
#include <boost/simd/detail/overload.hpp>

#include <boost/simd/meta/hierarchy/simd.hpp>
#include <boost/simd/meta/as_logical.hpp>
#include <boost/simd/function/all.hpp>
#include <boost/simd/function/bitwise_or.hpp>
#include <boost/simd/function/is_equal.hpp>

namespace boost { namespace simd { namespace ext
{
   namespace bd = boost::dispatch;
   namespace bs = boost::simd;
   BOOST_DISPATCH_OVERLOAD_IF(is_included_
                          , (typename A0, typename X)
                          , (detail::is_native<X>)
                          , bd::cpu_
                          , bs::pack_<bd::arithmetic_<A0>, X>
                          , bs::pack_<bd::arithmetic_<A0>, X>
                          )
   {
     using sA0 =  bd::scalar_of_t<A0>;
     using result =bs::as_logical_t<sA0>;
     BOOST_FORCEINLINE result operator()(A0 const& a0,A0 const& a1) const
      {
        return bs::all(is_equal(bitwise_or(a0, a1), a1));
      }
   };


} } }
#endif

