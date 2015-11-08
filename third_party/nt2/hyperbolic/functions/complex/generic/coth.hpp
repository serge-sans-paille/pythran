//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_HYPERBOLIC_FUNCTIONS_COMPLEX_GENERIC_COTH_HPP_INCLUDED
#define NT2_HYPERBOLIC_FUNCTIONS_COMPLEX_GENERIC_COTH_HPP_INCLUDED
#include <nt2/hyperbolic/functions/coth.hpp>
#include <nt2/include/functions/sincos.hpp>
#include <nt2/include/functions/sinhcosh.hpp>
#include <nt2/include/functions/tan.hpp>
#include <nt2/include/functions/real.hpp>
#include <nt2/include/functions/imag.hpp>
#include <nt2/include/functions/coth.hpp>
#include <nt2/include/functions/cot.hpp>
#include <nt2/include/functions/is_eqz.hpp>
#include <nt2/include/functions/sign.hpp>
#include <nt2/include/functions/abs.hpp>
#include <nt2/sdk/complex/meta/as_complex.hpp>
#include <nt2/sdk/complex/meta/as_real.hpp>
#include <nt2/sdk/complex/meta/as_dry.hpp>
#include <nt2/include/functions/bitwise_cast.hpp>
#include <nt2/include/functions/rec.hpp>
//coth ( x + iy ) = coth ( x ) + i . tan ( y ) 1 + i . coth ( x ) tan ( y ) .
namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::coth_, tag::cpu_, (A0)
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
      return if_allbits_else(is_eqz(a0), (c+ch)/(result_type(sh, s)));
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::coth_, tag::cpu_, (A0)
                            , (generic_< dry_< arithmetic_<A0> > >)
                            )
  {
    typedef typename meta::as_real<A0>::type rA0;
    typedef typename meta::as_dry<rA0>::type result_type;
    NT2_FUNCTOR_CALL(1)
    {
      return bitwise_cast<result_type>(-nt2::coth(nt2::real(a0)));
    }
  };

} }

#endif
