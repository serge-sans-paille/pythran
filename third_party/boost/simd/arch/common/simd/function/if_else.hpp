//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_COMMON_SIMD_FUNCTION_IF_ELSE_HPP_INCLUDED
#define BOOST_SIMD_ARCH_COMMON_SIMD_FUNCTION_IF_ELSE_HPP_INCLUDED

#include <boost/simd/detail/overload.hpp>
#include <boost/simd/detail/traits.hpp>
#include <boost/simd/meta/hierarchy/simd.hpp>
#include <boost/simd/function/bitwise_or.hpp>
#include <boost/simd/function/bitwise_and.hpp>
#include <boost/simd/function/bitwise_andnot.hpp>
#include <boost/simd/function/genmask.hpp>
#include <boost/simd/function/is_nez.hpp>

namespace boost { namespace simd { namespace ext
{
  namespace bd = boost::dispatch;

  BOOST_DISPATCH_OVERLOAD_IF( if_else_
                            , (typename A0,typename A1,typename X)
                            , (detail::is_native<X>)
                            , bd::cpu_
                            , bs::pack_<bs::logical_<A0>,X>
                            , bs::pack_<bd::fundamental_<A1>,X>
                            , bs::pack_<bd::fundamental_<A1>,X>
                            )

  {
    BOOST_FORCEINLINE A1 operator()(const A0& a0, const A1& a1, const A1& a2) const BOOST_NOEXCEPT
    {
      auto m = genmask(a0);
      return bitwise_or(bitwise_and(a1,m), bitwise_andnot(a2,m));
    }
  };

  BOOST_DISPATCH_OVERLOAD_IF( if_else_
                            , (typename A0,typename A1,typename X)
                            , (detail::is_native<X>)
                            , bd::cpu_
                            , bs::pack_<bd::arithmetic_<A0>,X>
                            , bs::pack_<bd::fundamental_<A1>,X>
                            , bs::pack_<bd::fundamental_<A1>,X>
                            )
  {
    BOOST_FORCEINLINE A1 operator()(const A0& a0, const A1& a1, const A1&a2) const BOOST_NOEXCEPT
    {
      return if_else(is_nez(a0), a1, a2);
    }
  };
} } }

#endif
