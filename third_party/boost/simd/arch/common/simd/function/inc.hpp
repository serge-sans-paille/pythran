//==================================================================================================
/**
  Copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
**/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_COMMON_SIMD_FUNCTION_INC_HPP_INCLUDED
#define BOOST_SIMD_ARCH_COMMON_SIMD_FUNCTION_INC_HPP_INCLUDED

#include <boost/simd/constant/one.hpp>
#include <boost/simd/function/plus.hpp>
#include <boost/simd/function/inc.hpp>
#include <boost/simd/detail/dispatch/function/overload.hpp>
#include <boost/config.hpp>

namespace boost { namespace simd { namespace ext
{
  namespace bd = boost::dispatch;
  BOOST_DISPATCH_OVERLOAD_IF ( inc_
                          , (typename A0, typename X)
                          , (detail::is_native<X>)
                          , bd::cpu_
                          , bs::pack_< bd::arithmetic_<A0>, X>
                          )
  {
    BOOST_FORCEINLINE A0 operator()(A0 const& a0) const BOOST_NOEXCEPT_IF_EXPR(a0+A0(1))
    {
      return a0+A0(1);
    }
  };
  BOOST_DISPATCH_OVERLOAD_IF ( inc_
                          , (typename T, typename X)
                          , (detail::is_native<X>)
                          ,  bd::cpu_
                          ,  bs::saturated_tag
                          ,  bs::pack_<bd::fundamental_<T>, X>
                          )
  {
    BOOST_FORCEINLINE T operator()(const saturated_tag &, const T& a
                                  ) const BOOST_NOEXCEPT
    {
      return saturated_(inc)(a);
    }
  };
} } }

#include <boost/simd/arch/common/simd/function/inc_s.hpp>

#endif
