//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2011 - 2012   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_EXPR_WHEREIJ_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_EXPR_WHEREIJ_HPP_INCLUDED

#include <nt2/core/functions/whereij.hpp>
#include <nt2/core/container/dsl.hpp>

namespace nt2 { namespace ext
{
  /// INTERNAL ONLY
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::whereij_, tag::cpu_,
                              (A0)(A1)(A2),
                              (unspecified_<A0>)
                              ((ast_<A1, nt2::container::domain>))
                              ((ast_<A2, nt2::container::domain>))
                            )
  {
    BOOST_DISPATCH_RETURNS(3, (A0 const& a0, A1 const& a1, A2 const& a2)
                            , (boost::proto::
                                make_expr<nt2::tag::whereij_, container::domain>
                                ( a0
                                , boost::cref(a1)
                                , boost::cref(a2)
                                )
                              )
                          );
  };

  /// INTERNAL ONLY
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::whereij_, tag::cpu_,
                              (A0)(A1)(A2),
                              (unspecified_<A0>)
                              ((ast_<A1, nt2::container::domain>))
                              (scalar_< unspecified_<A2> >)
                            )
  {
    BOOST_DISPATCH_RETURNS(3, (A0 const& a0, A1 const& a1, A2 const& a2)
                            , (boost::proto::
                                make_expr<nt2::tag::whereij_, container::domain>
                                ( a0
                                , boost::cref(a1)
                                , a2
                                )
                              )
                          );
  };

  /// INTERNAL ONLY
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::whereij_, tag::cpu_,
                              (A0)(A1)(A2),
                              (unspecified_<A0>)
                              (scalar_< unspecified_<A1> >)
                              ((ast_<A2, nt2::container::domain>))
                            )
  {
    BOOST_DISPATCH_RETURNS(3, (A0 const& a0, A1 const& a1, A2 const& a2)
                            , (boost::proto::
                                make_expr<nt2::tag::whereij_, container::domain>
                                ( a0
                                , a1
                                , boost::cref(a2)
                                )
                              )
                          );
  };
} }

#endif
