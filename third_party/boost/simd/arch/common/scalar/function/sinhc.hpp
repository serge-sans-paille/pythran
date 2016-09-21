//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_COMMON_SCALAR_FUNCTION_SINHC_HPP_INCLUDED
#define BOOST_SIMD_ARCH_COMMON_SCALAR_FUNCTION_SINHC_HPP_INCLUDED

#ifndef BOOST_SIMD_NO_INFINITIES
#include <boost/simd/constant/inf.hpp>
#endif
#include <boost/simd/arch/common/detail/generic/sinhc_kernel.hpp>
#include <boost/simd/constant/half.hpp>
#include <boost/simd/constant/log_2.hpp>
#include <boost/simd/detail/constant/maxlog.hpp>
#include <boost/simd/constant/one.hpp>
#include <boost/simd/function/abs.hpp>
#include <boost/simd/function/average.hpp>
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
  BOOST_DISPATCH_OVERLOAD ( sinhc_
                          , (typename A0)
                          , bd::cpu_
                          , bd::scalar_< bd::floating_<A0> >
                          )
  {

    BOOST_FORCEINLINE A0 operator() (A0 a0) const BOOST_NOEXCEPT
    {
      //////////////////////////////////////////////////////////////////////////////
      // if x = abs(a0) is less than 1 sinhc is computed using a polynomial(float)
      // respectively rational(double) approx inspired from cephes sinh approx.
      // else according x < Threshold e =  exp(x) or exp(x/2) is respectively
      // computed
      // * in the first case sinh is ((e-rec(e))/2)/x
      // * in the second     sinh is (e/2/x)*e (avoiding undue overflow)
      // Threshold is Maxlog - Log_2 defined in Maxshlog
      //////////////////////////////////////////////////////////////////////////////
      A0 x = bs::abs(a0);
      #ifndef BOOST_SIMD_NO_INFINITIES
      if (x == Inf<A0>()) return x;
      #endif
      if( x < One<A0>())
      {
        return detail::sinhc_kernel<A0>::compute(sqr(x));
      }
      else
      {
        auto test1 = (x >  Maxlog<A0>()-Log_2<A0>());
        A0 fac = (test1 ? Half<A0>() : One<A0>());
        A0 tmp = exp(x*fac);
        A0 tmp1 = (Half<A0>()*tmp)/x;
        return (test1 ? tmp1*tmp: average(tmp, -rec(tmp))/x);
      }
     }
  };
} } }


#endif
