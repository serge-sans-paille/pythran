//===============================================================================
//       Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//       Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//        Distributed under the Boost Software License, Version 1.0.
//               See accompanying file LICENSE.txt or copy at
//                   http://www.boost.org/LICENSE_1_0.txt
//===============================================================================
#ifndef NT2_HYPERBOLIC_FUNCTIONS_SIMD_COMMON_SINHCOSH_HPP_INCLUDED
#define NT2_HYPERBOLIC_FUNCTIONS_SIMD_COMMON_SINHCOSH_HPP_INCLUDED

#include <nt2/hyperbolic/functions/sinhcosh.hpp>
#include <nt2/hyperbolic/functions/details/sinh_kernel.hpp>
#include <nt2/include/constants/half.hpp>
#include <nt2/include/constants/log_2.hpp>
#include <nt2/include/constants/maxlog.hpp>
#include <nt2/include/constants/one.hpp>
#include <nt2/include/functions/simd/abs.hpp>
#include <nt2/include/functions/simd/average.hpp>
#include <nt2/include/functions/simd/bitofsign.hpp>
#include <nt2/include/functions/simd/bitwise_xor.hpp>
#include <nt2/include/functions/simd/exp.hpp>
#include <nt2/include/functions/simd/if_else.hpp>
#include <nt2/include/functions/simd/any.hpp>
#include <nt2/include/functions/simd/is_greater.hpp>
#include <nt2/include/functions/simd/is_less.hpp>
#include <nt2/include/functions/simd/minus.hpp>
#include <nt2/include/functions/simd/multiplies.hpp>
#include <nt2/include/functions/simd/rec.hpp>
#include <nt2/include/functions/simd/sqr.hpp>
#include <nt2/include/functions/simd/unary_minus.hpp>
#include <nt2/sdk/meta/as_logical.hpp>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION(  nt2::tag::sinhcosh_, tag::cpu_,(A0)(X)
                            , ((simd_<floating_<A0>,X>))
                               ((simd_<floating_<A0>,X>))
                               ((simd_<floating_<A0>,X>))
                            )
  {
    typedef void result_type;
    inline result_type operator()(A0 const& a0,A0 & a1,A0 & a2) const
    {
      //////////////////////////////////////////////////////////////////////////////
      // if x = abs(a0) is less than 1 sinh is computed using a polynomial(float)
      // respectively rational(double) approx from cephes.
      // else according x < Threshold e =  exp(x) or exp(x/2) is respectively
      // computed
      // *  in the first case sinh is (e-rec(e))/2 and cosh (e+rec(e))/2
      // *  in the second     sinh and cosh are (e/2)*e (avoiding undue overflow)
      // Threshold is Maxlog - Log_2 defined in Maxshlog
      //////////////////////////////////////////////////////////////////////////////
      typedef typename meta::as_logical<A0>::type bA0;
      A0 x = nt2::abs(a0);
      bA0 lt1= lt(x, One<A0>());
      A0 bts = bitofsign(a0);
      if(nt2::any(lt1))
      {
        a1 = details::sinh_kernel<A0>::compute(x, sqr(x));
      }
      bA0 test1 = gt(x, Maxlog<A0>()-Log_2<A0>());
      A0 fac = if_else(test1, Half<A0>(), One<A0>());
      A0 tmp = exp(x*fac);
      A0 tmp1 = Half<A0>()*tmp;
      A0 rtmp = rec(tmp);
      A0 r = if_else(test1, tmp1*tmp, tmp1-Half<A0>()*rtmp);
      a1 = b_xor(if_else(lt1, a1, r), bts);
      a2 = if_else(test1, r, nt2::average(tmp, rtmp));
    }
  };

} }
#endif
