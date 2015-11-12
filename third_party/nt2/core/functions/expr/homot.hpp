//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_EXPR_HOMOT_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_EXPR_HOMOT_HPP_INCLUDED

#include <nt2/core/functions/homot.hpp>
#include <nt2/core/container/dsl.hpp>

namespace nt2 { namespace ext
{
  /// INTERNAL ONLY
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::homot_, tag::cpu_
                            , (A0)(A1)
                            , (scalar_< unspecified_<A0> >)
                              ((ast_<A1, nt2::container::domain>))
                            )
  {
   BOOST_DISPATCH_RETURNS( 2, ( const A0& a0, const A1& a1)
                          , (nt2::homot( a0, nt2::as_size(a1)))
                          )
  };
} }

#endif
