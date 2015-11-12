//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_IEEE_FUNCTIONS_CONTAINER_MODF_HPP_INCLUDED
#define NT2_IEEE_FUNCTIONS_CONTAINER_MODF_HPP_INCLUDED
#include <nt2/ieee/functions/modf.hpp>
#include <nt2/include/functions/tie.hpp>
#include <nt2/core/container/dsl.hpp>
#include <boost/dispatch/meta/terminal_of.hpp>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::modf_, tag::cpu_
                            , (A0)(A1)(A2)
                            , ((ast_<A0, nt2::container::domain>))
                              (unspecified_<A1>)
                              (unspecified_<A2>)
                            )
  {
    typedef void result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& a0,A1 & r0,A2& r1) const
    {
      nt2::tie(r0,r1) = nt2::modf(a0);
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::modf_, tag::cpu_
                            , (A0)(A1)
                            , ((ast_<A0, nt2::container::domain>))
                              (unspecified_<A1>)
                            )
  {
    typedef typename boost::dispatch::meta::terminal_of<A0>::type result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& a0,A1& r1) const
    {
      result_type r0;
      nt2::tie(r0,r1) = nt2::modf(a0);
      return r0;
    }
  };
} }

#endif
