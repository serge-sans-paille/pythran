//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_COMMON_SCALAR_FUNCTION_SINHCOSH_HPP_INCLUDED
#define BOOST_SIMD_ARCH_COMMON_SCALAR_FUNCTION_SINHCOSH_HPP_INCLUDED

#include <boost/simd/arch/common/detail/generic/sinh_kernel.hpp>
#include <boost/simd/constant/half.hpp>
#include <boost/simd/constant/log_2.hpp>
#include <boost/simd/detail/constant/maxlog.hpp>
#include <boost/simd/constant/one.hpp>
#include <boost/simd/function/abs.hpp>
#include <boost/simd/function/average.hpp>
#include <boost/simd/function/bitofsign.hpp>
#include <boost/simd/function/bitwise_xor.hpp>
#include <boost/simd/function/exp.hpp>
#include <boost/simd/function/if_else.hpp>
#include <boost/simd/function/rec.hpp>
#include <boost/simd/function/sqr.hpp>
#include <boost/simd/detail/dispatch/function/overload.hpp>
#include <boost/config.hpp>

namespace boost { namespace simd { namespace ext
{
  namespace bd = boost::dispatch;
  namespace bs = boost::simd;
  BOOST_DISPATCH_OVERLOAD ( sinhcosh_
                          , (typename A0)
                          , bd::cpu_
                          , bd::scalar_<bd::floating_<A0> >
                          )
  {
    //////////////////////////////////////////////////////////////////////////////
    // if x = abs(a0) is less than 1 sinh is computed using a polynomial(float)
    // respectively rational(double) approx from cephes.
    // else according x < Threshold e =  exp(x) or exp(x/2) is respectively
    // computed
    // * in the first case sinh is (e-rec(e))/2 and cosh (e+rec(e))/2
    // * in the second     sinh and cosh are (e/2)*e (avoiding undue overflow)
    // Threshold is Maxlog - Log_2
    //////////////////////////////////////////////////////////////////////////////
    using result_t = std::pair<A0, A0>;
    BOOST_FORCEINLINE result_t operator() ( A0 a0) const BOOST_NOEXCEPT
    {
      A0 x = bs::abs(a0);
      auto test1 = (x >  Maxlog<A0>()-Log_2<A0>());
      A0 fac = (test1? Half<A0>(): One<A0>());
      A0 tmp = exp(x*fac);
      A0 tmp1 = Half<A0>()*tmp;
      A0 rtmp = rec(tmp);
      A0 r =  test1 ? tmp1*tmp : tmp1-Half<A0>()*rtmp;
      return {bitwise_xor(((x < One<A0>())
                           ? detail::sinh_kernel<A0>::compute(x, sqr(x))
                           : r),
                          bitofsign(a0)),
          test1 ? r : bs::average(tmp, rtmp)};
    }
  };
} } }


#endif
