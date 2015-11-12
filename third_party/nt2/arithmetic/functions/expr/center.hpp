//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2011 - 2012   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_ARITHMETIC_FUNCTIONS_EXPR_CENTER_HPP_INCLUDED
#define NT2_ARITHMETIC_FUNCTIONS_EXPR_CENTER_HPP_INCLUDED

#include <nt2/arithmetic/functions/center.hpp>
#include <nt2/core/container/dsl.hpp>
#include <nt2/include/functions/mean.hpp>
#include <nt2/include/functions/wmean.hpp>
#include <nt2/include/functions/bsxfun.hpp>

namespace nt2 { namespace ext
{
  /// INTERNAL ONLY
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::center_, tag::cpu_
                            , (A0)
                            , ((ast_<A0, nt2::container::domain>))
                            )
  {
    BOOST_DISPATCH_RETURNS(1, (A0 const& a0),
      nt2::bsxfun(nt2::functor<tag::minus_>(), a0, nt2::mean(a0))
    )
  };

  /// INTERNAL ONLY
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::center_, tag::cpu_
                            , (A0)(A1)
                            , ((ast_<A0, nt2::container::domain>))
                              (scalar_<integer_<A1> > )
                            )
  {
    BOOST_DISPATCH_RETURNS(2, (A0 const& a0, const A1& a1),
      nt2::bsxfun(nt2::functor<tag::minus_>(), a0, nt2::mean(a0, a1))
    )
  };

  /// INTERNAL ONLY
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::center_, tag::cpu_
                            , (A0)(A1)
                            , ((ast_<A0, nt2::container::domain>))
                              ((ast_<A1, nt2::container::domain>))
                            )
  {
    BOOST_DISPATCH_RETURNS(2, (A0 const& a0, A1 const& a1),
      nt2::bsxfun(nt2::functor<tag::minus_>(), a0, nt2::wmean(a0, a1))
    )
  };

  /// INTERNAL ONLY
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::center_, tag::cpu_,
                              (A0)(A1)(A2),
                              ((ast_<A0, nt2::container::domain>))((ast_<A1, nt2::container::domain>))
                              (scalar_<integer_<A2> > )
                              )
  {
    BOOST_DISPATCH_RETURNS(3, (A0 const& a0, const A1& a1, const A2& a2),
      nt2::bsxfun(nt2::functor<tag::minus_>(), a0, nt2::wmean(a0, a1, a2))
    )
  };
} }

#endif
