//==================================================================================================
/*!
  @file

  @copyright 2017 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_COMMON_SCALAR_FUNCTION_CLAMP_HPP_INCLUDED
#define BOOST_SIMD_ARCH_COMMON_SCALAR_FUNCTION_CLAMP_HPP_INCLUDED

#include <boost/simd/function/multiplies.hpp>
#include <boost/simd/function/pedantic.hpp>
#include <boost/simd/detail/dispatch/function/overload.hpp>
#include <boost/config.hpp>
#include <boost/assert.hpp>

namespace boost { namespace simd { namespace ext
{
  namespace bd = boost::dispatch;
  BOOST_DISPATCH_OVERLOAD ( clamp_
                          , (typename A0)
                          , bd::cpu_
                          , bd::scalar_< bd::unspecified_<A0> >
                          , bd::scalar_< bd::unspecified_<A0> >
                          , bd::scalar_< bd::unspecified_<A0> >
                          )
  {
    BOOST_FORCEINLINE
    A0 operator() ( A0 v, A0 lo, A0 hi) const BOOST_NOEXCEPT
    {
      BOOST_ASSERT_MSG(lo <= hi, "lo is not less or equal to hi");
      return (v < lo) ? lo : (hi < v) ? hi : v;
    }
  };

  BOOST_DISPATCH_OVERLOAD ( clamp_
                          , (typename A0)
                          , bd::cpu_
                          , bs::pedantic_tag
                          , bd::scalar_< bd::unspecified_<A0> >
                          , bd::scalar_< bd::unspecified_<A0> >
                          , bd::scalar_< bd::unspecified_<A0> >
                          )
  {
    BOOST_FORCEINLINE
    A0 operator() ( pedantic_tag const &
                  , A0 v, A0 lo, A0 hi) const BOOST_NOEXCEPT
    {
      BOOST_ASSERT_MSG(lo <=  hi, "lo is not less or equal to hi");
      return (v < lo) ? lo : (hi < v) ? hi : v;
    }
  };

} } }


#endif
