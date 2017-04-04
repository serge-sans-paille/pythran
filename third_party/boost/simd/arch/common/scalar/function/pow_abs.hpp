//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_COMMON_SCALAR_FUNCTION_POW_ABS_HPP_INCLUDED
#define BOOST_SIMD_ARCH_COMMON_SCALAR_FUNCTION_POW_ABS_HPP_INCLUDED

#ifndef BOOST_SIMD_NO_INVALIDS
#include <boost/simd/constant/nan.hpp>
#include <boost/simd/function/is_nan.hpp>
#endif
#include <boost/simd/arch/common/detail/generic/pow_kernel.hpp>
#include <boost/simd/constant/inf.hpp>
#include <boost/simd/constant/log2_em1.hpp>
#include <boost/simd/constant/mhalf.hpp>
#include <boost/simd/constant/minf.hpp>
#include <boost/simd/detail/constant/powlargelim.hpp>
#include <boost/simd/detail/constant/powlowlim.hpp>
#include <boost/simd/constant/ratio.hpp>
#include <boost/simd/constant/zero.hpp>
#include <boost/simd/function/abs.hpp>
#include <boost/simd/function/exp.hpp>
#include <boost/simd/function/floor.hpp>
#include <boost/simd/function/fma.hpp>
#include <boost/simd/function/fms.hpp>
#include <boost/simd/function/ifrexp.hpp>
#include <boost/simd/function/if_else.hpp>
#include <boost/simd/function/is_eqz.hpp>
#include <boost/simd/function/is_ltz.hpp>
#include <boost/simd/function/ldexp.hpp>
#include <boost/simd/function/log.hpp>
#include <boost/simd/function/pow2.hpp>
#include <boost/simd/function/sqr.hpp>
#include <boost/simd/detail/dispatch/function/overload.hpp>
#include <boost/simd/detail/dispatch/meta/as_integer.hpp>
#include <boost/config.hpp>
#include <tuple>

namespace boost { namespace simd { namespace ext
{
  namespace bd = boost::dispatch;
  namespace bs = boost::simd;

  BOOST_DISPATCH_OVERLOAD ( pow_abs_
                          , (typename A0, typename A1)
                          , bd::cpu_
                          , bd::scalar_< bd::floating_<A0> >
                          , bd::scalar_< bd::floating_<A1> >
                          )
  {
    inline A0 operator() ( A0 const& a0, A1 const& a1) const BOOST_NOEXCEPT
    {
      const A0 Oneo_16 = Ratio<A0, 1, 16>();
      using i_t = bd::as_integer_t<A0>;
      const i_t Sixteen = Ratio<i_t, 16>();
      A0 x =  bs::abs(a0);
      if (x == One<A0>()) return x;
      if (is_eqz(x)) return is_eqz(a1) ? One<A0>() : is_ltz(a1) ? Inf<A0>() : Zero<A0>();
    #ifndef BOOST_SIMD_NO_INFINITIES
      if(x == a1 && a1 == Inf<A0>())  return Inf<A0>();
      if(x == Inf<A0>() && a1 == Minf<A0>()) return Zero<A0>();
      if(a1 == Inf<A0>()) return (x < One<A0>()) ? Zero<A0>() : Inf<A0>();
      if(a1 == Minf<A0>()) return (x >  One<A0>()) ? Zero<A0>() : Inf<A0>();
      if(x == Inf<A0>()) return (a1 < Zero<A0>()) ? Zero<A0>() : ((a1 == Zero<A0>()) ? One<A0>() : Inf<A0>());
    #endif
    #ifndef BOOST_SIMD_NO_INVALIDS
      if(is_nan(a0)) return is_eqz(a1) ? One<A0>() : a0;
      if(is_nan(a1)) return Nan<A0>();
    #endif
      i_t e;
      std::tie(x, e) = pedantic_(bs::ifrexp)(x);
      i_t i  = detail::pow_kernel<A0>::select(x);
      A0 z = sqr(x);
      A0 w = detail::pow_kernel<A0>::pow1(x, z);
      w = fma(Mhalf<A0>(), z, w);
      w = fma(Log2_em1<A0>(), w, w);
      z = fma(Log2_em1<A0>(), x, w);
      z += x;
      w =  fma(A0(-i), Oneo_16, A0(e));
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
      w = Ratio<A0, 16>()*(Wa + Wb);

      // Test the power of 2 for overflow
      if( w > Powlargelim<A0>() ) return Inf<A0>();
      if( w < Powlowlim<A0>()   ) return Zero<A0>();
      e = w;
      Wb = W - Wb;  //
      if( Wb > 0.0f ) //
      {
        ++e;
        Wb -= Oneo_16; //
      }
      z = detail::pow_kernel<A0>::pow2(Wb)*Wb; //
      i = (e/Sixteen) + (e>=0);
      e = fms(i, Sixteen, e);
      w =  detail::pow_kernel<A0>::twomio16(e);
      z = fma(w, z, w);
      z = pedantic_(ldexp)( z, i );
      return z;
    }
  private :
    static BOOST_FORCEINLINE A0 reduc(A0 x) BOOST_NOEXCEPT
    {
      // Find a multiple of 1/16 that is within 1/16 of x.
      return Ratio<A0, 1, 16>()*floor(Ratio<A0, 16>()*x);
    }
  };

  BOOST_DISPATCH_OVERLOAD ( pow_abs_
                          , (typename A0, typename A1)
                          , bd::cpu_
                          , bs::raw_tag
                          , bd::scalar_< bd::floating_<A0> >
                          , bd::scalar_< bd::floating_<A1> >
                          )
  {
    BOOST_FORCEINLINE A0 operator()(const raw_tag &, A0 a0, A1 a1) const BOOST_NOEXCEPT
    {
      return bs::exp(a1*bs::log(bs::abs(a0)));
    }
  };



} } }


#endif
