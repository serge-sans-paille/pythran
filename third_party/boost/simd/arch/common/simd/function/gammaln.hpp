//==================================================================================================
/*!
  @file
  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_COMMON_SIMD_FUNCTION_GAMMALN_HPP_INCLUDED
#define BOOST_SIMD_ARCH_COMMON_SIMD_FUNCTION_GAMMALN_HPP_INCLUDED

#include <boost/simd/function/std.hpp>
#include <boost/simd/arch/common/detail/generic/gammaln_kernel.hpp>

#include <boost/simd/constant/half.hpp>
#include <boost/simd/constant/inf.hpp>
#include <boost/simd/constant/invpi.hpp>
#include <boost/simd/constant/logpi.hpp>
#include <boost/simd/constant/logsqrt2pi.hpp>
#include <boost/simd/constant/minf.hpp>
#include <boost/simd/constant/mone.hpp>
#include <boost/simd/constant/nan.hpp>
#include <boost/simd/constant/one.hpp>
#include <boost/simd/constant/two.hpp>
#include <boost/simd/constant/three.hpp>
#include <boost/simd/constant/zero.hpp>


#include <boost/simd/constant/pi.hpp>
#include <boost/simd/constant/two.hpp>

#include <boost/simd/function/abs.hpp>
#include <boost/simd/function/any.hpp>
#include <boost/simd/function/dec.hpp>
#include <boost/simd/function/floor.hpp>
#include <boost/simd/function/fma.hpp>
#include <boost/simd/function/if_dec.hpp>
#include <boost/simd/function/if_else.hpp>
#include <boost/simd/function/if_inc.hpp>
#include <boost/simd/function/if_minus.hpp>
#include <boost/simd/function/if_nan_else.hpp>
#include <boost/simd/function/if_plus.hpp>
#include <boost/simd/function/is_equal.hpp>
#include <boost/simd/function/is_flint.hpp>
#include <boost/simd/function/is_less.hpp>
#include <boost/simd/function/is_lez.hpp>
#include <boost/simd/function/log.hpp>
#include <boost/simd/function/logical_and.hpp>
#include <boost/simd/function/logical_andnot.hpp>
#include <boost/simd/function/logical_or.hpp>
#include <boost/simd/function/nbtrue.hpp>
#include <boost/simd/function/sinpi.hpp>
#include <boost/simd/function/sqr.hpp>


#include <boost/simd/meta/as_logical.hpp>
#include <boost/simd/detail/dispatch/function/overload.hpp>
#include <boost/simd/detail/dispatch/meta/scalar_of.hpp>
#include <boost/config.hpp>
#include <cmath>

namespace boost { namespace simd { namespace ext
{
  namespace bd = boost::dispatch;
  namespace bs = boost::simd;
  BOOST_DISPATCH_OVERLOAD_IF ( gammaln_
                             , (typename A0, typename X)
                             , (detail::is_native<X>)
                             , bd::cpu_
                             , bs::pack_< bd::single_<A0>, X>
                             )
  {
    using sA0 = bd::scalar_of_t<A0>;
    A0 operator() (const A0& a0) const BOOST_NOEXCEPT
    {
      auto inf_result = logical_and(is_lez(a0), is_flint(a0));
      A0 x = if_nan_else(inf_result, a0);
      A0 q = bs::abs(x);
      #ifndef BOOST_SIMD_NO_INFINITES
      inf_result = logical_or(is_equal(x, Inf<A0>()), inf_result);
      #endif
      auto ltza0 = is_ltz(a0);
      size_t nb = bs::nbtrue(ltza0);
      A0 r;
      A0 r1 =  other(q);
      if(nb > 0)
      {
        //treat negative
        r = bs::if_else(inf_result, Inf<A0>(), negative(q, r1));
        if (nb >= A0::static_size) return r;
      }
      A0 r2 = if_else(ltza0, r, r1);
      return bs::if_else(is_equal(a0, Minf<A0>()),
                          Nan<A0>(),
                          bs::if_else(inf_result, Inf<A0>(), r2)
                         );
    }
  private :
    using lA0 = bs::as_logical_t<A0>;
    static inline A0 negative(const A0& q,  const A0& w)
    {
      A0 p = bs::floor(q);
      A0 z = q - p;
      auto test2 = is_less(z, bs::Half<A0>() );
      z = bs::if_dec(test2, z);
      z = q*bs::sinpi(z);
      z =  bs::abs(z);
      return -log(Invpi<A0>()*bs::abs(z))-w;
    }
    static inline A0 other(const A0& x)
    {
      auto xlt650 = is_less(x,A0(6.50) );
      size_t nb = nbtrue(xlt650);
      A0 r0x = x;
      A0 r0z = x;
      A0 r0s = One<A0>();
      A0 r1 = Zero<A0>();
      A0 p =  Nan<A0>();
      if (nb > 0)
      {
        auto kernelC = False<lA0>();
        A0 z = One<A0>();
        A0 tx = if_else_zero(xlt650, x);
        A0 nx = Zero<A0>();

        const A0 _075 = A0(0.75);
        const A0 _150 = A0(1.50);
        const A0 _125 = A0(1.25);
        const A0 _250 = A0(2.50);
        auto xge150 = is_greater_equal(x, _150);
        auto txgt250= is_greater(tx,_250);

        // x >= 1.5
        while (bs::any(logical_and(xge150, txgt250)))
        {
          nx = if_dec(txgt250, nx);
          tx = if_else(txgt250, x + nx, tx);
          z = if_else(txgt250, z*tx, z);
          txgt250= is_greater(tx,_250);
        }
        r0x = if_plus(xge150, x, nx - Two<A0>());
        r0z = if_else(xge150, z, r0z);
        r0s = if_else(xge150,One<A0>(), r0s);

        // x >= 1.25 && x < 1.5
        auto xge125 = is_greater_equal(x, _125);
        auto xge125t = logical_andnot(xge125, xge150);
        if (bs::any(xge125))
        {
          r0x =  if_else(xge125t, dec(x)    , r0x);
          r0z =  if_else(xge125t, z*x       , r0z);
          r0s =  if_else(xge125t, Mone<A0>(), r0s);
        }
        // x >= 0.75&& x < 1.5
        auto xge075  = is_greater_equal(x, _075);
        auto xge075t = logical_andnot(xge075, xge125);
        if (bs::any(xge075t))
        {
          kernelC =  xge075t;
          r0x =  if_else(xge075t, dec(x)    , r0x);
          r0z =  if_else(xge075t, One<A0>() , r0z);
          r0s =  if_else(xge075t, Mone<A0>(), r0s);
          p = detail::gammaln_kernel<A0>::gammalnC(r0x);
        }
        // tx < 1.5 && x < 0.75
        auto txlt150 = logical_andnot(is_less(tx,_150), xge075);
        if (bs::any(txlt150))
        {
          auto orig = txlt150;
          while( bs::any(txlt150) )
          {
            z  = if_else(txlt150, z*tx, z);
            nx = if_inc(txlt150, nx);
            tx = if_else(txlt150, x + nx, tx);
            txlt150= logical_andnot(is_less(tx,_150), xge075);
          }
          r0x =  if_plus(orig, r0x, nx - Two<A0>());
          r0z =  if_else(orig,z         , r0z);
          r0s =  if_else(orig,Mone<A0>(), r0s);
        }
        p =  if_else(kernelC, p, detail::gammaln_kernel<A0>::gammalnB(r0x));
        if (nb >= A0::static_size)
          return fma(r0x, p, r0s*bs::log(bs::abs(r0z)));
      }
      r0z = if_else(xlt650, bs::abs(r0z), x);
      A0 m = bs::log(r0z);
      r1 = fma(r0x, p, r0s*m);
      A0 r2 = fma(x-Half<A0>(),m,Logsqrt2pi<A0>()-x);
      r2 += detail::gammaln_kernel<A0>::gammaln2(rec(sqr(x)))/x;
      return if_else(xlt650, r1, r2);
    }
  };
  BOOST_DISPATCH_OVERLOAD_IF ( gammaln_
                             , (typename A0, typename X)
                             , (detail::is_native<X>)
                             , bd::cpu_
                             , bs::pack_< bd::double_<A0>, X >
                             )
  {
    BOOST_FORCEINLINE A0 operator() (const A0& a0) const BOOST_NOEXCEPT
    {
      auto inf_result = logical_and(is_lez(a0), is_flint(a0));
      A0 x = if_nan_else(inf_result, a0);
      A0 q = bs::abs(x);
      #ifndef BOOST_SIMD_NO_INFINITES
      inf_result = is_equal(q, Inf<A0>());
      #endif
      auto test = is_less(a0, A0(-34.0));
      size_t nb = bs::nbtrue(test);
      A0 r =  Nan<A0>();
      if(nb > 0)
      {
        //treat negative large with reflection
        r = large_negative(q);
        if (nb >= A0::static_size)
          return bs::if_else(inf_result, Nan<A0>(), r);
      }
      A0 r1 = other(a0);
      A0 r2 = if_else(test, r, r1);
      return bs::if_else(is_equal(a0, Minf<A0>()),
                          Nan<A0>(),
                          bs::if_else(inf_result, Inf<A0>(), r2)
                         );
    }
  private :
    static inline A0 large_negative(const A0& q)
    {
      A0 w = gammaln(q);
      A0 p = bs::floor(q);
      A0 z = q - p;
      auto test2 = is_less(z, bs::Half<A0>() );
      z = bs::if_dec(test2, z);
      z = q*bs::sinpi(z);
      z =  bs::abs(z);
      return Logpi<A0>()-log(z)-w;
    }
    static inline A0 other(const A0& xx)
    {
      A0 x =  xx;
      auto test = is_less(x, A0(13.0) );
      size_t nb = nbtrue(test);
      A0 r1 = Zero<A0>();
      if (nb > 0)
      {
        A0 z = One<A0>();
        A0 p = Zero<A0>();
        A0 u = if_else_zero(test, x);
        auto test1 = is_greater_equal(u,Three<A0>());
        while(bs::any(test1))
        {
          p = if_dec(test1, p);
          u = if_else(test1, x+p, u);
          z = if_else(test1, z*u, z);
          test1 = is_greater_equal(u,Three<A0>());
        }
        //all u are less than 3
        auto test2 = is_less(u,Two<A0>());

        while(bs::any(test2))
        {
          z = if_else(test2, z/u, z);
          p = if_inc(test2, p);
          u = if_else(test2, x+p, u);
          test2 = is_less(u,Two<A0>());
        }
        z = bs::abs(z);
        x +=  p-Two<A0>();
        r1 = x * detail::gammaln_kernel<A0>::gammaln1(x)+bs::log(z);
        if (nb >= A0::static_size) return r1;
      }
      A0 r2 = fma(xx-Half<A0>(),bs::log(xx), Logsqrt2pi<A0>()-xx);
      A0 p = rec(sqr(xx));
      r2 += detail::gammaln_kernel<A0>::gammalnA(p)/xx;
      return if_else(test, r1, r2);
    }
  };

} } }


#endif
