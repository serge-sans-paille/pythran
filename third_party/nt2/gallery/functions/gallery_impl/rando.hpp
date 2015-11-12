//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_GALLERY_FUNCTIONS_GALLERY_IMPL_RANDO_HPP_INCLUDED
#define NT2_GALLERY_FUNCTIONS_GALLERY_IMPL_RANDO_HPP_INCLUDED

#include <nt2/gallery/functions/rando.hpp>
#include <nt2/include/functions/numel.hpp>
#include <nt2/include/functions/rand.hpp>
#include <nt2/include/functions/multiplies.hpp>
#include <nt2/include/functions/iceil.hpp>
#include <nt2/include/constants/one.hpp>
#include <nt2/core/container/table/table.hpp>
#include <nt2/core/container/dsl/size.hpp>
#include <nt2/core/container/dsl/value_type.hpp>
#include <nt2/sdk/meta/value_as.hpp>
#include <nt2/sdk/meta/boxed_size.hpp>

namespace nt2 { namespace ext
{
  template<class Domain, class Expr>
  struct size_of<tag::rando_, Domain, 2, Expr>
       : meta::boxed_size<Expr, 1>
  {
  };

  template <class Domain, class Expr>
  struct value_type<tag::rando_, Domain, 2, Expr>
       : meta::value_as<Expr, 0>
  {
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::rando_, tag::cpu_,
                              (A0)(A1)(A2)(T),
                              (scalar_<integer_<A0> >)
                              (scalar_<integer_<A1> >)
                              (scalar_<integer_<A2> >)
                              (target_<scalar_<floating_<T> > > )
                            )
  {
    typedef typename T::type                                                v_t;
    BOOST_DISPATCH_RETURNS_ARGS ( 4
                                , ( A0 const& n, A1 const& m
                                  , A2 const& k, T const & t
                                  )
                                , ( A0 const& n, A1 const& m
                                  , A2 const& k, T const&
                                  )
                                , ( boost::proto
                                    ::make_expr < nt2::tag::rando_
                                                , container::domain
                                                > ( nt2::_( k == 1?v_t(0):v_t(-1)
                                                          , k == 2 ? v_t(k):v_t(1)
                                                          , v_t(1)
                                                          )
                                                  , nt2::of_size(n,m)
                                                  )
                                  )
                                )
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::rando_, tag::cpu_,
                              (A0)(A1)(T),
                              (scalar_<integer_<A0> >)
                              (scalar_<integer_<A1> >)
                              (target_<scalar_<floating_<T> > > )
                            )
  {
    BOOST_DISPATCH_RETURNS_ARGS(3, (A0 const& n, A1 const& m, T const & t), (A0 const& n, A1 const& m, T const & ),
                           (rando(n, m, nt2::One<size_t>(), T()))
                          )
      };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::rando_, tag::cpu_,
                              (A0)(T),
                              (scalar_<integer_<A0> >)
                              (target_<scalar_<floating_<T> > > )
                            )
  {
    BOOST_DISPATCH_RETURNS_ARGS(2, (A0 const& n, T const & t),(A0 const& n, T const & ),
                           (rando(n, n, nt2::One<size_t>(), T()))
                          )
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::rando_, tag::cpu_,
                              (A0)(A1)(A2),
                              (scalar_<integer_<A0> >)
                              (scalar_<integer_<A1> >)
                              (scalar_<integer_<A2> >)
                            )
  {
    BOOST_DISPATCH_RETURNS(3, (A0 const& n, A1 const& m, A2 const& k),
                           (rando(n, m, k, nt2::meta::as_<double>()))
                          )
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::rando_, tag::cpu_,
                              (A0)(A1),
                              (scalar_<integer_<A0> >)
                              (scalar_<integer_<A1> >)
                            )
  {
    BOOST_DISPATCH_RETURNS(2, (A0 const& n, A1 const& m),
                           (rando(n, m, nt2::One<size_t>(), nt2::meta::as_<double > ()))
                          )
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::run_assign_, tag::cpu_
                            , (A0)(A1)(N)
                            , ((ast_<A0, nt2::container::domain>))
                              ((node_<A1,nt2::tag::rando_,N,nt2::container::domain>))
                            )
  {
    typedef A0&                                                         result_type;
    typedef typename  boost::proto::result_of::child_c<A1&,0>::type        tmp_type;
    typedef typename  meta::strip<tmp_type>::type                         tmp1_type;
    typedef typename  tmp1_type::value_type                                 value_t;
    typedef nt2::table<value_t>                                               tab_t;
    result_type operator()(A0& out, const A1& in) const
    {
      BOOST_AUTO_TPL(x,boost::proto::child_c<0>(in));
      _2D siz =  boost::proto::value(boost::proto::child_c<1>(in));
      size_t n = siz[0];
      size_t m = siz[1];
      tab_t rnd = nt2::rand(n*m, 1, nt2::meta::as_<value_t>());
      value_t p = nt2::numel(x);
      out.resize(siz);
      out(nt2::_) = x(nt2::iceil(rnd*p));
      return out;
    }
  };
} }

#endif
