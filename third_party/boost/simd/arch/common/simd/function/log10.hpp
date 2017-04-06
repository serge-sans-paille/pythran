//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_COMMON_SIMD_FUNCTION_LOG10_HPP_INCLUDED
#define BOOST_SIMD_ARCH_COMMON_SIMD_FUNCTION_LOG10_HPP_INCLUDED

#include <boost/simd/detail/assert_utils.hpp>
#include <boost/simd/function/frexp.hpp>
#include <boost/simd/function/if_else.hpp>
#include <boost/simd/function/if_minus.hpp>
#include <boost/simd/function/if_dec.hpp>
#include <boost/simd/function/if_else_zero.hpp>
#include <boost/simd/function/if_nan_else.hpp>
#include <boost/simd/function/is_not_nan.hpp>
#include <boost/simd/function/is_positive.hpp>
#include <boost/simd/function/is_lez.hpp>
#include <boost/simd/function/is_ngez.hpp>
#include <boost/simd/function/any.hpp>
#include <boost/simd/arch/common/detail/tags.hpp>
#include <boost/simd/detail/dispatch/function/overload.hpp>
#include <boost/config.hpp>

namespace boost { namespace simd { namespace ext
{
  namespace bd = boost::dispatch;
  namespace bs = boost::simd;
  BOOST_DISPATCH_OVERLOAD_IF ( log10_
                          , (typename A0, typename X)
                          , (detail::is_native<X>)
                          , bd::cpu_
                          , bs::pack_< bd::single_<A0>, X>
                          )
  {
    BOOST_FORCEINLINE A0 operator() ( A0 const& a0) const BOOST_NOEXCEPT
    {
      return musl_(log10)(a0);
    }
  };

  BOOST_DISPATCH_OVERLOAD_IF ( log10_
                          , (typename A0, typename X)
                          , (detail::is_native<X>)
                          , bd::cpu_
                          , bs::pack_< bd::double_<A0>, X>
                          )
  {
    BOOST_FORCEINLINE A0 operator() ( A0 const& a0) const BOOST_NOEXCEPT
    {
      return musl_(log10)(a0);
    }
  };
  BOOST_DISPATCH_OVERLOAD_IF ( log10_
                          , (typename A0, typename X)
                          , (detail::is_native<X>)
                          , bd::cpu_
                          , bs::musl_tag
                          , bs::pack_< bd::single_<A0>, X>
                          )
  {
    BOOST_FORCEINLINE A0 operator() (const musl_tag &, const A0& a0) const BOOST_NOEXCEPT
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
       const A0
        ivln10hi ( 4.3432617188e-01), /* 0x3ede6000 */
        ivln10lo (-3.1689971365e-05), /* 0xb804ead9 */
        log10_2hi( 3.0102920532e-01), /* 0x3e9a2080 */
        log10_2lo( 7.9034151668e-07); /* 0x355427db */
      using uiA0 = bd::as_integer_t<A0, unsigned>;
      using iA0 = bd::as_integer_t<A0,   signed>;
      A0 x = a0;
      iA0 k(0);
      auto isnez = is_nez(a0);
#ifndef BOOST_SIMD_NO_DENORMALS
      auto test = is_less(a0, Smallestposval<A0>())&&isnez;
      if (any(test))
      {
        k = if_minus(test, k, iA0(25));
        x = if_else(test, x*A0(33554432ul), x); //2^25
      }
#endif
      uiA0 ix = bitwise_cast<uiA0>(x);
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
      A0 dk = tofloat(k);
      A0 hfsq = Half<A0>()*sqr(f);

      A0  hibits = f - hfsq;
      hibits =  bitwise_and(hibits, uiA0(0xfffff000ul));
      A0  lobits = fma(s, hfsq+R, f - hibits - hfsq);
//      A0 r = ((((dk*log10_2lo + (lobits+hibits)*ivln10lo) + lobits*ivln10hi) + hibits*ivln10hi) + dk*log10_2hi);
      A0 r = fma(dk, log10_2hi,
                 fma(hibits, ivln10hi,
                     fma(lobits, ivln10hi,
                         fma(lobits+hibits, ivln10lo, dk*log10_2lo)
                        )
                    )
                );

#ifndef BOOST_SIMD_NO_INFINITIES
      A0 zz = if_else(isnez, if_else(a0 == Inf<A0>(), Inf<A0>(), r), Minf<A0>());
#else
      A0 zz = if_else(isnez, r, Minf<A0>());
#endif
      return if_nan_else(is_ngez(a0), zz);
    }
  };

  BOOST_DISPATCH_OVERLOAD_IF ( log10_
                             , (typename A0, typename X)
                             , (detail::is_native<X>)
                             , bd::cpu_
                             , bs::musl_tag
                             , bs::pack_< bd::double_<A0>, X>
                             )
  {
    BOOST_FORCEINLINE A0 operator() (const musl_tag &, const A0& a0) const BOOST_NOEXCEPT
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
      const A0
        ivln10hi (4.34294481878168880939e-01), /* 0x3fdbcb7b, 0x15200000 */
        ivln10lo (2.50829467116452752298e-11), /* 0x3dbb9438, 0xca9aadd5 */
        log10_2hi(3.01029995663611771306e-01), /* 0x3FD34413, 0x509F6000 */
        log10_2lo(3.69423907715893078616e-13); /* 0x3D59FEF3, 0x11F12B36 */
      using uiA0 = bd::as_integer_t<A0, unsigned>;
      using iA0 = bd::as_integer_t<A0,   signed>;
      A0 x = a0;
      uiA0 hx = bitwise_cast<uiA0>(x) >> 32;
      iA0 k(0);
      auto isnez = is_nez(a0);

#ifndef BOOST_SIMD_NO_DENORMALS
      auto test = is_less(a0, Smallestposval<A0>())&&isnez;
      if (any(test))
      {
        k = if_minus(test, k, iA0(54));
        x = if_else(test, x*A0(18014398509481984ull), x); //2^54
      }
#endif
      /* reduce x into [sqrt(2)/2, sqrt(2)] */
      hx += 0x3ff00000 - 0x3fe6a09e;
      k += bitwise_cast<iA0>(hx>>20) - 0x3ff;
      hx = (hx&0x000fffff) + 0x3fe6a09e;
      x = bitwise_cast<A0>(hx<<32 | (bitwise_and(0xffffffffull, bitwise_cast<uiA0>(x))));

      A0 f = dec(x);
      A0 dk = tofloat(k);
      A0 s = f/(2.0f + f);
      A0 z = sqr(s);
      A0 w = sqr(z);
      A0 t1= w*horn<A0, 0x3fd999999997fa04ll, 0x3fcc71c51d8e78afll, 0x3fc39a09d078c69fll > (w);
      A0 t2= z*horn<A0, 0x3fe5555555555593ll, 0x3fd2492494229359ll
                      , 0x3fc7466496cb03dell, 0x3fc2f112df3e5244ll> (w);
      A0 R = t2 + t1;
      A0 hfsq = Half<A0>()*sqr(f);
      //      A0 r = -(hfsq-(s*(hfsq+R))-f)*Invlog_10<A0>()+dk*Log_2olog_10<A0>(); // fast ?

      /* hi+lo = f - hfsq + s*(hfsq+R) ~ log(1+f) */
      A0  hi = f - hfsq;
      hi =  bitwise_and(hi, (Allbits<uiA0>() << 32));
      A0 lo = f - hi - hfsq + s*(hfsq+R);

      A0 val_hi = hi*ivln10hi;
      A0  y = dk*log10_2hi;
      A0  val_lo = dk*log10_2lo + (lo+hi)*ivln10lo + lo*ivln10hi;


//       /*
//        * Extra precision in for adding y is not strictly needed
//        * since there is no very large cancellation near x = sqrt(2) or
//        * x = 1/sqrt(2), but we do it anyway since it costs little on CPUs
//        * with some parallelism and it reduces the error for many args.
//        */
      A0 w1 = y + val_hi;
      val_lo += (y - w1) + val_hi;
      val_hi = w1;

      A0 r =  val_lo + val_hi;
#ifndef BOOST_SIMD_NO_INFINITIES
      A0 zz = if_else(isnez, if_else(a0 == Inf<A0>(), Inf<A0>(), r), Minf<A0>());
#else
      A0 zz = if_else(isnez, r, Minf<A0>());
#endif
      return if_nan_else(is_ngez(a0), zz);
    }
  };

  BOOST_DISPATCH_OVERLOAD_IF ( log10_
                          , (typename A0, typename X)
                          , (detail::is_native<X>)
                          , bd::cpu_
                          , bs::plain_tag
                          , bs::pack_< bd::single_<A0>, X>
                          )
  {
    BOOST_FORCEINLINE A0 operator() (const plain_tag &, const A0& a0) const BOOST_NOEXCEPT
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
       const A0
        ivln10hi ( 4.3432617188e-01), /* 0x3ede6000 */
        ivln10lo (-3.1689971365e-05), /* 0xb804ead9 */
        log10_2hi( 3.0102920532e-01), /* 0x3e9a2080 */
        log10_2lo( 7.9034151668e-07); /* 0x355427db */
      using uiA0 = bd::as_integer_t<A0, unsigned>;
      A0 x = a0;
      A0 dk = Zero<A0>();
      auto isnez = is_nez(a0);
#ifndef BOOST_SIMD_NO_DENORMALS
      auto test = is_less(a0, Smallestposval<A0>())&&isnez;
      if (any(test))
      {
        dk = if_minus(test, dk, A0(25));
        x = if_else(test, x*A0(33554432ul), x);
      }
#endif
      /* reduce x into [sqrt(2)/2, sqrt(2)] */
      A0 kk;
      std::tie(x, kk) = frexp(a0);
      auto  x_lt_sqrthf = (is_greater(Sqrt_2o_2<A0>(), x));
      dk += if_dec(x_lt_sqrthf, kk);
      A0 f = dec(x+if_else_zero(x_lt_sqrthf, x));
      A0 s = f/(2.0f + f);
      A0 z = sqr(s);
      A0 w = sqr(z);
      A0 t1= w*horn<A0, 0x3eccce13, 0x3e789e26>(w);
      A0 t2= z*horn<A0, 0x3f2aaaaa, 0x3e91e9ee>(w);
      A0 R = t2 + t1;
      A0 hfsq = Half<A0>()*sqr(f);

      A0  hi = f - hfsq;
      hi =  bitwise_and(hi, uiA0(0xfffff000ul));
      A0  lo = fma(s, hfsq+R, f - hi - hfsq);
      A0 r = fma(dk, log10_2hi,
                 fma(hi, ivln10hi,
                     fma(lo, ivln10hi,
                         fma(lo+hi, ivln10lo, dk*log10_2lo)
                        )
                    )
                );

#ifndef BOOST_SIMD_NO_INFINITIES
      A0 zz = if_else(isnez, if_else(a0 == Inf<A0>(), Inf<A0>(), r), Minf<A0>());
#else
      A0 zz = if_else(isnez, r, Minf<A0>());
#endif
      return if_nan_else(is_ngez(a0), zz);
    }
  };

  BOOST_DISPATCH_OVERLOAD_IF ( log10_
                             , (typename A0, typename X)
                             , (detail::is_native<X>)
                             , bd::cpu_
                             , bs::plain_tag
                             , bs::pack_< bd::double_<A0>, X>
                             )
  {
    BOOST_FORCEINLINE A0 operator() (const plain_tag &, const A0& a0) const BOOST_NOEXCEPT
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
      const A0
        ivln10hi (4.34294481878168880939e-01), /* 0x3fdbcb7b, 0x15200000 */
        ivln10lo (2.50829467116452752298e-11), /* 0x3dbb9438, 0xca9aadd5 */
        log10_2hi(3.01029995663611771306e-01), /* 0x3FD34413, 0x509F6000 */
        log10_2lo(3.69423907715893078616e-13); /* 0x3D59FEF3, 0x11F12B36 */
      using uiA0 = bd::as_integer_t<A0, unsigned>;
      A0 x = a0;
      A0 dk = Zero<A0>();
      auto isnez = is_nez(a0);

#ifndef BOOST_SIMD_NO_DENORMALS
      auto test = is_less(a0, Smallestposval<A0>())&&isnez;
      if (any(test))
      {
        dk = if_minus(test, dk, A0(54));
        x = if_else(test, x*A0(18014398509481984ull), x);
      }
#endif
      /* reduce x into [sqrt(2)/2, sqrt(2)] */
      A0 kk;
      std::tie(x, kk) = frexp(a0);
      auto  x_lt_sqrthf = (is_greater(Sqrt_2o_2<A0>(), x));
      dk += if_dec(x_lt_sqrthf, kk);
      A0 f = dec(x+if_else_zero(x_lt_sqrthf, x));
      A0 s = f/(2.0f + f);
      A0 z = sqr(s);
      A0 w = sqr(z);
      A0 t1= w*horn<A0, 0x3fd999999997fa04ll, 0x3fcc71c51d8e78afll, 0x3fc39a09d078c69fll > (w);
      A0 t2= z*horn<A0, 0x3fe5555555555593ll, 0x3fd2492494229359ll
                      , 0x3fc7466496cb03dell, 0x3fc2f112df3e5244ll> (w);
      A0 R = t2 + t1;
      A0 hfsq = Half<A0>()*sqr(f);
      A0  hi = f - hfsq;
      hi =  bitwise_and(hi, (Allbits<uiA0>() << 32));
      A0 lo = f - hi - hfsq + s*(hfsq+R);

      A0 val_hi = hi*ivln10hi;
      A0  y = dk*log10_2hi;
      A0  val_lo = dk*log10_2lo + (lo+hi)*ivln10lo + lo*ivln10hi;


//       /*
//        * Extra precision in for adding y is not strictly needed
//        * since there is no very large cancellation near x = sqrt(2) or
//        * x = 1/sqrt(2), but we do it anyway since it costs little on CPUs
//        * with some parallelism and it reduces the error for many args.
//        */
      A0 w1 = y + val_hi;
      val_lo += (y - w1) + val_hi;
      val_hi = w1;

      A0 r =  val_lo + val_hi;
#ifndef BOOST_SIMD_NO_INFINITIES
      A0 zz = if_else(isnez, if_else(a0 == Inf<A0>(), Inf<A0>(), r), Minf<A0>());
#else
      A0 zz = if_else(isnez, r, Minf<A0>());
#endif
      return if_nan_else(is_ngez(a0), zz);
    }
  };

} } }

#endif
