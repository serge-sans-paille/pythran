//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_EXPONENTIAL_FUNCTIONS_COMPLEX_GENERIC_POW_ABS_HPP_INCLUDED
#define NT2_EXPONENTIAL_FUNCTIONS_COMPLEX_GENERIC_POW_ABS_HPP_INCLUDED

#include <nt2/exponential/functions/pow_abs.hpp>
#include <nt2/include/functions/abs.hpp>
#include <nt2/include/functions/exp.hpp>
#include <nt2/include/functions/log.hpp>
#include <nt2/include/functions/real.hpp>
#include <nt2/sdk/complex/meta/as_complex.hpp>
#include <nt2/sdk/complex/meta/as_real.hpp>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::pow_abs_, tag::cpu_
                            , (A0)(A1)
                            , (generic_< unspecified_<A0> >)
                              (generic_< complex_<floating_<A1> > >)
                            )
  {
    typedef typename meta::as_complex<A0>::type result_type;
    NT2_FUNCTOR_CALL(2)
    {
      return exp(a1*log(nt2::abs(a0)));
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::pow_abs_, tag::cpu_
                            , (A0)(A1)
                            , (generic_< complex_<floating_<A0> > >)
                              (generic_< arithmetic_<A1> >)
                            )
  {
    typedef typename meta::as_real<A0>::type result_type;
    NT2_FUNCTOR_CALL(2)
    {
      return nt2::pow_abs(nt2::abs(a0), a1);
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::pow_abs_, tag::cpu_
                            , (A0)(A1)
                            , (generic_< complex_<floating_<A0> > >)
                              (generic_< dry_<floating_<A1> > >)
                            )
  {
    typedef typename meta::as_real<A0>::type result_type;
    NT2_FUNCTOR_CALL(2)
    {
      return nt2::pow_abs(nt2::abs(a0), nt2::real(a1));
    }
  };

} }


#endif
