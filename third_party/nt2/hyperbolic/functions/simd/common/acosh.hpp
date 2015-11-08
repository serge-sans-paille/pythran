//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_HYPERBOLIC_FUNCTIONS_SIMD_COMMON_ACOSH_HPP_INCLUDED
#define NT2_HYPERBOLIC_FUNCTIONS_SIMD_COMMON_ACOSH_HPP_INCLUDED
#include <nt2/hyperbolic/functions/acosh.hpp>
#include <nt2/include/constants/log_2.hpp>
#include <nt2/include/constants/oneotwoeps.hpp>
#include <nt2/include/functions/simd/if_else.hpp>
#include <nt2/include/functions/simd/is_greater.hpp>
#include <nt2/include/functions/simd/log1p.hpp>
#include <nt2/include/functions/simd/minusone.hpp>
#include <nt2/include/functions/simd/plus.hpp>
#include <nt2/include/functions/simd/seladd.hpp>
#include <nt2/include/functions/simd/sqr.hpp>
#include <nt2/include/functions/simd/sqrt.hpp>
#include <nt2/sdk/meta/as_logical.hpp>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::acosh_, tag::cpu_
                            , (A0)(X)
                            , ((simd_<floating_<A0>,X>))
                            )
  {

    typedef A0 result_type;

    NT2_FUNCTOR_CALL(1)
    {
      typedef typename meta::as_logical<A0>::type bA0;
      result_type t = minusone(a0);
      bA0 test = gt(t,Oneotwoeps<A0>());
      A0 z = if_else(test, a0, t+sqrt(t+t+sqr(t)));
      return seladd(test, log1p(z), Log_2<A0>());
    }
  };
} }
#endif
