//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_EXPONENTIAL_FUNCTIONS_SIMD_COMMON_EXPX2_HPP_INCLUDED
#define NT2_EXPONENTIAL_FUNCTIONS_SIMD_COMMON_EXPX2_HPP_INCLUDED

#include <nt2/exponential/functions/expx2.hpp>
#include <boost/simd/sdk/config.hpp>
#include <nt2/include/constants/expx2c1.hpp>
#include <nt2/include/constants/expx2c2.hpp>
#include <nt2/include/constants/half.hpp>
#include <nt2/include/constants/inf.hpp>
#include <nt2/include/constants/maxlog.hpp>
#include <nt2/include/functions/simd/abs.hpp>
#include <nt2/include/functions/simd/exp.hpp>
#include <nt2/include/functions/simd/floor.hpp>
#include <nt2/include/functions/simd/fma.hpp>
#include <nt2/include/functions/simd/if_else.hpp>
#include <nt2/include/functions/simd/is_greater.hpp>
#include <nt2/include/functions/simd/minus.hpp>
#include <nt2/include/functions/simd/multiplies.hpp>
#include <nt2/include/functions/simd/plus.hpp>
#include <nt2/include/functions/simd/signnz.hpp>
#include <nt2/include/functions/simd/sqr.hpp>

#ifndef BOOST_SIMD_NO_INFINITIES
#include <nt2/include/functions/simd/is_equal.hpp>
#endif

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::expx2_, tag::cpu_
                            , (A0)(X)
                            , ((simd_<floating_<A0>,X>))
                            )
  {
    typedef A0 result_type;
    BOOST_FORCEINLINE result_type operator()(const A0& a0) const
    {
      A0 x =  nt2::abs(a0);
      // Represent x as an exact multiple of 1/32 plus a residual.
      A0 m = Expx2c1<A0>()*nt2::floor(fma(Expx2c2<A0>(), x, nt2::Half<A0>()));
      A0 f =  x-m;
      // x**2 = m**2 + 2mf + f**2
      A0 u = nt2::sqr(m);
      A0 u1 = fma(m+m,f,sqr(f));
      // u is exact, u1 is small.
      A0 r = nt2::if_else(nt2::gt(u+u1, nt2::Maxlog<A0>()),
                          nt2::Inf<A0>(),
                          nt2::exp(u)*nt2::exp(u1));
      #ifndef BOOST_SIMD_NO_INFINITIES
      r =  nt2::if_else(eq(x, Inf<A0>()), x, r);
      #endif
      return r;
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::expx2_, tag::cpu_
                            , (A0)(X)
                            , ((simd_<floating_<A0>,X>))
                              ((simd_<floating_<A0>,X>))
                            )
  {
    typedef A0 result_type;
    BOOST_FORCEINLINE result_type operator()(const A0& a0,  const A0 & s) const
    {
      A0 sgn =  signnz(s);
      A0 x =  a0*sgn;
      // Represent x as an exact multiple of 1/32 plus a residual.
      A0 m = Expx2c1<A0>()*nt2::floor(fma(Expx2c2<A0>(), x, nt2::Half<A0>()));
      A0 f =  x-m;
      // x**2 = m**2 + 2mf + f**2
      A0 u = sgn*nt2::sqr(m);
      A0 u1 = sgn*fma(m+m,f,sqr(f));
      // u is exact, u1 is small.
      A0 r = nt2::if_else(nt2::gt(u+u1, nt2::Maxlog<A0>()),
                          nt2::Inf<A0>(),
                          nt2::exp(u)*nt2::exp(u1));
      #ifndef BOOST_SIMD_NO_INFINITIES
      r =  nt2::if_else(eq(x, Inf<A0>()), x, r);
      #endif
      return r;
    }
  };
} }

#endif
