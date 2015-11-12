//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_EXPONENTIAL_FUNCTIONS_SCALAR_POW_ABS_HPP_INCLUDED
#define NT2_EXPONENTIAL_FUNCTIONS_SCALAR_POW_ABS_HPP_INCLUDED

#include <nt2/exponential/functions/pow_abs.hpp>
#include <nt2/exponential/functions/details/pow_kernel.hpp>
#include <nt2/include/constants/inf.hpp>
#include <nt2/include/constants/log2_em1.hpp>
#include <nt2/include/constants/mhalf.hpp>
#include <nt2/include/constants/oneo_16.hpp>
#include <nt2/include/constants/powlargelim.hpp>
#include <nt2/include/constants/powlowlim.hpp>
#include <nt2/include/constants/sixteen.hpp>
#include <nt2/include/constants/zero.hpp>
#include <nt2/include/functions/abs.hpp>
#include <nt2/include/functions/floor.hpp>
#include <nt2/include/functions/fma.hpp>
#include <nt2/include/functions/fms.hpp>
#include <nt2/include/functions/frexp.hpp>
#include <nt2/include/functions/if_else.hpp>
#include <nt2/include/functions/is_eqz.hpp>
#include <nt2/include/functions/ldexp.hpp>
#include <nt2/include/functions/pow2.hpp>
#include <nt2/include/functions/sqr.hpp>
#include <nt2/sdk/meta/as_integer.hpp>
#include <nt2/sdk/meta/as_real.hpp>

#include <boost/dispatch/attributes.hpp>
#include <boost/simd/sdk/config.hpp>

#ifndef BOOST_SIMD_NO_INVALIDS
#include <nt2/include/constants/nan.hpp>
#include <nt2/include/functions/is_nan.hpp>
#endif

namespace nt2 { namespace ext
{

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::pow_abs_, tag::cpu_
                            , (A0)(A1)
                            , (scalar_< floating_<A0> >)
                              (scalar_< floating_<A1> >)
                            )
  {
    typedef A0 result_type;

    NT2_FUNCTOR_CALL(2)
    {
      typedef typename meta::as_integer<A0>::type  iA0;
      A0 x =  nt2::abs(a0);
      if (x == One<A0>()) return x;
      if (is_eqz(x)) return is_eqz(a1);
      #ifndef BOOST_SIMD_NO_INFINITIES
      if(x == a1 && a1 == Inf<A0>())  return Inf<A0>();
      if(x == Inf<A0>() && a1 == Minf<A0>()) return Zero<A0>();
      if(a1 == Inf<A0>()) return (x < One<A0>()) ? Zero<A0>() : Inf<A0>();
      if(a1 == Minf<A0>()) return (x >  One<A0>()) ? Zero<A0>() : Inf<A0>();
      #endif
      #ifndef BOOST_SIMD_NO_INVALIDS
      if(is_nan(a0) || is_nan(a1)) return Nan<A0>();
      #endif

      iA0 e;
      x = frexp(x, e );
      iA0 i  = details::pow_kernel<A0>::select(x);
      A0 z = sqr(x);
      A0 w = details::pow_kernel<A0>::pow1(x, z);
      w = fma(Mhalf<A0>(), z, w);
      w = fma(Log2_em1<A0>(), w, w);
      z = fma(Log2_em1<A0>(), x, w);
      z += x;
      w =  fma(A0(-i), Oneo_16<A0>(), A0(e));
      A0 ya = reduc(a1);
      A0 yb = a1 - ya;
      A0 W = fma(z, a1, w*yb);
      A0 Wa = reduc(W);
      A0 Wb = W - Wa;
      W = fma(w, ya, Wa);
      Wa = reduc(W);
      A0 u = W - Wa;
      W = Wb + u;
      Wb = reduc(W);
      w = Sixteen<A0>()*(Wa + Wb);

      // Test the power of 2 for overflow
      if( w > Powlargelim<A0>() ) return Inf<A0>();
      if( w < Powlowlim<A0>()   ) return Zero<A0>();
      e = w;
      Wb = W - Wb;  //
      if( Wb > 0.0f ) //
      {
        ++e;
        Wb -= Oneo_16<A0>(); //
      }
      z = details::pow_kernel<A0>::pow2(Wb)*Wb; //
      i = (e/Sixteen<iA0>()) + (e>=0);
      e = fms(i, Sixteen<iA0>(), e);
      w =  details::pow_kernel<A0>::twomio16(e);
      z = fma(w, z, w);
      z = ldexp( z, i );
      return z;
    }
  private :
    static BOOST_FORCEINLINE A0 reduc(const A0& x)
    {
      // Find a multiple of 1/16 that is within 1/16 of x.
      return Oneo_16<A0>()*floor(Sixteen<A0>()*x);
    }
  };
} }

#endif
