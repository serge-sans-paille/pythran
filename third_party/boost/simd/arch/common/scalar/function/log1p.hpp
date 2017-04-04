//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_COMMON_SCALAR_FUNCTION_LOG1P_HPP_INCLUDED
#define BOOST_SIMD_ARCH_COMMON_SCALAR_FUNCTION_LOG1P_HPP_INCLUDED
#include <boost/simd/function/std.hpp>
#include <boost/simd/function/plain.hpp>

#include <boost/simd/function/scalar/inc.hpp>
#include <boost/simd/function/musl.hpp>
#include <boost/simd/function/scalar/oneminus.hpp>
#include <boost/simd/detail/dispatch/function/overload.hpp>
#include <boost/config.hpp>
#include <cmath>
#include <boost/simd/function/bitwise_and.hpp>
#include <boost/simd/function/dec.hpp>
#include <boost/simd/function/scalar/inc.hpp>
#include <boost/simd/function/fma.hpp>
#include <boost/simd/function/frexp.hpp>
#include <boost/simd/function/horn.hpp>
#include <boost/simd/function/musl.hpp>
#include <boost/simd/function/plain.hpp>
#include <boost/simd/function/sqr.hpp>
#include <boost/simd/function/std.hpp>
#include <boost/simd/detail/constant/log_2hi.hpp>
#include <boost/simd/detail/constant/log_2lo.hpp>

#include <boost/simd/constant/inf.hpp>
#include <boost/simd/constant/nan.hpp>
#include <boost/simd/constant/minf.hpp>
#include <boost/simd/detail/dispatch/meta/as_integer.hpp>

namespace boost { namespace simd { namespace ext
{
  namespace bd = boost::dispatch;
  namespace bs = boost::simd;
  BOOST_DISPATCH_OVERLOAD ( log1p_
                          , (typename A0)
                          , bd::cpu_
                          , bd::scalar_< bd::floating_<A0> >
                          )
  {
    BOOST_FORCEINLINE A0 operator() ( A0 const& a0) const BOOST_NOEXCEPT
    {
      return musl_(log1p)(a0);
    }
  };
  BOOST_DISPATCH_OVERLOAD ( log1p_
                          , (typename A0)
                          , bd::cpu_
                          , bs::std_tag
                          , bd::scalar_< bd::floating_<A0> >
                          )
  {
    BOOST_FORCEINLINE A0 operator() (const std_tag &, A0 a0) const BOOST_NOEXCEPT
    {
      return std::log1p(a0);
    }
  };

  BOOST_DISPATCH_OVERLOAD ( log1p_
                          , (typename A0)
                          , bd::cpu_
                          , bs::musl_tag
                          , bd::scalar_< bd::single_<A0> >
                          )
  {
    BOOST_FORCEINLINE A0 operator() (const musl_tag &, A0 x) const BOOST_NOEXCEPT
    {
      using uiA0 = bd::as_integer_t<A0, unsigned>;
      using iA0 = bd::as_integer_t<A0,   signed>;
      uiA0 ix = bitwise_cast<uiA0>(x);
      iA0 k = 1;
      A0 c = Zero<A0>(), f = x;
      if (ix < 0x3ed413d0 || ix>>31)               /* 1+x < sqrt(2)+  */
      {
        if (ix >= 0xbf800000)                       /* x <= -1.0 */
        {
          if (x == Mone<A0>())  return Minf<A0>();  /* log1p(-1)=-inf */
          return Nan<A0>();                         /* log1p(x<-1)=NaN */
        }
        if (ix<<1 < 0x33800000<<1)                  /* |x| < 2**-24 */
        {
          if ((ix&0x7f800000) == 0) return x;
        }
        if (ix <= 0xbe95f619)                       /* sqrt(2)/2- <= 1+x < sqrt(2)+ */
        {
          k = 0;
        }
      }
      else if (ix >= 0x7f800000)  return x;
      if (k)
      {
        /* reduce u into [sqrt(2)/2, sqrt(2)] */
        A0 uf =  inc(x);
        uiA0 iu = bitwise_cast<uiA0>(uf);
        iu += 0x3f800000 - 0x3f3504f3;
        k = bitwise_cast<iA0>(iu>>23) - 0x7f;
        /* correction term ~ log(1+x)-log(u), avoid underflow in c/u */
        if (k < 25)
        {
          c = k >= 2 ? oneminus(uf-x) : x-dec(uf);
          c /= uf;
        }

        /* reduce u into [sqrt(2)/2, sqrt(2)] */
        iu = (iu&0x007fffff) + 0x3f3504f3;
        f =  dec(bitwise_cast<A0>(iu));
      }
      A0 s = f/(2.0f + f);
      A0 z = sqr(s);
      A0 w = sqr(z);
      A0 t1= w*horn<A0, 0x3eccce13, 0x3e789e26>(w);
      A0 t2= z*horn<A0, 0x3f2aaaaa, 0x3e91e9ee>(w);
      A0 R = t2 + t1;
      A0 hfsq = 0.5f*sqr(f);
      A0 dk = k;
      return  fma(dk, Log_2hi<A0>(), ((fma(s, (hfsq+R), dk*Log_2lo<A0>()+c) - hfsq) + f));
    }
  };

  BOOST_DISPATCH_OVERLOAD ( log1p_
                          , (typename A0)
                          , bd::cpu_
                          , bs::musl_tag
                          , bd::scalar_< bd::double_<A0> >
                          )
  {
    BOOST_FORCEINLINE A0 operator() (const musl_tag &, A0 x) const BOOST_NOEXCEPT
    {
      using uiA0 = bd::as_integer_t<A0, unsigned>;
      using iA0 = bd::as_integer_t<A0,   signed>;
      uiA0 hx = bitwise_cast<uiA0>(x) >> 32;
      iA0 k = 1;

      A0 c = Zero<A0>(), f = x;
      if (hx < 0x3fda827a || hx>>31)               /* 1+x < sqrt(2)+ */
      {
        if (hx >= 0xbff00000)                      /* x <= -1.0 */
        {
          if (x == Mone<A0>()) return Minf<A0>();  /* log1p(-1)=-inf */
          return Nan<A0>();                        /* log1p(x<-1)=NaN */
        }
        if (hx<<1 < 0x3ca00000<<1)                 /* |x| < 2**-53 */
        {
          if ((hx&0x7ff00000) == 0) return x;
        }
        if (hx <= 0xbfd2bec4)                      /* sqrt(2)/2- <= 1+x < sqrt(2)+ */
        {
          k = 0;
        }
      } else if (hx >= 0x7ff00000) return x;
      if (k)
      {
        /* reduce x into [sqrt(2)/2, sqrt(2)] */
        A0 uf =  inc(x);
        uiA0 hu = bitwise_cast<uiA0>(uf)>>32;
        hu += 0x3ff00000 - 0x3fe6a09e;
        k = (int)(hu>>20) - 0x3ff;
        /* correction term ~ log(1+x)-log(u), avoid underflow in c/u */
        if (k < 54)
        {
          c = k >= 2 ? oneminus(uf-x) : x-dec(uf);
          c /= uf;
        }
        hu =  (hu&0x000fffff) + 0x3fe6a09e;
        f = bitwise_cast<A0>( bitwise_cast<uiA0>(hu<<32) | (bitwise_and(0xffffffffull, bitwise_cast<uiA0>(uf))));
        f = dec(f);
      }

      A0 hfsq = 0.5*sqr(f);
      A0 s = f/(2.0f + f);
      A0 z = sqr(s);
      A0 w = sqr(z);
      A0 t1= w*horn<A0, 0x3fd999999997fa04ll, 0x3fcc71c51d8e78afll, 0x3fc39a09d078c69fll > (w);
      A0 t2= z*horn<A0, 0x3fe5555555555593ll, 0x3fd2492494229359ll
                      , 0x3fc7466496cb03dell, 0x3fc2f112df3e5244ll> (w);
      A0 R = t2 + t1;
      A0 dk = k;
      return  fma(dk, Log_2hi<A0>(), ((fma(s, (hfsq+R), dk*Log_2lo<A0>()+c) - hfsq) + f));
    }
  };

    BOOST_DISPATCH_OVERLOAD ( log1p_
                          , (typename A0)
                          , bd::cpu_
                          , bs::plain_tag
                          , bd::scalar_< bd::floating_<A0> >
                          )
  {
    BOOST_FORCEINLINE A0 operator() (const plain_tag &, A0 x) const BOOST_NOEXCEPT
    {
      return musl_(log1p)(x); //the "plain" version of the algorithm is never speedier than the "musl" version.
      // the call is here to allow a scalar fallback to simd calls
    }
  };

} } }


#endif
