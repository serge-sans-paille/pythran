//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_EXPR_NORM2_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_EXPR_NORM2_HPP_INCLUDED

#include <nt2/core/functions/norm2.hpp>
#include <nt2/core/container/dsl.hpp>
#include <nt2/core/functions/norm2.hpp>
#include <nt2/include/functions/sqrt.hpp>
#include <nt2/include/functions/asum2.hpp>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::norm2_, tag::cpu_,
                              (A0),
                              ((ast_<A0, nt2::container::domain>)) )
  {
    typedef typename meta::call<tag::sqrt_(typename meta::call<tag::asum2_(A0 const&)>::type) >::type
      result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& a0) const
    {
      return nt2::sqrt(nt2::asum2(a0));
    }
  };
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::norm2_, tag::cpu_,
                              (A0)(A1),
                              ((ast_<A0, nt2::container::domain>))
                              (scalar_<integer_<A1> > )
                              )
  {
    typedef typename meta::call<tag::sqrt_(typename meta::call<tag::asum2_(A0 const&, A1 const&) >::type) >::type
      result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& a0, A1 const& a1) const
    {
      return nt2::sqrt(nt2::asum2(a0, a1));
    }
  };
} }

#endif
