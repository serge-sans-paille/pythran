//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_ELLIPTIC_FUNCTIONS_SCALAR_ELLIPKE_HPP_INCLUDED
#define NT2_ELLIPTIC_FUNCTIONS_SCALAR_ELLIPKE_HPP_INCLUDED
#include <nt2/elliptic/functions/ellipke.hpp>
#include <nt2/include/constants/half.hpp>
#include <nt2/include/constants/inf.hpp>
#include <nt2/include/constants/nan.hpp>
#include <nt2/include/constants/one.hpp>
#include <nt2/include/constants/pio_2.hpp>
#include <nt2/include/constants/zero.hpp>
#include <nt2/include/functions/scalar/average.hpp>
#include <nt2/include/functions/scalar/is_equal.hpp>
#include <nt2/include/functions/scalar/is_greater.hpp>
#include <nt2/include/functions/scalar/is_ltz.hpp>
#include <nt2/include/functions/scalar/ldexp.hpp>
#include <nt2/include/functions/scalar/oneminus.hpp>
#include <nt2/include/functions/scalar/sqr.hpp>
#include <nt2/include/functions/scalar/sqrt.hpp>

namespace nt2 { namespace ext
{

  NT2_FUNCTOR_IMPLEMENTATION(  nt2::tag::ellipke_, tag::cpu_,(A0),
                               (scalar_<floating_<A0> >)
                               (scalar_<floating_<A0> >)
                               (scalar_<floating_<A0> >)
                               (scalar_<floating_<A0> >)
    )
  {
    typedef void result_type;
    inline result_type operator()(A0 const& a0,A0 const& a1, A0 & a2,A0 & a3) const
    {
      if (nt2::is_ltz(a0) || nt2::gt(a0, One<A0>()))
      {
        a2 = nt2::Nan<A0>();
        a3 = nt2::Nan<A0>();
        return;
      }
      A0 m = a0;
      A0 aa0 = One<A0>();;
      A0 bb0 = nt2::sqrt(nt2::oneminus(m));
      A0 s0 = m;
      size_t i1 = 0;
      A0 mm = 1;
      A0 aa1 = nt2::Zero<A0>();
      while (mm > a1) {
        aa1 = nt2::average(aa0, bb0);
        A0 bb1 = nt2::sqrt(aa0*bb0);
        A0 cc1 = nt2::average(aa0, -bb0);
        ++i1;
        mm = nt2::ldexp(nt2::sqr(cc1), i1);
        s0 += mm;
        aa0 = aa1;
        bb0 = bb1;
      };
      if (nt2::is_equal(m, One<A0>()))
      {
        a2 = nt2::Inf<A0>();
        a3 = nt2::One<A0>();
      }
      else
      {
        a2 = nt2::Pio_2<A0>()/aa1;
        a3 = a2*(nt2::One<A0>()-s0*nt2::Half<A0>());
      }
    }
  };

} }
#endif
