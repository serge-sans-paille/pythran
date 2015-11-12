//==============================================================================
//         Copyright 2003 - 2014 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2014 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_EULER_FUNCTIONS_DETAILS_DAWSON_KERNEL_HPP_INCLUDED
#define NT2_EULER_FUNCTIONS_DETAILS_DAWSON_KERNEL_HPP_INCLUDED
#include <nt2/include/functions/simd/divides.hpp>
#include <nt2/include/functions/simd/multiplies.hpp>
#include <nt2/include/functions/simd/plus.hpp>
#include <nt2/include/functions/simd/rec.hpp>
#include <nt2/polynomials/functions/scalar/impl/horner.hpp>
#include <nt2/sdk/meta/scalar_of.hpp>

#include <boost/dispatch/attributes.hpp>

namespace nt2 { namespace details
{
  template < class A0, class sA0 = typename meta::scalar_of<A0>::type >
  struct dawson_kernel;

  template < class A0 >
  struct dawson_kernel < A0, float >
  {
    typedef typename meta::scalar_of<A0>::type sA0;
    // computes dawson(a0)/a0 for float or float vectors
    // xx is sqr(a0) and 0 <= abs(x) <= 3.25
    static BOOST_FORCEINLINE A0 dawson1(const A0& x)
    {
      return NT2_HORNER_RAT(sA0, 10, 11, x,
                            (0x2d47fd98,
                             0x30697185,
                             0x32a70489,
                             0x357fdc17,
                             0x364e9480,
                             0x39b8d18b,
                             0xba5edc97,
                             0x3d2d1abc,
                             0xbdbbe665,
                             0x3f800000
                            ),
                            (0x2dd36efb,
                             0x30cc991a,
                             0x335fe1b9,
                             0x35aacdae,
                             0x37c306e7,
                             0x39aaab31,
                             0x3b6497e8,
                             0x3ce4ec9b,
                             0x3e22afee,
                             0x3f132dde,
                             0x3f800000
                            )
                           );
    }
    // computes dawson(a0)/a0 for double or double vectors
    // xx is sqr(a0) and 3.25 <= abs(a0) <= 6.25
    static BOOST_FORCEINLINE A0 dawson2(const A0& ox2, const A0 & x)
    {
      /* interval 3.25 to 6.25 */
      A0 num = horner<NT2_HORNER_COEFF_T(sA0, 11,
                                         (0x3f024ae3,
                                          0xbe7aa0e7,
                                          0x3dc0d25d,
                                          0xbcb32b13,
                                          0x3b6fff71,
                                          0xb9dde22a,
                                          0x3816d831,
                                          0xb6100aef,
                                          0x33c36c5f,
                                          0xb1251d8a,
                                          0x2e1dfe15
                                         )
                                        )> (ox2);
      A0 denom = horner<NT2_HORNER_COEFF_T(sA0, 11,
                                           (0x3f800000,
                                            0xbf21c042,
                                            0x3e726344,
                                            0xbd59d3f0,
                                            0x3c0af173,
                                            0xba7882fc,
                                            0x38a3cafe,
                                            0xb698f761,
                                            0x344b0b83,
                                            0xb1a8d160,
                                            0x2e9dfe10
                                           )
                                          )> (ox2);
      return nt2::rec(x)+ox2*num/(denom*x);
    }
    // computes dawson(a0)/a0 for double or double vectors
    // xx is sqr(a0) and    6.25 < abs(a0) < 1.0e9
    static BOOST_FORCEINLINE A0 dawson3(const A0& ox2, const A0 & x)
    {
      /* 6.25 to infinity */
      A0 num = horner<NT2_HORNER_COEFF_T(sA0, 5,
                                         (0xbf173118,
                                          0x3f211590,
                                          0xbe3101f1,
                                          0x3c8708d6,
                                          0xb9ff3ce5
                                         )
                                        )> (ox2);
      A0 denom =  horner<NT2_HORNER_COEFF_T(sA0, 6,
                                            (0x3f800000,
                                             0xc02caf51,
                                             0x3fddc960,
                                             0xbec9942c,
                                             0x3d0d0443,
                                             0xba7f3ce5
                                            )
                                           )> (ox2);
      return nt2::rec(x)+ox2*num/(denom*x);
    }
};

  template < class A0 >
  struct dawson_kernel < A0, double >
  {
    typedef typename meta::scalar_of<A0>::type sA0;
    // computes dawson(a0)/a0 for double or double vectors
    // xx is sqr(a0) and 0 <= abs(a0) <= 3.25
    static BOOST_FORCEINLINE A0 dawson1(const A0& x)
    {
      return NT2_HORNER_RAT(sA0, 10, 11, x,
                            (0x3da8ffb30f7d51f1ll, //(1.13681498971755972054E-11)
                             0x3e0d2e309db8f5fbll, //(8.49262267667473811108E-10)
                             0x3e54e09113ca0ba0ll, //(1.94434204175553054283E-8)
                             0x3eaffb82d857b833ll, //(9.53151741254484363489E-7)
                             0x3ec9d29007c3bd6all, //(3.07828309874913200438E-6)
                             0x3f371a3163a27174ll, //(3.52513368520288738649E-4)
                             0xbf4bdb92e4e9a921ll, //(-8.50149846724410912031E-4
                             0x3fa5a357714ced03ll, //(4.22618223005546594270E-2)
                             0xbfb77ccca3261da7ll, //(-9.17480371773452345351E-2)
                             0x3ff0000000000000ll  //(9.99999999999999994612E-1)
                            ),
                            (0x3dba6ddf536ed65all, //(2.40372073066762605484E-11
                             0x3e1993234f10c1b4ll, //(1.48864681368493396752E-9)
                             0x3e6bfc372910659cll, //(5.21265281010541664570E-8)
                             0x3eb559b5c414f013ll, //(1.27258478273186970203E-6)
                             0x3ef860dcd4d604a3ll, //(2.32490249820789513991E-5)
                             0x3f3555661ec43b62ll, //(3.25524741826057911661E-4)
                             0x3f6c92fcf5507532ll, //(3.48805814657162590916E-3)
                             0x3f9c9d9358f736f7ll, //(2.79448531198828973716E-2)
                             0x3fc455fdbcb2a008ll, //(1.58874241960120565368E-1)
                             0x3fe265bbc0f09197ll, //(5.74918629489320327824E-1)
                             0x3ff0000000000000ll  //(1.00000000000000000539E0)
                            )
                           );
    }

    // computes dawson(a0)/a0 for double or double vectors
    // xx is sqr(a0) and 3.25 <= abs(a0) <= 6.25
    static BOOST_FORCEINLINE A0 dawson2(const A0& ox2, const A0 & x)
    {
      /* interval 3.25 to 6.25 */
      A0 num = horner<NT2_HORNER_COEFF_T(sA0, 11,
                                         (0x3fe0495c52fe411ell,//(5.08955156417900903354E-1),
                                          0xbfcf541cdebcb905ll,//(-2.44754418142697847934E-1)
                                          0x3fb81a4b94e413c5ll,//(9.41512335303534411857E-2),
                                          0xbf966562633da983ll,//(-2.18711255142039025206E-2)
                                          0x3f6dffee25eba9bdll,//(3.66207612329569181322E-3),
                                          0xbf3bbc454e5479acll,//(-4.23209114460388756528E-4)
                                          0x3f02db061d28d773ll,//(3.59641304793896631888E-5),
                                          0xbec2015dd001fa5bll,//(-2.14640351719968974225E-6)
                                          0x3e786d8be5016991ll,//(9.10010780076391431042E-8),
                                          0xbe24a3b14d9709f0ll,//(-2.40274520828250956942E-9)
                                          0x3dc3bfc2ac32b39ell //(3.59233385440928410398E-11)
                                         )
                                        )> (ox2);
      A0 denom = horner<NT2_HORNER_COEFF_T(sA0, 11,
                                           (0x3ff0000000000000ll, //(1.00000000000000000000E0),
                                            0xbfe438083f2d47c7ll, //(-6.31839869873368190192E-1)
                                            0x3fce4c6875173c3ell, //(2.36706788228248691528E-1),
                                            0xbfab3a7e0ed1122bll, //(-5.31806367003223277662E-2)
                                            0x3f815e2e53c1fb60ll, //(8.48041718586295374409E-3),
                                            0xbf4f105f8f05c7d8ll, //(-9.47996768486665330168E-4)
                                            0x3f14795fc069cc34ll, //(7.81025592944552338085E-5),
                                            0xbed31eec145c9b53ll, //(-4.55875153252442634831E-6)
                                            0x3e8961705729c1cdll, //(1.89100358111421846170E-7),
                                            0xbe351a2c0f7cf15cll, //(-4.91324691331920606875E-9)
                                            0x3dd3bfc202a6b560ll  //(7.18466403235734541950E-11)
                                           )
                                          )> (ox2);
      return nt2::rec(x)+ox2*num/(denom*x);
    }

    // computes dawson(a0)/a0 for double or double vectors
    // xx is sqr(a0) and    6.25 < abs(a0) < 1.0e9
    static BOOST_FORCEINLINE A0 dawson3(const A0& ox2, const A0 & x)
    {
      /* 6.25 to infinity */
      A0 num = horner<NT2_HORNER_COEFF_T(sA0, 5,
                                         (0xbfe2e622ffa7ef20ll, //(-5.90592860534773254987E-1)
                                          0x3fe422b1f29fbcb6ll, //(6.29235242724368800674E-1),
                                          0xbfc6203e2f0a174ell, //(-1.72858975380388136411E-1)
                                          0x3f90e11ab3d4d36bll, //(1.64837047825189632310E-2),
                                          0xbf3fe79cad3d09fbll  //(-4.86827613020462700845E-4)
                                         )
                                        )> (ox2);
      A0 denom =  horner<NT2_HORNER_COEFF_T(sA0, 6,
                                            (0x3ff0000000000000ll,//(1.00000000000000000000E0),
                                             0xc00595ea2e7576e2ll,//(-2.69820057197544900361E0),
                                             0x3ffbb92c0388a954ll,//(1.73270799045947845857E0),
                                             0xbfd932857b438c94ll,//(-3.93708582281939493482E-1)
                                             0x3fa1a0885fe44f2dll,//(3.44278924041233391079E-2),
                                             0xbf4fe79cad3d0a8dll //(-9.73655226040941223894E-4)
                                            )
                                           )> (ox2);
      return nt2::rec(x)+ox2*num/(denom*x);
    }
  };
} }

#endif
