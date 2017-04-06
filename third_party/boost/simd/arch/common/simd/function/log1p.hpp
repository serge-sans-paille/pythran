//==================================================================================================
/**
  Copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
**/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_COMMON_SIMD_FUNCTION_LOG1P_HPP_INCLUDED
#define BOOST_SIMD_ARCH_COMMON_SIMD_FUNCTION_LOG1P_HPP_INCLUDED

#include <boost/simd/detail/overload.hpp>
#include <boost/simd/function/any.hpp>
#include <boost/simd/function/bitwise_cast.hpp>
#include <boost/simd/function/dec.hpp>
#include <boost/simd/function/fma.hpp>
#include <boost/simd/function/horn.hpp>
#include <boost/simd/function/if_else.hpp>
#include <boost/simd/function/if_nan_else.hpp>
#include <boost/simd/function/inc.hpp>
#include <boost/simd/function/is_ngez.hpp>
#include <boost/simd/function/is_nez.hpp>
#include <boost/simd/function/musl.hpp>
#include <boost/simd/function/plain.hpp>
#include <boost/simd/function/sqr.hpp>
#include <boost/simd/function/tofloat.hpp>

#include <boost/simd/constant/half.hpp>
#include <boost/simd/constant/inf.hpp>
#include <boost/simd/constant/minf.hpp>
#include <boost/simd/constant/sqrt_2o_2.hpp>
#include <boost/simd/constant/two.hpp>

#include <boost/simd/detail/constant/log_2hi.hpp>
#include <boost/simd/detail/constant/log_2lo.hpp>

#include <boost/simd/detail/dispatch/meta/as_integer.hpp>

namespace boost { namespace simd { namespace ext
{
  namespace bd = boost::dispatch;

 BOOST_DISPATCH_OVERLOAD_IF ( log1p_
                             , (typename A0, typename X)
                             , (detail::is_native<X>)
                             , bd::cpu_
                             , bs::pack_< bd::single_<A0>, X>
                          )
  {
    BOOST_FORCEINLINE A0 operator()( const A0& a0) BOOST_NOEXCEPT
    {
      return musl_(log1p)(a0);
    }
  };

 BOOST_DISPATCH_OVERLOAD_IF ( log1p_
                             , (typename A0, typename X)
                             , (detail::is_native<X>)
                             , bd::cpu_
                             , bs::pack_< bd::double_<A0>, X>
                          )
  {
    BOOST_FORCEINLINE A0 operator()( const A0& a0) BOOST_NOEXCEPT
    {
      return plain_(log1p)(a0);
    }
  };

  BOOST_DISPATCH_OVERLOAD_IF ( log1p_
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
      const A0 uf =  inc(a0);
      auto isnez = is_nez(uf);

      uiA0 iu = bitwise_cast<uiA0>(uf);
      iu += 0x3f800000 - 0x3f3504f3;
      iA0 k = bitwise_cast<iA0>(iu>>23) - 0x7f;
      /* correction term ~ log(1+x)-log(u), avoid underflow in c/u */
      /* reduce x into [sqrt(2)/2, sqrt(2)] */
      iu = (iu&0x007fffff) + 0x3f3504f3;
      A0 f =  dec(bitwise_cast<A0>(iu));
      A0 s = f/(2.0f + f);
      A0 z = sqr(s);
      A0 w = sqr(z);
      A0 t1= w*horn<A0, 0x3eccce13, 0x3e789e26>(w);
      A0 t2= z*horn<A0, 0x3f2aaaaa, 0x3e91e9ee>(w);
      A0 R = t2 + t1;
      A0 hfsq = Half<A0>()*sqr(f);
      A0 dk = tofloat(k);
      A0  c = if_else( k >= 2, oneminus(uf-a0), a0-dec(uf))/uf;
      A0 r = fma(dk, Log_2hi<A0>(), ((fma(s, (hfsq+R), dk*Log_2lo<A0>()+c) - hfsq) + f));
#ifndef BOOST_SIMD_NO_INFINITIES
      A0 zz = if_else(isnez, if_else(a0 == Inf<A0>(), Inf<A0>(), r), Minf<A0>());
#else
      A0 zz = if_else(isnez, r, Minf<A0>());
#endif
      return if_nan_else(is_ngez(uf), zz);
    }
  };

  BOOST_DISPATCH_OVERLOAD_IF ( log1p_
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
      const A0 uf =  inc(a0);
      auto isnez = is_nez(uf);

      /* reduce x into [sqrt(2)/2, sqrt(2)] */
      uiA0 hu = bitwise_cast<uiA0>(uf)>>32;
      hu += 0x3ff00000 - 0x3fe6a09e;
      iA0 k = bitwise_cast<iA0>(hu>>20) - 0x3ff;
      /* correction term ~ log(1+x)-log(u), avoid underflow in c/u */
      A0  c =  if_else( k >= 2, oneminus(uf-a0), a0-dec(uf))/uf;
      hu =  (hu&0x000fffff) + 0x3fe6a09e;
      A0 f = bitwise_cast<A0>( bitwise_cast<uiA0>(hu<<32) | (bitwise_and(0xffffffffull, bitwise_cast<uiA0>(uf))));
      f = dec(f);

      A0 hfsq = Half<A0>()*sqr(f);
      A0 s = f/(2.0 + f);
      A0 z = sqr(s);
      A0 w = sqr(z);
      A0 t1= w*horn<A0, 0x3fd999999997fa04ll, 0x3fcc71c51d8e78afll, 0x3fc39a09d078c69fll > (w);
      A0 t2= z*horn<A0, 0x3fe5555555555593ll, 0x3fd2492494229359ll
                      , 0x3fc7466496cb03dell, 0x3fc2f112df3e5244ll> (w);
      A0 R = t2 + t1;
      A0 dk = tofloat(k);
      A0 r = fma(dk, Log_2hi<A0>(), ((fma(s, (hfsq+R), dk*Log_2lo<A0>()+c) - hfsq) + f));

#ifndef BOOST_SIMD_NO_INFINITIES
      A0 zz = if_else(isnez, if_else(a0 == Inf<A0>(), Inf<A0>(), r), Minf<A0>());
#else
      A0 zz = if_else(isnez, r, Minf<A0>());
#endif
      return if_nan_else(is_ngez(uf), zz);
    }
  };
//=================================================================================================================
  BOOST_DISPATCH_OVERLOAD_IF ( log1p_
                          , (typename A0, typename X)
                          , (detail::is_native<X>)
                          , bd::cpu_
                          , bs::plain_tag
                          , bs::pack_< bd::single_<A0>, X>
                          )
  {
    BOOST_FORCEINLINE A0 operator() (const plain_tag &, const A0& a0) const BOOST_NOEXCEPT
    {
      const A0 uf =  inc(a0);
      auto isnez = is_nez(uf);

     /* reduce x into [sqrt(2)/2, sqrt(2)] */
      A0 k;
      A0 x;
      std::tie(x, k) = frexp(uf);
      auto  x_lt_sqrthf = (Sqrt_2o_2<A0>() >  x);
      k = if_dec(x_lt_sqrthf, k);
      A0 f = dec(x+if_else_zero(x_lt_sqrthf, x));
      /* correction term ~ log(1+x)-log(u), avoid underflow in c/u */
      A0  c = if_else( k >= 2, oneminus(uf-a0), a0-dec(uf))/uf;

      A0 s = f/(2.0f + f);
      A0 z = sqr(s);
      A0 w = sqr(z);
      A0 t1= w*horn<A0, 0x3eccce13, 0x3e789e26>(w);
      A0 t2= z*horn<A0, 0x3f2aaaaa, 0x3e91e9ee>(w);
      A0 R = t2 + t1;
      A0 hfsq = Half<A0>()*sqr(f);
      A0 r = fma(k, Log_2hi<A0>(), ((fma(s, (hfsq+R), k*Log_2lo<A0>()+c) - hfsq) + f));
#ifndef BOOST_SIMD_NO_INFINITIES
      A0 zz = if_else(isnez, if_else(a0 == Inf<A0>(), Inf<A0>(), r), Minf<A0>());
#else
      A0 zz = if_else(isnez, r, Minf<A0>());
#endif
      return if_nan_else(is_ngez(uf), zz);
    }
  };

  BOOST_DISPATCH_OVERLOAD_IF ( log1p_
                             , (typename A0, typename X)
                             , (detail::is_native<X>)
                             , bd::cpu_
                             , bs::plain_tag
                             , bs::pack_< bd::double_<A0>, X>
                             )
  {
    BOOST_FORCEINLINE A0 operator() (const plain_tag &, const A0& a0) const BOOST_NOEXCEPT
    {
//      using iA0 = bd::as_integer_t<A0,   signed>;
      const A0 uf =  inc(a0);
      auto isnez = is_nez(uf);

      /* reduce x into [sqrt(2)/2, sqrt(2)] */
      A0 k;
      A0 x;
      std::tie(x, k) = frexp(uf);
      auto  x_lt_sqrthf = (Sqrt_2o_2<A0>() >  x);
      k = if_dec(x_lt_sqrthf, k);
      A0 f = dec(x+if_else_zero(x_lt_sqrthf, x));
      /* correction term ~ log(1+x)-log(u), avoid underflow in c/u */
      A0  c = if_else( k >= 2, oneminus(uf-a0), a0-dec(uf))/uf;

      A0 hfsq = Half<A0>()*sqr(f);
      A0 s = f/(2.0 + f);
      A0 z = sqr(s);
      A0 w = sqr(z);
      A0 t1= w*horn<A0, 0x3fd999999997fa04ll, 0x3fcc71c51d8e78afll, 0x3fc39a09d078c69fll > (w);
      A0 t2= z*horn<A0, 0x3fe5555555555593ll, 0x3fd2492494229359ll
                      , 0x3fc7466496cb03dell, 0x3fc2f112df3e5244ll> (w);
      A0 R = t2 + t1;
      A0 r = fma(k, Log_2hi<A0>(), ((fma(s, (hfsq+R), k*Log_2lo<A0>()+c) - hfsq) + f));

#ifndef BOOST_SIMD_NO_INFINITIES
      A0 zz = if_else(isnez, if_else(a0 == Inf<A0>(), Inf<A0>(), r), Minf<A0>());
#else
      A0 zz = if_else(isnez, r, Minf<A0>());
#endif
      return if_nan_else(is_ngez(uf), zz);
    }
  };




} } }

#endif
