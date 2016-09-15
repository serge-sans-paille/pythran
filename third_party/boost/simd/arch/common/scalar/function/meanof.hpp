//==================================================================================================
/**
  Copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
**/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_COMMON_SCALAR_FUNCTION_MEANOF_HPP_INCLUDED
#define BOOST_SIMD_ARCH_COMMON_SCALAR_FUNCTION_MEANOF_HPP_INCLUDED

#include <boost/simd/constant/half.hpp>
#include <boost/simd/function/max.hpp>
#include <boost/simd/function/min.hpp>
#include <boost/simd/function/is_finite.hpp>
#include <boost/simd/detail/dispatch/function/overload.hpp>
#include <boost/config.hpp>

namespace boost { namespace simd { namespace ext
{
   namespace bd = boost::dispatch;
  BOOST_DISPATCH_OVERLOAD ( meanof_
                          , (typename A0)
                          , bd::cpu_
                          , bd::scalar_< bd::floating_<A0> >
                          , bd::scalar_< bd::floating_<A0> >
                          )
  {
    BOOST_FORCEINLINE A0 operator() ( A0 a0, A0 a1) const BOOST_NOEXCEPT
    {
      if (is_finite(a0)&&is_finite(a1))
      {
        A0 m = min(a0, a1);
        return m + (max(a0, a1)-m)*Half<A0>();
      }
      else
        return a0+a1;
    }
  };

  BOOST_DISPATCH_OVERLOAD ( meanof_
                          , (typename A0)
                          , bd::cpu_
                          , bd::scalar_< bd::integer_<A0>>
                          , bd::scalar_< bd::integer_<A0>>
                          )
  {
    BOOST_FORCEINLINE A0 operator() ( A0 a0, A0 a1) const BOOST_NOEXCEPT
    {
      return (a0 & a1) + ((a0 ^ a1) >> 1);
    }
  };

} } }


#endif
