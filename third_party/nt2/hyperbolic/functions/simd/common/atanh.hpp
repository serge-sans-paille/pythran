//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_HYPERBOLIC_FUNCTIONS_SIMD_COMMON_ATANH_HPP_INCLUDED
#define NT2_HYPERBOLIC_FUNCTIONS_SIMD_COMMON_ATANH_HPP_INCLUDED
#include <nt2/hyperbolic/functions/atanh.hpp>
#include <nt2/include/constants/half.hpp>
#include <nt2/include/functions/simd/abs.hpp>
#include <nt2/include/functions/simd/bitofsign.hpp>
#include <nt2/include/functions/simd/bitwise_xor.hpp>
#include <nt2/include/functions/simd/divides.hpp>
#include <nt2/include/functions/simd/fma.hpp>
#include <nt2/include/functions/simd/if_else.hpp>
#include <nt2/include/functions/simd/is_less.hpp>
#include <nt2/include/functions/simd/log1p.hpp>
#include <nt2/include/functions/simd/multiplies.hpp>
#include <nt2/include/functions/simd/oneminus.hpp>
#include <nt2/include/functions/simd/plus.hpp>
#include <nt2/sdk/meta/as_logical.hpp>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::atanh_, tag::cpu_
                            , (A0)(X)
                            , ((simd_<floating_<A0>,X>))
                            )
  {

    typedef A0 result_type;

    NT2_FUNCTOR_CALL(1)
    {
      typedef typename meta::as_logical<A0>::type bA0;
      A0 absa0 = nt2::abs(a0);
      A0 t =  absa0+absa0;
      A0 z1 = oneminus(absa0);
      bA0 test =  lt(absa0, Half<A0>());
      A0 tmp = if_else(test, absa0, t)/z1;
      return b_xor(bitofsign(a0), Half<A0>()*log1p(if_else(test, fma(t,tmp,t), tmp)));
    }
  };
} }
#endif
