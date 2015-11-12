//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_EXPR_MEANAD_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_EXPR_MEANAD_HPP_INCLUDED

#include <nt2/core/functions/meanad.hpp>
#include <nt2/core/container/dsl.hpp>
#include <nt2/include/functions/abs.hpp>
#include <nt2/include/functions/mean.hpp>
#include <nt2/include/functions/center.hpp>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::meanad_, tag::cpu_,
                              (A0),
                              ((ast_<A0, nt2::container::domain>)) )
  {
    typedef typename meta::call<tag::meanad_(A0 const&, std::size_t)>::type result_type;
    BOOST_FORCEINLINE result_type operator()(A0 const& a0) const
    {
      std::size_t dim = nt2::firstnonsingleton(a0);
      return nt2::meanad(a0,dim);
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::meanad_, tag::cpu_,
                              (A0)(A1),
                              ((ast_<A0, nt2::container::domain>))
                              (scalar_<integer_<A1> > )
                              )
  {
    typedef typename meta::call<tag::center_(A0 const&, A1 const &)>::type T0;
    typedef typename meta::call<tag::abs_(T0)>::type                       T1;
    typedef typename meta::call<tag::mean_(T1, A1 const &)>::type             result_type;
    BOOST_FORCEINLINE result_type operator()(A0 const& a0, const A1& dim) const
    {
      return nt2::mean(nt2::abs(nt2::center(a0, dim)), dim);
    }
  };
} }

#endif
