//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_HYPERBOLIC_FUNCTIONS_COMPLEX_GENERIC_COSH_HPP_INCLUDED
#define NT2_HYPERBOLIC_FUNCTIONS_COMPLEX_GENERIC_COSH_HPP_INCLUDED
#include <nt2/hyperbolic/functions/cosh.hpp>
#include <nt2/include/functions/sincos.hpp>
#include <nt2/include/functions/sinhcosh.hpp>
#include <nt2/include/functions/cosh.hpp>
#include <nt2/include/functions/sinh.hpp>
#include <nt2/include/functions/real.hpp>
#include <nt2/include/functions/imag.hpp>
#include <nt2/include/functions/sin.hpp>
#include <nt2/include/functions/cos.hpp>
#include <nt2/include/functions/is_eqz.hpp>
#include <nt2/include/functions/is_inf.hpp>
#include <nt2/include/functions/sign.hpp>
#include <nt2/include/functions/abs.hpp>
#include <nt2/include/constants/sqrt_2o_2.hpp>
#include <nt2/sdk/complex/meta/as_complex.hpp>
#include <nt2/sdk/complex/meta/as_real.hpp>
#include <nt2/sdk/complex/meta/as_dry.hpp>

//cosh(x + iy) = cosh(x)cos(y) + i(sinh(x)sin(y))
namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::cosh_, tag::cpu_, (A0)
                            , (generic_< complex_< arithmetic_<A0> > >)
                            )
  {
    typedef A0 result_type;
    NT2_FUNCTOR_CALL(1)
    {
      typedef typename meta::as_real<A0>::type rtype;
      rtype c, s, ch, sh;
      sincos(nt2::imag(a0), s, c);
      sinhcosh(nt2::real(a0), sh, ch);

      rtype r = c*ch;
      rtype i = s*sh;
      i = if_zero_else(logical_or(is_imag(a0), is_real(a0)), i);
      result_type res = result_type(r, i);
      if (none(is_invalid(a0))) return res;
      res = if_else(logical_and(is_inf(nt2::real(a0)), is_invalid(nt2::imag(a0))),
                    result_type( nt2::Inf<rtype>(), nt2::Nan<rtype>()), res);
      res = if_else(logical_and(is_nan(nt2::real(a0)), is_inf    (nt2::imag(a0))),
                    result_type( nt2::Nan<rtype>(), nt2::Nan<rtype>()), res);
      return res;
     }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::cosh_, tag::cpu_, (A0)
                            , (generic_< dry_< arithmetic_<A0> > >)
                            )
  {
    typedef A0 result_type;
    NT2_FUNCTOR_CALL(1)
    {
      return bitwise_cast<result_type>(nt2::cosh(nt2::real(a0)));
    }
  };
} }

#endif
