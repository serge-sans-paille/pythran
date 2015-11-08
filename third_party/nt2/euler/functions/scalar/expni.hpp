//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_EULER_FUNCTIONS_SCALAR_EXPNI_HPP_INCLUDED
#define NT2_EULER_FUNCTIONS_SCALAR_EXPNI_HPP_INCLUDED

#include <nt2/euler/functions/expni.hpp>
#include <nt2/include/functions/scalar/log.hpp>
#include <nt2/include/functions/scalar/exp.hpp>
#include <nt2/include/functions/scalar/oneplus.hpp>
#include <nt2/include/functions/scalar/sqr.hpp>
#include <nt2/include/functions/scalar/rec.hpp>
#include <nt2/include/functions/scalar/abs.hpp>
#include <nt2/include/functions/scalar/pow.hpp>
#include <nt2/include/functions/scalar/gamma.hpp>
#include <nt2/include/functions/scalar/is_nez.hpp>
#include <nt2/include/functions/scalar/is_eqz.hpp>
#include <nt2/include/functions/scalar/is_odd.hpp>
#include <nt2/include/functions/scalar/exp.hpp>
#include <nt2/include/constants/maxlog.hpp>
#include <nt2/include/constants/nan.hpp>
#include <nt2/include/constants/inf.hpp>
#include <nt2/include/constants/zero.hpp>
#include <nt2/include/constants/six.hpp>
#include <nt2/include/constants/one.hpp>
#include <nt2/include/constants/euler.hpp>
#include <nt2/include/constants/eight.hpp>
#include <nt2/include/constants/halfeps.hpp>
#include <nt2/include/constants/expnibig.hpp>

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A1 is arithmetic_
/////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::expni_, tag::cpu_
                            , (A0)(A1)
                            , (scalar_< integer_<A0> >)(scalar_< arithmetic_<A1> >)
                            )
  {
    typedef typename boost::dispatch::meta::as_floating<A1>::type result_type;
    NT2_FUNCTOR_CALL(2)
    {
      return nt2::expni(a0, result_type(a1));
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::expni_, tag::cpu_
                            , (A0)(A1)
                            , (scalar_< integer_<A0> >)(scalar_< floating_<A1> >)
                            )
  {
    typedef A1 result_type;
    NT2_FUNCTOR_CALL(2)
    {
      A1 x = a1;
      const int32_t n =  a0;
      if( n < 0 ||  x < nt2::Zero<A1>())      return nt2::Nan<A1>();
      if( x > nt2::Maxlog<A1>() )    return Zero<A1>();
      if( nt2::is_eqz(x) )           return (n < 2) ? nt2::Inf<A1>() : rec(n-nt2::One<A1>());
      if( n == 0 )              return nt2::exp(-x)/x;
      /* Expansion for large n */
      if( n > 5000 )
      {
        A1 xk = x + n;
        A1 yk = nt2::rec(nt2::sqr(xk));
        A1 t = (A1)n;
        A1 ans = yk*t*(nt2::Six<A1>()*sqr(x)-nt2::Eight<A1>()*t*x+nt2::sqr(t));
        ans = yk*(ans+t*(t-nt2::Two<A1>()*x));
        ans = yk*(ans+t);
        return nt2::oneplus(ans)*nt2::exp(-x)/xk;
      }

      if( x <=  One<A1>() )
      {
        /*        Power series expansion        */
        A1 psi = -Euler<A1>() - nt2::log(x);
        for( int32_t i=n-1; i; --i )  psi += nt2::rec((A1)i);
        A1 t;
        A1 z = -x;
        A1 xk = nt2::Zero<A1>();
        A1 yk = nt2::One<A1>();
        A1 pk = nt2::One<A1>() - n;
        A1 ans = ( n == 1 ) ? nt2::Zero<A1>() : nt2::rec(pk);
        do
        {
          xk += nt2::One<A1>();
          yk *= z/xk;
          pk += nt2::One<A1>();
          if(nt2::is_nez(pk)) ans += yk/pk;
          t = nt2::is_nez(ans) ? nt2::abs(yk/ans) : nt2::One<A1>();
        }
        while( t > nt2::Halfeps<A1>() );
        t = n;
        A1 r = n - 1;
        return (nt2::pow(z, r) * psi / gamma(t)) - ans;
      }
      /*          continued fraction            */
      int32_t k = 1;
      A1 t;
      A1 pkm2 = nt2::One<A1>();
      A1 qkm2 = x;
      A1 pkm1 =  nt2::One<A1>();
      A1 qkm1 = x + (A1)n;
      A1 ans = pkm1/qkm1;
      do
      {
        bool test =  nt2::is_odd(++k);
        A1 yk = test ? nt2::One<A1>() : x;
        A1 xk = test ? n + (k-1)/2 : k/2;
        A1 pk = pkm1 * yk  +  pkm2 * xk;
        A1 qk = qkm1 * yk  +  qkm2 * xk;
        if( nt2::is_nez(qk) )
        {
          A1 r = pk/qk;
          t = nt2::abs( (ans - r)/r );
          ans = r;
        }
        else
        {
          t = nt2::One<A1>();
        }
        pkm2 = pkm1;
        pkm1 = pk;
        qkm2 = qkm1;
        qkm1 = qk;
        if( nt2::abs(pk) > nt2::Expnibig<A1>() )
        {
          pkm2 *= nt2::Halfeps<A1>();
          pkm1 *= nt2::Halfeps<A1>();
          qkm2 *= nt2::Halfeps<A1>();
          qkm1 *= nt2::Halfeps<A1>();
        }
      }
      while( t > nt2::Halfeps<A1>() );
      return( ans*nt2::exp( -x ) );
    }
  };
} }


#endif
