//==================================================================================================
/*!

  Copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_COMMON_DETAIL_SIMD_F_LOG_HPP_INCLUDED
#define BOOST_SIMD_ARCH_COMMON_DETAIL_SIMD_F_LOG_HPP_INCLUDED


#include <boost/simd/function/multiplies.hpp>
#include <boost/simd/function/plus.hpp>
#include <boost/simd/function/fma.hpp>
#include <boost/simd/function/is_eqz.hpp>
#include <boost/simd/function/if_nan_else.hpp>
#include <boost/simd/function/if_else.hpp>
#include <boost/simd/function/if_else_zero.hpp>
#include <boost/simd/function/is_ltz.hpp>
#include <boost/simd/arch/common/detail/generic/f_log_kernel.hpp>
#include <boost/simd/arch/common/detail/tags.hpp>
#include <boost/simd/constant/mhalf.hpp>
#include <boost/simd/constant/minf.hpp>
#include <boost/simd/detail/constant/log_2hi.hpp>
#include <boost/simd/detail/constant/log_2lo.hpp>
#include <boost/simd/constant/log2_em1.hpp>
#include <boost/simd/detail/constant/log10_ehi.hpp>
#include <boost/simd/detail/constant/log10_elo.hpp>
#include <boost/simd/detail/constant/log10_2hi.hpp>
#include <boost/simd/detail/constant/log10_2lo.hpp>
#include <boost/simd/detail/dispatch/meta/as_integer.hpp>
#include <boost/simd/detail/dispatch/meta/scalar_of.hpp>

#ifndef BOOST_SIMD_NO_NANS
#include <boost/simd/function/is_nan.hpp>
#include <boost/simd/function/logical_or.hpp>
#endif
#ifndef BOOST_SIMD_NO_INFINITIES
#include <boost/simd/constant/inf.hpp>
#include <boost/simd/function/is_equal.hpp>
#endif
#ifndef BOOST_SIMD_NO_DENORMALS
#include <boost/simd/function/abs.hpp>
#include <boost/simd/function/is_less.hpp>
#include <boost/simd/constant/smallestposval.hpp>
#include <boost/simd/constant/twotonmb.hpp>
#include <boost/simd/constant/mlogtwo2nmb.hpp>
#include <boost/simd/constant/mlog2two2nmb.hpp>
#include <boost/simd/constant/mlog10two2nmb.hpp>
#endif

  //////////////////////////////////////////////////////////////////////////////
  // how to compute the various logarithms
  //////////////////////////////////////////////////////////////////////////////
  // The method is mainly taken from the cephes library:
  // first reduce the the data
  // a0 is supposed > 0
  // the input a0 is split into a mantissa and an exponent
  // the mantissa m is between sqrt(0.5) and sqrt(2) and the corresponding exponent is e
  // a0 = m*2^e
  // then the log? calculus is split in two parts (? being nothing: natural logarithm,  2: base 2 logarithm,
  //10 base ten logarithm)
  // as log?(a) = log?(2^e)+log?(m)
  // 1) computing log?(m)
  //   first put x = m-1 (so -0.29 <  x < 0.414)
  //   write log(m)   = log(1+x)   = x + x*x/2 + x*x*x*g(x)
  //   write log2(m)  = log2(1+x)  = C2*log(x),
  //     C2 = log(2)  the multiplication have to be taken seriously as C2 is not exact
  //   write log10(m) = log10(1+x) = C10*log(x),
  //     C10= log(10) the multiplication have to be taken seriously as C10 is not exact
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

namespace boost { namespace simd
{
  namespace detail
  {
    namespace bd = boost::dispatch;
    template < class A0 >
    struct logarithm< A0, tag::simd_type, float>
    {
      using int_type = bd::as_integer_t<A0, signed>;
      using sA0 = bd::scalar_of_t<A0>;
      using  kernel_t = kernel<A0, tag::simd_type, float>;

      static BOOST_FORCEINLINE A0 log(const A0& a0) BOOST_NOEXCEPT
      {
        A0 z = a0;
#ifndef BOOST_SIMD_NO_DENORMALS
        A0 t = Zero<A0>();
        auto denormal = is_less(bs::abs(z), Smallestposval<A0>());
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
        y = bs::fma(fe, Log_2lo<A0>(), y);
        y = bs::fma(Mhalf<A0>(), x2, y);
#ifdef BOOST_SIMD_NO_DENORMALS
        return finalize(a0, bs::fma(Log_2hi<A0>(), fe, x+y));
#else
        return finalize(a0, bs::fma(Log_2hi<A0>(), fe, x+y+t));
#endif
      }

      static BOOST_FORCEINLINE A0 log2(const A0& a0) BOOST_NOEXCEPT
      {
        A0 z =  a0;
#ifndef BOOST_SIMD_NO_DENORMALS
        auto denormal = is_less(bs::abs(z), Smallestposval<A0>());
        z = if_else(denormal, z*Twotonmb<A0>(), z);
        A0 t = if_else_zero(denormal, Mlog2two2nmb<A0>());
#endif
        //here let l2em1 = log2(e)-1, the computation is done as:
        //log2(a0) = ((l2em1*x+(l2em1*(y+x*x/2)))+(y+x*x/2)))+x+fe for best results
        // once again the order is very important.
        A0 x, fe, x2, y;
        kernel_t::log(z, fe, x, x2, y);
        y = bs::fma(Mhalf<A0>(),x2, y);
        z = bs::fma(x,Log2_em1<A0>(),y*Log2_em1<A0>());
#ifdef BOOST_SIMD_NO_DENORMALS
        return finalize(a0, ((z+y)+x)+fe);
#else
        return finalize(a0, ((z+y)+x)+fe+t);
#endif
      }

      static BOOST_FORCEINLINE A0 log10(const A0& a0) BOOST_NOEXCEPT
      {
        A0 z = a0;
#ifndef BOOST_SIMD_NO_DENORMALS
        auto denormal = is_less(bs::abs(z), Smallestposval<A0>());
        z = if_else(denormal, z*Twotonmb<A0>(), z);
        A0 t = if_else_zero(denormal, Mlog10two2nmb<A0>());
#endif
        // here there are two multiplication: log of fraction by log10(e) and base 2 exponent by log10(2)
        // and we have to split log10(e) and log10(2) in two parts to get extra precision when needed
        A0 x, fe, x2, y;
        kernel_t::log(z, fe, x, x2, y);
        y = bs::fma(x2, Mhalf<A0>(), y);
        z = (x+y)* Log10_elo<A0>();
        z = bs::fma(y, Log10_ehi<A0>(), z);
        z = bs::fma( x, Log10_ehi<A0>(), z);
        z = bs::fma(fe, Log10_2hi<A0>(), z);
#ifdef BOOST_SIMD_NO_DENORMALS
        return finalize(a0, bs::fma(fe, Log10_2lo<A0>(), z));
#else
        return finalize(a0, bs::fma(fe, Log10_2lo<A0>(), z+t));
#endif
      }
    private:
      static BOOST_FORCEINLINE A0 finalize(const A0& a0, const A0& y) BOOST_NOEXCEPT
      {
#ifdef BOOST_SIMD_NO_NANS
        auto test = bs::is_ltz(a0);
#else
        auto test = bs::logical_or(bs::is_ltz(a0), bs::is_nan(a0));
#endif
        A0 y1 = bs::if_nan_else(test, y);
#ifndef BOOST_SIMD_NO_INFINITIES
        y1 = if_else(bs::is_equal(a0, bs::Inf<A0>()), a0, y1);
#endif
        return if_else(is_eqz(a0), bs::Minf<A0>(), y1);
      }
    };
  }
} }

#endif

