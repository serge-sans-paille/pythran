//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TRIGONOMETRIC_FUNCTIONS_SIMD_COMMON_IMPL_TRIGO_F_TRIG_EVALUATION_HPP_INCLUDED
#define NT2_TRIGONOMETRIC_FUNCTIONS_SIMD_COMMON_IMPL_TRIGO_F_TRIG_EVALUATION_HPP_INCLUDED

#include <nt2/polynomials/functions/scalar/impl/horner.hpp>
#include <nt2/include/functions/simd/fma.hpp>
#include <nt2/include/functions/simd/multiplies.hpp>
#include <nt2/include/functions/simd/sqr.hpp>
#include <nt2/include/functions/simd/plus.hpp>
#include <nt2/include/functions/simd/if_else.hpp>
#include <nt2/include/functions/simd/is_equal.hpp>
#include <nt2/include/functions/simd/oneplus.hpp>
#include <nt2/include/functions/simd/rec.hpp>
#include <nt2/include/functions/simd/unary_minus.hpp>
#include <nt2/include/constants/mhalf.hpp>
#include <nt2/include/constants/one.hpp>

namespace nt2 { namespace details
{
  template <class A0> struct trig_evaluation < A0,  tag::simd_type, float>
  {

    typedef typename meta::as_integer<A0, signed>::type     int_type;
    typedef typename meta::scalar_of<A0>::type                 stype;
    typedef typename A0::native_type                            A0_n;
    typedef typename int_type::native_type                     iA0_n;

    static inline A0_n cos_eval(const A0_n z_n)
    {
      const A0 z = z_n;
      const A0 y = nt2::horner< NT2_HORNER_COEFF_T(stype, 3, (0x37ccf5ce, 0xbab60619, 0x3d2aaaa5) ) > (z);
      return nt2::oneplus(nt2::fma(z,nt2::Mhalf<A0>(), y*nt2::sqr(z)));
    }
    static inline A0_n sin_eval(const A0_n z_n, const A0& x)
    {
      const A0 z = z_n;
      const A0 y1 =  nt2::horner< NT2_HORNER_COEFF_T(stype, 3, (0xb94ca1f9, 0x3c08839d, 0xbe2aaaa2) ) > (z);
      return nt2::fma(nt2::mul(y1,z),x,x);
    }
    static inline A0_n base_tancot_eval(const A0_n z_n)
    {
      const A0 z = z_n;
      const A0 zz = nt2::sqr(z);
      return nt2::horner< NT2_HORNER_COEFF_T(stype, 6, (0x3c19c53b,
                                                        0x3b4c779c,
                                                        0x3cc821b5,
                                                        0x3d5ac5c9,
                                                        0x3e0896dd,
                                                        0x3eaaaa6f))>(zz)*zz*z+z;
    }
    static inline A0_n tan_eval(const A0_n z_n,  const iA0_n n_n)
    {
      const int_type n = n_n;
      const A0 z = z_n;
      A0 y = base_tancot_eval(z);
      return nt2::if_else(nt2::is_equal(n, nt2::One<int_type>()),y,-nt2::rec(y));
    }
    static inline A0_n cot_eval(const A0_n z_n,  const iA0_n n_n)
    {
      const int_type n = n_n;
      const A0 z = z_n;
      A0 y = base_tancot_eval(z);
      return nt2::if_else(nt2::is_equal(n, One<int_type>()),nt2::rec(y),-y);
    }
  };
} }


#endif
