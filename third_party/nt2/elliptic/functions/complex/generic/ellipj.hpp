//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_ELLIPTIC_FUNCTIONS_COMPLEX_GENERIC_ELLIPJ_HPP_INCLUDED
#define NT2_ELLIPTIC_FUNCTIONS_COMPLEX_GENERIC_ELLIPJ_HPP_INCLUDED

#include <nt2/include/functions/ellipj.hpp>
#include <nt2/include/constants/eps.hpp>
#include <nt2/include/functions/sqr.hpp>
#include <nt2/include/functions/rec.hpp>
#include <nt2/include/functions/real.hpp>
#include <nt2/include/functions/imag.hpp>
#include <nt2/include/functions/is_real.hpp>
#include <nt2/include/functions/multiplies.hpp>
#include <nt2/include/functions/unary_minus.hpp>
#include <nt2/include/functions/if_else_zero.hpp>
#include <nt2/include/functions/is_nez.hpp>
#include <nt2/include/functions/all.hpp>
#include <nt2/sdk/complex/meta/as_complex.hpp>
#include <nt2/sdk/meta/as_logical.hpp>


namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION(  nt2::tag::ellipj_, tag::cpu_,
                               (A0)(A1)(A2),
                               (generic_<complex_<floating_<A0> > >)
                               (generic_<floating_<A1> >)
                               (scalar_<floating_<A2> >)
                               (generic_<complex_<floating_<A0> > >)
                               (generic_<complex_<floating_<A0> > >)
                               (generic_<complex_<floating_<A0> > >)
                            )
  {
    typedef void result_type;
    inline result_type operator()(A0 const& a0, A1 const & a1, A2 const & a2,
                                  A0 & a3, A0 & a4, A0 & a5) const
    {
      typedef typename meta::as_real<A0>::type rA0;
      typedef typename meta::as_logical<A1>::type lA1;
      rA0 snr, cnr, dnr;
      rA0 sni, cni, dni;
      ellipj(real(a0),a1,a2,snr,cnr,dnr);
      if (all(is_real(a0)))
      {
        a3 = snr; a4 = cnr; a5 = dnr;
        return;
      }
      ellipj(imag(a0),oneminus(a1),a2,sni,cni,dni);
      lA1 isnezm = is_nez(a1);
      rA0 delta =rec(seladd(isnezm, sqr(cni), a1*sqr(snr*sni)));
      rA0 dnrsni =  dnr*sni;
      a3 = A0(snr*dni*delta, dnrsni*delta*cnr*cni);
      a4 = A0(cnr*cni*delta, -dnrsni*delta*snr*dni);
      a5 = A0(dnr*cni*dni*delta, -if_else_zero(isnezm,a1*snr*cnr*sni*delta));
      //TODO treat properly the limit cases ie delta = inf
    }
  };
    NT2_FUNCTOR_IMPLEMENTATION(  nt2::tag::ellipj_, tag::cpu_,
                               (A0)(A1)(A2),
                               (generic_<complex_<floating_<A0> > >)
                               (generic_<floating_<A1> >)
                               (unspecified_<A2>)
                               (generic_<complex_<floating_<A0> > >)
                               (generic_<complex_<floating_<A0> > >)
                               (generic_<complex_<floating_<A0> > >)
                            )
  {
    typedef void result_type;
    inline result_type operator()(A0 const& a0, A1 const & a1, A2 const &,
                                  A0 & a3, A0 & a4, A0 & a5) const
    {
      typedef typename meta::as_real<A0>::type rA0;
      ellipj(a0, a1, Eps<rA0>(), a3, a4, a5);
    }
  };
} }
#endif
