//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TRIGONOMETRIC_FUNCTIONS_COMPLEX_GENERIC_CSCPI_HPP_INCLUDED
#define NT2_TRIGONOMETRIC_FUNCTIONS_COMPLEX_GENERIC_CSCPI_HPP_INCLUDED
#include <nt2/trigonometric/functions/cscpi.hpp>
#include <nt2/include/functions/sinpi.hpp>
#include <nt2/include/functions/rec.hpp>
#include <nt2/include/constants/cnan.hpp>
#include <nt2/include/constants/nan.hpp>
#include <nt2/sdk/complex/meta/as_complex.hpp>
#include <nt2/sdk/complex/meta/as_real.hpp>
#include <nt2/sdk/complex/meta/as_dry.hpp>

//cscpi(x+iy)=rec(sinpi(x+iy)).
namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::cscpi_, tag::cpu_, (A0)
                            , (generic_< complex_< arithmetic_<A0> > >)
                            )
  {
    typedef A0 result_type;
    NT2_FUNCTOR_CALL(1)
    {
      return if_else(is_eqz(a0),
                     Cnan<result_type>(),
                     rec(nt2::sinpi(a0))
                     );
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::cscpi_, tag::cpu_, (A0)
                            , (generic_< dry_< arithmetic_<A0> > >)
                            )
  {
    typedef A0 result_type;
    NT2_FUNCTOR_CALL(1)
    {
      return if_else(is_eqz(a0),
                     Nan<result_type>(),
                     rec(nt2::sinpi(a0))
                     );
    }
  };

} }

#endif
