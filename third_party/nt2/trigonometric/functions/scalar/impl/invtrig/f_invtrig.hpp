//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TRIGONOMETRIC_FUNCTIONS_SCALAR_IMPL_INVTRIG_F_INVTRIG_HPP_INCLUDED
#define NT2_TRIGONOMETRIC_FUNCTIONS_SCALAR_IMPL_INVTRIG_F_INVTRIG_HPP_INCLUDED

#include <nt2/polynomials/functions/scalar/impl/horner.hpp>
#include <nt2/include/functions/scalar/bitofsign.hpp>
#include <nt2/include/functions/scalar/oneminus.hpp>
#include <nt2/include/functions/scalar/minusone.hpp>
#include <nt2/include/functions/scalar/oneplus.hpp>
#include <nt2/include/functions/scalar/sqr.hpp>
#include <nt2/include/functions/scalar/sqrt.hpp>
#include <nt2/include/functions/scalar/bitwise_xor.hpp>
#include <nt2/include/functions/scalar/rec.hpp>
#include <nt2/include/functions/scalar/is_eqz.hpp>
#include <nt2/include/functions/scalar/is_inf.hpp>
#include <nt2/include/functions/scalar/abs.hpp>
#include <nt2/include/functions/scalar/multiplies.hpp>
#include <nt2/include/functions/scalar/fma.hpp>
#include <nt2/include/functions/scalar/multiplies.hpp>
#include <nt2/include/constants/real_splat.hpp>
#include <nt2/include/constants/pio_2.hpp>
#include <nt2/include/constants/pi.hpp>
#include <nt2/include/constants/half.hpp>
#include <nt2/include/constants/mhalf.hpp>
#include <nt2/include/constants/one.hpp>
#include <nt2/include/constants/two.hpp>
#include <nt2/include/constants/nan.hpp>
#include <nt2/include/constants/zero.hpp>
#include <nt2/sdk/simd/tags.hpp>

namespace nt2 { namespace details {
  template < class A0,
             class unit_tag,
             class style,
             class base_A0 = typename meta::scalar_of<A0>::type
  >
  struct invtrig_base{};

  template < class A0 >
  struct invtrig_base<A0,radian_tag,tag::not_simd_type, float>
  {
    static inline A0 asin(const  A0& a0)
    {
      A0 sign, x, z;
      x = nt2::abs(a0);
      sign = nt2::bitofsign(a0);
      if ((x < single_constant<A0,0x38d1b717>())) return a0; //1.0e-4
      if ((x >  nt2::One<A0>())) return nt2::Nan<A0>();
      bool bx_larger_05    = (x > nt2::Half<A0>());
      if (bx_larger_05)
      {
        z = nt2::Half<A0>()*nt2::oneminus(x);
        x =  nt2::sqrt(z);
      }
      else
      {
        z = nt2::sqr(x);
      }
      A0 z1 = horner<NT2_HORNER_COEFF_T(A0, 5,
                                        ( 0x3d2cb352,
                                          0x3cc617e3,
                                          0x3d3a3ec7,
                                          0x3d9980f6,
                                          0x3e2aaae4
                                        )
                                       )> (z);
      z1 = nt2::fma(z1, z*x, x);
      if(bx_larger_05)
      {
        z1 = z1+z1;
        z1 = nt2::Pio_2<A0>()-z1;
      }
      return bitwise_xor(z1, sign);
    }

    static inline A0 acos(const  A0& a0)
    {
      if (a0 < nt2::Mhalf<A0>())
        return nt2::Pi<A0>()-asin( nt2::sqrt(nt2::oneplus(a0)*nt2::Half<A0>()))*nt2::Two<A0>();
      else if (a0 > nt2::Half<A0>())
        return asin( nt2::sqrt(nt2::oneminus(a0)*nt2::Half<A0>()))*nt2::Two<A0>();
      return (nt2::Pio_2<A0>()-asin(a0));
    }

    static inline A0 atan(const A0& a0)
    {
      A0 x  = kernel_atan(a0);
      return nt2::bitwise_xor(x, nt2::bitofsign(a0));
    }

    static inline A0 kernel_atan(const  A0& a0)
    {
      if (nt2::is_eqz(a0))  return nt2::Zero<A0>();
      if (nt2::is_inf(a0))  return nt2::Pio_2<A0>();
      A0 x = nt2::abs(a0);
      A0 y = 0.0;
      A0 more = Zero<A0>();
      if( x > Tan_3pio_8<A0>())
      {
        y = nt2::Pio_2<A0>();
        more = Pio_2lo<A0>();
        x = -nt2::rec(x);
      }
      else if( x > Tanpio_8<A0>())
      {
        y = nt2::Pio_4<A0>();
        more =  Pio_4lo<A0>();
        x = nt2::minusone(x)/nt2::oneplus(x);
      }
      A0 z = nt2::sqr(x);
      A0 z1 = horner<NT2_HORNER_COEFF_T(A0, 4,
                                         ( 0x3da4f0d1ul  //  8.5460119e-02
                                         , 0xbe0e1b85ul  // -1.4031009e-01
                                         , 0x3e4c925ful  //  1.9991724e-01
                                         , 0xbeaaaa2aul  // -3.3333293e-01
                                         )
                                       )> (z);
      z1 = nt2::fma(x, mul( z1, z), x);

      return y+(z1+more);
    }
  };
} }



#endif
