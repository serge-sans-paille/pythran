//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_COMBINATORIAL_FUNCTIONS_EXPR_PERMS_HPP_INCLUDED
#define NT2_COMBINATORIAL_FUNCTIONS_EXPR_PERMS_HPP_INCLUDED

#include <nt2/combinatorial/functions/perms.hpp>
#include <nt2/include/functions/numel.hpp>
#include <nt2/include/functions/permsn.hpp>
#include <nt2/include/functions/prod.hpp>
#include <nt2/include/functions/min.hpp>
#include <nt2/include/functions/colon.hpp>
#include <nt2/include/functions/assign.hpp>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::perms_, tag::cpu_,
                              (A0)(A1),
                              ((ast_<A0, nt2::container::domain >))
                              (scalar_<integer_<A1> >)
                            )
  {
    BOOST_DISPATCH_RETURNS(2, (A0 const& a0, A1 const& a1),
                           (boost::proto::
                            make_expr<nt2::tag::perms_, container::domain>
                            (boost::cref(a0), size_t(a1))
                           )
                          )
      };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::perms_, tag::cpu_,
                              (A0),
                              ((ast_<A0, nt2::container::domain >))
                            )
  {
    BOOST_DISPATCH_RETURNS(1, (A0 const& a0),
                           (nt2::perms(a0, nt2::prod(nt2::_(size_t(1), nt2::numel(a0)))))
                          )
      };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::run_assign_, tag::cpu_
                            , (A0)(A1)(N)
                            , ((ast_<A0, nt2::container::domain>))
                              ((node_<A1,nt2::tag::perms_,N,nt2::container::domain>))
                            )
  {
    typedef A0&                                                          result_type;
    typedef typename nt2::container::table<size_t>                              ts_t;
    result_type operator()(A0& out, const A1& in) const
    {
      BOOST_AUTO_TPL(v, boost::proto::child_c<0>(in));
      size_t k = boost::proto::child_c<1>(in);
      size_t n = nt2::numel(v);
      out.resize(nt2::of_size(n, k));
      out = v(nt2::permsn(n, k));
      return out;
    }
  };

} }


#endif
