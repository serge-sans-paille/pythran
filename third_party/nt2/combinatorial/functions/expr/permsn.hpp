//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_COMBINATORIAL_FUNCTIONS_EXPR_PERMSN_HPP_INCLUDED
#define NT2_COMBINATORIAL_FUNCTIONS_EXPR_PERMSN_HPP_INCLUDED

#include <nt2/combinatorial/functions/permsn.hpp>
#include <nt2/include/functions/numel.hpp>
#include <nt2/include/functions/of_size.hpp>
#include <nt2/include/functions/prod.hpp>
#include <nt2/include/functions/min.hpp>
#include <nt2/include/functions/colvect.hpp>
#include <nt2/include/functions/colon.hpp>
#include <nt2/include/functions/numel.hpp>
#include <nt2/core/container/table/table.hpp>
#include <nt2/core/container/colon/colon.hpp>
#include <nt2/include/functions/assign.hpp>
#include <algorithm>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::permsn_, tag::cpu_
                            , (A0)(A1)
                            , (scalar_<integer_<A0> >)
                              (scalar_<integer_<A1> >)
                            )
  {
    BOOST_DISPATCH_RETURNS(2, (A0 const& n, A1 const& k),
                           ( boost::proto::make_expr<nt2::tag::permsn_, container::domain>
                             (size_t(n), size_t(k), _2D(nt2::of_size(n, k)))
                           ))
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::permsn_, tag::cpu_
                            , (A0)
                            , (scalar_<integer_<A0> >)
                            )
  {
    BOOST_DISPATCH_RETURNS(1, (A0 const& n),
                           (nt2::permsn(n, nt2::prod(nt2::_(size_t(1), n))))
                          )
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::run_assign_, tag::cpu_
                            , (A0)(A1)(N)
                            , ((ast_<A0, nt2::container::domain>))
                              ((node_<A1,nt2::tag::permsn_,N,nt2::container::domain>))
                            )
  {
    typedef A0&                                                          result_type;
    typedef typename nt2::container::table<size_t>                              ts_t;
    result_type operator()(A0& out, const A1& in) const
    {
      size_t n = boost::proto::child_c<0>(in);
      size_t k = boost::proto::child_c<1>(in);
      k = nt2::min(k, nt2::prod(nt2::_(size_t(1), n)));
      out.resize(nt2::of_size(n, k));
      ts_t cur = nt2::colvect(nt2::_(size_t(1), size_t(n)));
      out(nt2::_, 1) =  cur;
      for (size_t i = 2; i <= k; ++i)
      {
        std::next_permutation(cur.begin(), cur.end());
        out(nt2::_, i) =  cur;
      }
      return out;
    }
  };
} }

#endif
