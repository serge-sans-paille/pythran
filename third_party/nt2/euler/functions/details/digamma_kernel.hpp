//==============================================================================
//         Copyright 2003 - 2014 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2014 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_EULER_FUNCTIONS_DETAILS_DIGAMMA_KERNEL_HPP_INCLUDED
#define NT2_EULER_FUNCTIONS_DETAILS_DIGAMMA_KERNEL_HPP_INCLUDED
#include <nt2/include/constants/one.hpp>
#include <nt2/include/constants/two.hpp>
#include <nt2/include/functions/simd/divides.hpp>
#include <nt2/include/functions/simd/fma.hpp>
#include <nt2/include/functions/simd/log.hpp>
#include <nt2/include/functions/simd/minus.hpp>
#include <nt2/include/functions/simd/multiplies.hpp>
#include <nt2/include/functions/simd/plus.hpp>
#include <nt2/include/functions/simd/rec.hpp>
#include <nt2/include/functions/simd/splat.hpp>
#include <nt2/include/functions/simd/sqr.hpp>
#include <nt2/polynomials/functions/scalar/impl/horner.hpp>
#include <nt2/sdk/meta/scalar_of.hpp>

#include <boost/dispatch/attributes.hpp>

namespace nt2 { namespace details
{
  template < class A0, class sA0 = typename meta::scalar_of<A0>::type >
  struct digamma_kernel;

  template < class A0 >
  struct digamma_kernel < A0, double >
  {
    typedef typename meta::scalar_of<A0>::type sA0;
    // computes digamma(a0)/a0 for double or double vectors
    // xx is sqr(a0) and 0 <= abs(a0) <= 3.25
    static BOOST_FORCEINLINE A0 digamma_1_2(const A0& a0)
    {
      float fY = 0.99558162689208984f;
      const A0 Y = splat<A0>(fY); // 0.99558162689208984;
      const A0 root1 = splat<A0>(1569415565.0 / 1073741824uL);
      const A0 root2 = splat<A0>((381566830.0 / 1073741824uL) / 1073741824uL);
      const A0 root3 = splat<A0>(0.9016312093258695918615325266959189453125e-19);

      A0 x = a0;
      A0 g = x - root1;
      g -= root2;
      g -= root3;
      x-= nt2::One<A0>();
      A0 r =  NT2_HORNER_RAT(sA0, 6, 7, x,
                             (0xbf60f7e5f66c2537ll,
                              0xbfa72b2e63723c78ll,
                              0xbfd2821c13c5e2bfll,
                              0xbfe4cf68d26e295all,
                              0xbfd4d5d0f9ab412fll,
                              0x3fd04e9e69894978ll
                             ),
                             (0xbea2b84f95bbf448ll,
                              0x3f616fc90a0a1908ll,
                              0x3fabb9c8cc612ca3ll,
                              0x3fdbe65d28de361cll,
                              0x3ff75eb79397c930ll,
                              0x40009d1b06674d41ll,
                              0x3ff0000000000000ll
                             )
                            );
      A0 result = nt2::fma(g, Y, g * r);
      return result;
    }

    static BOOST_FORCEINLINE A0 digamma_imp_large(const A0& a0)
    {
      // x >  20
      A0 x = a0;
      x -= nt2::One<A0>();
      A0 result = nt2::log(x);
      result += nt2::rec(nt2::Two<A0>()*x);
      A0 z = nt2::rec(nt2::sqr(x));
      result -= z *
        horner<NT2_HORNER_COEFF_T(sA0, 8,
                                  (0xbfdc5e5e5e5e5e5ell,
                                   0x3fb5555555555555ll,
                                   0xbf95995995995996ll,
                                   0x3f7f07c1f07c1f08ll,
                                   0xbf71111111111111ll,
                                   0x3f70410410410410ll,
                                   0xbf81111111111111ll,
                                   0x3fb5555555555555ll
                                  )
                                 )> (z);
      return result;
    }
  };
} }

#endif
