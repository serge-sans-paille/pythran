//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_COMMON_SIMD_FUNCTION_IS_NORMAL_HPP_INCLUDED
#define BOOST_SIMD_ARCH_COMMON_SIMD_FUNCTION_IS_NORMAL_HPP_INCLUDED

#include <boost/simd/constant/smallestposval.hpp>
#include <boost/simd/function/logical_and.hpp>
#include <boost/simd/function/is_nez.hpp>
#include <boost/simd/function/is_not_denormal.hpp>
#include <boost/simd/function/is_finite.hpp>
#include <boost/simd/function/logical_and.hpp>
#include <boost/simd/meta/as_logical.hpp>
#include <boost/simd/detail/dispatch/function/overload.hpp>
#include <boost/config.hpp>

namespace boost { namespace simd { namespace ext
{
  namespace bd = boost::dispatch;
  namespace bs = boost::simd;
  BOOST_DISPATCH_OVERLOAD_IF ( is_normal_
                          , (typename A0, typename X)
                          , (detail::is_native<X>)
                          , bd::cpu_
                          , bs::pack_< bd::integer_<A0>, X>
                          )
  {
    BOOST_FORCEINLINE bs::as_logical_t<A0> operator() (const A0& a0) const BOOST_NOEXCEPT
    {
      return is_nez(a0);
    }
  };
  BOOST_DISPATCH_OVERLOAD_IF ( is_normal_
                          , (typename A0, typename X)
                          , (detail::is_native<X>)
                          , bd::cpu_
                          , bs::pack_< bd::floating_<A0>, X>
                          )
  {
    BOOST_FORCEINLINE  bs::as_logical_t<A0> operator() ( A0 const& a0) const BOOST_NOEXCEPT
    {
      return   logical_and(logical_and(is_finite(a0), is_nez(a0)), is_not_denormal(a0));
    }
  };
} } }


#endif
