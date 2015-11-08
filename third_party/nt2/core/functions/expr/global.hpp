//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_EXPR_GLOBAL_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_EXPR_GLOBAL_HPP_INCLUDED

#include <nt2/core/functions/global.hpp>
#include <nt2/core/container/dsl.hpp>
#include <nt2/include/functions/colvect.hpp>
#include <nt2/include/functions/all.hpp>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::global_, tag::cpu_,
                              (A0)(A1),
                              (unspecified_<A0>)
                              ((ast_<A1, nt2::container::domain>))
                              )
  {
    typedef typename A1::value_type                               value_type;
    typedef typename meta::result_of<A0 const(const value_type&)>::type result_type;
    BOOST_FORCEINLINE result_type operator()(A0 const& a0, A1 const& a1) const
    {
      return a0(nt2::colvect(a1))(1);
    }
  };
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::global_, tag::cpu_,
                              (A0)(A1),
                              (unspecified_<A0>)
                              (generic_<unspecified_<A1> > )
                              )
  {
    typedef typename meta::result_of<A0 const(const A1&)>::type result_type;
    BOOST_FORCEINLINE result_type operator()(A0 const& a0, const A1& a1) const
    {
      return a0(a1);
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::global_, tag::cpu_,
                              (A0)(A1)(A2),
                              (unspecified_<A0>)
                              ((ast_<A1, nt2::container::domain>))
                              (unspecified_<A2>)
                              )
  {
    typedef typename A1::value_type                               value_type;
    typedef typename meta::result_of<A0 const(const value_type&, const A2&)>::type result_type;
    BOOST_FORCEINLINE result_type operator()(A0 const& a0, A1 const& a1, A2 const& a2) const
    {
      return a0(nt2::colvect(a1), a2)(1);
    }
  };
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::global_, tag::cpu_,
                              (A0)(A1)(A2),
                              (unspecified_<A0>)
                              (generic_<unspecified_<A1> > )
                              (unspecified_<A2>)
                              )
  {
    typedef typename meta::result_of<A0 const(const A1&, const A2&)>::type result_type;
    BOOST_FORCEINLINE result_type operator()(A0 const& a0, const A1& a1, A2 const& a2) const
    {
      return a0(a1, a2);
    }
  };
} }

#endif
