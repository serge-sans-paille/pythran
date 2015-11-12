//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_OPERATOR_FUNCTIONS_COMPLEX_GENERIC_DIVIDES_HPP_INCLUDED
#define NT2_OPERATOR_FUNCTIONS_COMPLEX_GENERIC_DIVIDES_HPP_INCLUDED
#include <nt2/operator/functions/divides.hpp>
#include <nt2/include/functions/abs.hpp>
#include <nt2/include/functions/real.hpp>
#include <nt2/include/functions/imag.hpp>
#include <nt2/include/functions/minus.hpp>
#include <nt2/include/functions/multiplies.hpp>
#include <nt2/include/functions/is_inf.hpp>
#include <nt2/include/functions/is_finite.hpp>
#include <nt2/include/functions/is_eqz.hpp>
#include <nt2/include/functions/unary_minus.hpp>
#include <nt2/include/functions/plus.hpp>
#include <nt2/include/functions/rec.hpp>
#include <nt2/include/functions/sqr_abs.hpp>
#include <nt2/include/functions/copysign.hpp>
#include <nt2/arithmetic/functions/complex/generic/conj.hpp>
#include <nt2/include/functions/ldexp.hpp>
#include <nt2/include/constants/inf.hpp>
#include <nt2/sdk/complex/complex.hpp>
#include <nt2/sdk/complex/dry.hpp>
#include <nt2/sdk/complex/meta/as_real.hpp>
#include <nt2/sdk/meta/as_integer.hpp>
#include <nt2/include/functions/bitwise_cast.hpp>

namespace nt2 { namespace ext
{
  // complex/complex
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::divides_, tag::cpu_, (A0)
                            , (generic_< complex_< arithmetic_<A0> > >)
                              (generic_< complex_< arithmetic_<A0> > >)
                            )
  {
    typedef A0 result_type;
    NT2_FUNCTOR_CALL_REPEAT(2)
    {
      typedef typename meta::as_real<result_type>::type rtype;
      typedef typename meta::as_integer<rtype>::type itype;
      rtype rr =  nt2::abs(nt2::real(a1));
      rtype ii =  nt2::abs(nt2::imag(a1));
      itype e =  -if_else(lt(rr, ii), exponent(ii), exponent(rr));
      A0 aa1 =  nt2::ldexp(a1, e);
      rtype denom =  sqr_abs(aa1);
      A0 num = nt2::multiplies(a0, conj(aa1));
      A0 r =  ldexp(nt2::divides(num, denom), e);
      if (nt2::all(is_finite(r))) return r;
      r = if_else(is_eqz(denom), nt2::multiplies(a0, copysign(Inf<rtype>(), nt2::real(a1))), r);
      r = if_else(is_inf(a1),    nt2::multiplies(a0, rec(copysign(denom, nt2::real(a1)))), r);
      return r;
    }
  };

  // complex/real
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::divides_, tag::cpu_, (A0)(A1)
                            , (generic_< arithmetic_<A0> >)
                              (generic_< complex_< arithmetic_<A1> > >)
                            )
  {
    typedef A1 result_type;
    NT2_FUNCTOR_CALL(2)
    {
      A0 tmp = a0/sqr_abs(a1);
      return if_else(is_inf(a1), result_type(tmp), tmp*conj(a1));
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::divides_, tag::cpu_, (A0)(A1)
                            , (generic_< complex_< arithmetic_<A0> > >)
                              (generic_< arithmetic_<A1> >)
                            )
  {
    typedef A0 result_type;
    NT2_FUNCTOR_CALL(2)
    {
      return nt2::multiplies(a0, rec(a1));
    }
  };

  // dry/complex
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::divides_, tag::cpu_, (A0)(A1)
                            , (generic_< dry_< arithmetic_<A0> > >)
                              (generic_< complex_< arithmetic_<A1> > >)
                            )
  {
    typedef typename meta::as_real<A0>::type rtype;
    typedef typename meta::as_complex<A0>::type result_type;
    NT2_FUNCTOR_CALL(2)
    {
      return nt2::divides(nt2::real(a0), a1);
    }
  };

  // complex/dry
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::divides_, tag::cpu_, (A0)(A1)
                            , (generic_< complex_< arithmetic_<A0> > > )
                              (generic_< dry_< arithmetic_<A1> > >)
                            )
  {
    typedef typename meta::as_real<A1>::type rtype;
    typedef typename meta::as_complex<A1>::type result_type;
    NT2_FUNCTOR_CALL(2)
    {
      return result_type(nt2::real(a0)/nt2::real(a1), nt2::imag(a0)/nt2::real(a1));
    }
  };

  // dry/arithmetic
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::divides_, tag::cpu_, (A0)(A1)
                            , (generic_< dry_< arithmetic_<A0> > >)
                              (generic_< arithmetic_<A1> >)
                            )
  {
    typedef A0 result_type;
    NT2_FUNCTOR_CALL(2)
    {
      return bitwise_cast<result_type>(nt2::real(a0)/a1);
    }
  };

  // arithmetic/dry
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::divides_, tag::cpu_, (A0)(A1)
                            , (generic_< arithmetic_<A0> >)
                              (generic_< dry_< arithmetic_<A1> > >)

                            )
  {
    typedef A1 result_type;
    NT2_FUNCTOR_CALL(2)
    {
      return bitwise_cast<result_type>(a0/nt2::real(a1));
    }
  };

  // dry/dry
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::divides_, tag::cpu_, (A0)
                            , (generic_< dry_< arithmetic_<A0> > >)
                              (generic_< dry_< arithmetic_<A0> > >)

                            )
  {
    typedef A0 result_type;
    NT2_FUNCTOR_CALL_REPEAT(2)
    {
      return bitwise_cast<result_type>(nt2::real(a0)/nt2::real(a1));
    }
  };

} }

#endif
