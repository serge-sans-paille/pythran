//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_EXPR_EXPAND_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_EXPR_EXPAND_HPP_INCLUDED

#include <nt2/core/functions/expand.hpp>
#include <nt2/core/container/dsl.hpp>
#include <nt2/include/functions/numel.hpp>
#include <nt2/include/functions/as_size.hpp>

namespace nt2 { namespace ext
{
  /// INTERNAL ONLY - expand from ast + fusion sequence as size
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::expand_, tag::cpu_
                            , (A0)(A1)
                            , ((ast_<A0, nt2::container::domain>))
                              (fusion_sequence_<A1>)
                            )
  {
    BOOST_DISPATCH_RETURNS(2, (A0 const& a0, A1 const& a1)
                          , (boost::proto::make_expr< nt2::tag::expand_
                                                    , container::domain
                                                    > ( boost::cref(a0)
                                                      , a1
                                                      , nt2::numel(a0)-1
                                                      )
                            )
                          )
  };

  /// INTERNAL ONLY - expand from scalar + fusion sequence as size
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::expand_, tag::cpu_
                            , (A0)(A1)
                            , (scalar_<unspecified_<A0> >)
                              (fusion_sequence_<A1>)
                            )
  {
    BOOST_DISPATCH_RETURNS(2, (A0 const& a0, A1 const& a1)
                          , (boost::proto::make_expr< nt2::tag::expand_
                                                    , container::domain
                                                    > ( boost::cref(a0)
                                                      , a1
                                                      , 0
                                                      )
                            )
                          )
  };
  /// INTERNAL ONLY - expand from ast + ast as size
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::expand_, tag::cpu_
                            , (A0)(A1)
                            , ((ast_<A0, nt2::container::domain>))
                              ((ast_<A1, nt2::container::domain>))
                            )
  {
    BOOST_DISPATCH_RETURNS(2, (A0 const& a0, A1 const& a1)
                          , (nt2::expand(a0,nt2::as_size(a1)))
                          )
  };

  /// INTERNAL ONLY - expand from scalar + ast as size
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::expand_, tag::cpu_
                            , (A0)(A1)
                            , (scalar_<unspecified_<A0> >)
                              ((ast_<A1, nt2::container::domain>))
                            )
  {
    BOOST_DISPATCH_RETURNS(2, (A0 const& a0, A1 const& a1)
                          , (nt2::expand(a0,nt2::as_size(a1)))
                          )
  };
} }

#endif
