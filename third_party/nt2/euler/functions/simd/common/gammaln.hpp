//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_EULER_FUNCTIONS_SIMD_COMMON_GAMMALN_HPP_INCLUDED
#define NT2_EULER_FUNCTIONS_SIMD_COMMON_GAMMALN_HPP_INCLUDED

#include <nt2/euler/functions/gammaln.hpp>
#include <nt2/euler/functions/details/gammaln_kernel.hpp>
#include <nt2/include/functions/simd/abs.hpp>
#include <nt2/include/functions/simd/any.hpp>
#include <nt2/include/functions/simd/dec.hpp>
#include <nt2/include/functions/simd/divides.hpp>
#include <nt2/include/functions/simd/floor.hpp>
#include <nt2/include/functions/simd/fma.hpp>
#include <nt2/include/functions/simd/if_allbits_else.hpp>
#include <nt2/include/functions/simd/if_else.hpp>
#include <nt2/include/functions/simd/inbtrue.hpp>
#include <nt2/include/functions/simd/is_equal.hpp>
#include <nt2/include/functions/simd/is_flint.hpp>
#include <nt2/include/functions/simd/is_greater.hpp>
#include <nt2/include/functions/simd/is_greater_equal.hpp>
#include <nt2/include/functions/simd/is_less.hpp>
#include <nt2/include/functions/simd/is_lez.hpp>
#include <nt2/include/functions/simd/is_ltz.hpp>
#include <nt2/include/functions/simd/log.hpp>
#include <nt2/include/functions/simd/logical_and.hpp>
#include <nt2/include/functions/simd/logical_andnot.hpp>
#include <nt2/include/functions/simd/minus.hpp>
#include <nt2/include/functions/simd/multiplies.hpp>
#include <nt2/include/functions/simd/plus.hpp>
#include <nt2/include/functions/simd/rec.hpp>
#include <nt2/include/functions/simd/seladd.hpp>
#include <nt2/include/functions/simd/seldec.hpp>
#include <nt2/include/functions/simd/selinc.hpp>
#include <nt2/include/functions/simd/selsub.hpp>
#include <nt2/include/functions/simd/sinpi.hpp>
#include <nt2/include/functions/simd/splat.hpp>
#include <nt2/include/functions/simd/sqr.hpp>
#include <nt2/include/functions/simd/unary_minus.hpp>
#include <nt2/include/constants/false.hpp>
#include <nt2/include/constants/half.hpp>
#include <nt2/include/constants/inf.hpp>
#include <nt2/include/constants/invpi.hpp>
#include <nt2/include/constants/logpi.hpp>
#include <nt2/include/constants/logsqrt2pi.hpp>
#include <nt2/include/constants/minf.hpp>
#include <nt2/include/constants/mone.hpp>
#include <nt2/include/constants/nan.hpp>
#include <nt2/include/constants/one.hpp>
#include <nt2/include/constants/three.hpp>
#include <nt2/include/constants/two.hpp>
#include <nt2/include/constants/zero.hpp>
#include <nt2/sdk/meta/as_logical.hpp>
#include <nt2/sdk/meta/cardinal_of.hpp>
#include <nt2/sdk/meta/scalar_of.hpp>

#include <boost/simd/sdk/config.hpp>

#ifndef BOOST_SIMD_NO_INFINITES
#include <nt2/include/functions/simd/logical_or.hpp>
#endif

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::gammaln_, tag::cpu_
                            , (A0)(X)
                            , ((simd_<double_<A0>,X>))
                            )
  {
    typedef A0 result_type;
    typedef typename meta::as_logical<A0>::type bA0;
    NT2_FUNCTOR_CALL(1)
    {
      bA0 inf_result = logical_and(is_lez(a0), is_flint(a0));
      A0 x = if_nan_else(inf_result, a0);
      A0 q = nt2::abs(x);
      #ifndef BOOST_SIMD_NO_INFINITES
      inf_result = eq(q, Inf<A0>());
      #endif
      bA0 test = lt(a0, nt2::splat<A0>(-34.0));
      size_t nb = nt2::inbtrue(test);
      A0 r =  Nan<A0>();
      if(nb > 0)
      {
        //treat negative large with reflection
        r = large_negative(q);
        if (nb >= meta::cardinal_of<A0>::value)
          return nt2::if_else(inf_result, Nan<A0>(), r);
      }
      A0 r1 = other(a0);
      A0 r2 = if_else(test, r, r1);
      return nt2::if_else(eq(a0, Minf<A0>()),
                          Nan<A0>(),
                          nt2::if_else(inf_result, Inf<A0>(), r2)
                         );
    }
  private :
    static inline A0 large_negative(const A0& q)
    {
      A0 w = gammaln(q);
      A0 p = nt2::floor(q);
      A0 z = q - p;
      bA0 test2 = lt(z, nt2::Half<A0>() );
      z = nt2::selsub(test2, z, nt2::One<A0>());
      z = q*nt2::sinpi(z);
      z =  nt2::abs(z);
      return Logpi<A0>()-log(z)-w;
    }
    static inline A0 other(const A0& xx)
    {
      A0 x =  xx;
      bA0 test = lt(x, nt2::splat<A0>(13.0) );
      size_t nb = inbtrue(test);
      A0 r1 = Zero<A0>();
      if (nb > 0)
      {
        A0 z = One<A0>();
        A0 p = Zero<A0>();
        A0 u = x;
        bA0 test1 = ge(u,Three<A0>());
        while(nt2::any(test1))
        {
          p = seldec(test1, p);
          u = if_else(test1, x+p, u);
          z = if_else(test1, z*u, z);
          test1 = ge(u,Three<A0>());
        }
        //all u are less than 3
        bA0 test2 = lt(u,Two<A0>());

        while(nt2::any(test2))
        {
          z = if_else(test2, z/u, z);
          p = selinc(test2, p);
          u = if_else(test2, x+p, u);
          test2 = lt(u,Two<A0>());
        }
        z = nt2::abs(z);
        x +=  p-Two<A0>();
        r1 = x * details::gammaln_kernel<A0>::gammaln1(x)+nt2::log(z);
        if (nb >= meta::cardinal_of<A0>::value) return r1;
      }
      A0 r2 = fma(xx-Half<A0>(),nt2::log(xx), Logsqrt2pi<A0>()-xx);
      A0 p = rec(sqr(xx));
      r2 += details::gammaln_kernel<A0>::gammalnA(p)/xx;
      return if_else(test, r1, r2);
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::gammaln_, tag::cpu_
                            , (A0)(X)
                            , ((simd_<single_<A0>,X>))
                            )
  {

    typedef A0 result_type;
    typedef typename meta::as_logical<A0>::type bA0;
    typedef typename meta::scalar_of<A0>::type sA0;
    NT2_FUNCTOR_CALL(1)
    {
      bA0 inf_result = logical_and(is_lez(a0), is_flint(a0));
      A0 x = if_nan_else(inf_result, a0);
      A0 q = nt2::abs(x);
      #ifndef BOOST_SIMD_NO_INFINITES
      inf_result = logical_or(eq(x, Inf<A0>()), inf_result);
      #endif
      bA0 ltza0 = is_ltz(a0);
      size_t nb = nt2::inbtrue(ltza0);
      A0 r, r1 =  other(q);
      if(nb > 0)
      {
        //treat negative
        r = nt2::if_else(inf_result, Inf<A0>(), negative(q, r1));
        if (nb >= meta::cardinal_of<A0>::value) return r;
      }
      A0 r2 = if_else(ltza0, r, r1);
      return nt2::if_else(eq(a0, Minf<A0>()),
                          Nan<A0>(),
                          nt2::if_else(inf_result, Inf<A0>(), r2)
                         );
    }
  private :
    static inline A0 negative(const A0& q,  const A0& w)
    {
      A0 p = nt2::floor(q);
      A0 z = q - p;
      bA0 test2 = lt(z, nt2::Half<A0>() );
      z = nt2::selsub(test2, z, nt2::One<A0>());
      z = q*nt2::sinpi(z);
      z =  nt2::abs(z);
      return -log(Invpi<A0>()*nt2::abs(z))-w;
    }
    static inline A0 other(const A0& x)
    {
      bA0 xlt650 = lt(x, nt2::splat<A0>(6.50) );
      size_t nb = inbtrue(xlt650);
      A0 r0x = x;
      A0 r0z = x;
      A0 r0s = One<A0>();
      A0 r1 = Zero<A0>();
      A0 p =  Nan<A0>();
      if (nb > 0)
      {
        bA0 kernelC = False<bA0>();
        A0 z = One<A0>();
        A0 tx = x;
        A0 nx = Zero<A0>();

        const A0 _075 = nt2::splat<A0>(0.75);
        const A0 _150 = Two<A0>()*_075;
        const A0 _125 = nt2::splat<A0>(1.25);
        const A0 _250 = Two<A0>()*_125;
        bA0 xge150 = ge(x, _150);
        bA0 txgt250= gt(tx,_250);

        // x >= 1.5
        while (nt2::any(logical_and(xge150, txgt250)))
        {
          nx = seldec(txgt250, nx);
          tx = if_else(txgt250, x + nx, tx);
          z = if_else(txgt250, z*tx, z);
          txgt250= gt(tx,_250);
        }
        r0x = seladd(xge150, x, nx - Two<A0>());
        r0z = if_else(xge150, z, r0z);
        r0s = if_else(xge150,One<A0>(), r0s);

        // x >= 1.25 && x < 1.5
        bA0 xge125 = ge(x, _125);
        bA0 xge125t = l_andnot(xge125, xge150);
        if (nt2::any(xge125))
        {
          r0x =  if_else(xge125t, dec(x)    , r0x);
          r0z =  if_else(xge125t, z*x       , r0z);
          r0s =  if_else(xge125t, Mone<A0>(), r0s);
        }
        // x >= 0.75&& x < 1.5
        bA0 xge075  = ge(x, _075);
        bA0 xge075t = l_andnot(xge075, xge125);
        if (nt2::any(xge075t))
        {
          kernelC =  xge075t;
          r0x =  if_else(xge075t, dec(x)    , r0x);
          r0z =  if_else(xge075t, One<A0>() , r0z);
          r0s =  if_else(xge075t, Mone<A0>(), r0s);
          p = details::gammaln_kernel<A0>::gammalnC(r0x);
        }
        // tx < 1.5 && x < 0.75
        bA0 txlt150 = l_andnot(lt(tx,_150), xge075);
        if (nt2::any(txlt150))
        {
          bA0 orig = txlt150;
          while( nt2::any(txlt150) )
          {
            z  = if_else(txlt150, z*tx, z);
            nx = selinc(txlt150, nx);
            tx = if_else(txlt150, x + nx, tx);
            txlt150= l_andnot(lt(tx,_150), xge075);
          }
          r0x =  seladd(orig, r0x, nx - Two<A0>());
          r0z =  if_else(orig,z         , r0z);
          r0s =  if_else(orig,Mone<A0>(), r0s);
        }
        p =  if_else(kernelC, p, details::gammaln_kernel<A0>::gammalnB(r0x));
        if (nb >= meta::cardinal_of<A0>::value)
          return fma(r0x, p, r0s*nt2::log(nt2::abs(r0z)));
      }
      r0z = if_else(xlt650, nt2::abs(r0z), x);
      A0 m = nt2::log(r0z);
      r1 = fma(r0x, p, r0s*m);
      A0 r2 = fma(x-Half<A0>(),m,Logsqrt2pi<A0>()-x);
      r2 += details::gammaln_kernel<A0>::gammaln2(rec(sqr(x)))/x;
      return if_else(xlt650, r1, r2);
    }
  };
} }

#endif
