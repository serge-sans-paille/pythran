//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_EXPONENTIAL_FUNCTIONS_DETAILS_EXPM1_KERNEL_HPP_INCLUDED
#define NT2_EXPONENTIAL_FUNCTIONS_DETAILS_EXPM1_KERNEL_HPP_INCLUDED

#include <nt2/include/constants/half.hpp>
#include <nt2/include/constants/invlog_2.hpp>
#include <nt2/include/constants/log_2hi.hpp>
#include <nt2/include/constants/log_2lo.hpp>
#include <nt2/include/constants/maxexponent.hpp>
#include <nt2/include/constants/nbmantissabits.hpp>
#include <nt2/include/constants/six.hpp>
#include <nt2/include/constants/three.hpp>
#include <nt2/include/constants/twenty.hpp>
#include <nt2/include/functions/simd/bitwise_cast.hpp>
#include <nt2/include/functions/simd/divides.hpp>
#include <nt2/include/functions/simd/expm1.hpp>
#include <nt2/include/functions/simd/fast_ldexp.hpp>
#include <nt2/include/functions/simd/fms.hpp>
#include <nt2/include/functions/simd/fnms.hpp>
#include <nt2/include/functions/simd/if_else.hpp>
#include <nt2/include/functions/simd/is_less.hpp>
#include <nt2/include/functions/simd/minus.hpp>
#include <nt2/include/functions/simd/multiplies.hpp>
#include <nt2/include/functions/simd/oneminus.hpp>
#include <nt2/include/functions/simd/oneplus.hpp>
#include <nt2/include/functions/simd/plus.hpp>
#include <nt2/include/functions/simd/round2even.hpp>
#include <nt2/include/functions/simd/shift_left.hpp>
#include <nt2/include/functions/simd/sqr.hpp>
#include <nt2/include/functions/simd/toint.hpp>
#include <nt2/include/functions/simd/unary_minus.hpp>
#include <nt2/polynomials/functions/scalar/impl/horner.hpp>
#include <nt2/sdk/meta/as_integer.hpp>
#include <nt2/sdk/meta/scalar_of.hpp>

namespace nt2 { namespace details
{
  template < class A0, class sA0 = typename meta::scalar_of<A0>::type >
  struct expm1_kernel;

  template < class A0 >
  struct expm1_kernel < A0, float >
  {
    // computes expm1 for float or float vectors
    static BOOST_FORCEINLINE A0 expm1(const A0& a0)
    {
      typedef typename meta::as_integer<A0>::type iA0;
      typedef typename meta::scalar_of<A0>::type sA0;
      A0 k  = nt2::round2even(Invlog_2<A0>()*a0);
      A0 x = fnms(k, Log_2hi<A0>(), a0);
      x =  fnms(k, Log_2lo<A0>(), x);
      A0 hx  = x*Half<A0>();
      A0 hxs = x*hx;
      A0 r1 = horner<NT2_HORNER_COEFF_T(sA0, 3,
                                        (0x3acf6db4, // 1.5825541e-03
                                         0xbd08887f, // -3.3333298e-02
                                         0x3f800000) // 1
                                       )> (hxs);
      A0 t  = fnms(r1, hx, Three<A0>());
      A0 e  = hxs*((r1-t)/(Six<A0>() - x*t));
      e  = fms(x, e, hxs);
      iA0 ik =  toint(k);
      A0 two2mk = bitwise_cast<A0>(shl(Maxexponent<A0>()-ik,Nbmantissabits<sA0>()));
      A0 y = oneminus(two2mk)-(e-x);
      return fast_ldexp(y, ik);
    }
  };

  template < class A0 >
  struct expm1_kernel < A0, double >
  {
    // computes expm1 for  double or double vectors
    static  BOOST_FORCEINLINE A0 expm1(const A0& a0)
    {
      typedef typename meta::as_integer<A0>::type iA0;
      typedef typename meta::scalar_of<A0>::type sA0;
      A0 k  = nt2::round2even(Invlog_2<A0>()*a0);
      A0 hi = fnms(k, Log_2hi<A0>(), a0);
      A0 lo = k*Log_2lo<A0>();
      A0 x  = hi-lo;
      A0 hxs = sqr(x)*Half<A0>();
      A0 r1 = horner<NT2_HORNER_COEFF_T(sA0, 6,
                                        (0xBE8AFDB76E09C32Dll,
                                         0x3ED0CFCA86E65239ll,
                                         0xBF14CE199EAADBB7ll,
                                         0x3F5A01A019FE5585ll,
                                         0xBFA11111111110F4ll,
                                         0x3ff0000000000000ll)
                                       )> (hxs);
      A0 t  = Three<A0>()-r1*Half<A0>()*x;
      A0 e  = hxs*((r1-t)/(Six<A0>() - x*t));
      A0 c = (hi-x)-lo;
      e  = (x*(e-c)-c)-hxs;
      iA0 ik =  toint(k);
      A0 two2mk = bitwise_cast<A0>(shl(Maxexponent<A0>()-ik,Nbmantissabits<sA0>()));
      A0 ct1= oneminus(two2mk)-(e-x);
      A0 ct2= oneplus((x-(e+two2mk)));
      A0 y = if_else(lt(k, Twenty<A0>()),ct1,ct2);
      return fast_ldexp(y, ik);
    }
  };
} }

#endif
