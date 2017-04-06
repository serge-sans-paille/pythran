//==================================================================================================
/*!
  @file

  @copyright 2015 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_COMMON_SCALAR_FUNCTION_SQRT1PM1_HPP_INCLUDED
#define BOOST_SIMD_ARCH_COMMON_SCALAR_FUNCTION_SQRT1PM1_HPP_INCLUDED

#include <boost/simd/constant/half.hpp>
#include <boost/simd/function/abs.hpp>
#include <boost/simd/function/divides.hpp>
#include <boost/simd/function/if_else.hpp>
#include <boost/simd/function/is_less.hpp>
#include <boost/simd/function/dec.hpp>
#include <boost/simd/function/inc.hpp>
#include <boost/simd/function/sqrt.hpp>
#include <boost/simd/detail/dispatch/function/overload.hpp>
#include <boost/config.hpp>

namespace boost { namespace simd { namespace ext
{
  namespace bd = boost::dispatch;
  namespace bs = boost::simd;
  BOOST_DISPATCH_OVERLOAD ( sqrt1pm1_
                          , (typename A0)
                          , bd::cpu_
                          , bd::scalar_< bd::floating_<A0> >
                          )
  {
    BOOST_FORCEINLINE A0 operator() ( A0 a0) const BOOST_NOEXCEPT
    {
      A0 tmp =  bs::sqrt(inc(a0));
      return  ((bs::abs(a0) < bs::Half<A0>())? a0/bs::inc(tmp) : bs::dec(tmp));
    }
  };
} } }


#endif
