//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_BESSEL_FUNCTIONS_SCALAR_Y1_HPP_INCLUDED
#define NT2_BESSEL_FUNCTIONS_SCALAR_Y1_HPP_INCLUDED

#include <nt2/bessel/functions/y1.hpp>
#include <nt2/include/functions/scalar/is_ltz.hpp>
#include <nt2/include/functions/scalar/is_nan.hpp>
#include <nt2/include/functions/scalar/is_eqz.hpp>
#include <nt2/include/functions/scalar/is_inf.hpp>
#include <nt2/include/functions/scalar/sqr.hpp>
#include <nt2/include/functions/scalar/rec.hpp>
#include <nt2/include/functions/scalar/plevl.hpp>
#include <nt2/include/functions/scalar/polevl.hpp>
#include <nt2/include/functions/scalar/abs.hpp>
#include <nt2/include/functions/scalar/sqrt.hpp>
#include <nt2/include/functions/scalar/sincos.hpp>
#include <nt2/include/functions/scalar/cos.hpp>
#include <nt2/include/functions/scalar/is_less.hpp>
#include <nt2/include/functions/scalar/multiplies.hpp>
#include <nt2/include/functions/scalar/divides.hpp>
#include <nt2/include/functions/scalar/plus.hpp>
#include <nt2/include/functions/scalar/minus.hpp>
#include <nt2/include/constants/digits.hpp>
#include <nt2/include/constants/infinites.hpp>
#include <nt2/include/constants/real.hpp>
#include <nt2/trigonometric/constants.hpp>
#include <boost/simd/sdk/math.hpp>
#include <boost/array.hpp>
#include <boost/simd/sdk/config.hpp>

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is arithmetic_
/////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::y1_, tag::cpu_
                            , (A0)
                            , (scalar_< arithmetic_<A0> >)
                            )
  {

    typedef typename boost::dispatch::meta::as_floating<A0>::type result_type;

    NT2_FUNCTOR_CALL(1)
    {
      return nt2::y1(result_type(a0));
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::y1_, tag::cpu_
                              , (A0)
                              , (scalar_< double_<A0> >)
    )
  {

    typedef A0 result_type;

    NT2_FUNCTOR_CALL(1)
    {
      static boost::array<A0, 7> PP = {{
          7.62125616208173112003E-4,
          7.31397056940917570436E-2,
          1.12719608129684925192E0,
          5.11207951146807644818E0,
          8.42404590141772420927E0,
          5.21451598682361504063E0,
          1.00000000000000000254E0,
        }};
      static boost::array<A0, 7> PQ = {{
          5.71323128072548699714E-4,
          6.88455908754495404082E-2,
          1.10514232634061696926E0,
          5.07386386128601488557E0,
          8.39985554327604159757E0,
          5.20982848682361821619E0,
          9.99999999999999997461E-1,
        }};
      static boost::array<A0,6> YP = {{
          1.26320474790178026440E9,
          -6.47355876379160291031E11,
          1.14509511541823727583E14,
          -8.12770255501325109621E15,
          2.02439475713594898196E17,
          -7.78877196265950026825E17,
        }};
      static boost::array<A0,8> YQ = {{
          /* 1.00000000000000000000E0,*/
          5.94301592346128195359E2,
          2.35564092943068577943E5,
          7.34811944459721705660E7,
          1.87601316108706159478E10,
          3.88231277496238566008E12,
          6.20557727146953693363E14,
          6.87141087355300489866E16,
          3.97270608116560655612E18,
        }};
      static boost::array<A0,8> QP = {{
          5.10862594750176621635E-2,
          4.98213872951233449420E0,
          7.58238284132545283818E1,
          3.66779609360150777800E2,
          7.10856304998926107277E2,
          5.97489612400613639965E2,
          2.11688757100572135698E2,
          2.52070205858023719784E1,
        }};
      static boost::array<A0,7> QQ = {{
          /* 1.00000000000000000000E0,*/
          7.42373277035675149943E1,
          1.05644886038262816351E3,
          4.98641058337653607651E3,
          9.56231892404756170795E3,
          7.99704160447350683650E3,
          2.82619278517639096600E3,
          3.36093607810698293419E2,
        }};
      typedef result_type rtype;
      if (is_ltz(a0)) return Nan<rtype>();
#ifndef BOOST_SIMD_NO_INVALIDS
      if (is_nan(a0)) return Nan<result_type>();
      if (is_inf(a0)) return Zero<rtype>();
#endif
      if (is_eqz(a0)) return Minf<rtype>();
      rtype x = a0;
      if( x <= Five<A0>() )
      {
        //          const A0 TWOOPI =  6.36619772367581343075535E-1; //       2/pi
        A0 z = sqr(x);
        A0 w = x * (polevl( z, YP) / p1evl( z, YQ));
        w += Twoopi<A0>() * ( j1(x) * log(x)  -  rec(x) );
        return w;
      }
      //      const A0 SQ2OPI =  7.9788456080286535587989E-1; // sqrt( 2/pi )
      //      const A0 THPIO4 =  2.35619449019234492885; //           3*pi/4
      A0 w = Five<A0>()/x;
      A0 z = w * w;
      A0 p = polevl( z, PP)/polevl( z, PQ);
      A0 q = polevl( z, QP)/p1evl( z, QQ);
      A0 xn = x - Threepio_4<A0>();
      A0 c, s;
      boost::fusion::tie(s, c) = sincos(xn);
      p = p * s + w * q * c;
      return( p * Sqrt_2opi<A0>() / sqrt(x) );
      //return ::y1(a0);
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::y1_, tag::cpu_
                              , (A0)
                              , (scalar_< single_<A0> >)
    )
  {

    typedef A0 result_type;

    NT2_FUNCTOR_CALL(1)
    {
      if (is_ltz(a0)) return Nan<result_type>();
#ifndef BOOST_SIMD_NO_INVALIDS
      if (is_nan(a0)) return Nan<result_type>();
      if (is_inf(a0)) return Zero<result_type>();
#endif
      if (is_eqz(a0)) return Minf<result_type>();
#ifdef BOOST_SIMD_HAS__Y1F
      return ::_y1f(a0);
#elif defined(BOOST_SIMD_HAS_Y1F)
      return ::y1f(a0);
#elif 0 // TODO: fix single-precision implementation
      typedef typename meta::scalar_of<A0>::type stype;
      if (is_ltz(a0)) return Nan<float>();
      if (is_eqz(a0)) return Minf<float>();
      A0 x = nt2::abs(a0);
      if (lt(x,Two<A0>()))
      {
        A0 z = sqr(x);
        return (z-single_constant<float,0x416ae95a> ())*x*
          horner< NT2_HORNER_COEFF_T(stype, 5,
                                     (0xb1a7a246,
                                      0x35214df5,
                                      0xb83e7a4f,
                                      0x3afdefd1,
                                      0xbd0b7da6
                                       ) ) > (z);
    }
      A0 q = rec(x);
      A0 w = sqrt(q);
      A0 p3 = w *
        horner< NT2_HORNER_COEFF_T(stype, 8,
                                   (0x3d8d98f9,
                                    0xbe69f6b3,
                                    0x3ea0ad85,
                                    0xbe574699,
                                    0x3bb21b25,
                                    0x3e18ec50,
                                    0x36a6f7c5,
                                    0x3f4c4229
                                     ) ) > (q);
  w = sqr(q);
  A0 xn =  q*
    horner< NT2_HORNER_COEFF_T(stype, 8,
                               (0xc233e16d,
                                0x424af04a,
                                0xc1c6dca7,
                                0x40e72299,
                                0xbfc5bd69,
                                0x3eb364d9,
                                0xbe27bad7,
                                0x3ebfffdd
                                 ) ) > (w)-single_constant<float,0x4016cbe4 > ();
  return p3*nt2::cos(xn+x);
#else
  return float(y1(double(a0)));
#endif
}
  };
} }


#endif
