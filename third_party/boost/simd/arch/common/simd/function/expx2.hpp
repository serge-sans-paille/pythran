//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_COMMON_SIMD_FUNCTION_EXPX2_HPP_INCLUDED
#define BOOST_SIMD_ARCH_COMMON_SIMD_FUNCTION_EXPX2_HPP_INCLUDED

#include <boost/simd/detail/overload.hpp>
#include <boost/simd/detail/constant/expx2c1.hpp>
#include <boost/simd/detail/constant/expx2c2.hpp>
#include <boost/simd/constant/half.hpp>
#include <boost/simd/constant/inf.hpp>
#include <boost/simd/detail/constant/maxlog.hpp>
#include <boost/simd/function/abs.hpp>
#include <boost/simd/function/exp.hpp>
#include <boost/simd/function/floor.hpp>
#include <boost/simd/function/fma.hpp>
#include <boost/simd/function/if_else.hpp>
#include <boost/simd/function/is_greater.hpp>
#include <boost/simd/function/minus.hpp>
#include <boost/simd/function/multiplies.hpp>
#include <boost/simd/function/plus.hpp>
#include <boost/simd/function/signnz.hpp>
#include <boost/simd/function/sqr.hpp>

#ifndef BOOST_SIMD_NO_INFINITIES
#include <boost/simd/function/is_equal.hpp>
#endif

namespace boost { namespace simd { namespace ext
{
   namespace bd = boost::dispatch;
   namespace bs = boost::simd;
   BOOST_DISPATCH_OVERLOAD_IF( expx2_
                          , (typename A0, typename X)
                          , (detail::is_native<X>)
                          , bd::cpu_
                          , bs::pack_<bd::floating_<A0>, X>
                          )
   {
     BOOST_FORCEINLINE A0 operator()(const A0& a0) const
      {
        A0 x =  bs::abs(a0);
        // Represent x as an exact multiple of 1/32 plus a residual.
        A0 m = Expx2c1<A0>()*bs::floor(fma(Expx2c2<A0>(), x, bs::Half<A0>()));
        A0 f =  x-m;
        // x**2 = m**2 + 2mf + f**2
        A0 u = bs::sqr(m);
        A0 u1 = fma(m+m,f,sqr(f));
        // u is exact, u1 is small.
        A0 r = bs::if_else(bs::is_greater(u+u1, bs::Maxlog<A0>()),
                            bs::Inf<A0>(),
                            bs::exp(u)*bs::exp(u1));
        #ifndef BOOST_SIMD_NO_INFINITIES
        r =  bs::if_else(is_equal(x, Inf<A0>()), x, r);
        #endif
        return r;
      }
   };

   BOOST_DISPATCH_OVERLOAD_IF( expx2_
                          , (typename A0, typename X)
                          , (detail::is_native<X>)
                          , bd::cpu_
                          , bs::pack_<bd::floating_<A0>, X>
                          , bs::pack_<bd::floating_<A0>, X>
                          )
   {
     BOOST_FORCEINLINE A0 operator()(const A0& a0,  const A0 & s) const
      {
        A0 sgn =  signnz(s);
        A0 x =  a0*sgn;
        // Represent x as an exact multiple of 1/32 plus a residual.
        A0 m = Expx2c1<A0>()*bs::floor(fma(Expx2c2<A0>(), x, bs::Half<A0>()));
        A0 f =  x-m;
        // x**2 = m**2 + 2mf + f**2
        A0 u = sgn*bs::sqr(m);
        A0 u1 = sgn*fma(m+m,f,sqr(f));
        // u is exact, u1 is small.
        A0 r = bs::if_else(bs::is_greater(u+u1, bs::Maxlog<A0>()),
                            bs::Inf<A0>(),
                            bs::exp(u)*bs::exp(u1));
        #ifndef BOOST_SIMD_NO_INFINITIES
        r =  bs::if_else(is_equal(x, Inf<A0>()), x, r);
        #endif
        return r;
      }
   };

} } }

#endif
