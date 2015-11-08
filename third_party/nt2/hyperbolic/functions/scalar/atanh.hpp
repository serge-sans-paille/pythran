//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_HYPERBOLIC_FUNCTIONS_SCALAR_ATANH_HPP_INCLUDED
#define NT2_HYPERBOLIC_FUNCTIONS_SCALAR_ATANH_HPP_INCLUDED
#include <nt2/hyperbolic/functions/atanh.hpp>
#include <nt2/include/constants/half.hpp>
#include <nt2/include/functions/scalar/abs.hpp>
#include <nt2/include/functions/scalar/bitofsign.hpp>
#include <nt2/include/functions/scalar/bitwise_xor.hpp>
#include <nt2/include/functions/scalar/fma.hpp>
#include <nt2/include/functions/scalar/log1p.hpp>
#include <nt2/include/functions/scalar/oneminus.hpp>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::atanh_, tag::cpu_
                            , (A0)
                            , (scalar_< floating_<A0> >)
                            )
  {
    // Exhaustive test for: boost::dispatch::functor<nt2::tag::atanh_, boost::simd::tag::sse4_2_>
    //              versus: float(boost::simd::atanh(double))
    //              With T: float
    //            in range: [-1, 1]
    // 2130706432 values computed.
    // 1965486672 values (92.25%)  within 0.0 ULPs
    //  165215696 values (7.75%) within 0.5 ULPs in range [-9.999999404e-01, 9.999999404e-01]. Example: -9.999999404e-01 returns -8.664339066e+00 instead of -8.664340019e+00
    //       4064 values (0.00%) within 1.0 ULPs in range [-1.243482381e-01, 1.243482381e-01]. Example: -1.243482381e-01 returns -1.249951422e-01 instead of -1.249951646e-01
    typedef A0 result_type;

    NT2_FUNCTOR_CALL(1)
    {
      A0 absa0 = nt2::abs(a0);
      A0 t =  absa0+absa0;
      A0 z1 = oneminus(absa0);
      return b_xor(bitofsign(a0), Half<A0>()*log1p((absa0 < Half<A0>()) ? fma(t, absa0/z1, t) : t/z1));
    }
  };
} }
#endif
