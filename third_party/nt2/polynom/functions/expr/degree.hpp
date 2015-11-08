//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_POLYNOM_FUNCTIONS_EXPR_DEGREE_HPP_INCLUDED
#define NT2_POLYNOM_FUNCTIONS_EXPR_DEGREE_HPP_INCLUDED

#include <nt2/polynom/functions/degree.hpp>
#include <nt2/include/functions/reduce.hpp>
#include <nt2/include/functions/if_zero_else_one.hpp>
#include <nt2/include/functions/size.hpp>
#include <nt2/include/functions/real.hpp>

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is arithmetic_
/////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::degree_, tag::cpu_
                            , (A0)
                            , ((ast_<A0, nt2::container::domain>))
                            )
  {

    typedef ptrdiff_t result_type;
    NT2_FUNCTOR_CALL(1)
    {
      return nt2::size(reduce(a0), 2)-1; ;
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::degree_, tag::cpu_
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
