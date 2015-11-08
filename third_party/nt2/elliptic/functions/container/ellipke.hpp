//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_ELLIPTIC_FUNCTIONS_CONTAINER_ELLIPKE_HPP_INCLUDED
#define NT2_ELLIPTIC_FUNCTIONS_CONTAINER_ELLIPKE_HPP_INCLUDED

#include <nt2/elliptic/functions/ellipke.hpp>
#include <nt2/include/functions/tie.hpp>
#include <nt2/core/container/dsl.hpp>
#include <boost/dispatch/meta/terminal_of.hpp>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION ( nt2::tag::ellipke_, tag::cpu_
                             , (A0)(A1)(A2)(A3)
                             , ((ast_<A0, nt2::container::domain>))
                               (scalar_<floating_<A1> >)
                               (unspecified_<A2>)
                               (unspecified_<A3>)
                              )
  {
    typedef void result_type;

    BOOST_FORCEINLINE result_type
    operator()(A0 const& a0,A1 const & a1, A2 & r0, A3& r1) const
    {
      nt2::tie(r0,r1) = nt2::ellipke(a0, a1);
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION ( nt2::tag::ellipke_, tag::cpu_
                             , (A0)(A1)(A2)
                             , ((ast_<A0, nt2::container::domain>))
                               (scalar_<floating_<A1> >)
                               (unspecified_<A2>)
                             )
  {
    typedef typename boost::dispatch::meta::terminal_of<A0>::type result_type;

    BOOST_FORCEINLINE result_type
    operator()(A0 const& a0,A1 const & a1, A2& r1) const
    {
      result_type r0;
      nt2::tie(r0,r1) = nt2::ellipke(a0, a1);
      return r0;
    }
  };
} }

#endif
