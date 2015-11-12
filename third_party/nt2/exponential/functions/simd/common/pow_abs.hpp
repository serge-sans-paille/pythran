//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_EXPONENTIAL_FUNCTIONS_SIMD_COMMON_POW_ABS_HPP_INCLUDED
#define NT2_EXPONENTIAL_FUNCTIONS_SIMD_COMMON_POW_ABS_HPP_INCLUDED

#include <nt2/exponential/functions/pow_abs.hpp>
#include <nt2/include/constants/inf.hpp>
#include <nt2/include/constants/log2_em1.hpp>
#include <nt2/include/constants/mhalf.hpp>
#include <nt2/include/constants/one.hpp>
#include <nt2/include/constants/oneo_16.hpp>
#include <nt2/include/constants/powlargelim.hpp>
#include <nt2/include/constants/powlowlim.hpp>
#include <nt2/include/constants/sixteen.hpp>
#include <nt2/include/functions/simd/abs.hpp>
#include <nt2/include/functions/simd/divides.hpp>
#include <nt2/include/functions/simd/fma.hpp>
#include <nt2/include/functions/simd/frexp.hpp>
#include <nt2/include/functions/simd/if_else.hpp>
#include <nt2/include/functions/simd/if_else_zero.hpp>
#include <nt2/include/functions/simd/if_one_else_zero.hpp>
#include <nt2/include/functions/simd/if_zero_else.hpp>
#include <nt2/include/functions/simd/is_eqz.hpp>
#include <nt2/include/functions/simd/is_greater.hpp>
#include <nt2/include/functions/simd/is_gtz.hpp>
#include <nt2/include/functions/simd/is_less.hpp>
#include <nt2/include/functions/simd/is_odd.hpp>
#include <nt2/include/functions/simd/ldexp.hpp>
#include <nt2/include/functions/simd/logical_and.hpp>
#include <nt2/include/functions/simd/minus.hpp>
#include <nt2/include/functions/simd/multiplies.hpp>
#include <nt2/include/functions/simd/oneminus.hpp>
#include <nt2/include/functions/simd/oneplus.hpp>
#include <nt2/include/functions/simd/plus.hpp>
#include <nt2/include/functions/simd/pow2.hpp>
#include <nt2/include/functions/simd/selinc.hpp>
#include <nt2/include/functions/simd/selsub.hpp>
#include <nt2/include/functions/simd/shift_right.hpp>
#include <nt2/include/functions/simd/signnz.hpp>
#include <nt2/include/functions/simd/sqr.hpp>
#include <nt2/include/functions/simd/tofloat.hpp>
#include <nt2/include/functions/simd/toint.hpp>
#include <nt2/include/functions/simd/unary_minus.hpp>
#include <nt2/sdk/meta/as_integer.hpp>
#include <nt2/sdk/meta/as_logical.hpp>
#include <boost/simd/sdk/config.hpp>

#ifndef BOOST_SIMD_NO_INFINITIES
#include <nt2/include/constants/mzero.hpp>
#include <nt2/include/constants/minf.hpp>
#include <nt2/include/functions/simd/bitwise_and.hpp>
#include <nt2/include/functions/simd/is_equal.hpp>
#include <nt2/include/functions/simd/is_inf.hpp>
#include <nt2/include/functions/simd/is_ltz.hpp>
#endif

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::pow_abs_, tag::cpu_
                            , (A0)(X)
                            , ((simd_<floating_<A0>,X>))
                              ((simd_<floating_<A0>,X>))
                            )
  {
    typedef A0 result_type;
    NT2_FUNCTOR_CALL_REPEAT(2)
    {
      typedef typename meta::as_logical<A0>::type bA0;
      typedef typename meta::as_integer<A0>::type iA0;
      iA0 e;
      A0 ax = nt2::abs(a0);
      A0 x = frexp(ax, e);
      iA0 i  = details::pow_kernel<A0>::select(x);
      A0 z = sqr(x);
      A0 w = details::pow_kernel<A0>::pow1(x, z);
      w = fma(Mhalf<A0>(), z, w);
      w = fma(Log2_em1<A0>(), w, w);
      z = fma(Log2_em1<A0>(), x, w);
      z += x;
      w =  fma(tofloat(-i), Oneo_16<A0>(), tofloat(e));

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

      // Test the power of 2 for over/underflow
      bA0 inf_ret = gt(w, Powlargelim<A0>());
      bA0 zer_ret = lt(w, Powlowlim<A0>());
      e = toint(w);
      Wb = W - Wb;
      bA0 test = is_gtz(Wb);
      e = selinc(test, e);
      Wb = selsub(test, Wb, Oneo_16<A0>());

      z = details::pow_kernel<A0>::pow2(Wb)*Wb;
      i = selinc(is_gtz(e), (e/Sixteen<iA0>()));
      e = (i*Sixteen<iA0>()) - e;
      w =  details::pow_kernel<A0>::twomio16(e);
      z = fma(w, z, w);
      z = ldexp( z, i );
      bA0 gtax1 = gt(ax,One<A0>());
      #ifndef BOOST_SIMD_NO_INFINITIES
      z =  if_else(eq(a1,  Inf<A0>()),if_else_zero(gtax1, Inf<A0>()), z);
      z =  if_else(eq(a1, Minf<A0>()),if_zero_else(gtax1, Inf<A0>()), z);
      #endif
      z = if_zero_else(zer_ret, z);
      z = if_else(inf_ret, Inf<A0>(), z);
      z = if_else(eq(ax, One<A0>()), ax, z);
      return if_else(is_eqz(a0), if_one_else_zero(is_eqz(a1)), z);

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
