//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_BOOLEAN_FUNCTIONS_COMPLEX_GENERIC_IF_ALLBITS_ELSE_HPP_INCLUDED
#define NT2_BOOLEAN_FUNCTIONS_COMPLEX_GENERIC_IF_ALLBITS_ELSE_HPP_INCLUDED

#include <nt2/boolean/functions/if_allbits_else.hpp>
#include <nt2/include/functions/real.hpp>
#include <nt2/include/functions/imag.hpp>
#include <nt2/include/functions/is_nez.hpp>
#include <nt2/sdk/meta/as_logical.hpp>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::if_allbits_else_, tag::cpu_, (A0)(A1)
                            , (generic_< logical_<A0> >)
                              (generic_< complex_<floating_<A1> > >)
                            )
  {
    typedef A1 result_type;
    result_type  operator()(A0 const& a0, A1 const& a1) const
    {
      return result_type(if_allbits_else(a0, real(a1)), if_allbits_else(a0, imag(a1)));
    }
  };
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::if_allbits_else_, tag::cpu_, (A0)(A1)
                            , (generic_< complex_<floating_<A0> > > )
                              (generic_< complex_<floating_<A1> > > )
                            )
  {
    typedef A1 result_type;
    result_type  operator()(A0 const& a0, A1 const& a1) const
    {
      return result_type(if_allbits_else(is_nez(a0), real(a1)), if_allbits_else(is_nez(a0), imag(a1)));
    }
  };
} }

#endif
