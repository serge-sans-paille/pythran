//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_EULER_FUNCTIONS_SCALAR_GAMMALN_HPP_INCLUDED
#define NT2_EULER_FUNCTIONS_SCALAR_GAMMALN_HPP_INCLUDED

#include <nt2/euler/functions/gammaln.hpp>
#include <nt2/euler/functions/details/gammaln_kernel.hpp>
#include <nt2/include/constants/half.hpp>
#include <nt2/include/constants/inf.hpp>
#include <nt2/include/constants/invpi.hpp>
#include <nt2/include/constants/logpi.hpp>
#include <nt2/include/constants/logsqrt2pi.hpp>
#include <nt2/include/constants/maxgammaln.hpp>
#include <nt2/include/constants/nan.hpp>
#include <nt2/include/constants/one.hpp>
#include <nt2/include/constants/pi.hpp>
#include <nt2/include/constants/two.hpp>
#include <nt2/include/constants/zero.hpp>
#include <nt2/include/functions/scalar/abs.hpp>
#include <nt2/include/functions/scalar/dec.hpp>
#include <nt2/include/functions/scalar/floor.hpp>
#include <nt2/include/functions/scalar/fma.hpp>
#include <nt2/include/functions/scalar/inc.hpp>
#include <nt2/include/functions/scalar/is_eqz.hpp>
#include <nt2/include/functions/scalar/log.hpp>
#include <nt2/include/functions/scalar/rec.hpp>
#include <nt2/include/functions/scalar/sin.hpp>
#include <nt2/include/functions/scalar/sinpi.hpp>
#include <nt2/include/functions/scalar/sqr.hpp>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::gammaln_, tag::cpu_
                            , (A0)
                            , (scalar_< single_<A0> >)
                            )
  {
    typedef A0 result_type;
    NT2_FUNCTOR_CALL(1)
    {
      if ((a0 > Maxgammaln<A0>()) || nt2::is_eqz(a0) ) return nt2::Inf<A0>();
      A0 x = a0;
      A0 q = nt2::abs(x);
      if( x < 0.0f )
      {
        if(q > Maxgammaln<A0>()) return Nan<A0>();
        A0 w = gammaln(q);
        A0 p =  nt2::floor(q);
        if (p == q) return nt2::Inf<A0>();
        A0 z = q - p;
        if( z > nt2::Half<A0>() )
        {
          p += nt2::One<A0>();
          z = p-q;
        }
        z = q*nt2::sinpi(z);
        if( nt2::is_eqz(z) ) return nt2::Inf<A0>();
        return -log(Invpi<A0>()*nt2::abs(z))-w;
      }

      if( x < 6.5f )
      {
        A0 z = One<A0>();
        A0 tx = x;
        A0 nx = Zero<A0>();
        if( x >= 1.5f )
        {
          while( tx > 2.5f )
          {
            nx = dec(nx);
            tx = x + nx;
            z *=tx;
          }
          x += nx - Two<A0>();
          A0 p = x * details::gammaln_kernel<A0>::gammalnB(x);
          return p+nt2::log(z);

        }
        if( x >= 1.25f )
        {
          z *= x;
          x =  dec(x);
          A0 p = x *  details::gammaln_kernel<A0>::gammalnB(x);
          return p-nt2::log(z);
        }
        if( x >= 0.75f )
        {
          x = dec(x); //-= 1.0f;
          return x * details::gammaln_kernel<A0>::gammalnC(x);
        }
        while( tx < 1.5f )
        {
          if(is_eqz(tx) ) return Inf<A0>();
          z *=tx;
          nx = inc(nx);
          tx = x + nx;
        }
        x += nx - Two<A0>();
        A0 p = x *  details::gammaln_kernel<A0>::gammalnB(x);
        q = log(z);
        return p-q;
      }
      q = fma(( x - 0.5f ), nt2::log(x), Logsqrt2pi<A0>() - x);
      if( x <= 1.0e4f )
      {
        A0 z = rec(x);
        A0 p = sqr(z);
        q = fma(z, details::gammaln_kernel<A0>::gammaln2(p), q);
      }
      return q;
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::gammaln_, tag::cpu_
                            , (A0)
                            , (scalar_< double_<A0> >)
                            )
  {
    typedef A0 result_type;
    NT2_FUNCTOR_CALL(1)
    {
      if ((a0 == nt2::Inf<A0>()) || nt2::is_eqz(a0) ) return nt2::Inf<A0>();
      A0 x = a0;
      A0 q = nt2::abs(x);
      if(x > Maxgammaln<A0>()) return Inf<A0>();
      if( x < -34.0 )
      {
        if(q > Maxgammaln<A0>()) return Nan<A0>();
        A0 w = gammaln(q);
        A0 p =  nt2::floor(q);
        if (p == q) return nt2::Inf<A0>();
        A0 z = q - p;
        if( z > nt2::Half<A0>() )
        {
          p += nt2::One<A0>();
          z = p-q;
        }
        z = q*nt2::sin(Pi<A0>()*z);
        if( nt2::is_eqz(z) ) return nt2::Inf<A0>();
        return Logpi<A0>()-log(z)-w;
      }

      if( x < 13.0 )
      {
        A0 z = One<A0>();
        A0 p = Zero<A0>();
        A0 u = x;
        while( u >= 3.0 )
        {
          p -= 1.0;
          u = x + p;
          z *= u;
        }
        while( u < 2.0 )
        {
          if( u == 0.0 )  return Inf<A0>();
          z /= u;
          p += 1.0;
          u = x + p;
        }
        z = nt2::abs(z);
        if( u == 2.0 ) return( nt2::log(z) );
        p -= 2.0;
        x = x + p;
        p = x * details::gammaln_kernel<A0>::gammaln1(x);
        return nt2::log(z) + p ;
      }
      q = fma(( x - 0.5 ), nt2::log(x), Logsqrt2pi<A0>()-x);
      if( x > 1.0e8 )
        return( q );

      A0 p = rec(sqr(x));
      q += details::gammaln_kernel<A0>::gammalnA(p)/x;
      return q;
    }
  };
} }

#endif
