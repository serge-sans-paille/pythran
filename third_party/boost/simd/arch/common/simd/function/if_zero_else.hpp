//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_COMMON_SIMD_FUNCTION_IF_ZERO_ELSE_HPP_INCLUDED
#define BOOST_SIMD_ARCH_COMMON_SIMD_FUNCTION_IF_ZERO_ELSE_HPP_INCLUDED
#include <boost/simd/detail/overload.hpp>

#include <boost/simd/meta/hierarchy/simd.hpp>
#include <boost/simd/meta/is_bitwise_logical.hpp>
#include <boost/simd/constant/zero.hpp>
#include <boost/simd/function/bitwise_andnot.hpp>
#include <boost/simd/function/genmask.hpp>

namespace boost { namespace simd { namespace ext
{
   namespace bd = boost::dispatch;
   namespace bs = boost::simd;
   BOOST_DISPATCH_OVERLOAD_IF(if_zero_else_
                             , (typename A0, typename A1, typename X)
                             , (detail::is_native<X>)
                             , bd::cpu_
                             , bs::pack_<bd::unspecified_<A0>, X>
                             , bs::pack_<bd::arithmetic_<A1>, X>
                             )
   {
      using result = A1;
      template<typename A0_>
      typename enable_if< bs::is_bitwise_logical<A0_>, result>::type
        BOOST_FORCEINLINE operator()(A0_ const& a0, A1 const& a1) const
      {
        return bitwise_andnot(a1, genmask(a0));
      }
      template<typename A0_>
      typename disable_if< bs::is_bitwise_logical<A0_>, result>::type
        BOOST_FORCEINLINE operator()(A0_ const& a0, A1 const& a1) const
      {
        return if_else(a0, Zero<A1>(), a1);
      }
   };

} } }

#endif

