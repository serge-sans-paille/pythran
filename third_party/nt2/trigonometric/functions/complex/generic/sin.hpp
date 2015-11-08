//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TRIGONOMETRIC_FUNCTIONS_COMPLEX_GENERIC_SIN_HPP_INCLUDED
#define NT2_TRIGONOMETRIC_FUNCTIONS_COMPLEX_GENERIC_SIN_HPP_INCLUDED
#include <nt2/trigonometric/functions/sin.hpp>
#include <nt2/include/functions/sinh.hpp>
#include <nt2/include/functions/sin.hpp>
#include <nt2/include/functions/bitwise_cast.hpp>
#include <nt2/include/functions/mul_i.hpp>
#include <nt2/include/functions/mul_minus_i.hpp>
#include <nt2/sdk/complex/meta/as_dry.hpp>

/* csin (x + I * y) = sin (x) * cosh (y)  + I * (cos (x) * sinh (y)) */
namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::sin_, tag::cpu_, (A0)
                            , (generic_< complex_< arithmetic_<A0> > >)
                            )
  {
    typedef A0 result_type;
    NT2_FUNCTOR_CALL(1)
    {
      return mul_minus_i(nt2::sinh(mul_i(a0)));
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::sin_, tag::cpu_, (A0)
                            , (generic_< dry_< arithmetic_<A0> > >)
                            )
  {
    typedef typename meta::as_dry<A0>::type result_type;
    NT2_FUNCTOR_CALL(1)
    {
      return bitwise_cast<result_type>(nt2::sin(nt2::real(a0)));
    }
  };
} }

#endif
