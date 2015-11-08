//===============================================================================
//       Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//       Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//        Distributed under the Boost Software License, Version 1.0.
//               See accompanying file LICENSE.txt or copy at
//                   http://www.boost.org/LICENSE_1_0.txt
//===============================================================================
#ifndef NT2_HYPERBOLIC_FUNCTIONS_SCALAR_SINHCOSH_HPP_INCLUDED
#define NT2_HYPERBOLIC_FUNCTIONS_SCALAR_SINHCOSH_HPP_INCLUDED

#include <nt2/hyperbolic/functions/sinhcosh.hpp>
#include <nt2/hyperbolic/functions/details/sinh_kernel.hpp>
#include <nt2/include/constants/half.hpp>
#include <nt2/include/constants/log_2.hpp>
#include <nt2/include/constants/maxlog.hpp>
#include <nt2/include/constants/one.hpp>
#include <nt2/include/functions/scalar/abs.hpp>
#include <nt2/include/functions/scalar/average.hpp>
#include <nt2/include/functions/scalar/bitofsign.hpp>
#include <nt2/include/functions/scalar/bitwise_xor.hpp>
#include <nt2/include/functions/scalar/exp.hpp>
#include <nt2/include/functions/scalar/if_else.hpp>
#include <nt2/include/functions/scalar/rec.hpp>
#include <nt2/include/functions/scalar/sqr.hpp>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION(  nt2::tag::sinhcosh_, tag::cpu_,(A0)
                            ,  ((scalar_<floating_<A0> >))
                               ((scalar_<floating_<A0> >))
                               ((scalar_<floating_<A0> >))
                            )
  {
    //////////////////////////////////////////////////////////////////////////////
    // if x = abs(a0) is less than 1 sinh is computed using a polynomial(float)
    // respectively rational(double) approx from cephes.
    // else according x < Threshold e =  exp(x) or exp(x/2) is respectively
    // computed
    // * in the first case sinh is (e-rec(e))/2 and cosh (e+rec(e))/2
    // * in the second     sinh and cosh are (e/2)*e (avoiding undue overflow)
    // Threshold is Maxlog - Log_2 defined in Maxshlog
    //////////////////////////////////////////////////////////////////////////////
    typedef void result_type;
    inline result_type operator()(A0 const& a0,A0 & a1,A0 & a2) const
    {
      A0 x = nt2::abs(a0);
      bool test1 = (x >  Maxlog<A0>()-Log_2<A0>());
      A0 fac = if_else(test1, Half<A0>(), One<A0>());
      A0 tmp = exp(x*fac);
      A0 tmp1 = Half<A0>()*tmp;
      A0 rtmp = rec(tmp);
      A0 r =  test1 ? tmp1*tmp : tmp1-Half<A0>()*rtmp;
      a1 = b_xor(((x < One<A0>())
                  ? details::sinh_kernel<A0>::compute(x, sqr(x))
                  : r),
                 bitofsign(a0));
      a2 = test1 ? r : nt2::average(tmp, rtmp);
    }
  };

} }
#endif
