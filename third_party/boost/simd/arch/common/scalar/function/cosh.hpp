//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_COMMON_SCALAR_FUNCTION_COSH_HPP_INCLUDED
#define BOOST_SIMD_ARCH_COMMON_SCALAR_FUNCTION_COSH_HPP_INCLUDED
#include <boost/simd/function/std.hpp>

#include <boost/simd/constant/half.hpp>
#include <boost/simd/constant/log_2.hpp>
#include <boost/simd/detail/constant/maxlog.hpp>
#include <boost/simd/constant/one.hpp>
#include <boost/simd/function/abs.hpp>
#include <boost/simd/function/average.hpp>
#include <boost/simd/function/exp.hpp>
#include <boost/simd/function/rec.hpp>
#include <boost/simd/function/std.hpp>
#include <boost/simd/detail/dispatch/function/overload.hpp>
#include <boost/config.hpp>
#include <cmath>

namespace boost { namespace simd { namespace ext
{
  namespace bd = boost::dispatch;
  namespace bs = boost::simd;
  BOOST_DISPATCH_OVERLOAD ( cosh_
                          , (typename A0)
                          , bd::cpu_
                          , bs::std_tag
                          , bd::scalar_< bd::floating_<A0> >
                          )
  {
    BOOST_FORCEINLINE A0 operator() (const std_tag &,  A0  a0) const BOOST_NOEXCEPT
    {
      return std::cosh(a0);
    }
  };

  BOOST_DISPATCH_OVERLOAD ( cosh_
                          , (typename A0)
                          , bd::cpu_
                          , bd::scalar_<bd::floating_<A0> >
                          )
  {
    BOOST_FORCEINLINE A0 operator() ( A0 const& a0) const BOOST_NOEXCEPT
    {
      //////////////////////////////////////////////////////////////////////////////
      // if x = abs(a0) according x < Threshold e =  exp(x) or exp(x/2) is
      // respectively computed
      // *  in the first case cosh (e+rec(e))/2
      // *  in the second     cosh is (e/2)*e (avoiding undue overflow)
      // Threshold is Maxlog - Log_2
      //////////////////////////////////////////////////////////////////////////////
      A0 x = bs::abs(a0);
      auto test1 = (x > Maxlog<A0>()-Log_2<A0>());
      A0 fac =test1 ? Half<A0>() : One<A0>();
      A0 tmp = exp(x*fac);
      A0 tmp1 = Half<A0>()*tmp;
      return test1 ?tmp1*tmp : bs::average(tmp, rec(tmp));
    }
  };

} } }


#endif
