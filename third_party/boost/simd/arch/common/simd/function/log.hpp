//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_COMMON_SIMD_FUNCTION_LOG_HPP_INCLUDED
#define BOOST_SIMD_ARCH_COMMON_SIMD_FUNCTION_LOG_HPP_INCLUDED

#include <boost/simd/detail/dispatch/function/overload.hpp>
#include <boost/config.hpp>

#include <boost/simd/function/any.hpp>
#include <boost/simd/function/bitwise_and.hpp>
#include <boost/simd/function/bitwise_cast.hpp>
#include <boost/simd/function/dec.hpp>
#include <boost/simd/function/fma.hpp>
#include <boost/simd/function/frexp.hpp>
#include <boost/simd/function/horn.hpp>
#include <boost/simd/function/if_else.hpp>
#include <boost/simd/function/if_minus.hpp>
#include <boost/simd/function/if_dec.hpp>
#include <boost/simd/function/if_else_zero.hpp>
#include <boost/simd/function/if_nan_else.hpp>
#include <boost/simd/function/is_ngez.hpp>
#include <boost/simd/function/is_nez.hpp>
#include <boost/simd/function/musl.hpp>
#include <boost/simd/function/plain.hpp>
#include <boost/simd/function/sqr.hpp>
#include <boost/simd/function/tofloat.hpp>

#include <boost/simd/constant/half.hpp>
#include <boost/simd/constant/inf.hpp>
#include <boost/simd/constant/minf.hpp>
#include <boost/simd/constant/smallestposval.hpp>
#include <boost/simd/constant/sqrt_2o_2.hpp>
#include <boost/simd/constant/two.hpp>

#include <boost/simd/detail/constant/log_2hi.hpp>
#include <boost/simd/detail/constant/log_2lo.hpp>

#include <boost/simd/detail/dispatch/meta/as_integer.hpp>

////////////////////////////////////////////////////////////////////////////////////
// Two implementations are given "musl_" and "plain_"
// They differ by the reduction step.
// The "plain" implementation of log is mainly for avx,  because avx does not have
// good support for integral vector types. "plain" uses frexp instead of ifrexp to run
// all the process with floting vector types
// The correct dispatch of log is done in each architecture related file or
// default to musl_
////////////////////////////////////////////////////////////////////////////////////

namespace boost { namespace simd { namespace ext
{
  namespace bd = boost::dispatch;
  namespace bs = boost::simd;


  BOOST_DISPATCH_OVERLOAD_IF ( log_
                          , (typename A0, typename X)
                          , (detail::is_native<X>)
                          , bd::cpu_
                          , bs::pack_< bd::single_<A0>, X>
                          )
  {
    BOOST_FORCEINLINE A0 operator() (A0 const & a0) const BOOST_NOEXCEPT
    {
      return musl_(log)(a0);
    }
  };

  BOOST_DISPATCH_OVERLOAD_IF ( log_
                          , (typename A0, typename X)
                          , (detail::is_native<X>)
                          , bd::cpu_
                          , bs::pack_< bd::double_<A0>, X>
                          )
  {
    BOOST_FORCEINLINE A0 operator() (A0 const & a0) const BOOST_NOEXCEPT
    {
      return musl_(log)(a0);
    }
  };
  BOOST_DISPATCH_OVERLOAD_IF ( log_
                          , (typename A0, typename X)
                          , (detail::is_native<X>)
                          , bd::cpu_
                          , bs::musl_tag
                          , bs::pack_< bd::single_<A0>, X>
                          )
  {
    BOOST_FORCEINLINE A0 operator() (const musl_tag &, const A0& a0) const BOOST_NOEXCEPT
    {
      using uiA0 = bd::as_integer_t<A0, unsigned>;
      using iA0 = bd::as_integer_t<A0,   signed>;
      A0 x =  a0;
      iA0 k(0);
      auto isnez = is_nez(a0);
#ifndef BOOST_SIMD_NO_DENORMALS
      auto test = is_less(a0, Smallestposval<A0>())&&isnez;
      if (any(test))
      {
        k = if_minus(test, k, iA0(23));
        x = if_else(test, x*A0(8388608ul), x);
      }
#endif
      uiA0 ix = bitwise_cast<uiA0>(x);
      /* reduce x into [sqrt(2)/2, sqrt(2)] */
      ix += 0x3f800000 - 0x3f3504f3;
      k += bitwise_cast<iA0>(ix>>23) - 0x7f;
      ix = (ix&0x007fffff) + 0x3f3504f3;
      x =  bitwise_cast<A0>(ix);
      A0 f = dec(x);
      A0 s = f/(Two<A0>() + f);
      A0 z = sqr(s);
      A0 w = sqr(z);
      A0 t1= w*horn<A0, 0x3eccce13, 0x3e789e26>(w);
      A0 t2= z*horn<A0, 0x3f2aaaaa, 0x3e91e9ee>(w);
      A0 R = t2 + t1;

      A0 hfsq = Half<A0>()*sqr(f);
      A0 dk = tofloat(k);
      A0 r = fma(dk, Log_2hi<A0>(), ((fma(s, (hfsq+R), dk*Log_2lo<A0>()) - hfsq) + f));
#ifndef BOOST_SIMD_NO_INFINITIES
      A0 zz = if_else(isnez, if_else(a0 == Inf<A0>(), Inf<A0>(), r), Minf<A0>());
#else
      A0 zz = if_else(isnez, r, Minf<A0>());
#endif
      return if_nan_else(is_ngez(a0), zz);
    }
  };

  BOOST_DISPATCH_OVERLOAD_IF ( log_
                             , (typename A0, typename X)
                             , (detail::is_native<X>)
                             , bd::cpu_
                             , bs::musl_tag
                             , bs::pack_< bd::double_<A0>, X>
                             )
  {
    BOOST_FORCEINLINE A0 operator() (const musl_tag &, const A0& a0) const BOOST_NOEXCEPT
    {
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
        x = if_else(test, x*A0(18014398509481984ull), x);
      }
#endif
      /* reduce x into [sqrt(2)/2, sqrt(2)] */
      hx += 0x3ff00000 - 0x3fe6a09e;
      k += bitwise_cast<iA0>(hx>>20) - 0x3ff;
      A0 dk = tofloat(k);
      hx = (hx&0x000fffff) + 0x3fe6a09e;
      x = bitwise_cast<A0>(hx<<32 | (bitwise_and(0xffffffffull, bitwise_cast<uiA0>(x))));

      A0 f = dec(x);
      A0 hfsq = Half<A0>()*sqr(f);
      A0 s = f/(Two<A0>() + f);
      A0 z = sqr(s);
      A0 w = sqr(z);
      A0 t1= w*horn<A0,
                    0x3fd999999997fa04ll,
                    0x3fcc71c51d8e78afll,
                    0x3fc39a09d078c69fll
                    > (w);
      A0 t2= z*horn<A0,
                    0x3fe5555555555593ll,
                    0x3fd2492494229359ll,
                    0x3fc7466496cb03dell,
                    0x3fc2f112df3e5244ll
                    > (w);
      A0 R = t2+t1;
      A0 r = fma(dk, Log_2hi<A0>(), ((fma(s, (hfsq+R), dk*Log_2lo<A0>()) - hfsq) + f));
#ifndef BOOST_SIMD_NO_INFINITIES
      A0 zz = if_else(isnez, if_else(a0 == Inf<A0>(), Inf<A0>(), r), Minf<A0>());
#else
      A0 zz = if_else(isnez, r, Minf<A0>());
#endif
      return if_nan_else(is_ngez(a0), zz);
    }
  };

  BOOST_DISPATCH_OVERLOAD_IF ( log_
                          , (typename A0, typename X)
                          , (detail::is_native<X>)
                          , bd::cpu_
                          , bs::plain_tag
                          , bs::pack_< bd::single_<A0>, X>
                          )
  {
    BOOST_FORCEINLINE A0 operator() (const plain_tag &, const A0& a0) const BOOST_NOEXCEPT
    {
      A0 x =  a0;
      A0 dk = Zero<A0>();
      auto isnez = is_nez(a0);
#ifndef BOOST_SIMD_NO_DENORMALS
      auto test = is_less(a0, Smallestposval<A0>())&&isnez;
      if (any(test))
      {
        dk = if_minus(test, dk, A0(23));
        x = if_else(test, x*A0(8388608ul), x);
      }
#endif
      A0 kk;
      std::tie(x, kk) = frexp(x);
      auto  x_lt_sqrthf = (Sqrt_2o_2<A0>() > x);
      dk += if_dec(x_lt_sqrthf, kk);
      A0 f = dec(x+if_else_zero(x_lt_sqrthf, x));
      A0 s = f/(Two<A0>() + f);
      A0 z = sqr(s);
      A0 w = sqr(z);
      A0 t1= w*horn<A0, 0x3eccce13, 0x3e789e26>(w);
      A0 t2= z*horn<A0, 0x3f2aaaaa, 0x3e91e9ee>(w);
      A0 R = t2 + t1;
      A0 hfsq = Half<A0>()*sqr(f);
      A0 r = fma(dk, Log_2hi<A0>(), ((fma(s, (hfsq+R), dk*Log_2lo<A0>()) - hfsq) + f));
#ifndef BOOST_SIMD_NO_INFINITIES
      A0 zz = if_else(isnez, if_else(a0 == Inf<A0>(), Inf<A0>(), r), Minf<A0>());
#else
      A0 zz = if_else(isnez, r, Minf<A0>());
#endif
      return if_nan_else(is_ngez(a0), zz);
    }
  };

  BOOST_DISPATCH_OVERLOAD_IF ( log_
                             , (typename A0, typename X)
                             , (detail::is_native<X>)
                             , bd::cpu_
                             , bs::plain_tag
                             , bs::pack_< bd::double_<A0>, X>
                             )
  {
    BOOST_FORCEINLINE A0 operator() (const plain_tag &, const A0& a0) const BOOST_NOEXCEPT
    {
      A0 x =  a0;
      A0 dk = Zero<A0>();
      auto isnez = is_nez(a0);
#ifndef BOOST_SIMD_NO_DENORMALS
      auto test = is_less(a0, Smallestposval<A0>())&&isnez;
      if (any(test))
      {
        dk = if_minus(test, dk, A0(23));
        x = if_else(test, x*A0(8388608ul), x);
      }
#endif
      A0 kk;
      std::tie(x, kk) = frexp(x);
      auto  x_lt_sqrthf = (Sqrt_2o_2<A0>() > x);
      dk += if_dec(x_lt_sqrthf, kk);
      A0 f = dec(x+if_else_zero(x_lt_sqrthf, x));

      // compute approximation
      A0 s = f/(Two<A0>()+f);
      A0 z = sqr(s);
      A0 w = sqr(z);
      A0 t1= w*horn<A0,
        0x3fd999999997fa04ll,
        0x3fcc71c51d8e78afll,
        0x3fc39a09d078c69fll
        > (w);
      A0 t2= z*horn<A0,
        0x3fe5555555555593ll,
        0x3fd2492494229359ll,
        0x3fc7466496cb03dell,
        0x3fc2f112df3e5244ll
        > (w);
      A0 R = t2+t1;
      A0 hfsq = Half<A0>()* sqr(f);
      A0 r = fma(dk, Log_2hi<A0>(), ((fma(s, (hfsq+R), dk*Log_2lo<A0>()) - hfsq) + f));
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
  /*
   *   1. Argument Reduction: find k and f such that
   *                      x = 2^k * (1+f),
   *         where  sqrt(2)/2 < 1+f < sqrt(2) .
   *
   *   2. Approximation of log(1+f).
   *      Let s = f/(2+f) ; based on log(1+f) = log(1+s) - log(1-s)
   *               = 2s + 2/3 s**3 + 2/5 s**5 + .....,
   *               = 2s + s*R
   *      We use a special Remez algorithm on [0,0.1716] to generate
   *      a polynomial of degree 14 to approximate R The maximum error
   *      of this polynomial approximation is bounded by 2**-58.45. In
   *      other words,
   *                      2      4      6      8      10      12      14
   *          R(z) ~ Lg1*s +Lg2*s +Lg3*s +Lg4*s +Lg5*s  +Lg6*s  +Lg7*s
   *      (the values of Lg1 to Lg7 are listed in the program)
   *      and
   *          |      2          14          |     -58.45
   *          | Lg1*s +...+Lg7*s    -  R(z) | <= 2
   *          |                             |
   *      Note that 2s = f - s*f = f - hfsq + s*hfsq, where hfsq = f*f/2.
   *      In order to guarantee error in log below 1ulp, we compute log
   *      by
   *              log(1+f) = f - s*(f - R)        (if f is not too large)
   *              log(1+f) = f - (hfsq - s*(hfsq+R)).     (better accuracy)
   *
   *      3. Finally,  log(x) = k*ln2 + log(1+f).
   *                          = k*ln2_hi+(f-(hfsq-(s*(hfsq+R)+k*ln2_lo)))
   *         Here ln2 is split into two floating point number:
   *                      ln2_hi + ln2_lo,
   *         where n*ln2_hi is always exact for |n| < 2000.
   */
