//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_COMBINATORIAL_FUNCTIONS_SIMD_COMMON_CNP_HPP_INCLUDED
#define NT2_COMBINATORIAL_FUNCTIONS_SIMD_COMMON_CNP_HPP_INCLUDED

#include <nt2/combinatorial/functions/cnp.hpp>
#include <nt2/include/constants/nan.hpp>
#include <nt2/include/constants/zero.hpp>
#include <nt2/include/functions/simd/anp.hpp>
#include <nt2/include/functions/simd/exp.hpp>
#include <nt2/include/functions/simd/gammaln.hpp>
#include <nt2/include/functions/simd/if_allbits_else.hpp>
#include <nt2/include/functions/simd/if_zero_else.hpp>
#include <nt2/include/functions/simd/is_less.hpp>
#include <nt2/include/functions/simd/is_ngez.hpp>
#include <nt2/include/functions/simd/logical_or.hpp>
#include <nt2/include/functions/simd/minus.hpp>
#include <nt2/include/functions/simd/oneplus.hpp>
#include <nt2/include/functions/simd/round2even.hpp>
#include <nt2/include/functions/simd/tofloat.hpp>
#include <nt2/include/functions/simd/toints.hpp>
#include <nt2/sdk/meta/as_floating.hpp>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION(nt2::tag::cnp_, tag::cpu_,
                      (A0)(X),
                      ((simd_<floating_<A0>,X>))
                      ((simd_<floating_<A0>,X>))
                     )
  {
    typedef A0 result_type;
    NT2_FUNCTOR_CALL_REPEAT(2)
    {
      const A0 n = oneplus(round2even(a0));
      const A0 p = oneplus(round2even(a1));
      return if_nan_else(l_or(is_ngez(a0), is_ngez(a1)),
                   if_zero_else(lt(a0,a1),
                      round2even(nt2::exp(gammaln(n)-gammaln(p)
                                          -gammaln(oneplus(n-p)))
                                )
                           )
                        );
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION(nt2::tag::cnp_, tag::cpu_,
                      (A0)(X),
                      ((simd_<arithmetic_<A0>,X>))
                      ((simd_<arithmetic_<A0>,X>))
                     )
  {
    typedef A0 result_type;
    NT2_FUNCTOR_CALL_REPEAT(2)
    {
      return toints(cnp(tofloat(a0), tofloat(a1)));
    }
  };

} }
#endif
