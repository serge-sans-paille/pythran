//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_EULER_FUNCTIONS_SIMD_COMMON_EXPNI_HPP_INCLUDED
#define NT2_EULER_FUNCTIONS_SIMD_COMMON_EXPNI_HPP_INCLUDED

#include <nt2/euler/functions/expni.hpp>
#include <nt2/include/constants/eight.hpp>
#include <nt2/include/constants/eps.hpp>
#include <nt2/include/constants/euler.hpp>
#include <nt2/include/constants/expnibig.hpp>
#include <nt2/include/constants/halfeps.hpp>
#include <nt2/include/constants/inf.hpp>
#include <nt2/include/constants/maxlog.hpp>
#include <nt2/include/constants/nan.hpp>
#include <nt2/include/constants/one.hpp>
#include <nt2/include/constants/six.hpp>
#include <nt2/include/constants/two.hpp>
#include <nt2/include/constants/zero.hpp>
#include <nt2/include/functions/simd/abs.hpp>
#include <nt2/include/functions/simd/any.hpp>
#include <nt2/include/functions/simd/divides.hpp>
#include <nt2/include/functions/simd/exp.hpp>
#include <nt2/include/functions/simd/gamma.hpp>
#include <nt2/include/functions/simd/if_allbits_else.hpp>
#include <nt2/include/functions/simd/if_else.hpp>
#include <nt2/include/functions/simd/if_else_allbits.hpp>
#include <nt2/include/functions/simd/inbtrue.hpp>
#include <nt2/include/functions/simd/is_eqz.hpp>
#include <nt2/include/functions/simd/is_greater.hpp>
#include <nt2/include/functions/simd/is_less.hpp>
#include <nt2/include/functions/simd/is_less_equal.hpp>
#include <nt2/include/functions/simd/is_ltz.hpp>
#include <nt2/include/functions/simd/is_nan.hpp>
#include <nt2/include/functions/simd/is_nez.hpp>
#include <nt2/include/functions/simd/is_odd.hpp>
#include <nt2/include/functions/simd/log.hpp>
#include <nt2/include/functions/simd/logical_or.hpp>
#include <nt2/include/functions/simd/minus.hpp>
#include <nt2/include/functions/simd/multiplies.hpp>
#include <nt2/include/functions/simd/oneplus.hpp>
#include <nt2/include/functions/simd/plus.hpp>
#include <nt2/include/functions/simd/pow.hpp>
#include <nt2/include/functions/simd/rec.hpp>
#include <nt2/include/functions/simd/seladd.hpp>
#include <nt2/include/functions/simd/splat.hpp>
#include <nt2/include/functions/simd/sqr.hpp>
#include <nt2/include/functions/simd/tofloat.hpp>
#include <nt2/include/functions/simd/unary_minus.hpp>
#include <nt2/sdk/meta/as_floating.hpp>
#include <nt2/sdk/meta/as_logical.hpp>
#include <nt2/sdk/meta/cardinal_of.hpp>
#include <nt2/sdk/meta/scalar_of.hpp>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::expni_, tag::cpu_
                            , (A0)(A1)(X)
                            , (scalar_< integer_<A0> >)((simd_<integer_<A1>,X>))
                            )
  {
    typedef typename meta::as_floating<A1>::type result_type;
    NT2_FUNCTOR_CALL_REPEAT(2)
    {
      return nt2::expni(a0, nt2::tofloat(a1));
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION(nt2::tag::expni_, tag::cpu_,
                      (A0)(A1)(X),
                      ((scalar_<integer_<A0> > ))
                      ((simd_<floating_<A1>,X>))
                    )
  {
    typedef A1 result_type;
    NT2_FUNCTOR_CALL(2)
    {
      typedef typename meta::as_logical<A1>::type bA1;
      bA1 isltza1 = nt2::is_ltz(a1);
      A1 x =  nt2::if_nan_else(isltza1, a1);
      const int32_t sn =  a0;
      if( sn == 0 )  return nt2::exp(-x)/x;
      if (sn < 0 )   return nt2::Nan<A1>();
      A1 n = nt2::splat<A1>(sn);
      if (sn  > 5000 )
      {
        A1 xk = x + n;
        A1 yk = nt2::rec(nt2::sqr(xk));
        A1 t = n;
        A1 ans = yk*t*(nt2::Six<A1>()*sqr(x)-nt2::Eight<A1>()*t*x+nt2::sqr(t));
        ans = yk*(ans+t*(t-nt2::Two<A1>()*x));
        ans = yk*(ans+t);
        return nt2::oneplus(ans)*exp(-x)/xk;
      }
      A1 r =  nt2::Nan<A1>();
      bA1 test1 = le(a1, nt2::One<A1>());
      std::size_t nb = nt2::inbtrue(test1);
      if(nb > 0)
      {
        A1 xx = nt2::if_else(test1, x, One<A1>());
        A1 y1 = case_1(xx, sn, n);
        r = if_else_nan(test1, y1);
        if (nb >= meta::cardinal_of<A1>::value)
        return nt2::if_nan_else(isltza1, r);
      }
      A1 xx = nt2::if_else(test1, Two<A1>(), x);
      A1 y2 =  case_2(xx, sn, n);
      r &= nt2::if_nan_else(test1, y2);
      r =  nt2::seladd(lt(x, nt2::Maxlog<A1>()), nt2::Zero<A1>(), r);
      return nt2::if_nan_else(nt2::logical_or(nt2::is_nan(a1), isltza1), r); // we are done
    }

  private :
    template < class AA1 >
    static inline AA1 case_1(AA1 & x,  int32_t sn, const AA1 & n)
    {
      typedef typename meta::as_logical<AA1>::type bAA1;
      typedef typename meta::scalar_of<AA1>::type sA1;
      /*            Power series expansion            */
      bAA1 eqzx = nt2::is_eqz(x);
      x = nt2::seladd(eqzx, x, One<A1>()); //loop is infinite for x == 0
      sA1 psi1 = Zero<sA1>();
      for( int32_t i=sn-1; i; --i )  psi1 += rec((sA1)i);
      AA1 psi = -Euler<A1>()-nt2::log(x)+splat<A1>(psi1);
      AA1 t;
      AA1 z = -x;
      AA1 xk = nt2::Zero<A1>();
      AA1 yk = nt2::One<A1>();
      AA1 pk = nt2::One<A1>() - n;
      AA1 ans = ( sn == 1 ) ? Zero<A1>() : rec(pk);
      do
      {
        xk += nt2::One<AA1>();
        yk *= z/xk;
        pk += nt2::One<AA1>();
        ans = nt2::seladd(nt2::is_nez(pk), ans, yk/pk);
        t = nt2::if_else(nt2::is_nez(ans), nt2::abs(yk/ans), One<AA1>());
      }
      while( nt2::any(gt(t, nt2::Halfeps<A1>())));
      return nt2::seladd(eqzx,(nt2::pow(z, sn-1) * psi / nt2::gamma(n)) - ans, nt2::Inf<A1>());
      //TO DO gamma splatted from scalar or mere factorial call
    }

    template < class AA1 >
    static inline AA1 case_2(const AA1 & x,  int32_t /*sn*/, const AA1 & n)
    {
      typedef typename meta::as_logical<AA1>::type bAA1;
      int32_t sk = 1;
      AA1 t;
      AA1 pkm2 = nt2::One<AA1>();
      AA1 qkm2 = x;
      AA1 pkm1 = nt2::One<AA1>();
      AA1 qkm1 = x + n;
      AA1 ans = pkm1/qkm1;
      do
      {
        bAA1 test =  nt2::is_nez(splat<AA1>(nt2::is_odd(++sk)));
        AA1 k_2 = nt2:: splat<AA1>(sk >> 1);
        AA1 yk = nt2::if_else(test, nt2::One<AA1>(), x);
        AA1 xk = nt2::seladd(test, k_2, n);
        AA1 pk = pkm1 * yk  +  pkm2 * xk;
        AA1 qk = qkm1 * yk  +  qkm2 * xk;
        AA1 r = pk/qk;
        test = nt2::is_nez(qk);
        t = nt2::if_else(test,nt2::abs((ans-r)/r),nt2::One<AA1>());
        ans = nt2::if_else(test, r, ans);
        pkm2 = pkm1;
        pkm1 = pk;
        qkm2 = qkm1;
        qkm1 = qk;
        test = nt2::gt(nt2::abs(pk), nt2::Expnibig<AA1>());
        AA1 fac = nt2::if_else(test, Halfeps<AA1>(), nt2::One<AA1>());
        pkm2 *= fac;
        pkm1 *= fac;
        qkm2 *= fac;
        qkm1 *= fac;
      }
      while( nt2::any(nt2::gt(t, nt2::Eps<AA1>())));
      return ans*nt2::exp(-x);
    }
  };
} }

#endif
