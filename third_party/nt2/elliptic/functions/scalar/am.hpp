//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_ELLIPTIC_FUNCTIONS_SCALAR_AM_HPP_INCLUDED
#define NT2_ELLIPTIC_FUNCTIONS_SCALAR_AM_HPP_INCLUDED

#include <nt2/elliptic/functions/am.hpp>
#include <boost/dispatch/attributes.hpp>
#include <nt2/elliptic/functions/generic/details/am_kernel.hpp>
#include <nt2/include/constants/one.hpp>
#include <nt2/include/constants/pio_2.hpp>
#include <nt2/include/constants/two.hpp>
#include <nt2/include/functions/scalar/abs.hpp>
#include <nt2/include/functions/scalar/atan.hpp>
#include <nt2/include/functions/scalar/exp.hpp>
#include <nt2/include/functions/scalar/is_equal.hpp>
#include <nt2/include/functions/scalar/is_eqz.hpp>

namespace nt2 { namespace ext
{

   NT2_FUNCTOR_IMPLEMENTATION(nt2::tag::am_, tag::cpu_,
                              (A0)(A1)(A2),
                              (scalar_<floating_<A0> >)
                              (scalar_<floating_<A1> >)
                              (scalar_<floating_<A2> >)
                             )
  {
    typedef A0 result_type;
    BOOST_FORCEINLINE result_type operator()(const A0 & u, const A1 & x,
                                             const A2 & tol) const
    {
      if(is_eqz(x)) return u;
      result_type k = nt2::abs(x);
      if(eq(k, One<A0>())) return Two<A0>()*atan(exp(u))-Pio_2<A0>();
      return details::am_kernel(u, k, tol);
    }
  };

} }
#endif
