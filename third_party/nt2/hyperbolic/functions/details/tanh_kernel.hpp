//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_HYPERBOLIC_FUNCTIONS_DETAILS_TANH_KERNEL_HPP_INCLUDED
#define NT2_HYPERBOLIC_FUNCTIONS_DETAILS_TANH_KERNEL_HPP_INCLUDED
#include <nt2/include/functions/scalar/fma.hpp>
#include <nt2/polynomials/functions/scalar/impl/horner.hpp>
#include <nt2/include/functions/simd/multiplies.hpp>
#include <nt2/include/functions/simd/divides.hpp>
#include <nt2/include/functions/simd/rec.hpp>
#include <nt2/include/functions/simd/fma.hpp>
#include <nt2/sdk/meta/scalar_of.hpp>

namespace nt2 { namespace details
{
  template < class A0, class sA0 = typename meta::scalar_of<A0>::type >
  struct tanh_kernel;

  template < class A0 >
  struct tanh_kernel < A0, float >
  {
    typedef typename meta::scalar_of<A0>::type sA0;
    // computes tanh for abs(a0) < 0.625 and x2 =  sqr(a0) for float
    static BOOST_FORCEINLINE A0 tanh(const A0& a0, const A0& x2)
    {
      return fma(horner < NT2_HORNER_COEFF_T(sA0, 5,
                                         (  0xbbbaf0ea, //    -5.70498872745E-3f
                                            0x3ca9134e, //    +2.06390887954E-2f
                                            0xbd5c1e2d, //    -5.37397155531E-2f
                                            0x3e088393, //    +1.33314422036E-1f
                                            0xbeaaaa99  //    -3.33332819422E-1f
                                         )
                                            )> (x2)*x2, a0, a0);
    }
    static BOOST_FORCEINLINE A0 coth(const A0& a0, const A0& x2)
    {
      return rec(tanh(a0, x2));
    }

  };

  template < class A0 >
  struct tanh_kernel < A0, double >
  {

    static  BOOST_FORCEINLINE A0 tanh(const A0& a0, const A0& x2)
    {
      return fma(x2*p(x2)/q(x2), a0, a0);
    }
    static  BOOST_FORCEINLINE A0 coth(const A0& a0, const A0& x2)
    {
      A0 qval =  q(x2);
      return qval/(a0*fma(p(x2), x2, qval));
    }
  private:
    typedef typename meta::scalar_of<A0>::type sA0;
    // computes tanh for abs(a0) < 0.625 and x2 =  sqr(a0) for doubles
    static  BOOST_FORCEINLINE A0 p(const A0& x2)
    {
      return horner<NT2_HORNER_COEFF_T(sA0, 3,
                                      (
                                        0xbfeedc5baafd6f4bull,  // -9.64399179425052238628E-1,
                                        0xc058d26a0e26682dull,  // -9.92877231001918586564E1,
                                        0xc0993ac030580563ull   // -1.61468768441708447952E3
                                      )
                                     )> (x2);
    }
    static  BOOST_FORCEINLINE A0 q(const A0& x2)
    {
      return horner<NT2_HORNER_COEFF_T(sA0, 4,
                                       (
                                         0x3FF0000000000000ULL,   //  1.0
                                         0x405c33f28a581b86ULL,   //  1.12811678491632931402E2,
                                         0x40a176fa0e5535faULL,   //  2.23548839060100448583E3,
                                         0x40b2ec102442040cULL    //  4.84406305325125486048E3
                                       )
                                      )> (x2);
    }


  };

} }



#endif
