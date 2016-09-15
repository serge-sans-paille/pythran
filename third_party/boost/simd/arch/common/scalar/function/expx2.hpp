//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_COMMON_SCALAR_FUNCTION_EXPX2_HPP_INCLUDED
#define BOOST_SIMD_ARCH_COMMON_SCALAR_FUNCTION_EXPX2_HPP_INCLUDED

// #include <boost/simd/detail/constant/expx2c1.hpp>
// #include <boost/simd/detail/constant/expx2c2.hpp>
#include <boost/simd/constant/half.hpp>
#include <boost/simd/constant/inf.hpp>
#include <boost/simd/detail/constant/maxlog.hpp>
#include <boost/simd/constant/real.hpp>
#include <boost/simd/constant/two.hpp>
#include <boost/simd/function/abs.hpp>
#include <boost/simd/function/exp.hpp>
#include <boost/simd/function/floor.hpp>
#include <boost/simd/function/fma.hpp>
#include <boost/simd/function/signnz.hpp>
#include <boost/simd/function/sqr.hpp>
#include <boost/simd/detail/dispatch/function/overload.hpp>
#include <boost/config.hpp>

namespace boost { namespace simd { namespace ext
{
  namespace bd = boost::dispatch;
  namespace bs = boost::simd;
  BOOST_DISPATCH_OVERLOAD ( expx2_
                          , (typename A0)
                          , bd::cpu_
                          , bd::scalar_< bd::floating_<A0> >
                          )
  {
    BOOST_FORCEINLINE A0 operator() ( A0 a0) const BOOST_NOEXCEPT
    {
    #ifndef BOOST_SIMD_NO_INFINITIES
      if (is_inf(a0)) return Inf<A0>();
    #endif
      A0 x =  bs::abs(a0);
      const A0 Expx2c1 = Real<A0, 0x4060000000000000ull, 0x42000000UL>();
      const A0 Expx2c2 = Real<A0, 0x3f80000000000000ull, 0x3d000000UL>();
      /* Represent x as an exact multiple of 1/32 plus a residual.  */
      A0 m = Expx2c1 * bs::floor(fma(Expx2c2, x, Half<A0>()));
      x -= m;
      /* x**2 = m**2 + 2mf + f**2 */
      A0 u = sqr(m);
      A0 u1 = fma(Two<A0>() * m, x, sqr(x));
      if ((u+u1) > bs::Maxlog<A0>()) return Inf<A0>();
      /* u is exact, u1 is small.  */
      return exp(u)*exp(u1);
    }
  };

  BOOST_DISPATCH_OVERLOAD ( expx2_
                          , (typename A0)
                          , bd::cpu_
                          , bd::scalar_<bd::floating_<A0> >
                          , bd::scalar_<bd::floating_<A0> >
                          )
  {
    BOOST_FORCEINLINE A0 operator() ( A0 a0, A0 s) const BOOST_NOEXCEPT
    {
      const A0 Expx2c1 = Real<A0, 0x4060000000000000ull, 0x42000000UL>();
      const A0 Expx2c2 = Real<A0, 0x3f80000000000000ull, 0x3d000000UL>();
      A0 sgn =  signnz(s);
      A0 x =  a0*sgn;
    #ifndef BOOST_SIMD_NO_INFINITIES
      if (bs::is_inf(a0)) return bs::Inf<A0>();
    #endif
      // Represent x as an exact multiple of 1/32 plus a residual.
      A0 m = Expx2c1*floor(fma(Expx2c2, x, Half<A0>()));
      A0 f =  x-m;
      // x**2 = m**2 + 2mf + f**2
      A0 u = sgn*sqr(m);
      A0 u1 = sgn*fma(m+m,f,sqr(f));
      // u is exact, u1 is small.
      if (u+u1 > Maxlog<A0>()) return bs::Inf<A0>();
      return exp(u)*exp(u1);
    }
  };
} } }


#endif
