//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_EXPONENTIAL_FUNCTIONS_SCALAR_IMPL_LOGS_D_LOG_HPP_INCLUDED
#define NT2_EXPONENTIAL_FUNCTIONS_SCALAR_IMPL_LOGS_D_LOG_HPP_INCLUDED

#include <nt2/include/functions/scalar/sqr.hpp>
#include <nt2/include/functions/scalar/tofloat.hpp>
#include <nt2/include/functions/scalar/is_ltz.hpp>
#include <nt2/include/functions/scalar/is_eqz.hpp>
#include <nt2/include/functions/scalar/is_greater.hpp>
#include <nt2/include/functions/scalar/multiplies.hpp>
#include <nt2/include/functions/scalar/plus.hpp>
#include <nt2/include/functions/scalar/fast_frexp.hpp>
#include <nt2/include/functions/scalar/genmask.hpp>
#include <nt2/include/functions/scalar/minusone.hpp>
#include <nt2/include/functions/scalar/fma.hpp>
#include <nt2/include/functions/scalar/bitwise_and.hpp>
#include <nt2/polynomials/functions/scalar/impl/horner.hpp>
#include <nt2/include/constants/real_splat.hpp>
#include <nt2/include/constants/invlog_2.hpp>
#include <nt2/include/constants/invlog_10.hpp>
#include <nt2/include/constants/log_2olog_10.hpp>
#include <nt2/include/constants/sqrt_2o_2.hpp>
#include <nt2/include/constants/mone.hpp>
#include <nt2/include/constants/zero.hpp>
#include <nt2/include/constants/two.hpp>
#include <nt2/include/constants/minf.hpp>
#include <nt2/include/constants/half.hpp>
#include <nt2/include/constants/nan.hpp>
#include <boost/simd/sdk/config.hpp>

#ifndef BOOST_SIMD_NO_NANS
#include <nt2/include/functions/scalar/is_nan.hpp>
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
  struct logarithm< A0, tag::not_simd_type, double>
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
      A0 x;
      int_type k;
      nt2::fast_frexp(a0, x, k);
      const int_type x_lt_sqrthf = nt2::is_greater(nt2::Sqrt_2o_2<A0>(), x)?nt2::Mone<int_type>():nt2::Zero<int_type>();
      k += x_lt_sqrthf;
      f = nt2::minusone(x+nt2::b_and(x, nt2::genmask(x_lt_sqrthf)));
      dk = nt2::tofloat(k);
      s = f/nt2::add(nt2::Two<A0>(),f);
      A0 z = nt2::sqr(s);
      A0 w = nt2::sqr(z);
      A0 t1= w*nt2::horner<NT2_HORNER_COEFF_T(sA0, 3,
                                              (0x3fc39a09d078c69fll,
                                               0x3fcc71c51d8e78afll,
                                               0x3fd999999997fa04ll)
                                             )> (w);
      A0 t2= z*horner<NT2_HORNER_COEFF_T(sA0, 4,
                                         (0x3fc2f112df3e5244ll,
                                          0x3fc7466496cb03dell,
                                          0x3fd2492494229359ll,
                                          0x3fe5555555555593ll)
                                        )> (w);
      R = t2+t1;
      hfsq = nt2::mul(Half<A0>(), nt2::sqr(f));
    }

    static inline A0 log(const A0& a0)
    {
      // ln(2)hi  =  6.93147180369123816490e-01  or  0x3fe62e42fee00000
      // ln(2)lo  =  1.90821492927058770002e-10  or  0x3dea39ef35793c76
#ifndef BOOST_SIMD_NO_INFINITIES
      if (a0 == Inf<A0>()) return a0;
#endif
      if (is_eqz(a0)) return nt2::Minf<A0>();
#ifdef BOOST_SIMD_NO_NANS
      if (nt2::is_ltz(a0)) return nt2::Nan<A0>();
#else
      if (nt2::is_nan(a0)||nt2::is_ltz(a0)) return nt2::Nan<A0>();
#endif
      A0 dk, hfsq, s, R, f;
      kernel_log(a0, dk, hfsq, s, R, f);
      return  nt2::mul(dk, double_constant<A0, 0x3fe62e42fee00000ll>())-
        ((hfsq-(s*(hfsq+R)+nt2::mul(dk,double_constant<A0, 0x3dea39ef35793c76ll>())))-f);
    }

    static inline A0 log2(const A0& a0)
    {
#ifndef BOOST_SIMD_NO_INFINITIES
      if (a0 == nt2::Inf<A0>()) return a0;
#endif
      if (nt2::is_eqz(a0)) return nt2::Minf<A0>();
#ifdef BOOST_SIMD_NO_NANS
      if (nt2::is_ltz(a0)) return nt2::Nan<A0>();
#else
      if (nt2::is_nan(a0)||nt2::is_ltz(a0)) return nt2::Nan<A0>();
#endif
      A0 dk, hfsq, s, R, f;
      kernel_log(a0, dk, hfsq, s, R, f);
      return -(hfsq-(s*(hfsq+R))-f)*Invlog_2<A0>()+dk;
    }

    static inline A0 log10(const A0& a0)
    {
#ifndef BOOST_SIMD_NO_INFINITIES
      if (a0 == nt2::Inf<A0>()) return a0;
#endif
      if (nt2::is_eqz(a0)) return nt2::Minf<A0>();
#ifdef BOOST_SIMD_NO_NANS
      if (nt2::is_ltz(a0)) return nt2::Nan<A0>();
#else
      if (nt2::is_nan(a0)||nt2::is_ltz(a0)) return nt2::Nan<A0>();
#endif
      A0 dk, hfsq, s, R, f;
      kernel_log(a0, dk, hfsq, s, R, f);
      return -(hfsq-(s*(hfsq+R))-f)*nt2::Invlog_10<A0>()+dk*nt2::Log_2olog_10<A0>();
    }
  };
} }


#endif
