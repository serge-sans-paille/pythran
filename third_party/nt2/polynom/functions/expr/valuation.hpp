//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_POLYNOM_FUNCTIONS_EXPR_VALUATION_HPP_INCLUDED
#define NT2_POLYNOM_FUNCTIONS_EXPR_VALUATION_HPP_INCLUDED
#include <nt2/polynom/functions/valuation.hpp>
#include <nt2/include/functions/reduce.hpp>
#include <nt2/include/functions/numel.hpp>
#include <nt2/include/functions/if_zero_else_one.hpp>
#include <nt2/include/functions/is_nez.hpp>


namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::valuation_, tag::cpu_
                              , (A0)
                              , ((ast_<A0, nt2::container::domain>))
                            )
  {

    typedef ptrdiff_t result_type;
    NT2_FUNCTOR_CALL(1)
    {
      ptrdiff_t na0 = nt2::numel(a0);
      for(ptrdiff_t i=na0; i!= 0; --i)
      {
        if (nt2::is_nez(a0(i))) {return na0-i; }
      }
      return -1;
    }
  };
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::valuation_, tag::cpu_
                            , (A0)
                            , (scalar_<unspecified_ < A0> > )
                            )
  {

    typedef ptrdiff_t result_type;
    NT2_FUNCTOR_CALL(1)
    {
      return -real(if_zero_else_one(a0));
    }
  };
} }


#endif
