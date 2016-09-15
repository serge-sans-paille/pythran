//==================================================================================================
/*!
  @file
  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_COMMON_SCALAR_FUNCTION_STIRLING_HPP_INCLUDED
#define BOOST_SIMD_ARCH_COMMON_SCALAR_FUNCTION_STIRLING_HPP_INCLUDED

#include <boost/config.hpp>
#include <boost/simd/detail/dispatch/function/overload.hpp>
#include <boost/simd/arch/common/detail/generic/stirling_kernel.hpp>
#include <boost/simd/constant/half.hpp>
#include <boost/simd/constant/inf.hpp>
#include <boost/simd/constant/one.hpp>
#include <boost/simd/constant/real.hpp>
#include <boost/simd/constant/sqrt_2pi.hpp>
#include <boost/simd/function/exp.hpp>
#include <boost/simd/function/fma.hpp>
#include <boost/simd/function/is_eqz.hpp>
#include <boost/simd/function/pow.hpp>
#include <boost/simd/function/rec.hpp>
#ifndef BOOST_SIMD_NO_INVALIDS
#include <boost/simd/function/is_nan.hpp>
#endif

namespace boost { namespace simd { namespace ext
{
  namespace bd = boost::dispatch;
  namespace bs = boost::simd;
  BOOST_DISPATCH_OVERLOAD ( stirling_
                          , (typename A0)
                          , bd::cpu_
                          , bd::scalar_< bd::floating_<A0> >
                          )
  {
    BOOST_FORCEINLINE A0 operator() (A0 a0) const BOOST_NOEXCEPT
    {
      if (is_ltz(a0)) return Nan<A0>();
      const A0 Stirlinglargelim = Real<A0, 0x4065800000000000ULL, 0X420C28F3UL>();// 172, 35.0399895f
      const A0 Stirlingsplitlim = Real<A0, 0X4061E083BA3443D4ULL, 0X41D628F6UL>();// 143.01608, 26.77f
      #ifndef BOOST_SIMD_NO_INVALIDS
      if (is_nan(a0)) return a0;
      #endif
      if (a0 > Stirlinglargelim) return Inf<A0>();
      A0 w = rec(a0);
      w = fma(w,detail::stirling_kernel<A0>::stirling1(w), One<A0>());
      A0 y = exp(-a0);
      if(is_eqz(y)) return Inf<A0>();
      A0 z =  a0 - Half<A0>();
      if( a0 >= Stirlingsplitlim )
      { /* Avoid overflow in pow() */
        const A0 v = pow_abs(a0,z*Half<A0>());
        y *= v;
        y *= v;
      }
      else
      {
        y *= pow_abs( a0, z );
      }
      y *= Sqrt_2pi<A0>()*w;
      return y;
    }
  };
} } }


#endif
