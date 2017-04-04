//==================================================================================================
/*!
  @file
  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_COMMON_SCALAR_FUNCTION_ERFC_HPP_INCLUDED
#define BOOST_SIMD_ARCH_COMMON_SCALAR_FUNCTION_ERFC_HPP_INCLUDED

#include <boost/simd/function/std.hpp>
#include <boost/simd/detail/dispatch/function/overload.hpp>
#include <boost/simd/arch/common/detail/generic/erf_kernel.hpp>
#include <boost/simd/constant/pi.hpp>
#include <boost/simd/constant/two.hpp>
#include <boost/simd/constant/ratio.hpp>
#include <boost/simd/constant/zero.hpp>
#include <boost/simd/function/abs.hpp>
#include <boost/simd/function/exp.hpp>
#include <boost/simd/function/oneminus.hpp>
#include <boost/simd/function/inc.hpp>
#include <boost/simd/function/sqr.hpp>
#include <boost/simd/function/sqrt.hpp>
#include <boost/simd/function/rec.hpp>
#ifndef BOOST_SIMD_NO_INVALIDS
#include <boost/simd/function/is_nan.hpp>
#endif
#ifndef BOOST_SIMD_NO_INFINITIES
#include <boost/simd/constant/inf.hpp>
#endif
#include <boost/config.hpp>
#include <cmath>

namespace boost { namespace simd { namespace ext
{
  namespace bd = boost::dispatch;
  namespace bs = boost::simd;
  BOOST_DISPATCH_OVERLOAD ( erfc_
                          , (typename A0)
                          , bd::cpu_
                          , bd::scalar_< bd::single_<A0> >
                          )
  {
    BOOST_FORCEINLINE A0 operator() (A0 a0) const BOOST_NOEXCEPT
    {
      A0 x =  bs::abs(a0);
      A0 r1 = Zero<A0>();
      A0 z =  x/inc(x);
      if (x < Ratio<A0, 2, 3>())
      {
        r1 = detail::erf_kernel<A0>::erfc3(z);
      }
      #ifndef BOOST_SIMD_NO_INFINITIES
      else if (BOOST_UNLIKELY(x == Inf<A0>()))
      {
        r1 = Zero<A0>();
      }
      #endif
      else
      {
       z-= 0.4f;
       r1 = exp(-sqr(x))*detail::erf_kernel<A0>::erfc2(z);
      }
      return (a0 < 0.0f) ? 2.0f-r1 : r1;
    }
  };
  BOOST_DISPATCH_OVERLOAD ( erfc_
                          , (typename A0)
                          , bd::cpu_
                          , bd::scalar_< bd::double_<A0> >
                          )
  {
    BOOST_FORCEINLINE A0 operator() (A0 x) const BOOST_NOEXCEPT
    {
      #ifndef BOOST_SIMD_NO_INVALIDS
      if(is_nan(x)) return x;
      #endif
      A0 y =  bs::abs(x);
      if (y <= Ratio<A0, 15, 32>()) // 0.46875
      {
        A0 res = detail::erf_kernel1<A0>::erf1(x, y);
        res =  oneminus(res);
        return res;
      }
      else if (y <= Ratio<A0, 4>())
      {
        A0 res = detail::erf_kernel1<A0>::erf2(x, y);
        res =    detail::erf_kernel1<A0>::finalize2(res, y);
        if (is_ltz(x)) res = Two<A0>()-res;
        return res;
      }
      else if  (y <= 26.543)
      {
        A0 res = detail::erf_kernel1<A0>::erf3(x, y);
        res =    detail::erf_kernel1<A0>::finalize2(res, y);
        if (is_ltz(x)) res = Two<A0>()-res;
        return res;
      }
      else return (is_ltz(x)) ? Two<A0>() : Zero<A0>();
    }
  };
  BOOST_DISPATCH_OVERLOAD ( erfc_
                          , (typename A0)
                          , bd::cpu_
                          , bs::std_tag
                          , bd::scalar_< bd::floating_<A0> >
                          )
  {
    BOOST_FORCEINLINE A0 operator() (const std_tag &, A0 a0) const BOOST_NOEXCEPT
    {
      return std::erfc(a0);
    }
  };
} } }


#endif
