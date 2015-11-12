//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_EXPONENTIAL_FUNCTIONS_DETAILS_POW_KERNEL_HPP_INCLUDED
#define NT2_EXPONENTIAL_FUNCTIONS_DETAILS_POW_KERNEL_HPP_INCLUDED

#include <nt2/include/constants/four.hpp>
#include <nt2/include/constants/mone.hpp>
#include <nt2/include/constants/nine.hpp>
#include <nt2/include/constants/one.hpp>
#include <nt2/include/constants/two.hpp>
#include <nt2/include/functions/simd/divides.hpp>
#include <nt2/include/functions/simd/if_else.hpp>
#include <nt2/include/functions/simd/inc.hpp>
#include <nt2/include/functions/simd/is_greater_equal.hpp>
#include <nt2/include/functions/simd/is_less_equal.hpp>
#include <nt2/include/functions/simd/load.hpp>
#include <nt2/include/functions/simd/minus.hpp>
#include <nt2/include/functions/simd/multiplies.hpp>
#include <nt2/include/functions/simd/plus.hpp>
#include <nt2/include/functions/simd/pow2.hpp>
#include <nt2/include/functions/simd/seladd.hpp>
#include <nt2/include/functions/simd/shr.hpp>
#include <nt2/include/functions/simd/unary_minus.hpp>
#include <nt2/polynomials/functions/scalar/impl/horner.hpp>
#include <nt2/sdk/meta/as_integer.hpp>
#include <nt2/sdk/meta/scalar_of.hpp>

#include <boost/array.hpp>
#include <boost/dispatch/attributes.hpp>

namespace nt2 { namespace details
{
  template < class A0, class sA0 = typename meta::scalar_of<A0>::type >
  struct pow_kernel;

  template < class A0 >
  struct pow_kernel < A0, float >
  {
    typedef typename meta::as_integer<A0>::type  iA0;
    typedef typename meta::scalar_of<A0>::type   sA0;
    static BOOST_FORCEINLINE A0 pow1(const A0& x, const A0& z)
    {
      return  z*x*horner<NT2_HORNER_COEFF_T(sA0, 4, (0xbe2a61b2, //  -0.1663883081054895f
                                                     0x3e4d2fa3, //  +0.2003770364206271f
                                                     0xbe800015, //  -0.2500006373383951f
                                                     0x3eaaaaa3) //  +0.3333331095506474f
                                           )>(x);
    }

    static BOOST_FORCEINLINE A0 pow2(const A0& x)
    {
      return horner<NT2_HORNER_COEFF_T(sA0, 4, (0x3c1a49bc, // 9.416993633606397E-003f
                                                0x3d634d38, // 5.549356188719141E-002f
                                                0x3e75fde1, // 2.402262883964191E-001f
                                                0x3f317218) // 6.931471791490764E-001f
                                      )>(x);
    }

    static BOOST_FORCEINLINE A0 twomio16(const iA0& i)
    {
      /* 2^(-i/16)
       * The decimal values are rounded to 24-bit precision
       */
      static const boost::array<sA0, 17> A = {{
          sA0(1.00000000000000000000E0),
          sA0(9.57603275775909423828125E-1),
          sA0(9.17004048824310302734375E-1),
          sA0(8.78126084804534912109375E-1),
          sA0(8.40896427631378173828125E-1),
          sA0(8.05245161056518554687500E-1),
          sA0(7.71105408668518066406250E-1),
          sA0(7.38413095474243164062500E-1),
          sA0(7.07106769084930419921875E-1),
          sA0(6.77127778530120849609375E-1),
          sA0(6.48419797420501708984375E-1),
          sA0(6.20928883552551269531250E-1),
          sA0(5.94603538513183593750000E-1),
          sA0(5.69394290447235107421875E-1),
          sA0(5.45253872871398925781250E-1),
          sA0(5.22136867046356201171875E-1),
          sA0(5.00000000000000000000E-1)
        }};
      return load<A0>(A.begin(), i); //A[i];
    }

    static BOOST_FORCEINLINE A0 continuation(const iA0& i)
    {
      /* continuation, for even i only
       * 2^(i/16)  =  A[i] + B[i/2]
       */
      static const boost::array<sA0, 9> B = {{
          sA0( 0.00000000000000000000E0),
          sA0(-5.61963907099083340520586E-9),
          sA0(-1.23776636307969995237668E-8),
          sA0( 4.03545234539989593104537E-9),
          sA0( 1.21016171044789693621048E-8),
          sA0(-2.00949968760174979411038E-8),
          sA0( 1.89881769396087499852802E-8),
          sA0(-6.53877009617774467211965E-9),
          sA0( 0.00000000000000000000E0)
        }};
      return load<A0>(B.begin(), i);
    }

    static BOOST_FORCEINLINE iA0 select(A0& x)
    {
      // find significand in antilog table A[]
      iA0 i = One<iA0>();
      i = if_else(le(x, twomio16(Nine<iA0>()))  , Nine<iA0>(), i);
      i = seladd (le(x, twomio16(i+Four<iA0>())), i, Four<iA0>());
      i = seladd (le(x, twomio16(i+Two<iA0>())) , i, Two<iA0>() );
      i = if_else(ge(x, twomio16(One<iA0>()))   , Mone<iA0>(), i);
      i = inc(i);
      A0 tmp = twomio16(i);
      x -= tmp;
      x -= continuation(shr(i, 1));
      x /= tmp;
      return i;
    }

  };

  template < class A0 >
  struct pow_kernel < A0, double >
  {
    typedef typename meta::as_integer<A0>::type  iA0;
    typedef typename meta::scalar_of<A0>::type   sA0;
    static BOOST_FORCEINLINE A0 pow1(const A0& x, const A0& z)
    {
      return  x*(z*horner<NT2_HORNER_COEFF_T(sA0, 4,
                                             (
                                               0x3fdfdb997f5b5cf0ll,//  4.97778295871696322025E-1,
                                               0x400dddefea9edf15ll,//  3.73336776063286838734E0,
                                               0x401eccbd7f78eb6fll,//  7.69994162726912503298E0,
                                               0x4012aa83b65c9b74ll //  4.66651806774358464979E0
                                             ) )>(x)/
        horner<NT2_HORNER_COEFF_T(sA0, 5,
                                  (
                                    0x3ff0000000000000ll,//  1.00000000000000000000E0,
                                    0x4022aab49b20914ell,//  9.33340916416696166113E0,
                                    0x403bffff41c1c9f5ll,//  2.79999886606328401649E1,
                                    0x4040ccbc1b176402ll,//  3.35994905342304405431E1,
                                    0x402bffc5918ae92ell //  1.39995542032307539578E1
                                  )
                                 )>(x));
    }

    static BOOST_FORCEINLINE A0 pow2(const A0& x)
    {
      return horner<NT2_HORNER_COEFF_T(sA0, 7, (
                                         0x3eef6307d7f2937fll,//  1.49664108433729301083E-5,
                                         0x3f242fbe60fc9259ll,//  1.54010762792771901396E-4,
                                         0x3f55d87ec84aef1dll,//  1.33335476964097721140E-3,
                                         0x3f83b2ab6ef133b7ll,//  9.61812908476554225149E-3,
                                         0x3fac6b08d7041a92ll,//  5.55041086645832347466E-2,
                                         0x3fcebfbdff82c56dll,//  2.40226506959099779976E-1,
                                         0x3fe62e42fefa39efll //  6.93147180559945308821E-1
                                       )
                                      )>(x);
    }
    static BOOST_FORCEINLINE A0 twomio16(const iA0& i)
    {
      /* 2^(-i/16), IEEE precision */
      static const boost::array < sA0, 17> A = {{
          sA0(1.00000000000000000000E0),
          sA0(9.57603280698573700036E-1),
          sA0(9.17004043204671215328E-1),
          sA0(8.78126080186649726755E-1),
          sA0(8.40896415253714502036E-1),
          sA0(8.05245165974627141736E-1),
          sA0(7.71105412703970372057E-1),
          sA0(7.38413072969749673113E-1),
          sA0(7.07106781186547572737E-1),
          sA0(6.77127773468446325644E-1),
          sA0(6.48419777325504820276E-1),
          sA0(6.20928906036742001007E-1),
          sA0(5.94603557501360513449E-1),
          sA0(5.69394317378345782288E-1),
          sA0(5.45253866332628844837E-1),
          sA0(5.22136891213706877402E-1),
          sA0(5.00000000000000000000E-1)
        }};
      return  load<A0>(A.begin(), i); //A[i];
    }

    static BOOST_FORCEINLINE A0 continuation(const iA0& i)
    {
      /* continuation, for even i only
       * 2^(i/16)  =  A[i] + B[i/2]
       */
      static const boost::array < sA0, 9> B = {{
          sA0( 0.00000000000000000000E0),
          sA0( 1.64155361212281360176E-17),
          sA0( 4.09950501029074826006E-17),
          sA0( 3.97491740484881042808E-17),
          sA0(-4.83364665672645672553E-17),
          sA0( 1.26912513974441574796E-17),
          sA0( 1.99100761573282305549E-17),
          sA0(-1.52339103990623557348E-17),
          sA0( 0.00000000000000000000E0)
        }};
      return  load<A0>(B.begin(), i);
    }

    static BOOST_FORCEINLINE iA0 select(A0& x)
    {
      // find significand in antilog table A[]
      iA0 i = One<iA0>();
      i = if_else(le(x, twomio16(Nine<iA0>()))  , Nine<iA0>(), i);
      i = seladd (le(x, twomio16(i+Four<iA0>())), i, Four<iA0>());
      i = seladd (le(x, twomio16(i+Two<iA0>())) , i, Two<iA0>() );
      i = if_else(ge(x, twomio16(One<iA0>()))   , Mone<iA0>(), i);
      i = inc(i);
      A0 tmp = twomio16(i);
      x -= tmp;
      x -= continuation(shr(i, 1));
      x /= tmp;
      return i;
    }

  };
} }

#endif
