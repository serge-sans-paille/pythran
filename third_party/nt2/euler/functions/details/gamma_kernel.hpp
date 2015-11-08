//==============================================================================
//         Copyright 2003 - 2014 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2014 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_EULER_FUNCTIONS_DETAILS_GAMMA_KERNEL_HPP_INCLUDED
#define NT2_EULER_FUNCTIONS_DETAILS_GAMMA_KERNEL_HPP_INCLUDED
#include <nt2/polynomials/functions/scalar/impl/horner.hpp>
#include <nt2/sdk/meta/scalar_of.hpp>

#include <boost/dispatch/attributes.hpp>

namespace nt2 { namespace details
{
  template < class A0, class sA0 = typename meta::scalar_of<A0>::type >
  struct gamma_kernel;

  template < class A0 >
  struct gamma_kernel < A0, float >
  {
    typedef typename meta::scalar_of<A0>::type sA0;
    static BOOST_FORCEINLINE A0 gamma1(const A0& x)
    {
      return horner<NT2_HORNER_COEFF_T(sA0, 8,
                                       (0x3ad28b22, //  1.606319369134976e-03
                                        0x3ba90c99, //  5.158972571345137e-03
                                        0x3b91db14, //  4.451165155708328e-03
                                        0x3d93ae7c, //  7.211014349068177e-02
                                        0x3da82a34, //  8.211174403261340e-02
                                        0x3ed2d411, //  4.117741948434743e-01
                                        0x3ed87799, //  4.227874605370421e-01
                                        0x3f800000  //  9.999999757445841e-01
                                       )
                                      )> (x);
    }

  };

  template < class A0 >
  struct gamma_kernel < A0, double >
  {
    typedef typename meta::scalar_of<A0>::type sA0;
    static BOOST_FORCEINLINE A0 gamma1(const A0& x)
    {
      return NT2_HORNER_RAT(sA0, 7, 8, x,
                            (0x3f24fcb839982153ll, // 1.60119522476751861407E-4
                             0x3f5384e3e686bfabll, // 1.19135147006586384913E-3
                             0x3f8557cde9db14b0ll, // 1.04213797561761569935E-2
                             0x3fa863d918c423d3ll, // 4.76367800457137231464E-2
                             0x3fca8da9dcae7d31ll, // 2.07448227648435975150E-1
                             0x3fdfa1373993e312ll, // 4.94214826801497100753E-1
                             0x3ff0000000000000ll  // 9.99999999999999996796E-1
                            ),
                            (0xbef8487a8400d3afll, // -2.31581873324120129819E-5
                             0x3f41ae8a29152573ll, //  5.39605580493303397842E-4
                             0xbf7240e4e750b44all, // -4.45641913851797240494E-3
                             0x3f8831ed5b1bb117ll, //  1.18139785222060435552E-2
                             0x3fa25779e33fde67ll, //  3.58236398605498653373E-2
                             0xbfce071a9d4287c2ll, // -2.34591795718243348568E-1
                             0x3fb24944c9cd3c51ll, //  7.14304917030273074085E-2
                             0x3ff0000000000000ll  //  1.00000000000000000320E00
                            )
                           );

    }
  };
} }

#endif
