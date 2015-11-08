//==============================================================================
//         Copyright 2003 - 2014 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2014 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_EULER_FUNCTIONS_DETAILS_ERFINV_KERNEL_HPP_INCLUDED
#define NT2_EULER_FUNCTIONS_DETAILS_ERFINV_KERNEL_HPP_INCLUDED
#include <nt2/include/functions/simd/multiplies.hpp>
#include <nt2/include/functions/simd/plus.hpp>
#include <nt2/include/functions/simd/splat.hpp>
#include <nt2/include/functions/simd/unary_minus.hpp>
#include <nt2/polynomials/functions/scalar/impl/horner.hpp>
#include <nt2/sdk/meta/scalar_of.hpp>

#include <boost/dispatch/attributes.hpp>

namespace nt2 { namespace details
{
  template < class A0, class sA0 = typename meta::scalar_of<A0>::type >
  struct erfinv_kernel;

  template < class A0 >
  struct erfinv_kernel < A0, float >
  {
    typedef typename meta::scalar_of<A0>::type sA0;
    static BOOST_FORCEINLINE A0 erfinv1(const A0& w)
    {
      return horner<NT2_HORNER_COEFF_T(sA0, 9,
                                       (0x32f16588, //  2.81022636e-08f
                                        0x34b84b36, //  3.43273939e-07f
                                        0xb66c7357, // -3.5233877e-06f
                                        0xb6935ac1, // -4.39150654e-06f
                                        0x396532db, //  0.00021858087f
                                        0xbaa45408, // -0.00125372503f
                                        0xbb88e4ef, // -0.00417768164f
                                        0x3e7c8f63, //  0.246640727f
                                        0x3fc02e2f) //  1.50140941f
                                      )> (w);
    }

    static BOOST_FORCEINLINE A0 erfinv2(const A0& w)
    {
      return horner<NT2_HORNER_COEFF_T(sA0, 9,
                                       (0xb951f09b, //  -0.000200214257f
                                        0x38d3b56b, //   0.000100950558f
                                        0x3ab0dc72, //   0.00134934322f
                                        0xbb70bde7, //  -0.00367342844f
                                        0x3bbc127b, //   0.00573950773f
                                        0xbbf9c5d7, //  -0.0076224613f
                                        0x3c1aa57e, //   0.00943887047f
                                        0x3f8036db, //   1.00167406f
                                        0x40354f7e) //   2.83297682f
                                      )> (w);
    }
    static BOOST_FORCEINLINE A0 erfcinv2(const A0& w)
    {
      return NT2_HORNER_RAT(sA0, 5, 5, w,
                            (0x3b3a8aee,
                             0x3ba62c57,
                             0xbc8bcf63,
                             0x3c98e17c,
                             0xbbaf8bfe
                            ),
                            (0x321631b2,
                             0x3b3a73c1,
                             0x3ba9025f,
                             0xbc5d80aa,
                             0x3c2f4022)
                           );
    }
  };

  template < class A0 >
  struct erfinv_kernel < A0, double >
  {
    typedef typename meta::scalar_of<A0>::type sA0;

    static BOOST_FORCEINLINE A0 erfinv1(const A0& w)
    {
        return horner<NT2_HORNER_COEFF_T(sA0, 23,
                                         (0xbbb135d2e746e627ll,  //  -3.6444120640178196996e-21
                                          0xbc08ddf93324d327ll,  //  -1.685059138182016589e-19
                                          0x3c37b83eef0b7c9fll,  //   1.2858480715256400167e-18
                                          0x3c69ba72cd589b91ll,  //   1.115787767802518096e-17
                                          0xbca33689090a6b96ll,  //  -1.333171662854620906e-16
                                          0x3c782e11898132e0ll,  //   2.0972767875968561637e-17
                                          0x3cfde4acfd9e26ball,  //   6.6376381343583238325e-15
                                          0xbd26d33eed66c487ll,  //  -4.0545662729752068639e-14
                                          0xbd36f2167040d8e2ll,  //  -8.1519341976054721522e-14
                                          0x3d872a22c2d77e20ll,  //   2.6335093153082322977e-12
                                          0xbdac8859c4e5c0afll,  //  -1.2975133253453532498e-11
                                          0xbdcdc583d118a561ll,  //  -5.4154120542946279317e-11
                                          0x3e120f47ccf46b3cll,  //   1.051212273321532285e-09
                                          0xbe31a9e38dc84d60ll,  //  -4.1126339803469836976e-09
                                          0xbe5f36cd6d3d46a9ll,  //  -2.9070369957882005086e-08
                                          0x3e9c6b4f5d03b787ll,  //   4.2347877827932403518e-07
                                          0xbeb6e8a5434ae8a2ll,  //  -1.3654692000834678645e-06
                                          0xbeed1d1f7b8736f6ll,  //  -1.3882523362786468719e-05
                                          0x3f2879c2a212f024ll,  //   0.0001867342080340571352
                                          0xbf4845769484fca8ll,  //  -0.00074070253416626697512
                                          0xbf78b6c33114f909ll,  //  -0.0060336708714301490533
                                          0x3fcebd80d9b13e28ll,  //   0.24015818242558961693
                                          0x3ffa755e7c99ae86ll   //   1.6536545626831027356
                                         )
                                        )> (w);
    }

    static BOOST_FORCEINLINE A0 erfinv2(const A0& w)
    {
      return horner<NT2_HORNER_COEFF_T(sA0, 19,
                                      (0x3e23040f87dbd932ll, //   2.2137376921775787049e-09
                                       0x3e785cbe52878635ll, //   9.0756561938885390979e-08
                                       0xbe92777453dd3955ll, //  -2.7517406297064545428e-07
                                       0x3e5395abcd554c6cll, //   1.8239629214389227755e-08
                                       0x3eb936388a3790adll, //   1.5027403968909827627e-06
                                       0xbed0d5db812b5083ll, //   -4.013867526981545969e-06
                                       0x3ec8860cd5d652f6ll, //   2.9234449089955446044e-06
                                       0x3eea29a0cacdfb23ll, //   1.2475304481671778723e-05
                                       0xbf08cef1f80281f2ll, //  -4.7318229009055733981e-05
                                       0x3f11e684d0b9188all, //   6.8284851459573175448e-05
                                       0x3ef932cd54c8a222ll, //   2.4031110387097893999e-05
                                       0xbf37448a89ef8aa3ll, //   -0.0003550375203628474796
                                       0x3f4f3cc55ad40c25ll, //   0.00095328937973738049703
                                       0xbf5ba924132f38b1ll, //   -0.0016882755560235047313
                                       0x3f6468eeca533cf8ll, //    0.0024914420961078508066
                                       0xbf6ebadabb891bbdll, //   -0.0037512085075692412107
                                       0x3f75ffcfe5b76afcll, //     0.005370914553590063617
                                       0x3ff0158a6d641d39ll, //       1.0052589676941592334
                                       0x4008abcc380d5a48ll  //       3.0838856104922207635
                                      )
                                     )> (w);
    }

    static BOOST_FORCEINLINE A0 erfinv3(const A0& w)
    {
      return horner<NT2_HORNER_COEFF_T(sA0, 17,
                                       (0xbdbdcec3a7785389ll, //  -2.7109920616438573243e-11
                                        0xbdf18feec0e38727ll, //  -2.5556418169965252055e-10
                                        0x3e19e6bf2dda45e3ll, //   1.5076572693500548083e-09
                                        0xbe30468fb24e2f5fll, //  -3.7894654401267369937e-09
                                        0x3e405ac6a8fba182ll, //   7.6157012080783393804e-09
                                        0xbe50102e495fb9c0ll, //  -1.4960026627149240478e-08
                                        0x3e5f4c20e1334af8ll, //   2.9147953450901080826e-08
                                        0xbe722d220fdf9c3ell, //  -6.7711997758452339498e-08
                                        0x3e8ebc8bb824cb54ll, //   2.2900482228026654717e-07
                                        0xbeb0a8d40ea372ccll, //  -9.9298272942317002539e-07
                                        0x3ed2fbd29d093d2bll, //   4.5260625972231537039e-06
                                        0xbef4a3497e1e0facll, //  -1.9681778105531670567e-05
                                        0x3f13ebf4eb00938fll, //   7.5995277030017761139e-05
                                        0xbf2c2f36a8fc5d53ll, //  -0.00021503011930044477347
                                        0xbf222ea5df04047cll, //  -0.00013871931833623122026
                                        0x3ff02a30d1fba0dcll, //       1.0103004648645343977
                                        0x4013664ddd1ad7fbll  //       4.8499064014085844221
                                       )
                                      )> (w);
    }
  };
} }

#endif
