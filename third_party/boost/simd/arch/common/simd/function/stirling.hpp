//==================================================================================================
/*!
  @file
  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_COMMON_SIMD_FUNCTION_STIRLING_HPP_INCLUDED
#define BOOST_SIMD_ARCH_COMMON_SIMD_FUNCTION_STIRLING_HPP_INCLUDED

#include <boost/config.hpp>
#include <boost/simd/detail/dispatch/function/overload.hpp>
#include <boost/simd/arch/common/detail/generic/stirling_kernel.hpp>
#include <boost/simd/constant/half.hpp>
#include <boost/simd/constant/inf.hpp>
#include <boost/simd/constant/one.hpp>
#include <boost/simd/constant/real.hpp>
#include <boost/simd/constant/sqrt_2pi.hpp>
#include <boost/simd/function/exp.hpp>
#include <boost/simd/function/if_else_nan.hpp>
#include <boost/simd/function/fma.hpp>
#include <boost/simd/function/is_eqz.hpp>
#include <boost/simd/function/is_gez.hpp>
#include <boost/simd/function/pow_abs.hpp>
#include <boost/simd/function/rec.hpp>
#ifndef BOOST_SIMD_NO_INVALIDS
#include <boost/simd/function/is_nan.hpp>
#endif

namespace boost { namespace simd { namespace ext
{
  namespace bd = boost::dispatch;
  namespace bs = boost::simd;
  BOOST_DISPATCH_OVERLOAD_IF ( stirling_
                             , (typename A0, typename X)
                             , (detail::is_native<X>)
                             , bd::cpu_
                             , bs::pack_< bd::floating_<A0>, X>
                             )
  {
    BOOST_FORCEINLINE A0 operator() (const A0& a00) const BOOST_NOEXCEPT
    {
      const A0 Stirlingsplitlim = Real<A0, 0X4061E083BA3443D4ULL, 0X41D628F6UL>();// 143.01608, 26.77f
      const A0 Stirlinglargelim = Real<A0, 0x4065800000000000ULL, 0X420C28F3UL>();// 172, 35.0399895f
      A0 a0 = if_else_nan(is_gez(a00), a00);
      A0 w = bs::rec(a0);
      w = fma(w,detail::stirling_kernel<A0>::stirling1(w), bs::One<A0>());
      A0 y = bs::exp(-a0);
      auto test = is_less(a0, Stirlingsplitlim);
      A0 z =  a0 - bs::Half<A0>();
      z =  if_else(test, z, Half<A0>()*z);
      A0 v =  bs::pow_abs(a0,z);
      y *= v;
      y = if_else(test,y, y*v); /* Avoid overflow in pow() */
      y *= bs::Sqrt_2pi<A0>()*w;
      #ifndef BOOST_SIMD_NO_INFINITIES
      y = if_else(is_equal(a0, Inf<A0>()), a0, y);
      #endif
      return if_else(a0 > Stirlinglargelim, Inf<A0>(), y);
    }
  };
} } }


#endif
