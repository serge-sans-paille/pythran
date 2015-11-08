//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_SIGNAL_FUNCTIONS_EXPR_ZERO_CROSSING_RATE_HPP_INCLUDED
#define NT2_SIGNAL_FUNCTIONS_EXPR_ZERO_CROSSING_RATE_HPP_INCLUDED

#include <nt2/signal/functions/zero_crossing_rate.hpp>
#include <nt2/include/functions/mean.hpp>
#include <nt2/include/functions/diff.hpp>
#include <nt2/include/functions/abs.hpp>
#include <nt2/include/functions/if_zero_else_one.hpp>
#include <nt2/include/functions/is_nltz.hpp>
#include <nt2/include/functions/firstnonsingleton.hpp>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::zero_crossing_rate_, tag::cpu_,
                              (A0),
                              ((ast_<A0, nt2::container::domain>)) )
  {
    BOOST_DISPATCH_RETURNS(1, (A0 const & a0),
                           nt2::zero_crossing_rate(a0, nt2::firstnonsingleton(a0))
                          )
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::zero_crossing_rate_, tag::cpu_,
                              (A0)(A1),
                              ((ast_<A0, nt2::container::domain>))
                              (scalar_<integer_<A1> > )
                            )
  {
    BOOST_DISPATCH_RETURNS(2, (A0 const & a0, A1 const& a1),
                           nt2::mean(
                             nt2::abs(
                               nt2::diff(
                                 nt2::if_zero_else_one(nt2::is_nltz(a0)),
                                 1, a1
                               )
                             ), a1
                           )
                          )
  };
} }

#endif
