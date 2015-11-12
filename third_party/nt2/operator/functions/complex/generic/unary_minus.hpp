//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_OPERATOR_FUNCTIONS_COMPLEX_GENERIC_UNARY_MINUS_HPP_INCLUDED
#define NT2_OPERATOR_FUNCTIONS_COMPLEX_GENERIC_UNARY_MINUS_HPP_INCLUDED

#include <nt2/operator/functions/unary_minus.hpp>
#include <nt2/include/functions/real.hpp>
#include <nt2/include/functions/imag.hpp>
#include <nt2/include/functions/bitwise_cast.hpp>

// for optimize
#include <nt2/include/functions/fnma.hpp>
#include <nt2/include/functions/fnms.hpp>

namespace nt2 { namespace ext
{
  // complex
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::unary_minus_, tag::cpu_, (A0)
                            , (generic_< complex_< arithmetic_<A0> > >)
                            )
  {
    typedef A0 result_type;
    NT2_FUNCTOR_CALL(1)
    {
      return result_type(-nt2::real(a0),-nt2::imag(a0));
    }
  };


  // dry
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::unary_minus_, tag::cpu_, (A0)
                            , (generic_< dry_< arithmetic_<A0> > >)
                            )
  {
    typedef A0 result_type;
    NT2_FUNCTOR_CALL(1)
    {
      return bitwise_cast<result_type>(-nt2::real(a0));
    }
  };
} }

#endif
