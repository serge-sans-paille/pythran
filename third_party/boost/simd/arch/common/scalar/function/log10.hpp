//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_COMMON_SCALAR_FUNCTION_LOG10_HPP_INCLUDED
#define BOOST_SIMD_ARCH_COMMON_SCALAR_FUNCTION_LOG10_HPP_INCLUDED
#include <boost/simd/function/std.hpp>
#include <boost/simd/function/plain.hpp>

#include <boost/simd/function/log.hpp>
#include <boost/simd/arch/common/detail/tags.hpp>
#include <boost/simd/detail/dispatch/function/overload.hpp>
#include <boost/simd/detail/dispatch/meta/as_integer.hpp>
#include <boost/simd/function/musl.hpp>
#include <boost/config.hpp>
#include <cmath>
#include <boost/simd/constant/log_2olog_10.hpp>
#include <boost/simd/constant/invlog_10.hpp>
#include <boost/simd/function/nearbyint.hpp>
#include <boost/simd/function/is_flint.hpp>
#include <boost/simd/detail/constant/invlog_10hi.hpp>
#include <boost/simd/detail/constant/invlog_10lo.hpp>
#include <boost/simd/detail/constant/log10_2hi.hpp>
#include <boost/simd/detail/constant/log10_2lo.hpp>

namespace boost { namespace simd { namespace ext
{
  namespace bd = boost::dispatch;
  namespace bs = boost::simd;

  BOOST_DISPATCH_OVERLOAD ( log10_
                          , (typename A0)
                          , bd::cpu_
                          , bd::scalar_< bd::int_<A0> >
                          )
  {
    BOOST_FORCEINLINE A0 operator() ( A0 a0) const BOOST_NOEXCEPT
    {
      using ui_t = bd::as_integer_t<A0, unsigned>;
      BOOST_ASSERT_MSG( a0 > 0, "log10 is not defined for zero or negative integers." );
      return static_cast<A0>(log10(static_cast<ui_t>(a0)));
    }
  };
  BOOST_DISPATCH_OVERLOAD ( log10_
                          , (typename A0)
                          , bd::cpu_
                          , bd::scalar_< bd::uint8_<A0> >
                          )
  {
    BOOST_FORCEINLINE A0 operator() ( A0 a0) const BOOST_NOEXCEPT
    {
      return (a0 >= 100u) ? 2 :
             (a0 >= 10u)  ? 1 : 0;
    }
  };
  BOOST_DISPATCH_OVERLOAD ( log10_
                          , (typename A0)
                          , bd::cpu_
                          , bd::scalar_< bd::uint16_<A0> >
                          )
  {
    BOOST_FORCEINLINE A0 operator() ( A0 a0) const BOOST_NOEXCEPT
    {
      return (a0 >= 10000u) ? 4 :
             (a0 >= 1000u)  ? 3 :
             (a0 >= 100u)   ? 2 :
             (a0 >= 10u)    ? 1 : 0;
    }

  };
  BOOST_DISPATCH_OVERLOAD ( log10_
                          , (typename A0)
                          , bd::cpu_
                          , bd::scalar_< bd::uint32_<A0> >
                          )
  {
    BOOST_FORCEINLINE A0 operator() ( A0 a0) const BOOST_NOEXCEPT
    {
      return (a0 >= 1000000000u) ? 9 :
             (a0 >= 100000000u) ?  8 :
             (a0 >= 10000000u) ?   7 :
             (a0 >= 1000000u) ?    6 :
             (a0 >= 100000u) ?     5 :
             (a0 >= 10000u) ?      4 :
             (a0 >= 1000u) ?       3 :
             (a0 >= 100u) ?        2 :
             (a0 >= 10u) ?         1 : 0;
    }
  };
  BOOST_DISPATCH_OVERLOAD ( log10_
                          , (typename A0)
                          , bd::cpu_
                          , bd::scalar_< bd::uint64_<A0> >
                          )
  {
    BOOST_FORCEINLINE A0 operator() ( A0 a0) const BOOST_NOEXCEPT
    {
      return(a0 >= 10000000000000000000ull) ? 19 :
            (a0 >= 1000000000000000000ull) ?  18 :
            (a0 >= 100000000000000000ull) ?   17 :
            (a0 >= 10000000000000000ull) ?    16 :
            (a0 >= 1000000000000000ull) ?     15 :
            (a0 >= 100000000000000ull) ?      14 :
            (a0 >= 10000000000000ull) ?       13 :
            (a0 >= 1000000000000ull) ?        12 :
            (a0 >= 100000000000ull) ?         11 :
            (a0 >= 10000000000ull) ?          10 :
            (a0 >= 1000000000ull) ?            9 :
            (a0 >= 100000000ull) ?             8 :
            (a0 >= 10000000ull) ?              7 :
            (a0 >= 1000000ull) ?               6 :
            (a0 >= 100000ull) ?                5 :
            (a0 >= 10000ull) ?                 4 :
            (a0 >= 1000ull) ?                  3 :
            (a0 >= 100ull) ?                   2 :
            (a0 >= 10ull) ?                    1 : 0;
    }
  };
  BOOST_DISPATCH_OVERLOAD ( log10_
                          , (typename A0)
                          , bd::cpu_
                          , bs::std_tag
                          , bd::scalar_< bd::floating_<A0> >
                          )
  {
    BOOST_FORCEINLINE A0 operator() (const std_tag &, A0 a0) const BOOST_NOEXCEPT
    {
      return std::log10(a0);
    }
  };

  BOOST_DISPATCH_OVERLOAD ( log10_
                          , (typename A0)
                          , bd::cpu_
                          , bs::plain_tag
                          , bd::scalar_< bd::floating_<A0> >
                          )
  {
    BOOST_FORCEINLINE A0 operator() (const plain_tag &, A0 a0) const BOOST_NOEXCEPT
    {
      return musl_(log10)(a0);
    }
  };

  BOOST_DISPATCH_OVERLOAD ( log10_
                          , (typename A0)
                          , bd::cpu_
                          , bd::scalar_< bd::floating_<A0> >
                          )
  {
    BOOST_FORCEINLINE A0 operator() ( A0 a0) const BOOST_NOEXCEPT
    {
      return musl_(log10)(a0);
    }
  };

  BOOST_DISPATCH_OVERLOAD ( log10_
                          , (typename A0)
                          , bd::cpu_
                          , bs::std_tag
                          , bd::scalar_< bd::arithmetic_<A0> >
                          )
  {
    BOOST_FORCEINLINE A0 operator() (const std_tag &, A0 a0
                                    ) const BOOST_NOEXCEPT
    {
      return musl_(log10(a0));
    }
  };

  BOOST_DISPATCH_OVERLOAD ( log10_
                          , (typename A0)
                          , bd::cpu_
                          , bs::musl_tag
                          , bd::scalar_< bd::single_<A0> >
                          )
  {
  /* origin: FreeBSD /usr/src/lib/msun/src/e_log10f.c */
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
      A0 hfsq = Half<A0>()*sqr(f);
//      return -(hfsq-(s*(hfsq+R))-f)*Invlog_10<A0>()+k*Log_2olog_10<A0>(); // fast ?

      A0 hibits = f - hfsq;
      hibits =  bitwise_and(hibits, uiA0(0xfffff000ul));
      A0  lobits = fma(s, hfsq+R, f - hibits - hfsq);
      A0 dk = k;
//      return ((((dk*Log10_2lo<A0> + (lobits+hibits)*Invlog_10lo<A0>()) + lobits*Invlog_10hi<A0>()) + hibits*Invlog_10hi<A0>()) + dk*Log10_2hi<A0>());
      return fma(dk, Log10_2hi<A0>(),
                 fma(hibits, Invlog_10hi<A0>(),
                     (fma(lobits, Invlog_10hi<A0>(),
                          fma(lobits+hibits, Invlog_10lo<A0>(), dk*Log10_2lo<A0>())
                         )
                     )
                    )
                );
    }
  };

  BOOST_DISPATCH_OVERLOAD ( log10_
                          , (typename A0)
                          , bd::cpu_
                          , bs::musl_tag
                          , bd::scalar_< bd::double_<A0> >
                          )
  {
    /* origin: FreeBSD /usr/src/lib/msun/src/e_log10.c */
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
//       const A0
//         Invlog_10hi<A0>()  = 4.34294481878168880939e-01, /* 0x3fdbcb7b, 0x15200000 */
//         Invlog_10lo<A0>()  = 2.50829467116452752298e-11, /* 0x3dbb9438, 0xca9aadd5 */
//         Log10_2hi<A0>() = 3.01029995663611771306e-01, /* 0x3FD34413, 0x509F6000 */
//         Log10_2lo<A0> = 3.69423907715893078616e-13; /* 0x3D59FEF3, 0x11F12B36 */
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
        k -= 54;
        x *= 18014398509481984.0;
        hx = bitwise_cast<uiA0>(x) >> 32;
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
      A0 hfsq = Half<A0>()*sqr(f);
      A0 s = f/(2.0f + f);
      A0 z = sqr(s);
      A0 w = sqr(z);
      A0 t1= w*horn<A0, 0x3fd999999997fa04ll, 0x3fcc71c51d8e78afll, 0x3fc39a09d078c69fll > (w);
      A0 t2= z*horn<A0, 0x3fe5555555555593ll, 0x3fd2492494229359ll
                      , 0x3fc7466496cb03dell, 0x3fc2f112df3e5244ll> (w);
      A0 R = t2 + t1;
      A0 dk = k;
      //          return -(hfsq-(s*(hfsq+R))-f)*Invlog_10<A0>()+dk*Log_2olog_10<A0>(); //fast ?

      A0  hi = f - hfsq;
      hi =  bitwise_and(hi, (Allbits<uiA0>() << 32));

      A0 lo = f - hi - hfsq + s*(hfsq+R);

      /* val_hi+val_lo ~ log10(1+f) + k*log10(2) */
      A0 val_hi = hi*Invlog_10hi<A0>();
      A0 y = dk*Log10_2hi<A0>();
      A0 val_lo = fma(dk, Log10_2lo<A0>(),  fma(lo+hi, Invlog_10lo<A0>(),  lo*Invlog_10hi<A0>()));

//       /*
//        * Extra precision in for adding y is not strictly needed
//        * since there is no very large cancellation near x = sqrt(2) or
//        * x = 1/sqrt(2), but we do it anyway since it costs little on CPUs
//        * with some parallelism and it reduces the error for many args.
//        */
      A0 w1 = y + val_hi;
      val_lo += (y - w1) + val_hi;
      val_hi = w1;

      return val_lo + val_hi;
    }
  };

} } }


#endif

