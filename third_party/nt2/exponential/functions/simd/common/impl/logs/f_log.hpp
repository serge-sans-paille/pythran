//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_EXPONENTIAL_FUNCTIONS_SIMD_COMMON_IMPL_LOGS_F_LOG_HPP_INCLUDED
#define NT2_EXPONENTIAL_FUNCTIONS_SIMD_COMMON_IMPL_LOGS_F_LOG_HPP_INCLUDED

#include <nt2/include/functions/simd/multiplies.hpp>
#include <nt2/include/functions/simd/plus.hpp>
#include <nt2/include/functions/simd/fma.hpp>
#include <nt2/include/functions/simd/is_eqz.hpp>
#include <nt2/include/functions/simd/if_allbits_else.hpp>
#include <nt2/include/functions/simd/if_else.hpp>
#include <nt2/include/functions/simd/if_else_zero.hpp>
#include <nt2/include/functions/simd/is_ltz.hpp>
#include <nt2/exponential/functions/scalar/impl/logs/f_kernel.hpp>
#include <nt2/include/constants/mhalf.hpp>
#include <nt2/include/constants/minf.hpp>
#include <nt2/include/constants/log_2hi.hpp>
#include <nt2/include/constants/log_2lo.hpp>
#include <nt2/include/constants/log2_em1.hpp>
#include <nt2/include/constants/log10_ehi.hpp>
#include <nt2/include/constants/log10_elo.hpp>
#include <nt2/include/constants/log10_2hi.hpp>
#include <nt2/include/constants/log10_2lo.hpp>
#include <nt2/sdk/meta/as_logical.hpp>
#include <nt2/sdk/meta/as_integer.hpp>
#include <nt2/sdk/meta/scalar_of.hpp>
#include <boost/simd/sdk/config.hpp>
#include <boost/simd/sdk/meta/as_logical.hpp>

#ifndef BOOST_SIMD_NO_NANS
#include <nt2/include/functions/simd/is_nan.hpp>
#include <nt2/include/functions/simd/logical_or.hpp>
#endif
#ifndef BOOST_SIMD_NO_INFINITIES
#include <nt2/include/constants/inf.hpp>
#include <nt2/include/functions/simd/is_equal.hpp>
#endif
#ifndef BOOST_SIMD_NO_DENORMALS
#include <nt2/include/functions/simd/abs.hpp>
#include <nt2/include/functions/simd/is_less.hpp>
#include <nt2/include/constants/smallestposval.hpp>
#include <nt2/include/constants/twotonmb.hpp>
#include <nt2/include/constants/mlogtwo2nmb.hpp>
#include <nt2/include/constants/mlog2two2nmb.hpp>
#include <nt2/include/constants/mlog10two2nmb.hpp>
#endif

  //////////////////////////////////////////////////////////////////////////////
  // how to compute the various logarithms
  //////////////////////////////////////////////////////////////////////////////
  // The method is mainly taken from the cephes library:
  // first reduce the the data
  // a0 is supposed > 0
  // the input a0 is split into a mantissa and an exponent
  // the mantissa m is between sqrt(0.5) and sqrt(2) and the correspondint exponent is e
  // a0 = m*2^e
  // then the log? calculus is split in two parts (? being nothing: natural logarithm,  2: base 2 logarithm,  10 base ten logarithm)
  // as log?(a) = log?(2^e)+log?(m)
  // 1) computing log?(m)
  //   first put x = m-1 (so -0.29 <  x < 0.414)
  //   write log(m)   = log(1+x)   = x + x*x/2 + x*x*x*g(x)
  //   write log2(m)  = log2(1+x)  = C2*log(x)   C2 =  log(2)  the multiplication have to be taken seriously as C2 is not exact
  //   write log10(m) = log10(1+x) = C10*log(x)  C10=  log(10) the multiplication have to be taken seriously as C10 is not exact
  // then g(x) has to be approximated
  // g is ((log(1+x)/x-1)/x-1/2)/x
  // It is not a good idea to approximate directly log(1+x) instead of g,  because this will lead to bad precision around 1.
  //
  // in this approximation one can choose a best approximation rational function given by remez algorithm.
  // there exist a classical solution which is a polynomial p8 one of degree 8 that gives 0.5ulps everywhere
  // this is what is done in the kernel_t::log impl;
  // Now,  it is possible to choose a rational fraction or a polynomial of lesser degree to approximate g
  // providing faster but less accurate logs.
  // 2) computing log?(2^e)
  // see the explanations relative to each case
  // 3) finalize
  // This is simply treating invalid entries
  // 4) For denormal we use the fact that log(x) =  log?(x*y)-log?(y) and that if y is
  // the constant two2nmb if x is denormal x*y and y are not.
  //////////////////////////////////////////////////////////////////////////////

namespace nt2 { namespace details
{
  //////////////////////////////////////////////////////////////////////////////
  // math log functions
  //////////////////////////////////////////////////////////////////////////////

  template < class A0 >
  struct logarithm< A0, tag::simd_type, float>
  {
    typedef typename meta::as_logical<A0>::type                 lA0;
    typedef typename meta::as_integer<A0, signed>::type    int_type;
    typedef typename meta::scalar_of<A0>::type                  sA0;
    typedef kernel<A0, tag::simd_type, float>              kernel_t;

    static inline A0 log(const A0& a0)
    {
      A0 z = a0;
#ifndef BOOST_SIMD_NO_DENORMALS
      A0 t = Zero<A0>();
      lA0 denormal = lt(nt2::abs(z), Smallestposval<A0>());
      z = if_else(denormal, z*Twotonmb<A0>(), z);
      t = if_else_zero(denormal, Mlogtwo2nmb<A0>());
#endif
      //log(2.0) in double is 6.931471805599453e-01
      //double(0.693359375f)+double(-0.00021219444f)  is  6.931471805600000e-01 at 1.0e-14 of log(2.0)
      // let us call Log_2hi 0.693359375f anf Log_2lo -0.00021219444f
      // We use thi to correct the sum where this could matter a lot
      // log(a0) = fe*Log_2hi+ (0.5f*x*x +(fe*Log_2lo+y))
      // These operations are order dependent: the parentheses do matter
      A0 x, fe, x2, y;
      kernel_t::log(z, fe, x, x2, y);
      y = nt2::fma(fe, Log_2lo<A0>(), y);
      y = nt2::fma(Mhalf<A0>(), x2, y);
#ifdef BOOST_SIMD_NO_DENORMALS
      return finalize(a0, nt2::fma(Log_2hi<A0>(), fe, x+y));
#else
      return finalize(a0, nt2::fma(Log_2hi<A0>(), fe, x+y+t));
#endif
    }

    static inline A0 log2(const A0& a0)
    {
      A0 z =  a0;
#ifndef BOOST_SIMD_NO_DENORMALS
      lA0 denormal = lt(nt2::abs(z), Smallestposval<A0>());
      z = if_else(denormal, z*Twotonmb<A0>(), z);
      A0 t = if_else_zero(denormal, Mlog2two2nmb<A0>());
#endif
      //here let l2em1 = log2(e)-1, the computation is done as:
      //log2(a0) = ((l2em1*x+(l2em1*(y+x*x/2)))+(y+x*x/2)))+x+fe for best results
      // once again the order is very important.
      A0 x, fe, x2, y;
      kernel_t::log(z, fe, x, x2, y);
      y =  nt2::fma(Mhalf<A0>(),x2, y);
      z = nt2::fma(x,Log2_em1<A0>(),y*Log2_em1<A0>());
#ifdef BOOST_SIMD_NO_DENORMALS
      return finalize(a0, ((z+y)+x)+fe);
#else
      return finalize(a0, ((z+y)+x)+fe+t);
#endif
    }

    static inline A0 log10(const A0& a0)
    {
      A0 z = a0;
#ifndef BOOST_SIMD_NO_DENORMALS
      lA0 denormal = lt(nt2::abs(z), Smallestposval<A0>());
      z = if_else(denormal, z*Twotonmb<A0>(), z);
      A0 t = if_else_zero(denormal, Mlog10two2nmb<A0>());
#endif
      // here there are two multiplication:  log of fraction by log10(e) and base 2 exponent by log10(2)
      // and we have to split log10(e) and log10(2) in two parts to get extra precision when needed
      A0 x, fe, x2, y;
      kernel_t::log(z, fe, x, x2, y);
      y = nt2::amul(y, Mhalf<A0>(), x2);
      z = mul(x+y, Log10_elo<A0>());
      z = nt2::amul(z, y, Log10_ehi<A0>());
      z = nt2::amul(z, x, Log10_ehi<A0>());
      z = nt2::amul(z, fe, Log10_2hi<A0>());
#ifdef BOOST_SIMD_NO_DENORMALS
      return finalize(a0, nt2::amul(z, fe, Log10_2lo<A0>()));
#else
      return finalize(a0, nt2::amul(z+t, fe, Log10_2lo<A0>()));
#endif
    }
  private:
    static inline A0 finalize(const A0& a0, const A0& y)
    {
      typedef typename meta::as_logical<A0>::type              lA0;
    #ifdef BOOST_SIMD_NO_NANS
      lA0 test = nt2::is_ltz(a0);
    #else
      lA0 test = nt2::logical_or(nt2::is_ltz(a0), nt2::is_nan(a0));
    #endif
      A0 y1 = nt2::if_nan_else(test, y);
    #ifndef BOOST_SIMD_NO_INFINITIES
      y1 = if_else(nt2::is_equal(a0, nt2::Inf<A0>()), a0, y1);
    #endif
      return if_else(is_eqz(a0), nt2::Minf<A0>(), y1);
    }
  };
} }

#endif
