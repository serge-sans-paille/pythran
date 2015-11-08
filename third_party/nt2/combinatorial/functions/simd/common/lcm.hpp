//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_COMBINATORIAL_FUNCTIONS_SIMD_COMMON_LCM_HPP_INCLUDED
#define NT2_COMBINATORIAL_FUNCTIONS_SIMD_COMMON_LCM_HPP_INCLUDED

#include <nt2/combinatorial/functions/lcm.hpp>
#include <nt2/include/functions/simd/abs.hpp>
#include <nt2/include/functions/simd/divides.hpp>
#include <nt2/include/functions/simd/gcd.hpp>
#include <nt2/include/functions/simd/is_eqz.hpp>
#include <nt2/include/functions/simd/multiplies.hpp>
#include <nt2/include/functions/simd/selinc.hpp>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION(nt2::tag::lcm_, tag::cpu_,
                      (A0)(X),
                      ((simd_<integer_<A0>,X>))
                      ((simd_<integer_<A0>,X>))
                     )
  {
    typedef A0 result_type;
    NT2_FUNCTOR_CALL_REPEAT(2)
    {
      A0 div = selinc(is_eqz(a1), a1);
      return nt2::abs(a0 * (a1 / gcd(a0, div)));
    }
  };
} }
#endif
