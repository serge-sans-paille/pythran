/*******************************************************************************
 *         Copyright 2003-2013 LASMEA UMR 6602 CNRS/U.B.P
 *         Copyright 2011-2013 LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_ELLIPTIC_FUNCTIONS_GENERIC_DETAILS_AM_KERNEL_HPP_INCLUDED
#define NT2_ELLIPTIC_FUNCTIONS_GENERIC_DETAILS_AM_KERNEL_HPP_INCLUDED

#include <nt2/include/functions/simd/sqrt.hpp>
#include <nt2/include/functions/simd/oneminus.hpp>
#include <nt2/include/functions/simd/sqr.hpp>
#include <nt2/include/functions/simd/average.hpp>
#include <nt2/include/functions/simd/asin.hpp>
#include <nt2/include/functions/simd/sin.hpp>
#include <nt2/include/functions/simd/divides.hpp>
#include <nt2/include/functions/simd/multiplies.hpp>
#include <nt2/include/functions/simd/plus.hpp>
#include <nt2/include/functions/simd/unary_minus.hpp>
#include <nt2/include/functions/simd/abs.hpp>
#include <nt2/include/functions/simd/maximum.hpp>
#include <nt2/include/constants/one.hpp>

namespace nt2
{
  namespace details
  {
    template < class A0, class A1, class A2>
    BOOST_FORCEINLINE static A0 am_kernel(const A0 & u,const A1 & k, const A2 & tol)
    {
      static const int N = 30;
      A0 a[N+1];
      A0 g[N+1];
      A0 c[N+1];
      a[0] = One<A0>();
      g[0] = nt2::sqrt(oneminus(sqr(k)));
      c[0] = k;

      // Perform the sequence of Gaussian transformations of arithmetic and
      // geometric means of successive arithmetic and geometric means until
      // the two means converge to a common mean (upto machine accuracy)
      // starting with a = 1 and g = k', which were set above.

      A0 two_n =  One<A0>();
      int n;
      for (n = 0; n < N; n++)
      {
        if (nt2::maximum(nt2::abs(c[n])) < tol) break;
        //if (all(is_nge(nt2::abs(a[n] - g[n]),tol*a[n])) break;
        two_n += two_n;
        a[n+1] = average(a[n], g[n]);
        g[n+1] = nt2::sqrt(a[n] * g[n]);
        c[n+1] = average(a[n], -g[n]);
      }
      // Prepare for the inverse transformation of phi = x * cm. //
      A0 phi = two_n * a[n] * u;
      // Perform backward substitution //
      for (; n > 0; --n)
      {
        phi = average(phi, nt2::asin(c[n]*nt2::sin(phi)/a[n]) );
      }
      return phi;
    }
  }

}

#endif
