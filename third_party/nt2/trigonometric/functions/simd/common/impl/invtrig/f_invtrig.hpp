//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TRIGONOMETRIC_FUNCTIONS_SIMD_COMMON_IMPL_INVTRIG_F_INVTRIG_HPP_INCLUDED
#define NT2_TRIGONOMETRIC_FUNCTIONS_SIMD_COMMON_IMPL_INVTRIG_F_INVTRIG_HPP_INCLUDED

#include <nt2/polynomials/functions/scalar/impl/horner.hpp>
#include <nt2/include/functions/simd/abs.hpp>
#include <nt2/include/functions/simd/bitofsign.hpp>
#include <nt2/include/functions/simd/is_greater.hpp>
#include <nt2/include/functions/simd/if_else.hpp>
#include <nt2/include/functions/simd/oneminus.hpp>
#include <nt2/include/functions/simd/sqr.hpp>
#include <nt2/include/functions/simd/fma.hpp>
#include <nt2/include/functions/simd/sqrt.hpp>
#include <nt2/include/functions/simd/bitwise_xor.hpp>
#include <nt2/include/functions/simd/is_greater_equal.hpp>
#include <nt2/include/functions/simd/logical_and.hpp>
#include <nt2/include/functions/simd/if_zero_else.hpp>
#include <nt2/include/functions/simd/unary_minus.hpp>
#include <nt2/include/functions/simd/rec.hpp>
#include <nt2/include/functions/simd/minusone.hpp>
#include <nt2/include/functions/simd/oneplus.hpp>
#include <nt2/include/functions/simd/seladd.hpp>
#include <nt2/include/functions/simd/ifnotadd.hpp>
#include <nt2/include/functions/simd/is_less.hpp>
#include <nt2/include/functions/simd/multiplies.hpp>
#include <nt2/include/functions/simd/plus.hpp>
#include <nt2/include/functions/simd/minus.hpp>
#include <nt2/include/functions/simd/divides.hpp>
#include <nt2/include/constants/real_splat.hpp>
#include <nt2/include/constants/pio_4.hpp>
#include <nt2/include/constants/half.hpp>
#include <nt2/include/constants/pio_4lo.hpp>
#include <nt2/include/constants/mhalf.hpp>
#include <nt2/include/constants/pio_2.hpp>
#include <nt2/include/constants/pio_2lo.hpp>
#include <nt2/include/constants/tan_3pio_8.hpp>
#include <nt2/include/constants/tanpio_8.hpp>
#include <nt2/sdk/simd/tags.hpp>
#include <nt2/sdk/meta/as_logical.hpp>

namespace nt2 { namespace details
{
  template < class A0 >
  struct invtrig_base<A0,radian_tag,tag::simd_type, float>
  {
    typedef typename meta::as_logical<A0>::type    bA0;
    typedef typename A0::native_type              A0_n;
    typedef typename meta::scalar_of<A0>::type sA0;
    static inline A0_n asin(const A0_n a0_n)
    {
      const A0 a0 = a0_n;
      A0 sign, x;
      x = nt2::abs(a0);
      sign = nt2::bitofsign(a0);
      const bA0 x_larger_05 = gt(x, nt2::Half<A0>());
      A0 z = if_else(x_larger_05, nt2::Half<A0>()*nt2::oneminus(x), nt2::sqr(x));
      x = if_else(x_larger_05, sqrt(z), x);
      // remez polynomial of degree 4 for (asin(rx)-rx)/(rx*rx*rx) in [0, 0.25]
      // 2120752146 values (99.53%) within 0.0 ULPs
      //    9954286 values (0.47%)  within 0.5 ULPs
      // 4.0 cycles/element SSE4.2 g++-4.8
      A0 z1 = horner<NT2_HORNER_COEFF_T(sA0, 5,
                                        ( 0x3d2cb352,
                                          0x3cc617e3,
                                          0x3d3a3ec7,
                                          0x3d9980f6,
                                          0x3e2aaae4
                                        )
                                       )> (z);
      z1 = nt2::fma(z1, z*x, x);
      z = if_else(x_larger_05, nt2::Pio_2<A0>()-(z1+z1), z1);
      return nt2::b_xor(z, sign);
    }

    static inline A0_n acos(const A0_n a0_n)
    {
      // 2130706432 values computed.
      // 1968272987 values (92.38%) within 0.0 ULPs
      //  162433445 values (7.62%)  within 0.5 ULPs
      // 8.5 cycles/element SSE4.2 g++-4.8
      const A0 a0 = a0_n;
      A0 x = nt2::abs(a0);
      bA0 x_larger_05 = gt(x, nt2::Half<A0>());
      x  = if_else(x_larger_05, nt2::sqrt(fma(nt2::Mhalf<A0>(), x, nt2::Half<A0>())), a0);
      x  = asin(x);
      x =  seladd(x_larger_05, x, x);
      x  = nt2::if_else(lt(a0, nt2::Mhalf<A0>()), nt2::Pi<A0>()-x, x);
      return nt2::if_else(x_larger_05, x, nt2::Pio_2<A0>()-x);
    }

    static inline A0_n atan(const A0_n a0_n)
    {
      // 4.5 cycles/element SSE4.2 g++-4.8
      const A0 a0 = a0_n;
      A0 x  = kernel_atan(a0);
      return nt2::b_xor(x, nt2::bitofsign(a0));
    }

    static inline A0_n kernel_atan(const A0_n a0_n)
    {
      //4278190076 values computed  in range: [-3.40282e+38, 3.40282e+38]
      //4257598358 values (99.52%)  within 0.0 ULPs
      //  20591718 values (0.48%)   within 0.5 ULPs
      const A0 a0 = a0_n;
      const A0 x = nt2::abs(a0);

      //here x is positive
      const bA0 flag1 = nt2::lt(x, Tan_3pio_8<A0>());
      const bA0 flag2 = nt2::logical_and(nt2::ge(x,single_constant<A0, 0x3ed413cd>()), flag1);
      A0 yy =  nt2::if_zero_else(flag1, Pio_2<A0>());
      yy =  nt2::if_else(flag2, Pio_4<A0>(), yy);
      A0 xx =   nt2::if_else(flag1, x, -rec(x));
      xx =  nt2::if_else(flag2, (nt2::minusone(x)/nt2::oneplus(x)),xx);
      const A0 z = nt2::sqr(xx);
      A0 z1 = horner<NT2_HORNER_COEFF_T(sA0, 4,
                                         ( 0x3da4f0d1ul  //  8.5460119e-02
                                         , 0xbe0e1b85ul  // -1.4031009e-01
                                         , 0x3e4c925ful  //  1.9991724e-01
                                         , 0xbeaaaa2aul  // -3.3333293e-01
                                         )
                                       )> (z);
      z1 = nt2::fma(xx, nt2::mul( z1, z), xx);
      z1 = ifadd(flag2, z1, Pio_4lo<A0>());
      z1 = ifnotadd(flag1, z1, Pio_2lo<A0>());
      return yy+z1;
    }
  };
} }

#endif
