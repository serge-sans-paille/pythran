//==================================================================================================
/*!
  @file

  @copyright 2015 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_COMMON_SCALAR_FUNCTION_SQR_ABS_HPP_INCLUDED
#define BOOST_SIMD_ARCH_COMMON_SCALAR_FUNCTION_SQR_ABS_HPP_INCLUDED

#include <boost/simd/function/sqr.hpp>
#include <boost/simd/function/saturated.hpp>
#include <boost/simd/detail/dispatch/function/overload.hpp>
#include <boost/config.hpp>

namespace boost { namespace simd { namespace ext
{
  namespace bd = boost::dispatch;
  BOOST_DISPATCH_OVERLOAD ( sqr_abs_
                          , (typename A0)
                          , bd::cpu_
                          , bd::scalar_< bd::arithmetic_<A0> >
                          )
  {
    BOOST_FORCEINLINE A0 operator() ( A0 a0) const BOOST_NOEXCEPT
    {
      return multiplies(a0, a0);
    }
  };

  BOOST_DISPATCH_OVERLOAD ( sqr_abs_
                          , (typename A0)
                          , bd::cpu_
                          , bs::saturated_tag
                          , bd::scalar_< bd::arithmetic_<A0> >
                          )
  {
    BOOST_FORCEINLINE A0 operator() (saturated_tag const&, A0 a0) const BOOST_NOEXCEPT
    {
      return saturated_(sqr)(a0);
    }
  };
} } }


#endif
