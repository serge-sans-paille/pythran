//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_SCALAR_REPMAT_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_SCALAR_REPMAT_HPP_INCLUDED

#include <nt2/core/functions/repmat.hpp>
#include <nt2/include/functions/repnum.hpp>
#include <nt2/core/container/dsl.hpp>

namespace nt2 { namespace ext
{
  //============================================================================
  // Generates from an expression and an extent
  //============================================================================
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::repmat_, tag::cpu_
                            , (A0)(A1)
                            , (scalar_< unspecified_<A0> >)
                              (fusion_sequence_<A1>)
                            )
  {
    BOOST_DISPATCH_RETURNS( 2, (A0 a0, A1 const& a1)
                          , nt2::repnum(a0,a1)
                          );
  };

  //============================================================================
  // Generates from an expression and a size
  //============================================================================
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::repmat_, tag::cpu_
                            , (A0)(A1)
                            , (scalar_< unspecified_<A0> >)
                              ((ast_<A1, nt2::container::domain>))
                            )
  {
    BOOST_DISPATCH_RETURNS( 2, (A0 a0, A1 const& a1)
                          , nt2::repnum(a0,a1)
                          );
  };

  //============================================================================
  // Generates from an expression and a single size
  //============================================================================
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::repmat_, tag::cpu_
                            , (A0)(A1)
                            , (scalar_< unspecified_<A0> >)
                              (scalar_< integer_<A1> >)
                            )
  {
    BOOST_DISPATCH_RETURNS( 2, (A0 a0, A1 a1)
                          , nt2::repnum(a0,a1)
                          );
  };

  //============================================================================
  // Generates from an expression and two sizes
  //============================================================================
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::repmat_, tag::cpu_
                            , (A0)(A1)(A2)
                            , (scalar_< unspecified_<A0> >)
                              (scalar_< integer_<A1> >)
                              (scalar_< integer_<A2> >)
                            )
  {
    BOOST_DISPATCH_RETURNS( 3, (A0 a0, A1 a1, A2 a2)
                          , nt2::repnum(a0,a1,a2)
                          );
  };
} }

#endif
