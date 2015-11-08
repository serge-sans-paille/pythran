//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_REDUCTION_FUNCTIONS_COMPLEX_GENERIC_INBTRUE_HPP_INCLUDED
#define NT2_REDUCTION_FUNCTIONS_COMPLEX_GENERIC_INBTRUE_HPP_INCLUDED
#include <nt2/reduction/functions/inbtrue.hpp>
#include <nt2/include/functions/real.hpp>
#include <nt2/include/functions/if_one_else_zero.hpp>


namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::inbtrue_, tag::cpu_, (A0)
                            , (generic_< complex_< arithmetic_<A0> > >)
                            )
  {
    typedef std::size_t result_type;
    NT2_FUNCTOR_CALL(1)
    {
      return nt2::inbtrue(real(if_one_else_zero(a0)));
    }
  };
} }

#endif
