//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_EULER_FUNCTIONS_SIMD_COMMON_ERFC_HPP_INCLUDED
#define NT2_EULER_FUNCTIONS_SIMD_COMMON_ERFC_HPP_INCLUDED

#include <nt2/euler/functions/erfc.hpp>
#include <nt2/euler/functions/details/erf_kernel.hpp>
#include <nt2/include/constants/two.hpp>
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
#include <nt2/include/functions/simd/oneminus.hpp>
#include <nt2/include/functions/simd/oneplus.hpp>
#include <nt2/include/functions/simd/plus.hpp>
#include <nt2/include/functions/simd/splat.hpp>
#include <nt2/include/functions/simd/sqr.hpp>
#include <nt2/include/functions/simd/unary_minus.hpp>
#include <nt2/sdk/meta/as_logical.hpp>
#include <nt2/sdk/meta/cardinal_of.hpp>

#include <boost/simd/sdk/config.hpp>

#ifndef BOOST_SIMD_NO_INFINITIES
#include <nt2/include/constants/inf.hpp>
#include <nt2/include/functions/simd/if_zero_else.hpp>
#include <nt2/include/functions/simd/is_equal.hpp>
#endif

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::erfc_, tag::cpu_
                              , (A0)(X)
                              , ((simd_<double_<A0>,X>))
                              )
  {
    typedef A0 result_type;
    NT2_FUNCTOR_CALL(1)
    {
      typedef typename meta::as_logical<A0>::type bA0;

      A0 x =  nt2::abs(a0);
      A0 xx =  nt2::sqr(x);
      A0 lim1 = nt2::splat<A0>(0.65);
      A0 lim2 = nt2::splat<A0>(2.2);
      bA0 test0 = nt2::is_ltz(a0);
      bA0 test1 = nt2::lt(x, lim1);
      A0 r1 = nt2::Zero<A0>();
      std::size_t nb = nt2::inbtrue(test1);
      if(nb > 0)
      {
        r1 = nt2::oneminus(x*details::erf_kernel<A0>::erf1(xx));
        if (nb >= meta::cardinal_of<A0>::value)
          return nt2::if_else(test0, nt2::Two<A0>()-r1, r1);
      }
      bA0 test2 = nt2::lt(x, lim2);
      bA0 test3 = nt2::logical_andnot(test2, test1);
      A0 ex = nt2::exp(-xx);

      std::size_t nb1 = nt2::inbtrue(test3);
      if(nb1 > 0)
      {
        A0 z = ex*details::erf_kernel<A0>::erfc2(x);
        r1 = nt2::if_else(test1, r1, z);
        nb += nb1;
        if (nb >= meta::cardinal_of<A0>::value)
          return nt2::if_else(test0, Two<A0>()-r1, r1);
      }
      A0 z =  ex*details::erf_kernel<A0>::erfc3(x);
      r1 = nt2::if_else(test2, r1, z);
      #ifndef BOOST_SIMD_NO_INFINITIES
      r1 = if_zero_else( eq(x, Inf<A0>()), r1);
      #endif
      return  nt2::if_else(test0, nt2::Two<A0>()-r1, r1);
      }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::erfc_, tag::cpu_
                              , (A0)(X)
                              , ((simd_<single_<A0>,X>))
                              )
  {
    typedef A0 result_type;
    NT2_FUNCTOR_CALL(1)
    {
      typedef typename meta::as_logical<A0>::type bA0;

      A0 x =  nt2::abs(a0);
      bA0 test0 = nt2::is_ltz(a0);
      A0 r1 = nt2::Zero<A0>();
      bA0 test1 = nt2::lt(x, Twothird<A0>());
      A0 z = x/oneplus(x);

      std::size_t nb = nt2::inbtrue(test1);
      if(nb > 0)
      {
        r1 = details::erf_kernel<A0>::erfc3(z);
        if (nb >= meta::cardinal_of<A0>::value)
          return nt2::if_else(test0, nt2::Two<A0>()-r1, r1);
      }
      z -= nt2::splat<A0>(0.4);
      A0 r2 = exp(-sqr(x))*details::erf_kernel<A0>::erfc2(z);
      r1 = if_else(test1, r1, r2);
      #ifndef BOOST_SIMD_NO_INFINITIES
      r1 = if_zero_else( eq(x, Inf<A0>()), r1);
      #endif
      return nt2::if_else(test0, nt2::Two<A0>()-r1, r1);
    }
  };
} }

#endif
