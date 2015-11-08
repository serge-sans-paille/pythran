//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_GALLERY_FUNCTIONS_GALLERY_IMPL_CYCOL_HPP_INCLUDED
#define NT2_GALLERY_FUNCTIONS_GALLERY_IMPL_CYCOL_HPP_INCLUDED

#include <nt2/gallery/functions/cycol.hpp>
#include <nt2/core/container/table/table.hpp>
#include <nt2/include/functions/horzcat.hpp>
#include <nt2/include/functions/randn.hpp>
#include <nt2/include/functions/of_size.hpp>
#include <nt2/include/functions/idivround.hpp>
#include <nt2/include/functions/idivceil.hpp>
#include <nt2/include/functions/ones.hpp>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::cycol_, tag::cpu_
                            , (A0)(A1)
                            , (scalar_<integer_<A0> >)
                              (scalar_<integer_<A1> >)
                            )
  {
    BOOST_DISPATCH_RETURNS( 2
                          , (A0 a0, A1 a1)
                          , ( boost::proto::make_expr
                              < nt2::tag::cycol_
                              , container::domain
                              > ( std::size_t(0)
                                , meta::as_<double>()
                                , _2D(a0,a1)
                                )
                            )
                          );
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::cycol_, tag::cpu_
                            , (A0)(A1)(A2)
                            , (scalar_<integer_<A0> >)
                              (scalar_<integer_<A1> >)
                              (scalar_<integer_<A2> >)
                            )
  {
    BOOST_DISPATCH_RETURNS( 3
                          , (A0 a0, A1 a1, A2 a2)
                          , ( boost::proto::make_expr
                              < nt2::tag::cycol_
                              , container::domain
                              > ( a2, meta::as_<double>(), _2D(a0,a1) )
                            )
                          );
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::cycol_, tag::cpu_
                            , (A0)(A1)(T)
                            , (scalar_<integer_<A0> >)
                              (scalar_<integer_<A1> >)
                              (target_< scalar_< unspecified_<T> > >)
                            )
  {
    BOOST_DISPATCH_RETURNS( 3
                          , (A0 a0, A1 a1, T const& tgt)
                          , ( boost::proto::make_expr
                              < nt2::tag::cycol_
                              , container::domain
                              > ( std::size_t(0), tgt, _2D(a0,a1) )
                            )
                          );
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::cycol_, tag::cpu_,
                              (A0)(A1)(A2)(T),
                              (scalar_<integer_<A0> >)
                              (scalar_<integer_<A1> >)
                              (scalar_<integer_<A2> >)
                              (target_< scalar_< unspecified_<T> > >)
    )
  {
    BOOST_DISPATCH_RETURNS( 4
                          , (A0 a0, A1 a1, A2 a2, T const& tgt)
                          , ( boost::proto::make_expr
                              < nt2::tag::cycol_
                              , container::domain
                              > ( a2
                                , tgt
                                , _2D(a0,a1)
                                )
                            )
                          );
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::run_assign_, tag::cpu_
                            , (A0)(A1)(N)
                            , ((ast_<A0, nt2::container::domain>))
                              ((node_<A1,nt2::tag::cycol_,N,nt2::container::domain>))
                            )
  {
    typedef A0&                                                           result_type;
    typedef typename boost::proto::result_of::child_c<A1&,1>::value_type  p_type;
    typedef typename p_type::value_type                                   v_t;
    typedef typename nt2::container::table<v_t>                           tab_t;

    result_type operator()(A0& out, const A1& in) const
    {
      _2D sizee = boost::proto::value(boost::proto::child_c<2>(in));
      out.resize(sizee);

      std::size_t k = boost::proto::value(boost::proto::child_c<0>(in));
      std::size_t n = sizee[1];

      if(k == 0) k = nt2::max ( nt2::idivround(sizee[1],std::size_t(4))
                              , std::size_t(1)
                              );

      tab_t c1, c = nt2::randn(sizee[0], k, meta::as_<v_t>());
//      tab_t c1, c = nt2::ones(sizee[0], k, meta::as_<v_t>());
      std::size_t imax = idivceil(sizee[1], k);

      for(std::size_t i=2; i <= imax; ++i)
      {
        c1 = nt2::cath(c, c(_,_(std::size_t(1), k)));
        c  = c1; // ALIASING
      }

      out = c(_, _(1, n-1));

      return out;
    }
  };
} }

#endif
