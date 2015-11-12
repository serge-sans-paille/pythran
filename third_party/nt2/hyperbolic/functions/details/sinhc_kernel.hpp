//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_HYPERBOLIC_FUNCTIONS_DETAILS_SINHC_KERNEL_HPP_INCLUDED
#define NT2_HYPERBOLIC_FUNCTIONS_DETAILS_SINHC_KERNEL_HPP_INCLUDED
#include <nt2/include/functions/scalar/oneplus.hpp>
#include <nt2/polynomials/functions/scalar/impl/horner.hpp>
#include <nt2/include/functions/simd/multiplies.hpp>
#include <nt2/include/functions/simd/divides.hpp>
#include <nt2/sdk/meta/scalar_of.hpp>

namespace nt2 { namespace details
{
  template < class A0, class sA0 = typename meta::scalar_of<A0>::type >
  struct sinhc_kernel;

  template < class A0 >
  struct sinhc_kernel < A0, float >
  {
    static BOOST_FORCEINLINE A0 compute(const A0& x2)
    {
      typedef typename meta::scalar_of<A0>::type sA0;
      return horner < NT2_HORNER_COEFF_T(sA0, 4,
                                         (  0x39559e2f, // 2.03721912945E-4f
                                            0x3c087bbe, // 8.33028376239E-3f
                                            0x3e2aaacc, // 1.66667160211E-1f
                                            0x3f800000  // 1.0f
                                         )
                                        )> (x2);
    }
  };

  template < class A0 >
  struct sinhc_kernel < A0, double >
  {
    // computes sinhc for abs(a0) < 1 and x2 =  sqr(a0) for doubles
    static  BOOST_FORCEINLINE A0 compute(const A0& x2)
    {
      typedef typename meta::scalar_of<A0>::type sA0;
      return oneplus( x2*horner<NT2_HORNER_COEFF_T(sA0, 4,
                                      ( 0xbfe9435fe8bb3cd6ull, //  -7.89474443963537015605E-1,
                                        0xc064773a398ff4feull, //  -1.63725857525983828727E2,
                                        0xc0c694b8c71d6182ull, //  -1.15614435765005216044E4,
                                        0xc115782bdbf6ab05ull  //  -3.51754964808151394800E5
                                      )
                                     )> (x2)/
           horner<NT2_HORNER_COEFF_T(sA0, 4,
                                     ( 0x3ff0000000000000ull, //   1.00000000000000000000E0,
                                       0xc0715b6096e96484ull, //  -2.77711081420602794433E2,
                                       0x40e1a7ba7ed72245ull, //   3.61578279834431989373E4,
                                       0xc1401a20e4f90044ull  //  -2.11052978884890840399E6
                                     )
                                    )> (x2));
    }
  };
} }



#endif
