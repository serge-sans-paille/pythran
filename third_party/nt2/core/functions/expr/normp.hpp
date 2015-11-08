//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_EXPR_NORMP_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_EXPR_NORMP_HPP_INCLUDED

#include <nt2/core/functions/normp.hpp>
#include <nt2/core/container/dsl.hpp>
#include <nt2/core/functions/normp.hpp>
#include <nt2/include/functions/pow.hpp>
#include <nt2/include/functions/asump.hpp>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::normp_, tag::cpu_,
                              (A0)(A1),
                              ((ast_<A0, nt2::container::domain>))
                              (scalar_<arithmetic_<A1> > )
                              )
  {
    typedef typename meta::as_real<typename A0::value_type>::type value_type;
    typedef typename meta::call<tag::pow_(typename meta::call<tag::asump_(A0 const&, A1 const&)>::type,
                                          value_type) >::type
      result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& a0, A1 const& p) const
    {
      value_type one_o_p = nt2::rec(value_type(p));
      return nt2::pow(nt2::asump(a0, p), one_o_p);
    }
  };
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::normp_, tag::cpu_,
                              (A0)(A1)(A2),
                              ((ast_<A0, nt2::container::domain>))
                              (scalar_<arithmetic_<A1> > )
                              (scalar_<integer_<A2> > )
                              )
  {
    typedef typename meta::as_real<typename A0::value_type>::type value_type;
    typedef typename meta::call<tag::pow_(typename meta::call<tag::asump_(A0 const&, A1 const&,
                                                                          A2 const ) >::type ,
                                value_type)>::type
      result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& a0, A1 const& p, A2 const& n) const
    {
      value_type one_o_p = nt2::rec(value_type(p));
      return nt2::pow(nt2::asump(a0, p, n), one_o_p);
    }
  };

} }

#endif
