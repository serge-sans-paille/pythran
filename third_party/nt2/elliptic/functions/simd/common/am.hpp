//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_ELLIPTIC_FUNCTIONS_SIMD_COMMON_AM_HPP_INCLUDED
#define NT2_ELLIPTIC_FUNCTIONS_SIMD_COMMON_AM_HPP_INCLUDED

#include <nt2/elliptic/functions/am.hpp>
#include <boost/dispatch/attributes.hpp>
#include <nt2/elliptic/functions/generic/details/am_kernel.hpp>
#include <nt2/include/constants/half.hpp>
#include <nt2/include/constants/one.hpp>
#include <nt2/include/constants/pio_2.hpp>
#include <nt2/include/constants/two.hpp>
#include <nt2/include/functions/simd/abs.hpp>
#include <nt2/include/functions/simd/atan.hpp>
#include <nt2/include/functions/simd/exp.hpp>
#include <nt2/include/functions/simd/if_else.hpp>
#include <nt2/include/functions/simd/is_equal.hpp>
#include <nt2/include/functions/simd/minus.hpp>
#include <nt2/include/functions/simd/multiplies.hpp>

namespace nt2 { namespace ext
{

   NT2_FUNCTOR_IMPLEMENTATION(nt2::tag::am_, tag::cpu_,
                              (A0)(A1)(A2)(X),
                              ((simd_<floating_<A0>,X >))
                              ((simd_<floating_<A1>,X >))
                              (scalar_<floating_<A2> >)
                             )
   {
     typedef A0 result_type;

     BOOST_FORCEINLINE result_type operator()(const A0 & u, const A1 & x,
                                             const A2 & tol) const
    {
      result_type xx = nt2::abs(x);
      result_type k = if_else(eq(xx, One<A0>()), Half<A0>(), xx);
      return  if_else(eq(xx, One<A0>()),
                      Two<A0>()*atan(exp(u))-Pio_2<A0>(),
                      details::am_kernel(u, k, tol));
    }
  };

} }
#endif
