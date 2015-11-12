//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_HYPERBOLIC_FUNCTIONS_COMPLEX_GENERIC_TANH_HPP_INCLUDED
#define NT2_HYPERBOLIC_FUNCTIONS_COMPLEX_GENERIC_TANH_HPP_INCLUDED
#include <nt2/hyperbolic/functions/tanh.hpp>
#include <nt2/include/functions/sincos.hpp>
#include <nt2/include/functions/sinhcosh.hpp>
#include <nt2/include/functions/tan.hpp>
#include <nt2/include/functions/real.hpp>
#include <nt2/include/functions/plus.hpp>
#include <nt2/include/functions/imag.hpp>
#include <nt2/include/functions/tanh.hpp>
#include <nt2/include/functions/is_eqz.hpp>
#include <nt2/include/functions/sign.hpp>
#include <nt2/include/functions/abs.hpp>
#include <nt2/sdk/complex/meta/as_complex.hpp>
#include <nt2/sdk/complex/meta/as_real.hpp>
#include <nt2/sdk/complex/meta/as_dry.hpp>
#include <nt2/include/functions/bitwise_cast.hpp>

//tanh ( x + iy ) = tanh ( x ) + i . tan ( y ) 1 + i . tanh ( x ) tan ( y ) .
namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::tanh_, tag::cpu_, (A0)
                            , (generic_< complex_< arithmetic_<A0> > >)
                            )
  {
    typedef A0 result_type;
    NT2_FUNCTOR_CALL(1)
    {
      typedef typename meta::as_real<A0>::type rtype;
      result_type aa0 =  a0+a0;
      rtype c, s, ch, sh;
      sincos(nt2::imag(aa0), s, c);
      sinhcosh(nt2::real(aa0), sh, ch);
      rtype tmp = c+ch;
      rtype r_part = if_zero_else(is_imag(a0),sh/tmp);
      rtype i_part = if_zero_else(is_real(a0),s/tmp);
      return result_type(r_part, i_part);
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::tanh_, tag::cpu_, (A0)
                            , (generic_< dry_< arithmetic_<A0> > >)
                            )
  {
    typedef typename meta::as_dry<A0>::type result_type;

    NT2_FUNCTOR_CALL(1)
    {
      return bitwise_cast<result_type>(nt2::tanh(nt2::real(a0)));
    }
  };

} }

#endif
