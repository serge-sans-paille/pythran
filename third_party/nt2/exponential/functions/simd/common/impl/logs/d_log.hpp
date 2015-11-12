//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_EXPONENTIAL_FUNCTIONS_SIMD_COMMON_IMPL_LOGS_D_LOG_HPP_INCLUDED
#define NT2_EXPONENTIAL_FUNCTIONS_SIMD_COMMON_IMPL_LOGS_D_LOG_HPP_INCLUDED

#include <nt2/include/functions/simd/minusone.hpp>
#include <nt2/include/functions/simd/tofloat.hpp>
#include <nt2/include/functions/simd/sqr.hpp>
#include <nt2/include/functions/simd/unary_minus.hpp>
#include <nt2/include/functions/simd/is_greater.hpp>
#include <nt2/include/functions/simd/is_ltz.hpp>
#include <nt2/include/functions/simd/is_equal.hpp>
#include <nt2/include/functions/simd/fast_frexp.hpp>
#include <nt2/include/functions/simd/seladd.hpp>
#include <nt2/include/functions/simd/plus.hpp>
#include <nt2/include/functions/simd/minus.hpp>
#include <nt2/include/functions/simd/multiplies.hpp>
#include <nt2/include/functions/simd/divides.hpp>
#include <nt2/include/functions/simd/bitwise_and.hpp>
#include <nt2/include/functions/simd/logical_or.hpp>
#include <nt2/include/functions/simd/if_allbits_else.hpp>
#include <nt2/include/functions/simd/if_else_zero.hpp>
#include <nt2/include/functions/simd/is_eqz.hpp>
#include <nt2/polynomials/functions/scalar/impl/horner.hpp>
#include <nt2/include/constants/invlog_2.hpp>
#include <nt2/include/constants/invlog_10.hpp>
#include <nt2/include/constants/log_2olog_10.hpp>
#include <nt2/include/constants/log_2hi.hpp>
#include <nt2/include/constants/log_2lo.hpp>
#include <nt2/include/constants/half.hpp>
#include <nt2/include/constants/sqrt_2o_2.hpp>
#include <nt2/include/constants/mone.hpp>
#include <nt2/include/constants/minf.hpp>
#include <boost/simd/sdk/config.hpp>
#include <boost/simd/sdk/meta/as_logical.hpp>

#ifndef BOOST_SIMD_NO_NANS
#include <nt2/include/functions/simd/is_nan.hpp>
#endif
#ifndef BOOST_SIMD_NO_INFINITIES
#include <nt2/include/constants/inf.hpp>
#endif

namespace nt2 { namespace details
{
  //////////////////////////////////////////////////////////////////////////////
  // math log functions
  //////////////////////////////////////////////////////////////////////////////

  template < class A0 >
  struct logarithm< A0, tag::simd_type, double>
  {
    static inline void kernel_log(const A0& a0,
                                  A0& dk,
                                  A0& hfsq,
                                  A0& s,
                                  A0& R,
                                  A0& f)
    {
      typedef typename meta::as_integer<A0, signed>::type int_type;
      typedef typename meta::scalar_of<A0>::type               sA0;
      int_type k;
      A0 x(nt2::fast_frexp(a0, k));
      const int_type x_lt_sqrthf = nt2::if_else_zero(nt2::gt(nt2::Sqrt_2o_2<A0>(), x),
                                                     nt2::Mone<int_type>());
      k = k+x_lt_sqrthf;
      f = nt2::minusone(x+nt2::bitwise_and(x, x_lt_sqrthf));
      dk = nt2::tofloat(k);
      s = f/nt2::add(Two<A0>(),f);
      A0 z = nt2::sqr(s);
      A0 w = nt2::sqr(z);
      A0 t1= w*nt2::horner<NT2_HORNER_COEFF_T(sA0, 3,
                                         (0x3fc39a09d078c69fll,
                                          0x3fcc71c51d8e78afll,
                                          0x3fd999999997fa04ll)
                                        )> (w);
      A0 t2= z*nt2::horner<NT2_HORNER_COEFF_T(sA0, 4,
                                         (0x3fc2f112df3e5244ll,
                                          0x3fc7466496cb03dell,
                                          0x3fd2492494229359ll,
                                          0x3fe5555555555593ll)
                                        )> (w);
      R = t2+t1;
      hfsq = nt2::mul(nt2::Half<A0>(), nt2::sqr(f));
    }

    static inline A0 log(const A0& a0)
    {
      A0 dk, hfsq, s, R, f;
      kernel_log(a0, dk, hfsq, s, R, f);
      A0 y =  nt2::mul(dk, Log_2hi<A0>())-
        ((hfsq-(s*(hfsq+R)+nt2::mul(dk,Log_2lo<A0>())))-f);
      return finalize(a0, y);
    }

    static inline A0 log2(const A0& a0)
    {
      A0 dk, hfsq, s, R, f;
      kernel_log(a0, dk, hfsq, s, R, f);
      A0 y = -(hfsq-(s*(hfsq+R))-f)*nt2::Invlog_2<A0>()+dk;
      return finalize(a0, y);
    }

    static inline A0 log10(const A0& a0)
    {
      A0 dk, hfsq, s, R, f;
      kernel_log(a0, dk, hfsq, s, R, f);
      A0 y = -(hfsq-(s*(hfsq+R))-f)*nt2::Invlog_10<A0>()+dk*nt2::Log_2olog_10<A0>();
      return finalize(a0, y);
    }
  private:
    static inline A0 finalize(const A0& a0, const A0& y)
    {
      typedef typename meta::as_logical<A0>::type              lA0;
    #ifdef BOOST_SIMD_NO_NANS
      lA0 test =  nt2::is_ltz(a0);
    #else
      lA0 test =  nt2::logical_or(nt2::is_ltz(a0), nt2::is_nan(a0));
    #endif
      A0 y1 = nt2::if_nan_else(test, y);
    #ifndef BOOST_SIMD_NO_INFINITIES
      y1 = if_else(nt2::eq(a0, nt2::Inf<A0>()), a0, y1);
    #endif
      return if_else(is_eqz(a0), nt2::Minf<A0>(), y1);
    }
  };

} }

#endif
