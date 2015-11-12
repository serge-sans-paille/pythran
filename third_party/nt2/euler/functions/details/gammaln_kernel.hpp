//==============================================================================
//         Copyright 2003 - 2014 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2014 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_EULER_FUNCTIONS_DETAILS_GAMMALN_KERNEL_HPP_INCLUDED
#define NT2_EULER_FUNCTIONS_DETAILS_GAMMALN_KERNEL_HPP_INCLUDED
#include <nt2/polynomials/functions/scalar/impl/horner.hpp>
#include <nt2/sdk/meta/scalar_of.hpp>
#include <boost/dispatch/attributes.hpp>

namespace nt2 { namespace details
{
  template < class A0, class sA0 = typename meta::scalar_of<A0>::type >
  struct gammaln_kernel;

  template < class A0 >
  struct gammaln_kernel < A0, float >
  {
    typedef typename meta::scalar_of<A0>::type sA0;
    static BOOST_FORCEINLINE A0 gammalnB( const A0& x)
    {
      // log gamma(x+2), -.5 < x < .5
     return horner<NT2_HORNER_COEFF_T(sA0, 8,
                                       (0x3a1ebb94, //    6.055172732649237E-004,
                                        0xbaabeab1, //   -1.311620815545743E-003,
                                        0x3b3ba883, //    2.863437556468661E-003,
                                        0xbbf164fd, //   -7.366775108654962E-003,
                                        0x3ca89ed8, //    2.058355474821512E-002,
                                        0xbd89f07e, //   -6.735323259371034E-002,
                                        0x3ea51a64, //    3.224669577325661E-001,
                                        0x3ed87730  //    4.227843421859038E-001
                                       )
                                      )> (x);
    }
    static BOOST_FORCEINLINE A0 gammalnC(const A0& x)
    {
      // log gamma(x+1), -.25 < x < .25
     return horner<NT2_HORNER_COEFF_T(sA0, 8,
                                      (0x3e0c3c4f,  //    1.369488127325832E-001,
                                       0xbe22d329,  //   -1.590086327657347E-001,
                                       0x3e2d4dab,  //    1.692415923504637E-001,
                                       0xbe53c04f,  //   -2.067882815621965E-001,
                                       0x3e8a898b,  //    2.705806208275915E-001,
                                       0xbecd27a8,  //   -4.006931650563372E-001,
                                       0x3f528d34,  //    8.224670749082976E-001,
                                       0xbf13c468   //   -5.772156501719101E-001
                                       )
                                      )> (x);
    }
     static BOOST_FORCEINLINE A0 gammaln2(const A0& p)
    {
      return horner<NT2_HORNER_COEFF_T(sA0, 3,
                                       (0x3a31fd69, //   6.789774945028216E-004f,
                                        0xbb358701, //  -2.769887652139868E-003f,
                                        0x3daaaa94  //   8.333316229807355E-002f
                                       )
                                      )> (p);
    }
  };

  template < class A0 >
  struct gammaln_kernel < A0, double >
  {
    typedef typename meta::scalar_of<A0>::type sA0;
    static BOOST_FORCEINLINE A0 gammaln1(const A0& x)
    {
      return NT2_HORNER_RAT(sA0, 6, 7, x,
                            (0xc09589018ff36761ll, //  -1.37825152569120859100E3,
                             0xc0e2f234355bb93ell, //  -3.88016315134637840924E4,
                             0xc1143d73f89089e5ll, //  -3.31612992738871184744E5,
                             0xc131bc82f994db51ll, //  -1.16237097492762307383E6,
                             0xc13a45890219f20bll, //  -1.72173700820839662146E6,
                             0xc12a0c675418055ell  //  -8.53555664245765465627E5
                            ),
                            (0x3ff0000000000000ll, //   1.00000000000000000000E0,
                             0xc075fd0d1cf312b2ll, //  -3.51815701436523470549E2,
                             0xc0d0aa0d7b89d757ll, //  -1.70642106651881159223E4,
                             0xc10aeb84b9744c9bll, //  -2.20528590553854454839E5,
                             0xc131628671950043ll, //  -1.13933444367982507207E6,
                             0xc1435255892ff34cll, //  -2.53252307177582951285E6,
                             0xc13ece4b6a11e14all  //  -2.01889141433532773231E6
                            )
                           );

    }

    static BOOST_FORCEINLINE A0 gammalnA(const A0& p)
    {
      return horner<NT2_HORNER_COEFF_T(sA0, 5,
                                       (0x3f4a985027336661ll,//    8.11614167470508450300E-4,
                                        0xbf437fbdb580e943ll,//   -5.95061904284301438324E-4,
                                        0x3f4a019f20dc5ebbll,//    7.93650340457716943945E-4,
                                        0xbf66c16c16b0a5a1ll,//   -2.77777777730099687205E-3,
                                        0x3fb555555555554bll //    8.33333333333331927722E-2
                                       )
                                      )> (p);
    }
  };

} }

#endif
