//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_COMMON_SCALAR_FUNCTION_SINH_HPP_INCLUDED
#define BOOST_SIMD_ARCH_COMMON_SCALAR_FUNCTION_SINH_HPP_INCLUDED
#include <boost/simd/function/std.hpp>

#include <boost/simd/arch/common/detail/generic/sinh_kernel.hpp>
#include <boost/simd/constant/half.hpp>
#include <boost/simd/constant/log_2.hpp>
#include <boost/simd/detail/constant/maxlog.hpp>
#include <boost/simd/function/abs.hpp>
#include <boost/simd/function/bitofsign.hpp>
#include <boost/simd/function/bitwise_xor.hpp>
#include <boost/simd/function/exp.hpp>
#include <boost/simd/function/fms.hpp>
#include <boost/simd/function/rec.hpp>
#include <boost/simd/function/sqr.hpp>
#include <boost/simd/detail/dispatch/function/overload.hpp>
#include <boost/config.hpp>
#include <cmath>

namespace boost { namespace simd { namespace ext
{
  namespace bd = boost::dispatch;
  namespace bs = boost::simd;
  BOOST_DISPATCH_OVERLOAD ( sinh_
                          , (typename A0)
                          , bd::cpu_
                          , bd::scalar_<bd::floating_<A0> >
                          )
  {
    BOOST_FORCEINLINE A0 operator() (A0 a0) const BOOST_NOEXCEPT
    {
      //////////////////////////////////////////////////////////////////////////////
      // if x = abs(a0) is less than 1 sinh is computed using a polynomial(float)
      // respectively rational(double) approx from cephes.
      // else according x < Threshold e =  exp(x) or exp(x/2) is respectively
      // computed
      // * in the first case sinh is (e-rec(e))/2
      // * in the second     sinh is (e/2)*e (avoiding undue overflow)
      // Threshold is Maxlog - Log_2 defined in Maxshlog
      //////////////////////////////////////////////////////////////////////////////
      A0 x = bs::abs(a0);
      if( x < One<A0>())
      {
       A0 x2 = sqr(x);
       return detail::sinh_kernel<A0>::compute(a0, x2);
      }
      else
      {
        A0 r;
        if (BOOST_UNLIKELY( x > Maxlog<A0>()-Log_2<A0>()))
        {
          A0 tmp = exp(Half<A0>()*x);
          r = (Half<A0>()*tmp)*tmp;
        }
        else
        {
          A0 tmp = exp(x);
          r =  fms(tmp, Half<A0>(), Half<A0>()*rec(tmp));
        }
        return bitwise_xor(r, bitofsign(a0));
      }
    }
  };
  BOOST_DISPATCH_OVERLOAD ( sinh_
                          , (typename A0)
                          , bd::cpu_
                          , bs::std_tag
                          , bd::scalar_< bd::floating_<A0> >
                         )
  {
    BOOST_FORCEINLINE A0 operator() (const std_tag &,  A0  a0) const BOOST_NOEXCEPT
    {
      return std::sinh(a0);
    }
  };

} } }


#endif
