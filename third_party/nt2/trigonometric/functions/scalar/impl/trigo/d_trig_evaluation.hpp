//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TRIGONOMETRIC_FUNCTIONS_SCALAR_IMPL_TRIGO_D_TRIG_EVALUATION_HPP_INCLUDED
#define NT2_TRIGONOMETRIC_FUNCTIONS_SCALAR_IMPL_TRIGO_D_TRIG_EVALUATION_HPP_INCLUDED
#include <nt2/polynomials/functions/scalar/impl/horner.hpp>
#include <nt2/include/functions/scalar/rec.hpp>
#include <nt2/include/functions/scalar/sqr.hpp>
#include <nt2/include/functions/scalar/fma.hpp>
#include <nt2/include/functions/scalar/oneminus.hpp>
#include <nt2/include/functions/scalar/multiplies.hpp>
#include <nt2/sdk/simd/tags.hpp>
#include <nt2/sdk/meta/as_integer.hpp>
#include <nt2/sdk/meta/scalar_of.hpp>

namespace nt2 { namespace details
{

  template < class A0>
  struct trig_evaluation < A0,  tag::not_simd_type, double >
  {
    typedef typename meta::as_integer<A0, signed>::type int_type;
    typedef typename meta::scalar_of<A0>::type stype;
    static inline A0 cos_eval(const A0& z)
    {
      const A0 y = nt2::horner< NT2_HORNER_COEFF_T(stype, 7, (0x3da8ff831ad9b219ll,
                                                         0xbe21eea7c1e514d4ll,
                                                         0x3e927e4f8e06d9a5ll,
                                                         0xbefa01a019ddbcd9ll,
                                                         0x3f56c16c16c15d47ll,
                                                         0xbfa5555555555551ll,
                                                         0x3fe0000000000000ll) ) > (z);
      return nt2::oneminus(y*z);
    }

    static inline A0 sin_eval(const A0& z, const A0& x)
    {
      const A0 y1 = horner< NT2_HORNER_COEFF_T(stype, 6, (0x3de5d8fd1fcf0ec1ll,
                                                          0xbe5ae5e5a9291691ll,
                                                          0x3ec71de3567d4896ll,
                                                          0xbf2a01a019bfdf03ll,
                                                          0x3f8111111110f7d0ll,
                                                          0xbfc5555555555548ll) ) > (z);
      return nt2::fma(nt2::mul(y1,z),x,x);
    }

    static inline A0 base_tan_eval(const A0& x)
    {
      const A0 zz = nt2::sqr(x);
      const A0 num = nt2::horner< NT2_HORNER_COEFF_T(stype, 3, (0xc0c992d8d24f3f38ll,
                                                           0x413199eca5fc9dddll,
                                                           0xc1711fead3299176ll))>(zz);
      const A0 den = nt2::horner< NT2_HORNER_COEFF_T(stype, 5, (0x3ff0000000000000ll,
                                                           0x40cab8a5eeb36572ll,
                                                           0xc13427bc582abc96ll,
                                                           0x4177d98fc2ead8efll,
                                                           0xc189afe03cbe5a31ll))>(zz);
      return x+ x*(zz*(num/den));
    }

    static inline A0 tan_eval(const A0& x,   int_type n )
    {
      A0 y =  base_tan_eval(x);
      if (n == 1) return y;  else return -nt2::rec(y);
    }
    static inline A0 cot_eval(const A0& x,  int_type n )
    {
      A0 y =  base_tan_eval(x);
      if (n == 1) return nt2::rec(y);  else return -y;
    }
  };
} }


#endif

// /////////////////////////////////////////////////////////////////////////////
// End of d_trig_evaluation.hpp
// /////////////////////////////////////////////////////////////////////////////
