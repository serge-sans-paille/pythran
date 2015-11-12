//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_EXPONENTIAL_FUNCTIONS_SCALAR_IMPL_LOGS_F_KERNEL_HPP_INCLUDED
#define NT2_EXPONENTIAL_FUNCTIONS_SCALAR_IMPL_LOGS_F_KERNEL_HPP_INCLUDED
#include <nt2/sdk/meta/as_logical.hpp>
#include <boost/simd/sdk/config.hpp>
#include <nt2/include/functions/simd/fast_frexp.hpp>
#include <nt2/include/functions/simd/is_less.hpp>
#include <nt2/include/functions/simd/tofloat.hpp>
#include <nt2/include/functions/simd/seladd.hpp>
#include <nt2/include/functions/simd/minusone.hpp>
#include <nt2/include/functions/simd/sqr.hpp>
#include <nt2/include/functions/simd/multiplies.hpp>

#include <nt2/include/constants/sqrt_2o_2.hpp>
#include <nt2/include/constants/mone.hpp>


#include <nt2/polynomials/functions/scalar/impl/horner.hpp>
#include <nt2/sdk/meta/as_logical.hpp>
#include <nt2/sdk/meta/as_integer.hpp>

namespace nt2 { namespace details
{
  template < class A0,
             class Style ,
             class base_A0 = typename meta::scalar_of<A0>::type>
             struct kernel{};

  template < class A0, class style>
  struct kernel< A0, style, float>
  {
    typedef typename meta::as_logical<A0>::type              lA0;
    typedef typename meta::as_integer<A0, signed>::type int_type;
    typedef typename meta::scalar_of<A0>::type               sA0;

    static inline void log(const A0& a0,
                           A0& fe,
                           A0& x,
                           A0& x2,
                           A0& y)
    {
      int_type e;
      x = nt2::fast_frexp(a0, e);
      lA0 xltsqrthf = lt(x, Sqrt_2o_2<A0>());
      fe = seladd(xltsqrthf, nt2::tofloat(e), Mone<A0>());
      x =  minusone(seladd(xltsqrthf, x, x));
      x2 = sqr(x);
      // performances informations using this kernel for nt2::log
      // exhaustive and bench tests with g++-4.7 sse4.2 or scalar give:
      // at most 0.5 ulp  for input in [0, 3.40282e+38]
      // 2130706656 values computed.
      // 2127648316 values (99.86%)  within 0.0 ULPs
      //    3058340 values (0.14%)   within 0.5 ULPs
      // bench produces  8.9 cycles/value (simd) 34.5 cycles/value (scalar) full computation
      // bench produces  7.1 cycles/value (simd) 32.2 cycles/value (scalar) with NO_DENORMALS, NO_INVALIDS etc.
      y =  horner< NT2_HORNER_COEFF_T( sA0
                                     , 8
                                     , (0xbda5dff0, //     -8.0993533e-02
                                        0x3e0229f9, //      1.2711324e-01
                                        0xbe04d6b7, //     -1.2972532e-01
                                        0x3e116e80, //      1.4202309e-01
                                        0xbe2a6aa0, //     -1.6642237e-01
                                        0x3e4cd0a3, //      2.0001464e-01
                                        0xbe800064, //     -2.5000298e-01
                                        0x3eaaaaa9  //      3.3333328e-01
                                       )
                                      )>(x)*x*x2;
    }
  };
} }


#endif
