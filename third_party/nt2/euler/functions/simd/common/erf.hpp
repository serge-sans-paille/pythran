//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_EULER_FUNCTIONS_SIMD_COMMON_ERF_HPP_INCLUDED
#define NT2_EULER_FUNCTIONS_SIMD_COMMON_ERF_HPP_INCLUDED

#include <nt2/euler/functions/erf.hpp>
#include <nt2/euler/functions/details/erf_kernel.hpp>
#include <nt2/include/constants/twothird.hpp>
#include <nt2/include/constants/zero.hpp>
#include <nt2/include/functions/simd/abs.hpp>
#include <nt2/include/functions/simd/divides.hpp>
#include <nt2/include/functions/simd/exp.hpp>
#include <nt2/include/functions/simd/if_else.hpp>
#include <nt2/include/functions/simd/inbtrue.hpp>
#include <nt2/include/functions/simd/is_less.hpp>
#include <nt2/include/functions/simd/is_ltz.hpp>
#include <nt2/include/functions/simd/logical_andnot.hpp>
#include <nt2/include/functions/simd/minus.hpp>
#include <nt2/include/functions/simd/multiplies.hpp>
#include <nt2/include/functions/simd/negif.hpp>
#include <nt2/include/functions/simd/oneminus.hpp>
#include <nt2/include/functions/simd/oneplus.hpp>
#include <nt2/include/functions/simd/plus.hpp>
#include <nt2/include/functions/simd/splat.hpp>
#include <nt2/include/functions/simd/sqr.hpp>
#include <nt2/include/functions/simd/unary_minus.hpp>
#include <nt2/sdk/meta/as_floating.hpp>
#include <nt2/sdk/meta/as_logical.hpp>
#include <nt2/sdk/meta/cardinal_of.hpp>
#include <nt2/sdk/meta/scalar_of.hpp>

#include <boost/simd/sdk/config.hpp>

#ifndef BOOST_SIMD_NO_INFINITIES
#include <nt2/include/functions/simd/is_inf.hpp>
#include <nt2/include/functions/simd/sign.hpp>
#endif

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::erf_, tag::cpu_
                            , (A0)(X)
                            , ((simd_<double_<A0>,X>))
                            )
  {
    typedef typename meta::as_floating<A0>::type result_type;
    typedef typename meta::scalar_of<A0>::type sA0;
    NT2_FUNCTOR_CALL(1)
    {
      typedef typename meta::as_logical<A0>::type bA0;

      A0 x =  nt2::abs(a0);
      A0 xx =  nt2::sqr(x);
      A0 lim1 = nt2::splat<A0>(0.65);
      A0 lim2 = nt2::splat<A0>(2.2);
      bA0 test1 = nt2::lt(x, lim1);
      A0 r1 = nt2::Zero<A0>();
      std::size_t nb = nt2::inbtrue(test1);

      if(nb > 0)
      {
        r1 = a0*details::erf_kernel<A0>::erf1(xx);
        if(nb >= meta::cardinal_of<A0>::value) return r1;
      }
      bA0 test2 = nt2::lt(x, lim2);
      bA0 test3 = nt2::logical_andnot(test2, test1);

      std::size_t nb1 = nt2::inbtrue(test3);
      A0 ex = nt2::exp(-xx);
      if(nb1 > 0)
      {
        A0 z = oneminus(ex*details::erf_kernel<A0>::erfc2(x));
        A0 r2 = nt2::negif(is_ltz(a0), z);
        r1 = nt2::if_else(test1, r1, r2);
        nb += nb1;
        if(nb >= meta::cardinal_of<A0>::value) return r1;
      }
      A0 z = nt2::negif( nt2::is_ltz(a0)
                       , nt2::oneminus(ex*details::erf_kernel<A0>::erfc3(x))
                       );
      #ifndef BOOST_SIMD_NO_INFINITIES
      z = nt2::if_else(nt2::is_inf(a0), nt2::sign(a0), z);
      #endif
      return nt2::if_else(test2, r1, z);
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::erf_, tag::cpu_
                            , (A0)(X)
                            , ((simd_<single_<A0>,X>))
                            )
  {
    typedef typename meta::as_floating<A0>::type result_type;
    typedef typename meta::scalar_of<A0>::type sA0;
    NT2_FUNCTOR_CALL(1)
    {
      typedef typename meta::as_logical<A0>::type bA0;
      A0 x =  nt2::abs(a0);
      A0 r1 = nt2::Zero<A0>();
      bA0 test1 = nt2::lt(x, Twothird<A0>());
      std::size_t nb = nt2::inbtrue(test1);
      if(nb > 0)
      {
        r1 =  a0*details::erf_kernel<A0>::erf1(sqr(x));
        if(nb >= meta::cardinal_of<A0>::value)
          return r1;
      }
      A0 z = x/oneplus(x);
      z-= nt2::splat<A0>(0.4);
      A0 r2 =   oneminus(exp(-sqr(x))*details::erf_kernel<A0>::erfc2(z));
      r2 = nt2::negif(is_ltz(a0), r2);
      r1 = if_else(test1, r1, r2);
      #ifndef BOOST_SIMD_NO_INFINITIES
      r1 = nt2::if_else(nt2::is_inf(a0), nt2::sign(a0), r1);
      #endif
      return r1;
    }
  };

} }
#endif
