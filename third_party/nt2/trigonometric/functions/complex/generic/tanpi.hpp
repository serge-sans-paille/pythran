//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TRIGONOMETRIC_FUNCTIONS_COMPLEX_GENERIC_TANPI_HPP_INCLUDED
#define NT2_TRIGONOMETRIC_FUNCTIONS_COMPLEX_GENERIC_TANPI_HPP_INCLUDED
#include <nt2/trigonometric/functions/tanpi.hpp>
#include <nt2/include/functions/sincospi.hpp>
#include <nt2/include/functions/sinhcosh.hpp>
#include <nt2/include/functions/real.hpp>
#include <nt2/include/functions/imag.hpp>
#include <nt2/include/functions/tanh.hpp>
#include <nt2/include/functions/is_eqz.hpp>
#include <nt2/include/functions/sign.hpp>
#include <nt2/include/functions/abs.hpp>
#include <nt2/include/functions/if_zero_else.hpp>
#include <nt2/include/constants/pi.hpp>
#include <nt2/sdk/complex/meta/as_complex.hpp>
#include <nt2/sdk/complex/meta/as_real.hpp>
/* ctan (x + I * y) = (sin (2 * x)  +  I * sinh(2 * y)) / (cos (2 * x)  +  cosh (2 * y)) */
namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::tanpi_, tag::cpu_, (A0)
                            , (generic_< complex_< arithmetic_<A0> > >)
                            )
  {
    typedef A0 result_type;
    NT2_FUNCTOR_CALL(1)
    {
      typedef typename meta::as_real<A0>::type rtype;
      result_type aa0 =  a0+a0;
      rtype c, s, ch, sh;
      sincospi(nt2::real(aa0), s, c);
      sinhcosh(nt2::imag(aa0)*nt2::Pi<rtype>(), sh, ch);
      rtype tmp = c+ch;
      rtype r_part = if_zero_else(is_imag(a0),s/tmp);
      rtype i_part = if_zero_else(is_real(a0),sh/tmp);
      return result_type(r_part, i_part);
    }
  };


  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::tanpi_, tag::cpu_, (A0)
                            , (generic_< dry_< arithmetic_<A0> > >)
                            )
  {
    typedef A0 result_type;
    NT2_FUNCTOR_CALL(1)
    {
      return result_type(nt2::tanpi(nt2::real(a0)));
    }
  };
} }

#endif
