//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TRIGONOMETRIC_FUNCTIONS_CONTAINER_REM_PIO2_STRAIGHT_HPP_INCLUDED
#define NT2_TRIGONOMETRIC_FUNCTIONS_CONTAINER_REM_PIO2_STRAIGHT_HPP_INCLUDED

#include <nt2/trigonometric/functions/rem_pio2_straight.hpp>
#include <nt2/include/functions/tie.hpp>
#include <nt2/sdk/meta/as_integer.hpp>
#include <boost/dispatch/meta/terminal_of.hpp>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::rem_pio2_straight_, tag::cpu_
                            , (A0)(A1)(A2)
                            , ((ast_<A0, nt2::container::domain>))
                              (unspecified_<A1>)
                              (unspecified_<A2>)
                            )
  {
    typedef void result_type;
    BOOST_FORCEINLINE result_type operator()(A0 const& a0,A1 & r0,A2& r1) const
    {
      nt2::tie(r0,r1) = nt2::rem_pio2_straight(a0);
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::rem_pio2_straight_, tag::cpu_
                            , (A0)(A1)
                            , ((ast_<A0, nt2::container::domain>))
                              (unspecified_<A1>)
                            )
  {
    typedef typename boost::dispatch::meta::terminal_of<A0>::type base;
    typedef typename meta::as_integer<base>::type                 result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& a0,A1& r1) const
    {
      result_type r0;
      nt2::tie(r0,r1) = nt2::rem_pio2_straight(a0);
      return r0;
    }
  };
} }

#endif
