//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_EXPONENTIAL_FUNCTIONS_COMPLEX_GENERIC_POW2_HPP_INCLUDED
#define NT2_EXPONENTIAL_FUNCTIONS_COMPLEX_GENERIC_POW2_HPP_INCLUDED
#include <nt2/exponential/functions/pow2.hpp>
#include <nt2/include/functions/exp2.hpp>
#include <nt2/include/functions/sincos.hpp>
#include <nt2/include/functions/real.hpp>
#include <nt2/include/functions/imag.hpp>
#include <nt2/include/constants/log_2.hpp>
#include <nt2/include/functions/is_equal.hpp>
#include <nt2/include/functions/logical_or.hpp>
#include <nt2/include/constants/minf.hpp>
#include <nt2/sdk/complex/meta/as_complex.hpp>
#include <nt2/sdk/complex/meta/as_real.hpp>
#include <nt2/sdk/error/warning.hpp>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::pow2_, tag::cpu_
                            , (A0)
                            , (generic_< complex_<floating_<A0> > >)
                            )
  {
    typedef A0 result_type;
    NT2_FUNCTOR_CALL(1)
    {
      typedef typename meta::as_real<A0>::type rtype;
      rtype c, s;
      sincos(nt2::imag(a0)*Log_2<rtype>(), s, c);
      rtype rho = nt2::exp2(nt2::real(a0));
      return if_else(logical_or(is_real(a0), eq(nt2::real(a0), Minf<rtype>())),
                     result_type(rho, Zero<rtype>()),
                     rho*result_type(c, s));
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::pow2_, tag::cpu_
                            , (A0)
                            , (generic_< dry_<floating_<A0> > >)
                            )
  {
    typedef A0 result_type;
    NT2_FUNCTOR_CALL(1)
    {
      return bitwise_cast<result_type>(nt2::pow2(nt2::real(a0)));
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::pow2_, tag::cpu_
                              , (A0)(A1)
                            , (generic_< complex_<floating_<A0> > >)
                              (generic_< integer_<A1> >)
                            )
  {
    typedef typename meta::as_dry<A0>::type result_type;
    NT2_FUNCTOR_CALL(2)
      {
        //        NT2_WARN(is_real(a0), "Warning: Imag part is ignored.");
        return bitwise_cast<result_type>(pow2(real(a0), a1));
      }
  };


  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::pow2_, tag::cpu_
                              , (A0)(A1)
                              , (generic_< dry_<floating_<A0> > >)
                              (generic_< integer_<A1> >)
                              )
  {
    typedef A0 result_type;
    NT2_FUNCTOR_CALL(2)
      {
        return bitwise_cast<result_type>(pow2(real(a0), a1));
      }
  };


} }


#endif
