//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_COMMON_SCALAR_FUNCTION_BROADCAST_HPP_INCLUDED
#define BOOST_SIMD_ARCH_COMMON_SCALAR_FUNCTION_BROADCAST_HPP_INCLUDED

#include <boost/simd/detail/dispatch/adapted/std/integral_constant.hpp>
#include <boost/simd/detail/dispatch/function/overload.hpp>
#include <boost/config.hpp>

namespace boost { namespace simd { namespace ext
{
  namespace bd = boost::dispatch;

  BOOST_DISPATCH_OVERLOAD ( broadcast_
                          , (typename A0, typename A1)
                          , bd::cpu_
                          , bd::scalar_<bd::unspecified_<A0>>
                          , bd::constant_<bd::integer_<A1>>
                          )
  {
    BOOST_FORCEINLINE A0 operator() ( A0 const& a0, A1 const&) const BOOST_NOEXCEPT
    {
      return (A1::value == 0) ? a0 : A0(0);
    }
  };
} } }


#endif
