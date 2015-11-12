//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_EULER_FUNCTIONS_SIMD_COMMON_STIRLING_HPP_INCLUDED
#define NT2_EULER_FUNCTIONS_SIMD_COMMON_STIRLING_HPP_INCLUDED

#include <nt2/euler/functions/stirling.hpp>
#include <nt2/euler/functions/details/stirling_kernel.hpp>
#include <nt2/include/constants/half.hpp>
#include <nt2/include/constants/one.hpp>
#include <nt2/include/constants/sqrt_2pi.hpp>
#include <nt2/include/constants/stirlingsplitlim.hpp>
#include <nt2/include/functions/simd/exp.hpp>
#include <nt2/include/functions/simd/fma.hpp>
#include <nt2/include/functions/simd/if_else.hpp>
#include <nt2/include/functions/simd/is_less.hpp>
#include <nt2/include/functions/simd/minus.hpp>
#include <nt2/include/functions/simd/multiplies.hpp>
#include <nt2/include/functions/simd/pow.hpp>
#include <nt2/include/functions/simd/rec.hpp>
#include <nt2/include/functions/simd/unary_minus.hpp>
#include <nt2/sdk/meta/as_logical.hpp>

#include <boost/simd/sdk/config.hpp>

#ifndef BOOST_SIMD_NO_INFINITIES
#include <nt2/include/constants/inf.hpp>
#include <nt2/include/functions/simd/is_equal.hpp>
#endif

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::stirling_, tag::cpu_
                            , (A0)(X)
                            , ((simd_<floating_<A0>,X>))
                            )
  {
    typedef A0 result_type;
    NT2_FUNCTOR_CALL(1)
    {
      typedef typename meta::as_logical<A0>::type bA0;
      A0 w = nt2::rec(a0);
      w = fma(w,details::stirling_kernel<A0>::stirling1(w), nt2::One<A0>());
      A0 y = nt2::exp(-a0);
      bA0 test = is_less(a0, nt2::Stirlingsplitlim<A0>());
      A0 z =  a0 - nt2::Half<A0>();
      z =  if_else(test, z, Half<A0>()*z);
      A0 v =  nt2::pow(a0,z);
      y *= v;
      y = if_else(test,y, y*v); /* Avoid overflow in pow() */
      y *= nt2::Sqrt_2pi<A0>()*w;
      #ifndef BOOST_SIMD_NO_INFINITIES
      y = if_else(eq(a0, Inf<A0>()), a0, y);
      #endif
      return y;
    }
  };
} }

#endif
