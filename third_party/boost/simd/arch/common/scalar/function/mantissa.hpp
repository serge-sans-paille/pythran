//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_COMMON_SCALAR_FUNCTION_MANTISSA_HPP_INCLUDED
#define BOOST_SIMD_ARCH_COMMON_SCALAR_FUNCTION_MANTISSA_HPP_INCLUDED

#ifndef BOOST_SIMD_NO_INVALIDS
#include <boost/simd/function/is_invalid.hpp>
#endif
#include <boost/simd/detail/constant/mantissamask.hpp>
#include <boost/simd/constant/one.hpp>
#include <boost/simd/function/bitwise_and.hpp>
#include <boost/simd/function/bitwise_or.hpp>
#include <boost/simd/detail/dispatch/function/overload.hpp>
#include <boost/config.hpp>

namespace boost { namespace simd { namespace ext
{
  namespace bd = boost::dispatch;
  BOOST_DISPATCH_OVERLOAD ( mantissa_
                          , (typename A0)
                          , bd::cpu_
                          , bd::scalar_< bd::integer_<A0> >
                          )
  {
    BOOST_FORCEINLINE A0 operator() ( A0 a0) const BOOST_NOEXCEPT
    {
      return a0;
    }
  };

  BOOST_DISPATCH_OVERLOAD ( mantissa_
                          , (typename A0)
                          , bd::cpu_
                          , bd::scalar_< bd::floating_<A0> >
                          )
  {
    BOOST_FORCEINLINE A0 operator() ( A0 a0) const BOOST_NOEXCEPT
    {
      if(!a0) return a0;
    #ifndef BOOST_SIMD_NO_INVALIDS
      if(is_invalid(a0)) return a0;
    #endif
      return bitwise_or(bitwise_and(a0,Mantissamask<A0>()),One<A0>());
    }
  };
} } }


#endif
