//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_EXPONENTIAL_FUNCTIONS_SCALAR_EXPX2_HPP_INCLUDED
#define NT2_EXPONENTIAL_FUNCTIONS_SCALAR_EXPX2_HPP_INCLUDED
#include <nt2/exponential/functions/expx2.hpp>
#include <boost/simd/sdk/config.hpp>
#include <nt2/include/constants/expx2c1.hpp>
#include <nt2/include/constants/expx2c2.hpp>
#include <nt2/include/constants/half.hpp>
#include <nt2/include/constants/inf.hpp>
#include <nt2/include/constants/maxlog.hpp>
#include <nt2/include/constants/two.hpp>
#include <nt2/include/functions/scalar/abs.hpp>
#include <nt2/include/functions/scalar/exp.hpp>
#include <nt2/include/functions/scalar/floor.hpp>
#include <nt2/include/functions/scalar/fma.hpp>
#include <nt2/include/functions/scalar/signnz.hpp>
#include <nt2/include/functions/scalar/sqr.hpp>

#ifndef BOOST_SIMD_NO_INFINITIES
#include <nt2/include/functions/scalar/is_inf.hpp>
#endif

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::expx2_, tag::cpu_
                            , (A0)
                            , (scalar_< floating_<A0> >)
                            )
  {
    typedef A0 result_type;
    NT2_FUNCTOR_CALL(1)
    {
      #ifndef BOOST_SIMD_NO_INFINITIES
      if (nt2::is_inf(a0)) return nt2::Inf<A0>();
      #endif
      A0 x =  nt2::abs(a0);
      /* Represent x as an exact multiple of 1/32 plus a residual.  */
      A0 m = nt2::Expx2c1<A0>() * nt2::floor(nt2::Expx2c2<A0>() * x + Half<A0>());
      x -= m;
      /* x**2 = m**2 + 2mf + f**2 */
      A0 u = sqr(m);
      A0 u1 = nt2::Two<A0>() * m * x  +  nt2::sqr(x);
      if ((u+u1) > nt2::Maxlog<A0>()) return nt2::Inf<A0>();
      /* u is exact, u1 is small.  */
      return nt2::exp(u) * nt2::exp(u1);
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::expx2_, tag::cpu_
                            , (A0)
                            , ((scalar_<floating_<A0> >))
                              ((scalar_<floating_<A0> >))
                            )
  {
    typedef A0 result_type;
    BOOST_FORCEINLINE result_type operator()(const A0& a0,  const A0 & s) const
    {
      A0 sgn =  signnz(s);
      A0 x =  a0*sgn;
      #ifndef BOOST_SIMD_NO_INFINITIES
      if (nt2::is_inf(a0)) return nt2::Inf<A0>();
      #endif
      // Represent x as an exact multiple of 1/32 plus a residual.
      A0 m = Expx2c1<A0>()*nt2::floor(fma(Expx2c2<A0>(), x, nt2::Half<A0>()));
      A0 f =  x-m;
      // x**2 = m**2 + 2mf + f**2
      A0 u = sgn*nt2::sqr(m);
      A0 u1 = sgn*fma(m+m,f,sqr(f));
      // u is exact, u1 is small.
      if (u+u1 >  nt2::Maxlog<A0>()) return nt2::Inf<A0>();
      return nt2::exp(u)*nt2::exp(u1);
    }
  };
} }

#endif
