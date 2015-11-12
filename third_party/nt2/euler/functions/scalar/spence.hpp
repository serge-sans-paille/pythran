//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_EULER_FUNCTIONS_SCALAR_SPENCE_HPP_INCLUDED
#define NT2_EULER_FUNCTIONS_SCALAR_SPENCE_HPP_INCLUDED
#include <nt2/euler/functions/spence.hpp>
#include <nt2/include/constants/half.hpp>
#include <nt2/include/constants/mhalf.hpp>
#include <nt2/include/constants/nan.hpp>
#include <nt2/include/constants/one.hpp>
#include <nt2/include/constants/pi2o_6.hpp>
#include <nt2/include/constants/two.hpp>
#include <nt2/include/constants/zero.hpp>
#include <nt2/include/functions/scalar/is_eqz.hpp>
#include <nt2/include/functions/scalar/log.hpp>
#include <nt2/include/functions/scalar/minusone.hpp>
#include <nt2/include/functions/scalar/oneminus.hpp>
#include <nt2/include/functions/scalar/rec.hpp>
#include <nt2/include/functions/scalar/sqr.hpp>
#include <nt2/polynomials/functions/scalar/impl/horner.hpp>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::spence_, tag::cpu_
                              , (A0)
                              , (scalar_< single_<A0> >)
    )
  {
    typedef A0 result_type;
    NT2_FUNCTOR_CALL(1)
    {
      A0 x = a0;
      if( x < nt2::Zero<A0>() ) return nt2::Nan<A0>();
      if( x == nt2::One<A0>() ) return nt2::Zero<A0>();
      if( nt2::is_eqz(x) )   return Pi2o_6<A0>() ;
      int flag = 0;
      if( x > nt2::Two<A0>() )
      {
        x = rec(x);
        flag |= 2;
      }
      A0 w;
      if( x > static_cast<A0>(1.5) )
      {
        w = nt2::minusone(nt2::rec(x));
        flag |= 2;
      }
      else if( x < nt2::Half<A0>() )
      {
        w = -x;
        flag |= 1;
      }
      else
        w = nt2::minusone(x);
      A0 y = -w*horner < NT2_HORNER_COEFF_T(A0, 11,
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
      if( flag & 1 )
        y = Pi2o_6<A0>() -nt2::log(x) * nt2::log(oneminus(x)) - y;
      if( flag & 2 )
      {
        A0 z = nt2::log(x);
        y = nt2::Mhalf<A0>() * nt2::sqr(z) - y;
      }
      return y;
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::spence_, tag::cpu_
                            , (A0)
                            , (scalar_< double_<A0> >)
                            )
  {
    typedef A0 result_type;
    NT2_FUNCTOR_CALL(1)
    {
      A0 x = a0;
      if( x < nt2::Zero<A0>() ) return nt2::Nan<A0>();
      if( x == nt2::One<A0>() ) return nt2::Zero<A0>();
      if( nt2::is_eqz(x) )   return Pi2o_6<A0>() ;
      int flag = 0;
      if( x > nt2::Two<A0>() )
      {
        x = rec(x);
        flag |= 2;
      }
      A0 w;
      if( x > static_cast<A0>(1.5) )
      {
        w = nt2::minusone(nt2::rec(x));
        flag |= 2;
      }
      else if( x < nt2::Half<A0>() )
      {
        w = -x;
        flag |= 1;
      }
      else
        w = nt2::minusone(x);
      A0 y = -w*horner < NT2_HORNER_COEFF_T(A0, 8,
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
        horner < NT2_HORNER_COEFF_T(A0, 8,
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
      if( flag & 1 )
        y = Pi2o_6<A0>() -nt2::log(x) * nt2::log(oneminus(x)) - y;
      if( flag & 2 )
      {
        A0 z = nt2::log(x);
        y = nt2::Mhalf<A0>() * nt2::sqr(z) - y;
      }
      return y;
    }
  };
} }

#endif
