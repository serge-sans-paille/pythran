//==================================================================================================
/*!
  @file

  @copyright 2017 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_COMMON_SIMD_FUNCTION_CLAMP_HPP_INCLUDED
#define BOOST_SIMD_ARCH_COMMON_SIMD_FUNCTION_CLAMP_HPP_INCLUDED

#include <boost/simd/function/multiplies.hpp>
#include <boost/simd/function/if_else.hpp>
#include <boost/simd/function/is_less.hpp>
#include <boost/simd/function/max.hpp>
#include <boost/simd/function/min.hpp>
#include <boost/simd/detail/dispatch/function/overload.hpp>
#include <boost/config.hpp>
#include <boost/assert.hpp>
namespace boost { namespace simd { namespace ext
{
  namespace bd = boost::dispatch;
  BOOST_DISPATCH_OVERLOAD ( clamp_
                          , (typename A0, typename X)
                          , bd::cpu_
                          , bs::pack_< bd::arithmetic_<A0>, X>
                          , bs::pack_< bd::arithmetic_<A0>, X>
                          , bs::pack_< bd::arithmetic_<A0>, X>
                          )
  {
    BOOST_FORCEINLINE
    A0 operator() ( A0 const& x, A0 const& lo, A0 const& hi) const BOOST_NOEXCEPT
    {
      BOOST_ASSERT_MSG(assert_all(is_less_equal(lo, hi)), "lo is not less or equal to hi");
      return bs::min(bs::max(x, lo), hi);
    }
  };

  BOOST_DISPATCH_OVERLOAD ( clamp_
                          , (typename A0, typename X)
                          , bd::cpu_
                          , bs::pedantic_tag
                          , bs::pack_< bd::arithmetic_<A0>, X>
                          , bs::pack_< bd::arithmetic_<A0>, X>
                          , bs::pack_< bd::arithmetic_<A0>, X>
                          )
  {
    BOOST_FORCEINLINE
    A0 operator() (pedantic_tag const&
                  , A0 const& x, A0 const& lo, A0 const& hi) const BOOST_NOEXCEPT
    {
      BOOST_ASSERT_MSG(assert_all(is_less_equal(lo, hi)), "lo is not less or equal to hi");
      return if_else(x < lo, lo, if_else(hi < x, hi, x));
    }
  };

} } }

#endif
