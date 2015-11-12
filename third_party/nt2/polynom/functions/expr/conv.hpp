//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_POLYNOM_FUNCTIONS_EXPR_CONV_HPP_INCLUDED
#define NT2_POLYNOM_FUNCTIONS_EXPR_CONV_HPP_INCLUDED

#include <nt2/polynom/functions/conv.hpp>
#include <nt2/dsl/functions/run.hpp>
#include <boost/assert.hpp>

#include <nt2/core/container/table/table.hpp>
#include <nt2/core/container/colon/colon.hpp>
#include <nt2/include/functions/repnum.hpp>

#include <nt2/include/functions/isvector.hpp>
#include <nt2/include/functions/numel.hpp>
#include <nt2/include/functions/zeros.hpp>
#include <nt2/include/functions/colvect.hpp>
#include <nt2/include/functions/function.hpp>
#include <nt2/include/functions/eye.hpp>
#include <nt2/include/functions/mtimes.hpp>
#include <nt2/include/functions/isempty.hpp>
#include <nt2/include/functions/of_size.hpp>
#include <nt2/include/functions/vertcat.hpp>
#include <nt2/include/functions/extent.hpp>
#include <nt2/core/container/dsl/size.hpp>
#include <nt2/core/container/dsl/value_type.hpp>
#include <nt2/sdk/meta/value_as.hpp>
#include <nt2/include/functions/numel.hpp>
#include <algorithm>


namespace nt2{ namespace ext
{

  template<class Domain, int N, class Expr>
  struct  size_of<tag::conv_,Domain,N,Expr>
  {
    typedef typename boost::proto::result_of::child_c<Expr&,0>::type A0;
    typedef _2D                                             result_type;
    BOOST_FORCEINLINE result_type operator ()(Expr& e) const
    {
      result_type sizee;
      sizee[0] = 1;
      size_t na = nt2::numel(boost::proto::child_c<0>(e));
      size_t nb = nt2::numel(boost::proto::child_c<1>(e));
      sizee[1] = std::max(std::max(na+nb ? na+nb-1u : 0u,na),nb);
      return sizee;
    }
  };

  template<class Domain, int N, class Expr>
  struct  value_type<tag::conv_,Domain,N,Expr>
        : meta::value_as<Expr,0>
  {};

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::conv_, tag::cpu_,
                              (A0),
                              (scalar_<unspecified_<A0> >)
                              (scalar_<unspecified_<A0> >)
                            )
  {
    BOOST_DISPATCH_RETURNS(2, (A0 const& a0, A0 const& a1),
                           ( conv(nt2::repnum(a0, 1, 1), nt2::repnum(a1, 1, 1)))
                          )
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::conv_, tag::cpu_,
                              (A0)(A1),
                              (scalar_<unspecified_<A0> >)
                              ((ast_<A1, nt2::container::domain>))
                            )
  {
    BOOST_DISPATCH_RETURNS(2, (A0 const& a0, A1 const& a1),
                           ( conv(nt2::repnum(a0, 1, 1), a1))
                          )
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::conv_, tag::cpu_,
                              (A0)(A1),
                              ((ast_<A0, nt2::container::domain>))
                              (scalar_<unspecified_<A1> >)
                            )
  {
    BOOST_DISPATCH_RETURNS(2, (A0 const& a0, A1 const& a1),
                           ( conv(a0, nt2::repnum(a1, 1, 1)))
                          )
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::run_assign_, tag::cpu_
                            , (A0)(A1)(N)
                            , ((ast_<A0, nt2::container::domain>))
                              ((node_<A1, nt2::tag::conv_, N,nt2::container::domain> ))
                            )
  {
    typedef typename boost::proto::result_of::child_c<A1&,0>::type        In0;
    typedef typename boost::proto::result_of::child_c<A1&,1>::type        In1;
    typedef typename A1::value_type                                       v_t;
    typedef typename nt2::container::table<v_t>                         tab_t;
    typedef A0&                                                   result_type;
    result_type operator()(A0& out, const A1& in) const
    {
      tab_t r;
      In0 a = boost::proto::child_c<0>(in);
      In1 b = boost::proto::child_c<1>(in);
      BOOST_ASSERT_MSG(nt2::isvector(a)&&nt2::isvector(b), "a0 and a1 must be vectors.");
      size_t na = nt2::numel(a);
      size_t nb = nt2::numel(b);
      size_t dim = na+nb ? na+nb-1u : 0u;
      out.resize(of_size(1, dim));
      if (nt2::isempty(a) || nt2::isempty(b))
        out = nt2::zeros(extent(out), meta::as_<v_t>());
      else
      {
        r = nt2::eye(dim, meta::as_<v_t>());
        for(size_t i=1; i <= na; ++i)
          r(nt2::_(i, (i-1)+nb), i) = nt2::colvect(b);

        BOOST_AUTO_TPL(tmp, nt2::catv(nt2::colvect(a), nt2::zeros(nb ? nb-1u :0u, 1, meta::as_<v_t>())));
        out = nt2::mtimes(r, tmp);
        out.resize(of_size(1, numel(out)));
      }
      return out;
    }
  };
} }

#endif
