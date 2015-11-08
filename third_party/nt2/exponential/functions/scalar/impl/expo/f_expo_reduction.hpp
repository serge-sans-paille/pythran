//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_EXPONENTIAL_FUNCTIONS_SCALAR_IMPL_EXPO_F_EXPO_REDUCTION_HPP_INCLUDED
#define NT2_EXPONENTIAL_FUNCTIONS_SCALAR_IMPL_EXPO_F_EXPO_REDUCTION_HPP_INCLUDED
// This implementation is also used with simd
#include <nt2/exponential/functions/scalar/impl/selection_tags.hpp>
#include <nt2/include/functions/simd/is_greater_equal.hpp>
#include <nt2/include/constants/maxlog.hpp>
#include <nt2/include/functions/simd/is_less_equal.hpp>
#include <nt2/include/constants/minlog.hpp>
#include <nt2/sdk/meta/scalar_of.hpp>
#include <nt2/sdk/meta/as_logical.hpp>
#include <nt2/polynomials/functions/scalar/impl/horner.hpp>
#include <nt2/include/functions/simd/inc.hpp>
#include <nt2/include/functions/simd/sqr.hpp>
#include <nt2/include/functions/simd/fma.hpp>
#include <nt2/include/functions/simd/round2even.hpp>
#include <nt2/include/functions/simd/multiplies.hpp>
#include <nt2/include/constants/invlog_2.hpp>
#include <nt2/include/functions/simd/fnms.hpp>
#include <nt2/include/constants/log_2hi.hpp>
#include <nt2/include/constants/log_2lo.hpp>
#include <nt2/include/constants/log_2.hpp>
#include <nt2/include/constants/minlog2.hpp>
#include <nt2/include/constants/maxlog2.hpp>
#include <nt2/include/functions/simd/minus.hpp>
#include <nt2/include/constants/minlog10.hpp>
#include <nt2/include/constants/maxlog10.hpp>
#include <nt2/include/constants/invlog10_2.hpp>
#include <nt2/include/constants/log10_2hi.hpp>
#include <nt2/include/constants/log10_2lo.hpp>
#include <nt2/include/constants/log_10.hpp>



namespace nt2 { namespace details
{
  template< class A0, class Tag
            , class Base_A0 = typename meta::scalar_of<A0>::type
  >
  struct exp_reduction;

  template<class A0> struct exp_reduction <A0,natural_tag,float>
  {
    typedef typename meta::as_logical<A0>::type bA0;
    static inline bA0 isgemaxlog(const A0 & a0)
    {
      return nt2::ge(a0,Maxlog<A0>());
    }

    static inline bA0 isleminlog(const A0 & a0)
    {
      return nt2::le(a0,Minlog<A0>());
    }

    static inline A0 approx(const A0& x)
    {
      typedef typename meta::scalar_of<A0>::type sA0;
      // remez polynomial of degree 4 on [-0.5 0.5] for (exp(x)-1-x)/sqr(x) tested in range: [-88.3763, 88.3763]
      //2214928753 values (98.98%)  within 0.0 ULPs
      //  22831063 values (1.02%)   within 0.5 ULPs
      //  4.89648 cycles/value (SSE4.2 g++-4.8)
      A0 y = nt2::horner<NT2_HORNER_COEFF_T(sA0, 5,
                                            (0x3ab778cf, //  1.3997796e-03
                                             0x3c098d8b, //  8.3955629e-03
                                             0x3d2aa957, //  4.1665401e-02
                                             0x3e2aa9a5, //  1.6666277e-01
                                             0x3f000000  //  5.0000000e-01
                                            )
                                           )>(x);
      return inc(fma(y, sqr(x), x));
    }
    static inline A0 reduce(const A0& a0, A0& x)
    {
      A0 k = nt2::round2even(nt2::Invlog_2<A0>()*a0);
      x = fnms(k, Log_2hi<A0>(), a0); //a0-k*L
      x =  fnms(k, Log_2lo<A0>(), x);
      return k;
    }
  };

  template < class A0 > struct exp_reduction < A0, two_tag, float>
  {
    typedef typename meta::as_logical<A0>::type bA0;
    static inline bA0 isgemaxlog(const A0 & a0)
    {
      return nt2::ge(a0,Maxlog2<A0>());
    }

    static inline bA0 isleminlog(const A0 & a0)
    {
      return nt2::le(a0,Minlog2<A0>());
    }

    static inline A0 approx(const A0& x)
    {
      typedef typename meta::scalar_of<A0>::type sA0;

      // remez polynom of degree 4 on [-0.5, 0.5] for (exp2(x)-1-x*log(2))/sqr(x)  tested in range: [-127 127]
      //2247884800 values computed.
      //2224606419 values (98.96%)  within 0.0 ULPs
      //  23278381 values (1.04%)   within 0.5 ULPs
      //  3.5 cycles/value  (SSE4.2 g++-4.8)
      A0 y = nt2::horner<NT2_HORNER_COEFF_T(sA0, 5,
                                            (0x3922c8c4,  //    1.5524315e-04
                                             0x3ab01218,  //    1.3433127e-03
                                             0x3c1d9422,  //    9.6178371e-03
                                             0x3d6356eb,  //    5.5502813e-02
                                             0x3e75fdf1   //    2.4022652e-01
                                            )
                                           )>(x);
      return inc(fma(y, sqr(x), x*Log_2<A0>()));
    }

    static inline A0 reduce(const A0& a0, A0& x)
    {
      A0 k = nt2::round2even(a0);
      x = (a0 - k);
      return k;
    }
  };

  template < class A0 > struct exp_reduction < A0, ten_tag, float>
  {
    typedef typename meta::as_logical<A0>::type bA0;
    static inline bA0 isgemaxlog(const A0 & a0)
    {
      return nt2::ge(a0,Maxlog10<A0>());
    }

    static inline bA0 isleminlog(const A0 & a0)
    {
      return nt2::le(a0,Minlog10<A0>());
    }

    static inline A0 reduce(const A0& a0, A0& x)
    {
      A0 k = round2even(Invlog10_2<A0>()*a0);
      x = fnms(k, Log10_2hi<A0>(), a0);
      x -= k*Log10_2lo<A0>();
      return k;
    }

    static inline A0 approx(const A0& x)
    {
      typedef typename meta::scalar_of<A0>::type sA0;
      // remez polynom of degree 5 on [-0.5, 0.5]*log10(2) for (exp10(x)-1)/x   tested in range: [-37.9, 38.2308]
      //2217772528 values computed.
      //2198853506 values (99.15%)  within 0.0 ULPs
      //  18919022 values (0.85%)   within 0.5 ULPs
      //      5.2 cycles/value  (SSE4.2 g++-4.8)
      return inc(nt2::horner<NT2_HORNER_COEFF_T(sA0, 6,
                                                (0x3e54dff1, //    2.0788552e-01
                                                 0x3f0aacef, //    5.4170126e-01
                                                 0x3f95eb4c, //    1.1712432e+00
                                                 0x400237da, //    2.0346589e+00
                                                 0x4029a926, //    2.6509490e+00
                                                 0x40135d8e  //    2.3025851e+00
                                                )
                                               )>(x)*x);
    }
  };
} }


#endif
