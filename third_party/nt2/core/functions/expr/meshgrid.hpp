//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_EXPR_MESHGRID_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_EXPR_MESHGRID_HPP_INCLUDED

#include <nt2/core/functions/meshgrid.hpp>
#include <nt2/sdk/meta/value_as.hpp>
#include <nt2/core/container/dsl.hpp>
#include <nt2/core/container/dsl/size.hpp>
#include <nt2/core/container/dsl/value_type.hpp>
#include <nt2/core/utility/of_size/mpl_value.hpp>
#include <nt2/include/functions/numel.hpp>

namespace nt2 { namespace ext
{
  template <class Domain, class Expr, int N>
  struct  value_type<tag::meshgrid_,Domain,N,Expr>
        : meta::value_as<Expr, 1>
  {};

  template<class Domain, class Expr>
  struct  size_of<tag::meshgrid_,Domain,2,Expr>
  {
    typedef typename boost::proto::result_of::child_c<Expr&,0>::value_type c0_t;
    typedef typename boost::proto::result_of::child_c<Expr&,1>::value_type c1_t;

    typedef typename
            meta::call<tag::numel_(typename c0_t::extent_type)>::type d0_t;

    typedef typename
            meta::call<tag::numel_(typename c1_t::extent_type)>::type d1_t;

    typedef typename mpl_value<d0_t>::type s0_t;
    typedef typename mpl_value<d1_t>::type s1_t;

    typedef of_size_<s1_t::value,s0_t::value> result_type;

    BOOST_FORCEINLINE result_type operator()(Expr& e) const
    {
      result_type that( nt2::numel( boost::proto::child_c<1>(e) )
                      , nt2::numel( boost::proto::child_c<0>(e) )
                      );
      return that;
    }
  };

  template<class Domain, class Expr>
  struct  size_of<tag::meshgrid_,Domain,3,Expr>
  {
    typedef typename boost::proto::result_of::child_c<Expr&,0>::value_type c0_t;
    typedef typename boost::proto::result_of::child_c<Expr&,1>::value_type c1_t;
    typedef typename boost::proto::result_of::child_c<Expr&,2>::value_type c2_t;

    typedef typename
            meta::call<tag::numel_(typename c0_t::extent_type)>::type d0_t;

    typedef typename
            meta::call<tag::numel_(typename c1_t::extent_type)>::type d1_t;

    typedef typename
            meta::call<tag::numel_(typename c2_t::extent_type)>::type d2_t;

    typedef typename mpl_value<d0_t>::type s0_t;
    typedef typename mpl_value<d1_t>::type s1_t;
    typedef typename mpl_value<d2_t>::type s2_t;

    typedef of_size_<s1_t::value,s0_t::value,s2_t::value> result_type;

    BOOST_FORCEINLINE result_type operator()(Expr& e) const
    {
      result_type that( nt2::numel( boost::proto::child_c<1>(e) )
                      , nt2::numel( boost::proto::child_c<0>(e) )
                      , nt2::numel( boost::proto::child_c<2>(e) )
                      );
      return that;
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::meshgrid_, tag::cpu_
                            , (A0)
                            , (scalar_< unspecified_<A0> >)
                              (scalar_< unspecified_<A0> >)
                            )
  {
    BOOST_DISPATCH_RETURNS( 2
                          , ( A0 a0, A0 a1 )
                          , ( boost::proto::make_expr
                              < nt2::tag::meshgrid_
                              , nt2::container::domain
                              >
                              ( a0, a1 )
                            )
                          );
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::meshgrid_, tag::cpu_
                            , (A0)
                            , (scalar_< unspecified_<A0> >)
                              (scalar_< unspecified_<A0> >)
                              (scalar_< unspecified_<A0> >)
                            )
  {
    BOOST_DISPATCH_RETURNS( 3
                          , ( A0 a0, A0 a1, A0 a2 )
                          , ( boost::proto::make_expr
                              < nt2::tag::meshgrid_
                              , nt2::container::domain
                              >
                              ( a0, a1, a2 )
                            )
                          );
  };
} }

#endif
