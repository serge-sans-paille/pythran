//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_EXPR_NANSUM_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_EXPR_NANSUM_HPP_INCLUDED

#include <nt2/core/functions/nansum.hpp>
#include <nt2/core/container/dsl.hpp>
#include <nt2/include/functions/sum.hpp>
#include <nt2/include/functions/rec.hpp>
#include <nt2/include/constants/zero.hpp>
#include <nt2/include/functions/multiplies.hpp>
#include <nt2/include/functions/firstnonsingleton.hpp>
#include <nt2/include/functions/is_nan.hpp>
#include <nt2/include/functions/if_zero_else.hpp>
#include <nt2/include/functions/size.hpp>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::nansum_, tag::cpu_,
                              (A0),
                              ((ast_<A0, nt2::container::domain>)) )
  {
    typedef typename meta::call < nt2::tag::is_nan_(A0 const &)>::type T2;
    typedef typename meta::call < nt2::tag::if_zero_else_(T2, A0 const &)>::type T3;
    typedef typename meta::call < nt2::tag::sum_(T3)>::type  result_type;


    BOOST_FORCEINLINE result_type operator()(A0 const& a0) const
    {
      return nt2::sum(nt2::if_zero_else(nt2::is_nan(a0), a0));
    }
  };
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::nansum_, tag::cpu_,
                              (A0)(A1),
                              ((ast_<A0, nt2::container::domain>))
                              (scalar_<integer_<A1> > )
                              )
  {
    typedef typename meta::call < nt2::tag::is_nan_(A0 const &)>::type T2;
    typedef typename meta::call < nt2::tag::if_zero_else_(T2, A0 const &)>::type T3;
    typedef typename meta::call < nt2::tag::sum_(T3, A1 const &)>::type  result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& a0, const A1& a1) const
    {
      return nt2::sum(nt2::if_zero_else(nt2::is_nan(a0), a0), a1);
    }
  };
} }

#endif
