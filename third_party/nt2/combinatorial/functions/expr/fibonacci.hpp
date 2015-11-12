//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_COMBINATORIAL_FUNCTIONS_EXPR_FIBONACCI_HPP_INCLUDED
#define NT2_COMBINATORIAL_FUNCTIONS_EXPR_FIBONACCI_HPP_INCLUDED

#include <nt2/combinatorial/functions/fibonacci.hpp>
#include <nt2/include/functions/numel.hpp>
#include <nt2/include/functions/colon.hpp>
#include <nt2/include/functions/assign.hpp>
#include <nt2/include/functions/cons.hpp>
#include <nt2/include/functions/linsolve.hpp>
#include <nt2/include/functions/vertcat.hpp>
#include <nt2/include/functions/minusone.hpp>
#include <nt2/include/functions/scalar/is_flint.hpp>
#include <nt2/include/functions/round.hpp>
#include <nt2/include/functions/pow.hpp>
#include <nt2/include/functions/cast.hpp>
#include <nt2/include/functions/scalar/rec.hpp>
#include <nt2/include/constants/one.hpp>
#include <nt2/include/constants/gold.hpp>
#include <nt2/include/constants/cgold.hpp>
#include <nt2/core/container/table/table.hpp>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::fibonacci_, tag::cpu_,
                              (A0)(A1),
                              (scalar_<arithmetic_<A0> >)
                              (scalar_<arithmetic_<A0> >)
                              ((ast_<A1, nt2::container::domain >))
                            )
  {
    BOOST_DISPATCH_RETURNS(3, (A0 const& a0, A0 const& a1, A1 const& a2),
                           (boost::proto::
                            make_expr<nt2::tag::fibonacci_, container::domain>
                            (a0, a1, boost::cref(a2))
                           )
                          )
      };



  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::run_assign_, tag::cpu_
                            , (A0)(A1)(N)
                            , ((ast_<A0, nt2::container::domain>))
                              ((node_<A1,nt2::tag::fibonacci_,N,nt2::container::domain>))
                            )
  {
    typedef A0&                                                          result_type;
    typedef typename A0::value_type                                           v_type;
    result_type operator()(A0& out, const A1& in) const
    {
      BOOST_AUTO_TPL(n, boost::proto::child_c<2>(in));
      v_type a = boost::proto::child_c<0>(in);
      v_type b = boost::proto::child_c<1>(in);
      out.resize(nt2::extent(n));
      const v_type gold1 = -rec(nt2::Gold<v_type>());
      nt2::container::table<v_type> m
        = nt2::cons(of_size(2, 2),
                    nt2::One<v_type>(), nt2::Gold<v_type>(),
                    nt2::One<v_type>(),gold1
                   );
      BOOST_AUTO_TPL(nm1, nt2::cast<v_type>(nt2::minusone(n)));
      nt2::container::table<v_type> c = nt2::linsolve(m, catv(a, b));
      BOOST_AUTO_TPL(f, c(1)*nt2::pow(nt2::Gold<v_type>(), nm1)+c(2)*nt2::pow(gold1, nm1));
      if (nt2::is_flint(a) && nt2::is_flint(b))
        out = nt2::round(f);
      else
        out = f;
      return out;
    }
  };

} }


#endif
