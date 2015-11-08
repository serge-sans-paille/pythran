//==============================================================================
//         Copyright 2003 - 2014 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2014 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_EULER_FUNCTIONS_DETAILS_STIRLING_KERNEL_HPP_INCLUDED
#define NT2_EULER_FUNCTIONS_DETAILS_STIRLING_KERNEL_HPP_INCLUDED
#include <nt2/polynomials/functions/scalar/impl/horner.hpp>
#include <nt2/sdk/meta/scalar_of.hpp>

////////////////////////////////////////////////////////////////////////////////
// These kernels allows some code factorization between stirling and stirlingc
// stirlingc is 1-stirling
// each one is better computed as 1 - the other at different spots
// where digits cancellation may occur
// Also these kernel codes are simd agnostic (generic)
////////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace details
{
  template < class A0, class sA0 = typename meta::scalar_of<A0>::type >
   struct stirling_kernel;

  template < class A0 >
  struct stirling_kernel < A0, float >
  {
    typedef typename meta::scalar_of<A0>::type sA0;
    static BOOST_FORCEINLINE A0 stirling1(const A0& x)
    {
      return  horner<NT2_HORNER_COEFF_T(sA0, 4,
                                        (0xb970b359,
                                         0xbb2fb930,
                                         0x3b638e39,
                                         0x3daaaaab
                                        )
                                       )>(x);
    }
  };

  template < class A0 >
  struct stirling_kernel < A0, double >
  {
    typedef typename meta::scalar_of<A0>::type sA0;
    static BOOST_FORCEINLINE A0 stirling1(const A0& x)
    {
      return  horner<NT2_HORNER_COEFF_T(sA0, 5,
                                        (0x3f49cc72592d7293ll, //   7.87311395793093628397E-4
                                         0xbf2e166b27e61d7cll, //  -2.29549961613378126380E-4
                                         0xbf65f72607d44fd7ll, //  -2.68132617805781232825E-3
                                         0x3f6c71c71b98c5fdll, //   3.47222221605458667310E-3
                                         0x3fb5555555555986ll  //   8.33333333333482257126E-2
                                        )
                                       )>(x);
    }
  };
} }

#endif




