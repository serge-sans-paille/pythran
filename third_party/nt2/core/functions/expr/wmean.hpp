//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_EXPR_WMEAN_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_EXPR_WMEAN_HPP_INCLUDED

#include <nt2/core/functions/wmean.hpp>
#include <nt2/core/container/dsl.hpp>
#include <nt2/include/functions/sum.hpp>
#include <nt2/include/functions/globalsum.hpp>
#include <nt2/include/functions/sx.hpp>
#include <nt2/include/functions/multiplies.hpp>
#include <nt2/include/functions/rec.hpp>


namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::wmean_, tag::cpu_,
                              (A0)(A1),
                              ((ast_<A0, nt2::container::domain>))
                              ((ast_<A1, nt2::container::domain>))
                              )
  {
    typedef typename A1::value_type value_type;
    typedef typename meta::call < tag::sx_(tag::multiplies_, const A0&, const A1&)>::type T1;
    typedef typename meta::call < tag::sum_(T1 const&)>::type T2;
    typedef typename meta::call < tag::multiplies_(value_type, T2)>::type result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& a0, A1 const& w) const
    {
      value_type f =  nt2::rec(nt2::globalsum(w));
      return nt2::multiplies(f, nt2::sum(nt2::sx(tag::multiplies_(), a0, w)));
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::wmean_, tag::cpu_,
                              (A0)(A1)(A2),
                              ((ast_<A0, nt2::container::domain>))
                              ((ast_<A1, nt2::container::domain>))
                              (scalar_<integer_<A2> > )
                              )
  {
    typedef typename A1::value_type value_type;
    typedef typename meta::call < tag::sx_(tag::multiplies_, const A0&, const A1&)>::type T1;
    typedef typename meta::call < tag::sum_(T1 const&, A2 const&)>::type T2;
    typedef typename meta::call < tag::multiplies_(value_type, T2)>::type result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& a0, const A1& w, const A2& dim) const
    {
      value_type f =  nt2::rec(nt2::globalsum(w));
      return nt2::multiplies(f, nt2::sum(nt2::sx(tag::multiplies_(), a0, w), dim));
    }
  };
} }

#endif
