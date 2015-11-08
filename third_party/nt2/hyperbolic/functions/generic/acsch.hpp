//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_HYPERBOLIC_FUNCTIONS_GENERIC_ACSCH_HPP_INCLUDED
#define NT2_HYPERBOLIC_FUNCTIONS_GENERIC_ACSCH_HPP_INCLUDED

#include <nt2/hyperbolic/functions/acsch.hpp>
#include <nt2/include/functions/asinh.hpp>
#include <nt2/include/functions/rec.hpp>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::acsch_, tag::cpu_
                            , (A0)
                            , (generic_< unspecified_<A0> >)
                            )
  {
    typedef A0 result_type;
    NT2_FUNCTOR_CALL(1)
    {
      return nt2::asinh(nt2::rec(a0));
    }
  };
} }
#endif
