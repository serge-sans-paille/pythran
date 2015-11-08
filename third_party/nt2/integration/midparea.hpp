//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_INTEGRATION_MIDPAREA_HPP_INCLUDED
#define NT2_INTEGRATION_MIDPAREA_HPP_INCLUDED

#include <nt2/include/functions/average.hpp>
#include <nt2/include/functions/fma.hpp>
#include <nt2/include/functions/multiplies.hpp>
#include <nt2/include/functions/minus.hpp>
#include <nt2/include/constants/half.hpp>
#include <nt2/sdk/meta/as_real.hpp>

namespace nt2
{
  namespace details
  {

    template < class R, class V, class F, class X>
    inline R
    midparea( F f, const X& a, const X& b)
    {
      typedef typename meta::as_real<X>::type real_t;
      // Return q = (b-a)*f((a+b)/2). Although formally correct as a low
      // order quadrature formula, this function is only used to return
      // nan or zero of the appropriate class when a == b, is_nan(a), or
      // is_nan(b).
      X tmp = nt2::multiplies(b, nt2::Half<real_t>());
      X x = nt2::fma(a, nt2::Half<real_t>(), tmp);
      V fx = f(x);
      return nt2::multiplies((b-a), f(x));
  }
  }
}


#endif
