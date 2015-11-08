//==============================================================================
//         Copyright 2003 - 2014 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2014 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_EULER_FUNCTIONS_DETAILS_ERF_KERNEL_HPP_INCLUDED
#define NT2_EULER_FUNCTIONS_DETAILS_ERF_KERNEL_HPP_INCLUDED
#include <nt2/include/functions/simd/multiplies.hpp>
#include <nt2/include/functions/simd/oneminus.hpp>
#include <nt2/polynomials/functions/scalar/impl/horner.hpp>
#include <nt2/sdk/meta/scalar_of.hpp>

////////////////////////////////////////////////////////////////////////////////
// These kernels allows some code factorization between erf and erfc
// erfc is 1-erf
// each one is better computed as 1 - the other at different spots
// where digits cancellation may occur
// Also these kernel codes are simd agnostic (generic)
////////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace details
{
  template < class A0, class sA0 = typename meta::scalar_of<A0>::type >
  struct erf_kernel;

  template < class A0 >
  struct erf_kernel < A0, float >
  {
    typedef typename meta::scalar_of<A0>::type sA0;
    // computes erf(a0)/a0 for float or float vectors
    // xx is sqr(a0) and 0 <= abs(x) <= 2/3
    static BOOST_FORCEINLINE A0 erf1(const A0& xx)
    {
      return horner<NT2_HORNER_COEFF_T(sA0, 6,
                                       (0xba1fc83b, //  -6.095205117313012e-04
                                        0x3ba4468d, //   5.013293006147870e-03
                                        0xbcdb61f4, //  -2.678010670585737e-02
                                        0x3de70f22, //   1.128218315189123e-01
                                        0xbec0937e, //  -3.761252839094832e-01
                                        0x3f906eba) //   1.128379154774254e+00
                                      )> (xx);
    }

    // computes erfc(x)*exp(sqr(x)) for float or float vectors
    // x >=  2/3
    static BOOST_FORCEINLINE A0 erfc2(const A0& z)
    {
      // approximation of erfc(z1./(1-z1))).*exp((z1./(1-z1)).^2) (z1 =  z+0.4) on [0 0.5]
      // with a polynomial of degree 11 gives 16 ulp on [2/3 inf] for erfc
      // (exhaustive test against float(erfc(double(x))))
      // z is A0 z = x/oneplus(x)-A0(0.4);
      return horner<NT2_HORNER_COEFF_T(sA0, 11,
                                       ( 0xc0283611, //  -2.628299919293280e+00
                                         0x40d67e3b, //   6.702908785399893e+00
                                         0xc0cd1a85, //  -6.409487379234005e+00
                                         0x4050b063, //   3.260765682222576e+00
                                         0xbfaea865, //  -1.364514006347145e+00
                                         0x3e2006f0, //   1.562764709849380e-01
                                         0x3e1175c7, //   1.420508523645926e-01
                                         0x3ec4ca6e, //   3.843569094305250e-01
                                         0x3e243828, //   1.603704761054187e-01
                                         0xbf918a62, //  -1.137035586823118e+00
                                         0x3f0a0e8b  //   5.392844046572836e-01
                                       )
                                      )> (z);

    }
    // computes erfc(x)*exp(sqr(x)) for float or float vectors
    // x >=  2/3
    static BOOST_FORCEINLINE A0 erfc3(const A0& z)
    {
      // approximation of erfc(z./(1-z))./(1-z) on [0 0.4]
      // with a polynomial of degree 8 gives 2 ulp on [0 2/3] for erfc
      // (exhaustive test against float(erfc(double(x))))
      // z is A0 z = x/oneplus(x);
      return  oneminus(z)* horner<NT2_HORNER_COEFF_T(sA0, 9,
                                                     (
                                                       0x41aa8e55, //   2.1319498e+01
                                                       0x401b5680, //   2.4271545e+00
                                                       0xc010d956, //  -2.2632651e+00
                                                       0x3f2cff3b, //   6.7576951e-01
                                                       0xc016c985, //  -2.3560498e+00
                                                       0xbffc9284, //  -1.9732213e+00
                                                       0xbfa11698, //  -1.2585020e+00
                                                       0xbe036d7e, //  -1.2834737e-01
                                                       0x3f7ffffe  //   9.9999988e-01
                                                     )
                                                    )> (z);
    }

  };

  template < class A0 >
  struct erf_kernel < A0, double >
  {
    typedef typename meta::scalar_of<A0>::type sA0;
    // computes erf(a0)/a0 for double or double vectors
    // xx is sqr(a0) and 0 <= abs(a0) <= 0.65
    static BOOST_FORCEINLINE A0 erf1(const A0& xx)
    {
      return NT2_HORNER_RAT(sA0, 5, 5, xx,
                               (0x3f110512d5b20332ull, // 6.49254556481904E-05
                                0x3f53b7664358865aull, // 1.20339380863079E-03
                                0x3fa4a59a4f02579cull, // 4.03259488531795E-02
                                0x3fc16500f106c0a5ull, // 0.135894887627278
                                0x3ff20dd750429b61ull  // 1.12837916709551
                               ),
                               (0x3f37ea4332348252ull, // 3.64915280629351E-04
                                0x3f8166f75999dbd1ull, // 8.49717371168693E-03
                                0x3fb64536ca92ea2full, // 8.69936222615386E-02
                                0x3fdd0a84eb1ca867ull, // 0.453767041780003
                                0x3ff0000000000000ull  // 1
                               )
                           );
    }

    // computes erfc(x)*exp(x*x) for double or double vectors
    // 0.65 <= abs(x) <= 2.2
    static BOOST_FORCEINLINE A0 erfc2(const A0& x)
    {
     return NT2_HORNER_RAT(sA0, 7, 7, x,
                              (0x0ull,                // 0
                               0x3f7cf4cfe0aacbb4ull, // 7.06940843763253E-03
                               0x3fb2488a6b5cb5e5ull, // 7.14193832506776E-02
                               0x3fd53dd7a67c7e9full, // 0.331899559578213
                               0x3fec1986509e687bull, // 0.878115804155882
                               0x3ff54dfe9b258a60ull, // 1.33154163936765
                               0x3feffffffbbb552bull  // 0.999999992049799
                              ),
                              (0x3f89a996639b0d00ull, // 1.25304936549413E-02
                               0x3fc033c113a7deeeull, // 0.126579413030178
                               0x3fe307622fcff772ull, // 0.594651311286482
                               0x3ff9e677c2777c3cull, // 1.61876655543871
                               0x40053b1052dca8bdull, // 2.65383972869776
                               0x4003adeae79b9708ull, // 2.45992070144246
                               0x3ff0000000000000ull  // 1
                              )
                             );
    }
    // computes erfc(x)*exp(x*x) for double or double vectors
    // 2.2 <= abs(x) <= 6
    static BOOST_FORCEINLINE A0 erfc3(const A0& x)
    {
      return  NT2_HORNER_RAT(sA0, 7, 7, x,
                             (0x0ll,                 //0
                              0x3f971d0907ea7a92ull, //2.25716982919218E-02
                              0x3fc42210f88b9d43ull, //0.157289620742839
                              0x3fe29be1cff90d94ull, //0.581528574177741
                              0x3ff44744306832aeull, //1.26739901455873
                              0x3ff9fa202deb88e5ull, //1.62356584489367
                              0x3fefff5a9e697ae2ull  //0.99992114009714
                             ),
                             (0x3fa47bd61bbb3843ull, //4.00072964526861E-02
                              0x3fd1d7ab774bb837ull, //0.278788439273629
                              0x3ff0cfd4cb6cde9full, //1.05074004614827
                              0x400315ffdfd5ce91ull, //2.38574194785344
                              0x400afd487397568full, //3.37367334657285
                              0x400602f24bf3fdb6ull, //2.75143870676376
                              0x3ff0000000000000ull  //1
                             )
                            );
    }
  };
} }

#endif
