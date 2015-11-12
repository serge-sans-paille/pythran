//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_EXPR_IND2SUB_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_EXPR_IND2SUB_HPP_INCLUDED

#include <nt2/core/functions/ind2sub.hpp>
#include <nt2/include/functions/as_size.hpp>
#include <nt2/core/container/dsl/size.hpp>
#include <nt2/core/container/dsl/value_type.hpp>
#include <nt2/core/container/dsl.hpp>
#include <nt2/sdk/meta/value_as.hpp>
#include <nt2/sdk/meta/size_as.hpp>

namespace nt2 { namespace ext
{
  template <class Domain, class Expr, int N>
  struct  value_type<tag::ind2sub_,Domain,N,Expr>
        : meta::value_as<Expr, 1>
  {};

  template<class Domain, int N, class Expr>
  struct  size_of<tag::ind2sub_,Domain,N,Expr>
        : meta::size_as<Expr,1>
  {};

  /// INTERNAL ONLY - ind2sub(size,IND)
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::ind2sub_, tag::cpu_
                            , (A0)(A1)
                            , (scalar_<arithmetic_<A0> >)
                              ((ast_<A1, nt2::container::domain>))
                            )
  {
    BOOST_DISPATCH_RETURNS(2, (A0 a0, A1 const& a1)
                          , nt2::ind2sub(a0,a1,1)
                          );
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::ind2sub_, tag::cpu_
                            , (A0)(A1)
                            , (fusion_sequence_<A0>)
                              ((ast_<A1, nt2::container::domain>))
                            )
  {
    BOOST_DISPATCH_RETURNS(2, (A0 const& a0, A1 const& a1)
                          , nt2::ind2sub(a0,a1,1)
                          );
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::ind2sub_, tag::cpu_
                            , (A0)(A1)
                            , ((ast_<A0, nt2::container::domain>))
                              ((ast_<A1, nt2::container::domain>))
                            )
  {
    BOOST_DISPATCH_RETURNS(2, (A0 const& a0, A1 const& a1)
                          , nt2::ind2sub(a0,a1,1)
                          );
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::ind2sub_, tag::cpu_
                            , (A0)(A1)
                            , ((ast_<A0, nt2::container::domain>))
                              (scalar_< arithmetic_<A1> >)
                            )
  {
    BOOST_DISPATCH_RETURNS(2, (A0 const& a0, A1 a1)
                          , nt2::ind2sub(a0,a1,1)
                          );
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::ind2sub_, tag::cpu_
                            , (A0)(A1)(A2)
                            , (scalar_<arithmetic_<A0> >)
                              ((ast_<A1, nt2::container::domain>))
                              (scalar_< arithmetic_<A2> >)
                            )
  {
    typedef typename  boost::proto::
                      result_of::make_expr< nt2::tag::ind2sub_
                                          , container::domain
                                          , _2D
                                          , A1 const&
                                          , A2
                                          >::type             result_type;

    BOOST_FORCEINLINE result_type operator()(A0 a0, A1 const& a1, A2 a2) const
    {
      return boost::proto::make_expr< nt2::tag::ind2sub_
                                    , container::domain
                                    > ( as_size(a0,1)
                                      , boost::cref(a1)
                                      , a2
                                      );
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::ind2sub_, tag::cpu_
                            , (A0)(A1)(A2)
                            , (fusion_sequence_<A0>)
                              ((ast_<A1, nt2::container::domain>))
                              (scalar_< arithmetic_<A2> >)
                            )
  {
    typedef typename  boost::proto::
                      result_of::make_expr< nt2::tag::ind2sub_
                                          , container::domain
                                          , typename boost::remove_const<A0>::type
                                          , A1 const&
                                          , A2
                                          >::type             result_type;

    BOOST_FORCEINLINE
    result_type operator()(A0 const& a0, A1 const& a1, A2 a2) const
    {
      return boost::proto::make_expr< nt2::tag::ind2sub_
                                    , container::domain
                                    > ( a0
                                      , boost::cref(a1)
                                      , a2
                                      );
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::ind2sub_, tag::cpu_
                            , (A0)(A1)(A2)
                            , ((ast_<A0, nt2::container::domain>))
                              ((ast_<A1, nt2::container::domain>))
                              (scalar_< arithmetic_<A2> >)
                            )
  {
    typedef typename  boost::proto::
                      result_of::make_expr< nt2::tag::ind2sub_
                                          , container::domain
                                          , of_size_max
                                          , A1 const&
                                          , A2
                                          >::type             result_type;

    BOOST_FORCEINLINE
    result_type operator()(A0 const& a0, A1 const& a1, A2 a2) const
    {
      return boost::proto::make_expr< nt2::tag::ind2sub_
                                    , container::domain
                                    > ( as_size(a0)
                                      , boost::cref(a1)
                                      , a2
                                      );
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::ind2sub_, tag::cpu_
                            , (A0)(A1)(A2)
                            , ((ast_<A0, nt2::container::domain>))
                              (scalar_< arithmetic_<A1> >)
                              (scalar_< arithmetic_<A2> >)
                            )
  {
    typedef typename  boost::proto::
                      result_of::make_expr< nt2::tag::ind2sub_
                                          , container::domain
                                          , of_size_max
                                          , A1
                                          , A2
                                          >::type             result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& a0, A1 a1, A2 a2) const
    {
      return boost::proto::make_expr< nt2::tag::ind2sub_
                                    , container::domain
                                    > ( as_size(a0)
                                      , a1
                                      , a2
                                      );
    }
  };
} }

#endif
