//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TRIGONOMETRIC_FUNCTIONS_COMPLEX_GENERIC_SIND_HPP_INCLUDED
#define NT2_TRIGONOMETRIC_FUNCTIONS_COMPLEX_GENERIC_SIND_HPP_INCLUDED
#include <nt2/trigonometric/functions/sind.hpp>
#include <nt2/include/functions/sincosd.hpp>
#include <nt2/include/functions/sinhcosh.hpp>
#include <nt2/include/functions/sinh.hpp>
#include <nt2/include/functions/cosh.hpp>
#include <nt2/include/functions/real.hpp>
#include <nt2/include/functions/imag.hpp>
#include <nt2/include/functions/sin.hpp>
#include <nt2/include/functions/any.hpp>
#include <nt2/include/functions/is_eqz.hpp>
#include <nt2/include/functions/sign.hpp>
#include <nt2/include/functions/abs.hpp>
#include <nt2/include/functions/if_zero_else.hpp>
#include <nt2/include/functions/is_real.hpp>
#include <nt2/include/functions/is_imag.hpp>
#include <nt2/sdk/complex/meta/as_complex.hpp>
#include <nt2/sdk/complex/meta/as_real.hpp>
#include <nt2/include/functions/sind.hpp>
#include <nt2/include/functions/cosd.hpp>
#include <nt2/include/functions/mul_minus_i.hpp>
#include <nt2/include/functions/mul_i.hpp>
#include <nt2/include/functions/multiplies.hpp>
#include <nt2/include/constants/deginrad.hpp>

/* csin (x + I * y) = sin (x) * cosh (y)  + I * (cos (x) * sinh (y)) */
namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::sind_, tag::cpu_, (A0)
                            , (generic_< complex_< arithmetic_<A0> > >)
                            )
  {
    typedef A0 result_type;
    NT2_FUNCTOR_CALL(1)
    {
      typedef typename meta::as_real<A0>::type rtype;
      //      return mul_minus_i(nt2::sinh(mul_i(a0*Deginrad<rtype>())));
      result_type a00 =  mul_i(a0);
      rtype c, s, ch, sh;
      sincosd(nt2::imag(a00), s, c);
      a00 = nt2::multiplies(a00, Deginrad<rtype>());
      sinhcosh(nt2::real(a00), sh, ch);
      rtype r = c*sh;
      rtype i = s*ch;
      result_type res = result_type(r, i);
      if (nt2::any(is_invalid(a00)))
      {
        r = if_else(logical_and(is_inf(nt2::real(a00)), is_invalid(nt2::imag(a00))), nt2::real(a00), r);
        i = if_else(logical_and(is_inf(nt2::real(a00)), is_nan(nt2::imag(a00))), nt2::Nan<rtype>(), i);
        r = if_else(is_nan(nt2::real(a00)), nt2::real(a00), r);
        i = if_else(is_nan(nt2::real(a00)), nt2::real(a00), i);
        i = if_zero_else(is_real(a00), i);
        r = if_zero_else(is_imag(a00), r);
        res =  result_type(r, i);//this is sinh(mul_i(a0)*Deginrad<rtype>())
      }
      return mul_minus_i(res);
    }
  };


  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::sind_, tag::cpu_, (A0)
                              , (generic_< dry_< arithmetic_<A0> > >)
    )
  {
    typedef typename meta::as_real<A0>::type rA0;
    typedef typename meta::as_dry<rA0>::type result_type;
    NT2_FUNCTOR_CALL(1)
    {
      return bitwise_cast<result_type>(nt2::sind(nt2::real(a0)));
    }
  };
} }

#endif

