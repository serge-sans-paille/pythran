//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_GALLERY_FUNCTIONS_GALLERY_IMPL_DORR_HPP_INCLUDED
#define NT2_GALLERY_FUNCTIONS_GALLERY_IMPL_DORR_HPP_INCLUDED

#include <nt2/gallery/functions/dorr.hpp>
#include <nt2/include/functions/assign.hpp>
#include <nt2/include/functions/tie.hpp>
#include <nt2/include/functions/ifloor.hpp>
#include <nt2/include/functions/rec.hpp>
#include <nt2/include/functions/sqr.hpp>
#include <nt2/include/functions/colon.hpp>
#include <nt2/include/functions/repnum.hpp>
#include <nt2/include/functions/tridiag.hpp>
#include <nt2/include/constants/half.hpp>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::dorr_, tag::cpu_,
                              (A0),
                              (scalar_<integer_<A0> >)
                            )
  {
    BOOST_DISPATCH_RETURNS( 1
                          , (A0 a0)
                          , ( boost::proto::make_expr
                              < nt2::tag::dorr_
                              , container::domain
                              > ( a0, 0.01, _2D(a0,a0) )
                            )
                          );
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::dorr_, tag::cpu_,
                              (A0)(A1),
                              (scalar_<integer_<A0> >)
                              (scalar_<floating_<A1> >)
                            )
  {
    BOOST_DISPATCH_RETURNS( 2
                          , (A0 a0, A1 a1)
                          , ( boost::proto::make_expr
                              < nt2::tag::dorr_
                              , container::domain
                              > ( a0, a1, _2D(a0,a0) )
                            )
                          );
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::dorr_, tag::cpu_,
                              (A0)(A1),
                              (scalar_<integer_<A0> >)
                              (target_ < scalar_<floating_<A1> > > )
                            )
  {
    typedef typename A1::type value_t;

    BOOST_DISPATCH_RETURNS_ARGS ( 2
                                , (A0 a0, A1 const& a1)
                                , (A0 a0, A1 const&)
                                , ( boost::proto::make_expr
                                    < nt2::tag::dorr_
                                    , container::domain
                                    > ( a0, value_t(0.01), _2D(a0,a0) )
                                  )
                                );
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::dorr_, tag::cpu_,
                              (A0)(A1)(A2),
                              (scalar_<integer_<A0> >)
                              (scalar_<arithmetic_<A1> > )
                              (target_ < scalar_<floating_<A2> > > )
                            )
  {
    typedef typename A2::type value_t;

    BOOST_DISPATCH_RETURNS_ARGS ( 3
                                , (A0 a0, A1 a1, A2 const& a2)
                                , (A0 a0, A1 a1, A2 const&)
                                , ( boost::proto::make_expr
                                    < nt2::tag::dorr_
                                    , container::domain
                                    > ( a0, value_t(a1), _2D(a0,a0) )
                                  )
                                );
  };



  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::dorr_, tag::cpu_
                              , (A0)(N0)(A1)(N1)
                              , ((node_<A0, nt2::tag::dorr_, N0, nt2::container::domain>))
                                ((node_<A1, nt2::tag::tie_ , N1, nt2::container::domain>))
                            )
  {
    typedef void                                                    result_type;
    typedef typename boost::proto::result_of::child_c<A1&,0>::type       child0;
    typedef typename meta::strip<child0>::type                          schild0;
    typedef typename boost::proto::result_of::child_c<A0&,1>::type       child1;
    typedef typename schild0::value_type                                 value_t;

    BOOST_FORCEINLINE result_type operator()( A0& a0, A1& a1 ) const
    {
      size_t n = boost::proto::child_c<0>(a0);
      value_t theta =   boost::proto::child_c<1>(a0);
      compute(n, theta, a1, N1());
    }

  private:
    BOOST_FORCEINLINE
    void compute(const size_t & n, const value_t & theta, A1& a1,
                 boost::mpl::long_<3> const&) const
    {
      typedef typename boost::proto::result_of::child_c<A1&,0>::type       c_t;
      typedef typename boost::proto::result_of::child_c<A1&,1>::type       d_t;
      typedef typename boost::proto::result_of::child_c<A1&,2>::type       e_t;
      c_t & c = boost::proto::child_c<0>(a1);
      c.resize(nt2::of_size(n,1));
      d_t & d = boost::proto::child_c<1>(a1);
      d.resize(nt2::of_size(n,1));
      e_t & e= boost::proto::child_c<2>(a1);
      e.resize(nt2::of_size(n,1));
      doit(n, theta, c, d, e);
    }

    BOOST_FORCEINLINE
    void compute(const size_t & n, const value_t & theta, A1 & a1,
                boost::mpl::long_<1> const&) const
    {
      nt2::table<value_t> c(nt2::of_size(n,1));
      nt2::table<value_t> d(nt2::of_size(n,1));
      nt2::table<value_t> e(nt2::of_size(n,1));
      doit(n, theta, c, d, e);
      boost::proto::child_c<0>(a1) = nt2::tridiag(c, d, e);
    }

    template < class C, class D,  class E> BOOST_FORCEINLINE
    void doit(const size_t & n, const value_t & theta, C & c, D&d, E& e) const
    {
      value_t np1 = value_t(n) + 1;
      value_t h = nt2::rec(np1);
      size_t m = ifloor(np1*nt2::Half<value_t>());
      value_t term = -theta/nt2::sqr(h);
      BOOST_AUTO_TPL(p, (Half<value_t>()-nt2::colvect(_(value_t(1), value_t(n))*h))/h);
      BOOST_AUTO_TPL(i, _(1, m));
      c(i) = term;
      e(i) = c(i) - p(i);
      d(i) = -(c(i) + e(i));
      BOOST_AUTO_TPL(j, _(m+1, n));
      e(j) = term;
      c(j) = e(j) + p(j);
      d(j) = -(c(j) + e(j));
      c = c(_(2, n));
      e.resize(of_size(n-1, 1));
    }
  };
} }

#endif
