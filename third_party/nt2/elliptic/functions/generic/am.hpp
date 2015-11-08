//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_ELLIPTIC_FUNCTIONS_GENERIC_AM_HPP_INCLUDED
#define NT2_ELLIPTIC_FUNCTIONS_GENERIC_AM_HPP_INCLUDED

#include <nt2/elliptic/functions/am.hpp>
#include <boost/dispatch/attributes.hpp>
#include <nt2/include/constants/eps.hpp>
#include <nt2/include/functions/simd/abs.hpp>
#include <nt2/include/functions/simd/sin.hpp>
#include <nt2/include/functions/simd/sqrt.hpp>
#include <nt2/sdk/meta/scalar_of.hpp>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION(nt2::tag::am_, tag::cpu_,
                             (A0)(A1)(A2)(A3),
                             (generic_<floating_<A0> >)
                             (generic_<floating_<A1> >)
                             (scalar_<floating_<A2> >)
                             (scalar_<integer_<A3> >)
                            )
  {
    typedef A0 result_type;

    BOOST_FORCEINLINE result_type operator()(const A0 & u, const A1 & x,
                                             const A2 & tol, const A3 & choice) const
    {
      switch (choice)
      {
      case 'a': return am(u,nt2::sin(x), tol);
      case 'm': return am(u,nt2::sqrt(nt2::abs(x)), tol);
      default : return am(u,x,tol);
      }
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION(nt2::tag::am_, tag::cpu_,
                             (A0)(A1)(A2),
                             (generic_<floating_<A0> >)
                             (generic_<floating_<A1> >)
                             (scalar_<integer_<A2> >)
                            )
  {
    typedef A0 result_type;

    BOOST_FORCEINLINE result_type operator()(const A0 & u, const A1 & x,
                                             const A2 & choice) const
    {
      typedef typename meta::scalar_of<result_type>::type sA0;
      return am(u,x,Eps<sA0>(),choice);
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION(nt2::tag::am_, tag::cpu_,
                              (A0)(A1),
                              (generic_<floating_<A0> >)
                              (generic_<floating_<A1> >)
                             )
  {
    typedef A0 result_type;
    BOOST_FORCEINLINE result_type operator()(const A0 & u, const A1 & x) const
    {
      typedef typename meta::scalar_of<result_type>::type sA0;
      return am(u,x,Eps<sA0>());
    }
  };
} }
#endif
