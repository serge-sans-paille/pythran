//==================================================================================================
/**
  Copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
**/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_COMMON_SCALAR_FUNCTION_INC_HPP_INCLUDED
#define BOOST_SIMD_ARCH_COMMON_SCALAR_FUNCTION_INC_HPP_INCLUDED

#include <boost/simd/constant/one.hpp>
#include <boost/simd/function/plus.hpp>
#include <boost/simd/function/inc.hpp>
#include <boost/simd/detail/dispatch/function/overload.hpp>
#include <boost/config.hpp>

namespace boost { namespace simd { namespace ext
{
  namespace bd = boost::dispatch;
  BOOST_DISPATCH_OVERLOAD ( inc_
                          , (typename A0)
                          , bd::cpu_
                          , bd::scalar_< bd::arithmetic_<A0> >
                          )
  {
    BOOST_FORCEINLINE A0 operator()(A0 a0) const BOOST_NOEXCEPT_IF_EXPR(a0+A0(1))
    {
      return a0+A0(1);
    }
  };
  BOOST_DISPATCH_OVERLOAD ( inc_
                          , (typename T)
                          ,  bd::cpu_
                          ,  bs::saturated_tag
                          ,  bd::scalar_<bd::fundamental_<T>>
                          )
  {
    BOOST_FORCEINLINE T operator()(const saturated_tag &, T a
                                  ) const BOOST_NOEXCEPT
    {
      return saturated_(inc)(a);
    }
  };
} } }

#include <boost/simd/arch/common/scalar/function/inc_s.hpp>

#endif
