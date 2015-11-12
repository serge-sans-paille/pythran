//==============================================================================
//         Copyright 2003 - 2013   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2013   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_SIGNAL_FUNCTIONS_COMMON_UNWRAP_HPP_INCLUDED
#define NT2_SIGNAL_FUNCTIONS_COMMON_UNWRAP_HPP_INCLUDED

#include <nt2/signal/functions/unwrap.hpp>
#include <nt2/include/constants/pi.hpp>
#include <nt2/include/constants/twopi.hpp>
#include <nt2/include/functions/firstnonsingleton.hpp>
#include <nt2/include/functions/size.hpp>
#include <nt2/include/functions/horzcat.hpp>
#include <nt2/include/functions/along.hpp>
#include <nt2/include/functions/if_one_else_zero.hpp>
#include <nt2/include/functions/cumsum.hpp>
#include <nt2/include/functions/minusone.hpp>
#include <nt2/include/functions/is_less.hpp>
#include <nt2/include/functions/is_greater.hpp>
#include <nt2/include/functions/assign.hpp>
#include <nt2/core/container/colon/colon.hpp>

namespace nt2 { namespace ext
{
 NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::unwrap_, tag::cpu_,
                              (A0),
                              ((ast_<A0, nt2::container::domain >))
                            )
  {
    typedef typename A0::value_type value_t;
    BOOST_DISPATCH_RETURNS(1, (A0 const& a0),
                           (boost::proto::
                            make_expr<nt2::tag::unwrap_, container::domain>
                            (boost::cref(a0), nt2::Pi<value_t>(), size_t(nt2::firstnonsingleton(a0)))
                           )
                          )
      };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::unwrap_, tag::cpu_,
                              (A0)(A1),
                              ((ast_<A0, nt2::container::domain >))
                              (scalar_<floating_<A1> >)
                            )
  {
    typedef typename A0::value_type value_t;
    BOOST_DISPATCH_RETURNS(2, (A0 const& a0, A1 const& a1),
                           (boost::proto::
                            make_expr<nt2::tag::unwrap_, container::domain>
                            (boost::cref(a0), value_t(a1),size_t(nt2::firstnonsingleton(a0)))
                           )
                          )
      };
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::unwrap_, tag::cpu_,
                              (A0)(A1),
                              ((ast_<A0, nt2::container::domain >))
                              (scalar_<integer_<A1> >)
                            )
  {
    typedef typename A0::value_type value_t;
    BOOST_DISPATCH_RETURNS(2, (A0 const& a0, A1 const& a1),
                           (boost::proto::
                            make_expr<nt2::tag::unwrap_, container::domain>
                            (boost::cref(a0), nt2::Pi<value_t>(),size_t(a1))
                           )
                          )
      };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::unwrap_, tag::cpu_,
                              (A0)(A1)(A2),
                              ((ast_<A0, nt2::container::domain >))
                              (scalar_<floating_<A1> >)
                              (scalar_<integer_<A2> >)
                            )
  {
    typedef typename A0::value_type value_t;
    BOOST_DISPATCH_RETURNS(3, (A0 const& a0, A1 const& a1, A2 const& a2),
                           (boost::proto::
                            make_expr<nt2::tag::unwrap_, container::domain>
                            (boost::cref(a0), value_t(a1), size_t(a2))
                           )
                          )
      };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::run_assign_, tag::cpu_
                            , (A0)(A1)(N)
                            , ((ast_<A0, nt2::container::domain>))
                              ((node_<A1,nt2::tag::unwrap_,N,nt2::container::domain>))
                            )
  {
    typedef A0&                                                          result_type;
    typedef typename A1::value_type                                          value_t;
      result_type operator()(A0& out, const A1& in) const
    {
      BOOST_AUTO_TPL(a, boost::proto::child_c<0>(in));
      value_t tol = boost::proto::child_c<1>(in);
      size_t dim =  boost::proto::child_c<2>(in);
      size_t m = size(a, dim);
      if (m == 1)
        out = a;
      else
      {
        BOOST_AUTO_TPL(idx, nt2::cath(size_t(1), _(size_t(1), nt2::minusone(m))));
        BOOST_AUTO_TPL(d, nt2::along(a, idx, dim)-a);
        BOOST_AUTO_TPL(p, Twopi<value_t>()*(if_one_else_zero(nt2::gt(d, tol))-
                                            if_one_else_zero(nt2::lt(d, -tol))));
        BOOST_AUTO_TPL(r, nt2::cumsum(p, dim));
        out = a+r;
      }
      return out;
    }
  };
} }

#endif
