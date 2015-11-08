//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_EULER_FUNCTIONS_SIMD_COMMON_SPENCE_HPP_INCLUDED
#define NT2_EULER_FUNCTIONS_SIMD_COMMON_SPENCE_HPP_INCLUDED

#include <nt2/euler/functions/spence.hpp>
#include <nt2/include/constants/half.hpp>
#include <nt2/include/constants/mhalf.hpp>
#include <nt2/include/constants/one.hpp>
#include <nt2/include/constants/pi2o_6.hpp>
#include <nt2/include/constants/two.hpp>
#include <nt2/include/functions/simd/divides.hpp>
#include <nt2/include/functions/simd/if_else.hpp>
#include <nt2/include/functions/simd/is_eqz.hpp>
#include <nt2/include/functions/simd/is_greater.hpp>
#include <nt2/include/functions/simd/is_less.hpp>
#include <nt2/include/functions/simd/log.hpp>
#include <nt2/include/functions/simd/logical_or.hpp>
#include <nt2/include/functions/simd/minus.hpp>
#include <nt2/include/functions/simd/minusone.hpp>
#include <nt2/include/functions/simd/multiplies.hpp>
#include <nt2/include/functions/simd/oneminus.hpp>
#include <nt2/include/functions/simd/plus.hpp>
#include <nt2/include/functions/simd/rec.hpp>
#include <nt2/include/functions/simd/sqr.hpp>
#include <nt2/include/functions/simd/tofloat.hpp>
#include <nt2/include/functions/simd/unary_minus.hpp>
#include <nt2/polynomials/functions/scalar/impl/horner.hpp>
#include <nt2/sdk/meta/as_floating.hpp>
#include <nt2/sdk/meta/as_logical.hpp>
#include <nt2/sdk/meta/scalar_of.hpp>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::spence_, tag::cpu_
                            , (A0)(X)
                            , ((simd_<arithmetic_<A0>,X>))
                            )
  {
    typedef typename meta::as_floating<A0>::type result_type;
    NT2_FUNCTOR_CALL(1)
    {
      return nt2::spence(nt2::tofloat(a0));
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::spence_, tag::cpu_
                            , (A0)(X)
                            , ((simd_<double_<A0>,X>))
                            )
  {
    typedef A0 result_type;
    NT2_FUNCTOR_CALL(1)
    {
      typedef typename meta::as_logical<A0>::type bA0;
      typedef typename meta::scalar_of<A0>::type sA0;
      A0 x = a0;
      bA0 flag2 =  nt2::gt(x, nt2::Two<A0>());
      x = nt2::if_else(flag2, rec(x), x);
      bA0 flag = nt2::gt(x,nt2::One<A0>()+nt2::Half<A0>());
      bA0 flag1= nt2::lt(x,nt2::Half<A0>());
      flag2 = nt2::logical_or(flag2, flag);
      A0 w =  nt2::if_else(flag,
                           nt2::minusone(nt2::rec(x)),
                           nt2::if_else(flag1, -x, nt2::minusone(x)));
      A0 y = -w*horner < NT2_HORNER_COEFF_T(sA0, 8,
                                            (0x3f0862d9a70a1bffll, // 4.65128586073990045278E-5
                                             0x3f7df74463beda34ll, // 7.31589045238094711071E-3
                                             0x3fc121eb61515c68ll, // 1.33847639578309018650E-1
                                             0x3fec266e64d1f41bll, // 8.79691311754530315341E-1
                                             0x4005b12621c05b6all, // 2.71149851196553469920E0
                                             0x401107238d7a3427ll, // 4.25697156008121755724E0
                                             0x400a61b791772b23ll, // 3.29771340985225106936E0
                                             0x3ff0000000000000ll // 1.00000000000000000126E0
                                            )
                                           ) > (w)/
        horner < NT2_HORNER_COEFF_T(sA0, 8,
                                    (0x3f46a472c69ef90ell, // 6.90990488912553276999E-4
                                     0x3f9a039ad7232021ll, // 2.54043763932544379113E-2
                                     0x3fd21c4296f8343fll, // 2.82974860602568089943E-1
                                     0x3ff6966dfa85ad29ll, // 1.41172597751831069617E0
                                     0x400d1aa28a4ec717ll, // 3.63800533345137075418E0
                                     0x401421936337526fll, // 5.03278880143316990390E0
                                     0x400c61b791772b23ll, // 3.54771340985225096217E0
                                     0x3ff0000000000000ll // 9.99999999999999998740E-1
                                    )
                                   ) > (w);
      A0 z = nt2::log(x);
      y = nt2::if_else(flag1, Pi2o_6<A0>()-z * nt2::log(nt2::oneminus(x))-y,y);
      y = nt2::if_else(flag2, nt2::Mhalf<A0>()*nt2::sqr(z)-y,y);
      return nt2::if_else(nt2::is_eqz(a0), Pi2o_6<A0>(), y);
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::spence_, tag::cpu_
                            , (A0)(X)
                            , ((simd_<single_<A0>,X>))
                            )
  {
    typedef A0 result_type;
    NT2_FUNCTOR_CALL(1)
    {
      typedef typename meta::as_logical<A0>::type bA0;
      typedef typename meta::scalar_of<A0>::type sA0;
      A0 x = a0;
      bA0 flag2 = nt2::gt(x, nt2::Two<A0>());
      x = nt2::if_else(flag2, rec(x), x);
      bA0 flag = nt2::gt(x,nt2::One<A0>()+nt2::Half<A0>());
      bA0 flag1= nt2::lt(x,nt2::Half<A0>());
      flag2 = nt2::logical_or(flag2, flag);
      A0 w = nt2::if_else(flag,
                           nt2::minusone(nt2::rec(x)),
                           nt2::if_else(flag1, -x, nt2::minusone(x)));
      A0 y = -w*horner < NT2_HORNER_COEFF_T(sA0, 11,
                                            (0x3c80e79e, //  1.573544461280107e-02
                                             0xbc8a8ad6, // -1.691190458077472e-02
                                             0x3c1f4a7f, //  9.722350716629080e-03
                                             0xbc604c2f, // -1.369003883877440e-02
                                             0x3caa7af5, //  2.081058345747539e-02
                                             0xbce56409, // -2.800180182703898e-02
                                             0x3d23ba15, //  3.997238484525606e-02
                                             0xbd7ff525, // -6.248964595941006e-02
                                             0x3de38e97, //  1.111118092410093e-01
                                             0xbe800004, // -2.500001325084512e-01
                                             0x3f800000  //  9.999999970814395e-01
                                            )
                                           ) > (w);
      A0 z = nt2::log(x);
      y = nt2::if_else(flag1, Pi2o_6<A0>()-z * nt2::log(nt2::oneminus(x))-y,y);
      y = nt2::if_else(flag2, nt2::Mhalf<A0>()*nt2::sqr(z)-y,y);
      return nt2::if_else(nt2::is_eqz(a0),  Pi2o_6<A0>(), y);
    }
  };
} }

#endif
