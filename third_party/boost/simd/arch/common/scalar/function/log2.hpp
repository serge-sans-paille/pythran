//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_COMMON_SCALAR_FUNCTION_LOG2_HPP_INCLUDED
#define BOOST_SIMD_ARCH_COMMON_SCALAR_FUNCTION_LOG2_HPP_INCLUDED
#include <boost/simd/function/std.hpp>

#include <boost/simd/detail/dispatch/function/overload.hpp>
#include <boost/simd/function/musl.hpp>
#include <boost/simd/function/std.hpp>
#include <boost/assert.hpp>
#include <boost/config.hpp>
#include <cmath>
#include <boost/simd/function/bitwise_and.hpp>
#include <boost/simd/function/dec.hpp>
#include <boost/simd/function/fma.hpp>
#include <boost/simd/function/frexp.hpp>
#include <boost/simd/function/horn.hpp>
#include <boost/simd/function/ilog2.hpp>
#include <boost/simd/function/musl.hpp>
#include <boost/simd/function/plain.hpp>
#include <boost/simd/function/sqr.hpp>
#include <boost/simd/function/std.hpp>

#include <boost/simd/constant/inf.hpp>
#include <boost/simd/constant/invlog_2.hpp>
#include <boost/simd/constant/nan.hpp>
#include <boost/simd/constant/minf.hpp>
#include <boost/simd/constant/smallestposval.hpp>
#include <boost/simd/constant/sqrt_2o_2.hpp>

#include <boost/simd/detail/constant/invlog_2hi.hpp>
#include <boost/simd/detail/constant/invlog_2lo.hpp>

#include <boost/simd/detail/dispatch/meta/as_integer.hpp>

#include <cmath>
namespace boost { namespace simd { namespace ext
{
  namespace bd = boost::dispatch;
  namespace bs = boost::simd;

  BOOST_DISPATCH_OVERLOAD ( log2_
                          , (typename A0)
                          , bd::cpu_
                          , bd::scalar_< bd::floating_<A0> >
                          )
  {
    BOOST_FORCEINLINE A0 operator() (A0 const& a0) const BOOST_NOEXCEPT
    {
      return musl_(log2)(a0);
    }
  };

  BOOST_DISPATCH_OVERLOAD ( log2_
                          , (typename A0)
                          , bd::cpu_
                          , bd::scalar_< bd::arithmetic_<A0> >
                          )
  {
    BOOST_FORCEINLINE A0 operator() (A0 const& a0) const BOOST_NOEXCEPT
    {
      return bs::ilog2(a0);
    }
  };

  BOOST_DISPATCH_OVERLOAD ( log2_
                          , (typename A0)
                          , bd::cpu_
                          , bs::std_tag
                          , bd::scalar_< bd::arithmetic_<A0> >
                          )
  {
    BOOST_FORCEINLINE A0 operator() (const std_tag &, A0 a0
                                    ) const BOOST_NOEXCEPT
    {
      return std::log2(a0);
    }
  };

  BOOST_DISPATCH_OVERLOAD ( log2_
                          , (typename A0)
                          , bd::cpu_
                          , bs::plain_tag
                          , bd::scalar_< bd::arithmetic_<A0> >
                          )
  {
    BOOST_FORCEINLINE A0 operator() (const std_tag &, A0 a0
                                    ) const BOOST_NOEXCEPT
    {
      return musl_(log2(a0));
    }
  };

  BOOST_DISPATCH_OVERLOAD ( log2_
                          , (typename A0)
                          , bd::cpu_
                          , bs::musl_tag
                          , bd::scalar_< bd::single_<A0> >
                          )
  {
    /* origin: FreeBSD /usr/src/lib/msun/src/e_log2f.c */
    /*
     * ====================================================
     * Copyright (C) 1993 by Sun Microsystems, Inc. All rights reserved.
     *
     * Developed at SunPro, a Sun Microsystems, Inc. business.
     * Permission to use, copy, modify, and distribute this
     * software is freely granted, provided that this notice
     * is preserved.
     * ====================================================
     */
     BOOST_FORCEINLINE A0 operator() (const musl_tag &, A0 x) const BOOST_NOEXCEPT
    {
      using uiA0 = bd::as_integer_t<A0, unsigned>;
      using iA0 = bd::as_integer_t<A0,   signed>;
      uiA0 ix = bitwise_cast<uiA0>(x);
      iA0 k = 0;
      if (ix < 0x00800000 || ix>>31)         /* x < 2**-126  */
      {
        if (ix<<1 == 0) return Minf<A0>();  /* log(+-0)=-inf */
        if (ix>>31) return Nan<A0>();       /* log(-#) = NaN */
#ifndef BOOST_SIMD_NO_DENORMALS
        /* subnormal number, scale up x */
        k -= 25;
        x *= 33554432.0f;
         ix = bitwise_cast<iA0>(x);
#endif
      }
      else if (ix >= 0x7f800000)
      {
        return x;
      }
      else if (ix == 0x3f800000)
        return 0;

      /* reduce x into [sqrt(2)/2, sqrt(2)] */
      ix += 0x3f800000 - 0x3f3504f3;
      k += bitwise_cast<iA0>(ix>>23) - 0x7f;
      ix = (ix&0x007fffff) + 0x3f3504f3;
      x =  bitwise_cast<A0>(ix);
      A0 f = dec(x);
      A0 s = f/(2.0f + f);
      A0 z = sqr(s);
      A0 w = sqr(z);
      A0 t1= w*horn<A0, 0x3eccce13, 0x3e789e26>(w);
      A0 t2= z*horn<A0, 0x3f2aaaaa, 0x3e91e9ee>(w);
      A0 R = t2 + t1;
      A0 hfsq = 0.5f*sqr(f);
      return -(hfsq-(s*(hfsq+R))-f)*Invlog_2<A0>()+k;
      // The original algorithm does some extra calculation in place of the return line
      // to get extra precision but this is uneeded for float as the exhaustive test shows
      // a 0.5 ulp maximal error on the full range.
      // Moreover all log2(exp2(i)) i =  1..31 are flint
      // I leave the code here in case an exotic proc will not play the game.
      //       A0  hi = f - hfsq;
      //       hi =  bitwise_and(hi, uiA0(0xfffff000ul));
      //       A0  lo = fma(s, hfsq+R, f - hi - hfsq);
      //       return fma((lo+hi), Invlog_2lo<A0>(), lo*Invlog_2hi<A0>() + hi*Invlog_2hi<A0>() + k);
    }
  };

  BOOST_DISPATCH_OVERLOAD ( log2_
                          , (typename A0)
                          , bd::cpu_
                          , bs::musl_tag
                          , bd::scalar_< bd::double_<A0> >
                          )
  {
    /* origin: FreeBSD /usr/src/lib/msun/src/e_log2.c */
    /*
     * ====================================================
     * Copyright (C) 1993 by Sun Microsystems, Inc. All rights reserved.
     *
     * Developed at SunSoft, a Sun Microsystems, Inc. business.
     * Permission to use, copy, modify, and distribute this
     * software is freely granted, provided that this notice
     * is preserved.
     * ====================================================
     */
    BOOST_FORCEINLINE A0 operator() (const musl_tag &, A0 x) const BOOST_NOEXCEPT
    {
      using uiA0 = bd::as_integer_t<A0, unsigned>;
      using iA0 = bd::as_integer_t<A0,   signed>;
      uiA0 hx = bitwise_cast<uiA0>(x) >> 32;
      iA0 k = 0;
      if (hx < 0x00100000 || hx>>31)
      {
        if(is_eqz(x))
          return Minf<A0>();  /* log(+-0)=-inf */
        if (hx>>31)
          return Nan<A0>(); /* log(-#) = NaN */
        /* subnormal number, scale x up */
#ifndef BOOST_SIMD_NO_DENORMALS
        k -= 54;
        x *=  18014398509481984.0;
        hx = bitwise_cast<uiA0>(x) >> 32;
#endif
      }
      else if (hx >= 0x7ff00000)
      {
        return x;
      }
      else if (x == One<A0>())
        return Zero<A0>();
      /* reduce x into [sqrt(2)/2, sqrt(2)] */
      hx += 0x3ff00000 - 0x3fe6a09e;
      k += bitwise_cast<iA0>(hx>>20) - 0x3ff;
      hx = (hx&0x000fffff) + 0x3fe6a09e;
      x = bitwise_cast<A0>( (uint64_t)hx<<32 | (bitwise_and(0xffffffffull, bitwise_cast<uiA0>(x))));
      A0 f = dec(x);
      A0 hfsq = 0.5*sqr(f);
      A0 s = f/(2.0f + f);
      A0 z = sqr(s);
      A0 w = sqr(z);
      A0 t1= w*horn<A0, 0x3fd999999997fa04ll, 0x3fcc71c51d8e78afll, 0x3fc39a09d078c69fll > (w);
      A0 t2= z*horn<A0, 0x3fe5555555555593ll, 0x3fd2492494229359ll
                      , 0x3fc7466496cb03dell, 0x3fc2f112df3e5244ll> (w);
      A0 R = t2 + t1;
//        return -(hfsq-(s*(hfsq+R))-f)*Invlog_2<A0>()+dk;  // fast ?


      /*
       * f-hfsq must (for args near 1) be evaluated in extra precision
       * to avoid a large cancellation when x is near sqrt(2) or 1/sqrt(2).
       * This is fairly efficient since f-hfsq only depends on f, so can
       * be evaluated in parallel with R.  Not combining hfsq with R also
       * keeps R small (though not as small as a true `lo' term would be),
       * so that extra precision is not needed for terms involving R.
       *
       * Compiler bugs involving extra precision used to break Dekker's
       * theorem for spitting f-hfsq as hi+lo, unless double_t was used
       * or the multi-precision calculations were avoided when double_t
       * has extra precision.  These problems are now automatically
       * avoided as a side effect of the optimization of combining the
       * Dekker splitting step with the clear-low-bits step.
       *
       * y must (for args near sqrt(2) and 1/sqrt(2)) be added in extra
       * precision to avoid a very large cancellation when x is very near
       * these values.  Unlike the above cancellations, this problem is
       * specific to base 2.  It is strange that adding +-1 is so much
       * harder than adding +-ln2 or +-log10_2.
       *
       * This uses Dekker's theorem to normalize y+val_hi, so the
       * compiler bugs are back in some configurations, sigh.  And I
       * don't want to used double_t to avoid them, since that gives a
       * pessimization and the support for avoiding the pessimization
       * is not yet available.
       *
       * The multi-precision calculations for the multiplications are
       * routine.
       */

      /* hi+lo = f - hfsq + s*(hfsq+R) ~ log(1+f) */
      A0  hi = f - hfsq;
      hi =  bitwise_and(hi, (Allbits<uiA0>() << 32));
      A0 lo = f - hi - hfsq + s*(hfsq+R);

      A0 val_hi = hi*Invlog_2hi<A0>();
      A0 val_lo = fma(lo+hi, Invlog_2lo<A0>(), lo*Invlog_2hi<A0>());

      A0 dk = k;
      A0 w1 = dk + val_hi;
      val_lo += (dk - w1) + val_hi;
      val_hi = w1;
      return val_lo + val_hi;
    }
  };

  BOOST_DISPATCH_OVERLOAD ( log2_
                          , (typename A0)
                          , bd::cpu_
                          , bs::plain_tag
                          , bd::scalar_< bd::floating_<A0> >
                          )
  {
    BOOST_FORCEINLINE A0 operator() (const plain_tag &, A0 x) const BOOST_NOEXCEPT
    {
      return musl_(log2)(x); //the "plain" version of the algorithm is never speedier than the "musl" version.
      // the call is here to allow a scalar fallback to simd calls
    }
  };

} } }


#endif
