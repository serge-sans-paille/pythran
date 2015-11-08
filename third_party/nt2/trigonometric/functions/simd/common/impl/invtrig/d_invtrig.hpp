//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TRIGONOMETRIC_FUNCTIONS_SIMD_COMMON_IMPL_INVTRIG_D_INVTRIG_HPP_INCLUDED
#define NT2_TRIGONOMETRIC_FUNCTIONS_SIMD_COMMON_IMPL_INVTRIG_D_INVTRIG_HPP_INCLUDED

#include <nt2/polynomials/functions/scalar/impl/horner.hpp>
#include <nt2/include/functions/simd/bitofsign.hpp>
#include <nt2/include/functions/simd/abs.hpp>
#include <nt2/include/functions/simd/sqrt.hpp>
#include <nt2/include/functions/simd/sqr.hpp>
#include <nt2/include/functions/simd/if_else.hpp>
#include <nt2/include/functions/simd/if_zero_else.hpp>
#include <nt2/include/functions/simd/if_allbits_else.hpp>
#include <nt2/include/functions/simd/bitwise_xor.hpp>
#include <nt2/include/functions/simd/logical_and.hpp>
#include <nt2/include/functions/simd/is_greater_equal.hpp>
#include <nt2/include/functions/simd/is_greater.hpp>
#include <nt2/include/functions/simd/is_less.hpp>
#include <nt2/include/functions/simd/multiplies.hpp>
#include <nt2/include/functions/simd/plus.hpp>
#include <nt2/include/functions/simd/minus.hpp>
#include <nt2/include/functions/simd/unary_minus.hpp>
#include <nt2/include/functions/simd/divides.hpp>
#include <nt2/include/functions/simd/fma.hpp>
#include <nt2/include/functions/simd/fms.hpp>
#include <nt2/include/functions/simd/rec.hpp>
#include <nt2/include/functions/simd/minusone.hpp>
#include <nt2/include/functions/simd/oneplus.hpp>
#include <nt2/include/functions/simd/oneminus.hpp>
#include <nt2/include/functions/simd/seladd.hpp>
#include <nt2/include/constants/real_splat.hpp>
#include <nt2/include/constants/pio_2.hpp>
#include <nt2/include/constants/pio_4.hpp>
#include <nt2/include/constants/pio_2lo.hpp>
#include <nt2/include/constants/pio_4lo.hpp>
#include <nt2/include/constants/two.hpp>
#include <nt2/include/constants/half.hpp>
#include <nt2/include/constants/mhalf.hpp>
#include <nt2/include/constants/sqrteps.hpp>
#include <nt2/sdk/simd/tags.hpp>
#include <nt2/sdk/meta/as_logical.hpp>
#include <nt2/sdk/meta/scalar_of.hpp>

namespace nt2 { namespace details
{
  template < class A0 >
  struct invtrig_base<A0,radian_tag,tag::simd_type, double>
  {
    typedef typename meta::as_logical<A0>::type    bA0;
    typedef typename A0::native_type A0_n;
    static inline A0_n asin(const A0_n a0_n)
    {
      const A0 a0 = a0_n;
      typedef typename meta::scalar_of<A0>::type sA0;
      A0 x = nt2::abs(a0);
      const bA0 small_=  nt2::lt(x, nt2::Sqrteps<A0>());
      const A0 ct1      = double_constant<A0, 0x3fe4000000000000ll>();
      A0 zz1 = nt2::oneminus(x);
      const A0 vp = zz1*horner< NT2_HORNER_COEFF_T(sA0, 5,
                                                   (0x3f684fc3988e9f08ll,
                                                    0xbfe2079259f9290fll,
                                                    0x401bdff5baf33e6all,
                                                    0xc03991aaac01ab68ll,
                                                    0x403c896240f3081dll)
                                                  )>(zz1)/
        nt2::horner< NT2_HORNER_COEFF_T(sA0, 5,
                                        (0x3ff0000000000000ll,
                                         0xc035f2a2b6bf5d8cll,
                                         0x40626219af6a7f42ll,
                                         0xc077fe08959063eell,
                                         0x40756709b0b644bell)
                                                     )>(zz1);
      zz1 =  nt2::sqrt(zz1+zz1);
      A0 z = nt2::Pio_4<A0>()-zz1;
      zz1 = fms(zz1, vp, Pio_2lo<A0>());
      z =  z-zz1;
      zz1 = z+nt2::Pio_4<A0>();
      A0 zz2 = nt2::sqr(a0);
      z = zz2*nt2::horner< NT2_HORNER_COEFF_T(sA0, 6,
                                              (0x3f716b9b0bd48ad3ll,
                                               0xbfe34341333e5c16ll,
                                               0x4015c74b178a2dd9ll,
                                               0xc0304331de27907bll,
                                               0x40339007da779259ll,
                                               0xc020656c06ceafd5ll)
                                             )>(zz2)/
         nt2::horner< NT2_HORNER_COEFF_T(sA0, 6,
                                         (0x3ff0000000000000ll,
                                          0xc02d7b590b5e0eabll,
                                          0x40519fc025fe9054ll,
                                          0xc06265bb6d3576d7ll,
                                          0x4061705684ffbf9dll,
                                          0xc04898220a3607acll)
                                        )>(zz2);
      zz2 = x*z+x;
      return nt2::if_nan_else(nt2::gt(x,nt2::One<A0>()),
                              nt2::bitwise_xor(nt2::if_else( small_,
                                                             x,
                                                             nt2::if_else(nt2::gt(x, ct1)
                                                                         , zz1
                                                                         , zz2
                                                                         )
                                                           )
                                              , nt2::bitofsign(a0)
                                              )
                             );
    }

    static inline A0_n acos(const A0_n a0_n)
    {
      const A0 a0 = a0_n;
      typedef typename meta::as_logical<A0>::type    bA0;
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
      const A0 a0 = a0_n;
      const A0 x  = kernel_atan(a0);
      return nt2::bitwise_xor(x, nt2::bitofsign(a0));
    }

    static inline A0_n kernel_atan(const A0_n a0_n)
    {
      typedef typename meta::scalar_of<A0>::type sA0;
      const A0 a0 = a0_n;
      const A0 x =  nt2::abs(a0);
      const bA0 flag1 = nt2::lt(x,  Tan_3pio_8<A0>());
      const bA0 flag2 = nt2::logical_and(nt2::ge(x, Tanpio_8<A0>()), flag1);
      A0 yy = nt2::if_zero_else(flag1, nt2::Pio_2<A0>());
      yy = nt2::if_else(flag2, nt2::Pio_4<A0>(), yy);
      A0 xx = nt2::if_else(flag1, x, -nt2::rec(x));
      xx = nt2::if_else(flag2, nt2::minusone(x)/nt2::oneplus(x),xx);
      A0 z = nt2::sqr(xx);
      z = z*nt2::horner< NT2_HORNER_COEFF_T(sA0, 5,
                                            (0xbfec007fa1f72594ll,
                                             0xc03028545b6b807all,
                                             0xc052c08c36880273ll,
                                             0xc05eb8bf2d05ba25ll,
                                             0xc0503669fd28ec8ell)
                                           )>(z)/
              nt2::horner< NT2_HORNER_COEFF_T(sA0, 6,
                                              (0x3ff0000000000000ll,
                                               0x4038dbc45b14603cll,
                                               0x4064a0dd43b8fa25ll,
                                               0x407b0e18d2e2be3bll,
                                               0x407e563f13b049eall,
                                               0x4068519efbbd62ecll)
                                             )>(z);
      z = nt2::fma(xx, z, xx);
      z = nt2::seladd(flag2, z, Pio_4lo<A0>());
      z = z+nt2::if_zero_else(flag1, Pio_2lo<A0>());
      return yy + z;
    }
  };
} }

#endif
