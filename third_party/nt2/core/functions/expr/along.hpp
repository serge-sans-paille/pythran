//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_EXPR_ALONG_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_EXPR_ALONG_HPP_INCLUDED

#include <nt2/core/functions/along.hpp>
#include <nt2/include/functions/firstnonsingleton.hpp>
#include <nt2/include/functions/along_index.hpp>
#include <nt2/core/container/dsl/generator.hpp>

namespace nt2 { namespace ext
{
  template<class Domain, class Expr>
  struct size_of<nt2::tag::along_, Domain, 2, Expr>
  {
    typedef typename boost::proto::result_of::child_c<Expr&,1>::value_type child1;
    typedef size_of<tag::along_index_, Domain, 3, child1 const> impl;
    typedef typename impl::result_type result_type;

    result_type operator()(Expr& expr) const
    {
      return impl()(boost::proto::child_c<1>(expr));
    }
  };

  template<class Domain, class Expr>
  struct value_type<nt2::tag::along_, Domain, 2, Expr>
  {
    typedef typename boost::proto::result_of::child_c<Expr&,0>::value_type c0_t;
    typedef typename meta::scalar_of<c0_t>::type type;
  };
} }

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::along_, tag::cpu_,
                              (A0)(A1),
                              ((ast_<A0, nt2::container::domain>))
                              (unspecified_<A1>)
                            )
  {
    BOOST_DISPATCH_RETURNS(2, (A0& a0, A1 const& a1),
      along(a0, a1, nt2::firstnonsingleton(a0))
    )
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::along_, tag::cpu_,
                              (A0)(A1)(A2),
                              ((ast_<A0, nt2::container::domain>))
                              (unspecified_<A1>)
                              (unspecified_<A2>)
                            )
  {
    BOOST_DISPATCH_RETURNS(3, (A0& a0, A1 const& a1, A2 const& a2),
      (boost::proto::make_expr<tag::along_, nt2::container::domain>(boost::ref(a0), along_index(a1, a2, a0.extent())))
    )
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::run_, tag::cpu_,
                              (A0)(State)(Data),
                              ((node_<A0, nt2::tag::along_, boost::mpl::long_<2> , nt2::container::domain>))
                              (generic_< arithmetic_<State> > )
                              (unspecified_<Data>)
                            )
  {
    typedef typename boost::proto::result_of::child_c<A0&,0>::value_type child0;
    typedef typename boost::proto::result_of::child_c<A0&,1>::value_type child1;
    typedef typename meta::call< tag::run_( child0 const&
                                          , typename meta::call< tag::run_( child1 const&
                                                                          , State const&
                                                                          , Data const&
                                                                          )
                                                               >::type
                                          , Data const&
                                          )
                               >::type                        result_type;

    result_type operator()(A0& a0, State const& state, Data const& data) const
    {
      return nt2::run ( boost::proto::child_c<0>(a0)
                      , nt2::run( boost::proto::child_c<1>(a0)
                                , state
                                , data
                                )
                      , data
                      );
    }
  };

} }

#endif
