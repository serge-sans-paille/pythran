//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_GALLERY_FUNCTIONS_GALLERY_IMPL_CHEBVAND_HPP_INCLUDED
#define NT2_GALLERY_FUNCTIONS_GALLERY_IMPL_CHEBVAND_HPP_INCLUDED

#include <nt2/gallery/functions/chebvand.hpp>
#include <nt2/include/functions/linspace.hpp>
#include <nt2/include/functions/rowvect.hpp>
#include <nt2/include/functions/ones.hpp>
#include <nt2/include/functions/colon.hpp>
#include <nt2/include/functions/numel.hpp>
#include <nt2/include/constants/two.hpp>
#include <nt2/include/constants/zero.hpp>
#include <nt2/include/constants/one.hpp>
#include <nt2/core/container/dsl/size.hpp>
#include <nt2/core/container/dsl/value_type.hpp>
#include <nt2/sdk/meta/is_target.hpp>
#include <nt2/sdk/meta/container_traits.hpp>
#include <boost/dispatch/dsl/semantic_of.hpp>
#include <boost/mpl/eval_if.hpp>

namespace nt2 { namespace ext
{
  template<class Domain, class Expr>
  struct size_of<tag::chebvand_, Domain, 3, Expr>
  {
    typedef _2D                               result_type;
    BOOST_FORCEINLINE result_type operator()(Expr& e) const
    {
      size_t m =  boost::proto::child_c<0>(e);
      size_t n =  boost::proto::child_c<1>(e);
      result_type sizee;
      sizee[0] = m; sizee[1] = n;
      return sizee;
    }
  };

  template <class Domain, class Expr>
  struct value_type<tag::chebvand_, Domain, 3, Expr>
  {
    typedef typename Expr::proto_child2 child2;
    typedef typename boost::dispatch::meta::semantic_of<child2>::type semantic;
    typedef typename boost::mpl::
            eval_if< meta::is_target<semantic>
                   , semantic
                   , meta::value_type_<semantic>
                   >::type type;
  };

  //1
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::chebvand_, tag::cpu_,
                              (A0)(A1),
                              (scalar_<integer_<A0> >)
                              (scalar_<integer_<A1> >)
                            )
  {
    typedef typename  boost::proto::
      result_of::make_expr< nt2::tag::chebvand_
      , container::domain
      , A0 const &
      , A1 const &
      , meta::as_<double>
      >::type             result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& a0,
                                             A1 const& a1) const
    {
      return  boost::proto::
        make_expr<nt2::tag::chebvand_, container::domain>
        ( boost::cref(a0)
          , boost::cref(a1)
          , meta::as_<double>()
          );
    }
  };
  //1bis
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::chebvand_, tag::cpu_,
                              (A0)(A1)(T),
                              (scalar_<integer_<A0> >)
                              (scalar_<integer_<A1> >)
                              (target_<scalar_<unspecified_<T> > > )
                            )
  {
    typedef typename  boost::proto::
      result_of::make_expr< nt2::tag::chebvand_
      , container::domain
      , A0 const &
      , A1 const &
      , T
      >::type             result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& a0,
                                             A1 const& a1,
                                             T const& tgt) const
    {
      return  boost::proto::
        make_expr<nt2::tag::chebvand_, container::domain>
        ( boost::cref(a0)
          , boost::cref(a1)
          , tgt
          );
    }
  };

  //2
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::chebvand_, tag::cpu_,
                              (A0),
                              (scalar_<integer_<A0> >)
    )
  {
    typedef typename  boost::proto::
      result_of::make_expr< nt2::tag::chebvand_
      , container::domain
      , A0 const &
      , A0 const &
      , meta::as_<double>
      >::type             result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& a0) const
    {
      return  boost::proto::
        make_expr<nt2::tag::chebvand_, container::domain>
        ( boost::cref(a0)
          , boost::cref(a0)
          , meta::as_<double>()
          );
    }
  };
  //2bis
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::chebvand_, tag::cpu_,
                              (A0)(T),
                              (scalar_<integer_<A0> >)
                              (target_<scalar_<unspecified_<T> > > )
    )
  {
    typedef typename  boost::proto::
      result_of::make_expr< nt2::tag::chebvand_
      , container::domain
      , A0 const &
      , A0 const &
      , T
      >::type             result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& a0, T const& tgt) const
    {
      return  boost::proto::
        make_expr<nt2::tag::chebvand_, container::domain>
        ( boost::cref(a0)
          , boost::cref(a0)
          , tgt
          );
    }
  };
  //3
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::chebvand_, tag::cpu_,
                              (A0)(A1),
                              (scalar_<integer_<A0> >)
                              ((ast_<A1, nt2::container::domain>))
    )
  {
    typedef typename  boost::proto::
      result_of::make_expr< nt2::tag::chebvand_
      , container::domain
      , A0 const&
      , size_t const&
      , A1 const&
      >::type             result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& a0, A1 const& a1) const
    {
      size_t n = numel(a1);
      return  boost::proto::
        make_expr<nt2::tag::chebvand_, container::domain>
        ( boost::cref(a0)
          , boost::cref(n)
          , boost::cref(a1)
          );
    }
  };
  //4
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::chebvand_, tag::cpu_,
                              (A0),
                              ((ast_<A0, nt2::container::domain>))
                            )
  {
    typedef typename  boost::proto::
                      result_of::make_expr< nt2::tag::chebvand_
                                          , container::domain
                                          , size_t const&
                                          , size_t const&
                                          , A0 const&
                                          >::type             result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& a0) const
    {
      size_t n = numel(a0);
      return  boost::proto::
        make_expr<nt2::tag::chebvand_, container::domain>
        ( boost::cref(n)
          , boost::cref(n)
          , boost::cref(a0)
          );
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::run_assign_, tag::cpu_
                            , (A0)(A1)
                            , ((ast_<A0, nt2::container::domain>))
                              ((node_<A1, nt2::tag::chebvand_, boost::mpl::long_<3>, nt2::container::domain>))
    )
  {
    typedef A0&                                                          result_type;
    typedef typename boost::dispatch::meta::
            semantic_of<typename A1::proto_child2>::type                 child2_sem;
    typedef typename meta::is_target<child2_sem>::type                   choice_type;
    result_type operator()(A0& out, const A1& in) const
    {
      size_t m =  boost::proto::child_c<0>(in);
      size_t n =  boost::proto::child_c<1>(in);
      prepare(out, in, m, n, choice_type());
      return out;
    }
  private :
    static void prepare(A0& out, const A1 &, size_t m, size_t n,boost::mpl::true_)
    {
      typedef typename A1::value_type                                   v_type;
      BOOST_AUTO_TPL(p, nt2::linspace(Zero<v_type>(), One<v_type>(), n));
      out.resize(nt2::of_size(m, n));
      compute(out, m, n, p);
    }
    static void prepare(A0& out, const A1 & in, size_t m, size_t n, boost::mpl::false_)
    {
      BOOST_AUTO_TPL(p, boost::proto::child_c<2>(in));
      out.resize(nt2::of_size(m, nt2::numel(p)));
      compute(out, m, n, p);
    }
    template < class P >
    static void compute(A0& c, size_t m, size_t n, const P& p)
    {
      typedef typename A1::value_type                                   v_type;
      BOOST_AUTO_TPL(rp, nt2::rowvect(p));
      c = ones(m,n,meta::as_<v_type>());
      if (n == 1) return;
      c(2, _) = rp;
      //      Use Chebyshev polynomial recurrence.
      for (size_t i = 3; i <= m; ++i){
        c(i, _) = nt2::Two<v_type>()*rp*c(i-1, _)-c(i-2, _);
      }
    }
  };
} }

#endif
