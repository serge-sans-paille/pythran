//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_REDUCTION_FUNCTIONS_COMPLEX_GENERIC_NBTRUE_HPP_INCLUDED
#define NT2_REDUCTION_FUNCTIONS_COMPLEX_GENERIC_NBTRUE_HPP_INCLUDED
#include <nt2/include/functions/nbtrue.hpp>
#include <nt2/include/functions/imag.hpp>
#include <nt2/include/functions/real.hpp>
#include <nt2/include/functions/if_one_else_zero.hpp>
#include <nt2/sdk/complex/meta/as_complex.hpp>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::nbtrue_, tag::cpu_, (A0)
                            , (generic_< complex_< arithmetic_<A0> > >)
                            )
  {
    typedef typename meta::as_real<A0>::type result_type;
    NT2_FUNCTOR_CALL(1)
    {
      return nt2::nbtrue(if_one_else_zero(a0));
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::nbtrue_, tag::cpu_, (A0)(A1)
                            , (generic_< complex_< arithmetic_<A0> > >)
                              (scalar_< integer_<A1> > )
                            )
  {
    typedef typename meta::as_real<A0>::type result_type;
    inline result_type operator()(A0 const & a0, A1 const &) const
    {
      return nt2::nbtrue(if_one_else_zero(a0));
    }
  };
} }

#endif
