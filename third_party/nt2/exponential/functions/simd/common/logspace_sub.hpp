//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_EXPONENTIAL_FUNCTIONS_SIMD_COMMON_LOGSPACE_SUB_HPP_INCLUDED
#define NT2_EXPONENTIAL_FUNCTIONS_SIMD_COMMON_LOGSPACE_SUB_HPP_INCLUDED

#include <nt2/exponential/functions/logspace_sub.hpp>
#include <nt2/include/constants/log_2.hpp>
#include <nt2/include/functions/simd/exp.hpp>
#include <nt2/include/functions/simd/expm1.hpp>
#include <nt2/include/functions/simd/if_else.hpp>
#include <nt2/include/functions/simd/is_greater.hpp>
#include <nt2/include/functions/simd/log.hpp>
#include <nt2/include/functions/simd/log1p.hpp>
#include <nt2/include/functions/simd/minus.hpp>
#include <nt2/include/functions/simd/plus.hpp>
#include <nt2/include/functions/simd/unary_minus.hpp>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::logspace_sub_, tag::cpu_
                            , (A0)(X)
                            , ((simd_< floating_<A0>, X >))
                              ((simd_< floating_<A0>, X >))
                            )
  {
    typedef A0 result_type;
    NT2_FUNCTOR_CALL_REPEAT(2)
    {
      A0 x = a1-a0;
      A0 tmp = if_else(gt(x, -Log_2<A0>()),
                       nt2::log(-expm1(x)),
                       nt2::log1p(-exp(x)));
      return a0 + tmp;
    }
  };
} }

#endif
