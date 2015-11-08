//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_EXPONENTIAL_FUNCTIONS_COMPLEX_GENERIC_LOG1P_HPP_INCLUDED
#define NT2_EXPONENTIAL_FUNCTIONS_COMPLEX_GENERIC_LOG1P_HPP_INCLUDED

#include <nt2/exponential/functions/log1p.hpp>
#include <nt2/include/functions/log1p.hpp>
#include <nt2/include/functions/oneplus.hpp>
#include <nt2/include/constants/two.hpp>
#include <nt2/include/functions/real.hpp>
#include <nt2/include/functions/is_real.hpp>
#include <nt2/include/functions/is_nan.hpp>
#include <nt2/include/functions/arg.hpp>
#include <nt2/include/functions/imag.hpp>
#include <nt2/sdk/complex/meta/as_complex.hpp>
#include <nt2/sdk/complex/meta/as_real.hpp>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::log1p_, tag::cpu_
                            , (A0)
                            , ((generic_<complex_<floating_<A0> > >))
                            )
  {
    typedef A0 result_type;
    NT2_FUNCTOR_CALL(1)
    {
      typedef typename meta::as_real<A0>::type rtype;
      result_type m = oneplus(a0);
      rtype theta = if_else(logical_and(nt2::is_real(a0), nt2::is_nan(a0)), Zero<rtype>(), nt2::arg(m)) ;
      rtype ra =  nt2::real(a0);
      rtype rb2 =  sqr(nt2::imag(a0));
      return result_type(Half<rtype>()*nt2::log1p(ra*(ra+Two<rtype>())+rb2), theta);
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::log1p_, tag::cpu_
                            , (A0)
                            , (generic_< dry_<floating_<A0> > >)
                            )
  {
    typedef typename meta::as_real<A0>::type rtype;
    typedef typename meta::as_complex<rtype>::type result_type;
    NT2_FUNCTOR_CALL(1)
    {
      rtype m = oneplus(nt2::real(a0));
      rtype theta = nt2::arg(m);
      rtype ra =  nt2::real(a0);
      return result_type(Half<rtype>()*nt2::log1p(ra*(ra+Two<rtype>())), theta);
    }
  };
} }

#endif
