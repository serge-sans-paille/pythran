//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2011 - 2012   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_EXPR_ASUM2_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_EXPR_ASUM2_HPP_INCLUDED

#include <nt2/core/functions/asum2.hpp>
#include <nt2/core/container/dsl.hpp>
#include <nt2/include/functions/sum.hpp>
#include <nt2/include/functions/sqr_abs.hpp>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::asum2_, tag::cpu_
                            , (A0)
                            , ((ast_<A0, nt2::container::domain>))
                            )
  {
    typedef typename  meta
                    ::call<tag::sum_( typename  meta
                                          ::call<tag::sqr_abs_(A0 const&)>::type
                                    )
                          >::type             result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& a0) const
    {
      return nt2::sum(nt2::sqr_abs(a0));
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::asum2_, tag::cpu_,
                              (A0)(A1),
                              ((ast_<A0, nt2::container::domain>))
                              (scalar_<integer_<A1> > )
                              )
  {
    typedef typename  meta
                    ::call<tag::sum_( typename  meta
                                          ::call<tag::sqr_abs_(A0 const&)>::type
                                    , A1 const&
                                    )
                          >::type             result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& a0, const A1& a1) const
    {
      return nt2::sum(nt2::sqr_abs(a0), a1);
    }
  };
} }

#endif
