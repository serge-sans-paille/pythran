//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_COMMON_SCALAR_FUNCTION_MAXNUM_HPP_INCLUDED
#define BOOST_SIMD_ARCH_COMMON_SCALAR_FUNCTION_MAXNUM_HPP_INCLUDED
#include <boost/simd/function/std.hpp>

#include <boost/simd/function/is_nan.hpp>
#include <boost/simd/function/max.hpp>
#include <boost/simd/detail/dispatch/function/overload.hpp>
#include <boost/config.hpp>
#include <cmath>

namespace boost { namespace simd { namespace ext
{
  namespace bd = boost::dispatch;
 BOOST_DISPATCH_OVERLOAD ( maxnum_
                         , (typename A0)
                         , bd::cpu_
                         , bd::scalar_< bd::arithmetic_<A0> >
                         , bd::scalar_< bd::arithmetic_<A0> >
                         )
 {
   BOOST_FORCEINLINE A0 operator() ( A0 a0, A0 a1) const BOOST_NOEXCEPT
   {
     return boost::simd::max(a0, a1);
   }
 };
  BOOST_DISPATCH_OVERLOAD ( maxnum_
                          , (typename A0)
                          , bd::cpu_
                          , bd::scalar_< bd::floating_<A0> >
                          , bd::scalar_< bd::floating_<A0> >
                          )
  {
    BOOST_FORCEINLINE A0 operator() ( A0 a0, A0 a1) const BOOST_NOEXCEPT
    {
      if (is_nan(a0)) return a1;
      else return simd::max(a0, a1);
    }
  };
  BOOST_DISPATCH_OVERLOAD ( maxnum_
                          , (typename A0)
                          , bd::cpu_
                          , boost::simd::std_tag
                          , bd::scalar_< bd::floating_<A0> >
                          , bd::scalar_< bd::floating_<A0> >
                          )
  {
    BOOST_FORCEINLINE A0 operator() (const std_tag &,  A0 a0, A0 a1) const BOOST_NOEXCEPT
    {
      return std::fmax(a0, a1);
    }
  };
} } }


#endif
