//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_ELLIPTIC_FUNCTIONS_SIMD_COMMON_ELLPE_HPP_INCLUDED
#define NT2_ELLIPTIC_FUNCTIONS_SIMD_COMMON_ELLPE_HPP_INCLUDED
#include <nt2/elliptic/functions/ellpe.hpp>
#include <nt2/include/constants/one.hpp>
#include <nt2/include/functions/simd/if_allbits_else.hpp>
#include <nt2/include/functions/simd/if_else.hpp>
#include <nt2/include/functions/simd/is_eqz.hpp>
#include <nt2/include/functions/simd/is_greater.hpp>
#include <nt2/include/functions/simd/is_ltz.hpp>
#include <nt2/include/functions/simd/log.hpp>
#include <nt2/include/functions/simd/logical_or.hpp>
#include <nt2/include/functions/simd/minus.hpp>
#include <nt2/include/functions/simd/multiplies.hpp>
#include <nt2/polynomials/functions/scalar/impl/horner.hpp>
#include <nt2/sdk/meta/scalar_of.hpp>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION(nt2::tag::ellpe_, tag::cpu_,
                        (A0)(X),
                        ((simd_<single_<A0>,X>))
                       )
  {
    typedef A0 result_type;
    NT2_FUNCTOR_CALL_REPEAT(1)
    {
      typedef typename meta::scalar_of<A0>::type sA0;
      A0 temp = nt2::horner< NT2_HORNER_COEFF_T(sA0, 11,
                               (0x392102f5,
                                0x3b246c1b,
                                0x3c0e578f,
                                0x3c2fe240,
                                0x3bfebca9,
                                0x3bf882cf,
                                0x3c3d8b3f,
                                0x3cb2d89a,
                                0x3d68ac90,
                                0x3ee2e430,
                                0x3f800000) ) > (a0)
      -nt2::log(a0)*a0*nt2::horner< NT2_HORNER_COEFF_T(sA0, 10,
                                 (0x38098de4,
                                  0x3a84557e,
                                  0x3bd53114,
                                  0x3c8a54f6,
                                  0x3cd67118,
                                  0x3d0925e1,
                                  0x3d2ef92b,
                                  0x3d6fffe9,
                                  0x3dc00000,
                                  0x3e800000
                                  ) ) > (a0);
      return nt2::if_else(nt2::is_eqz(a0),
                nt2::One<A0>(),
                nt2::if_nan_else(
                  nt2::logical_or(nt2::gt(a0, nt2::One<A0>()),
                                  nt2::is_ltz(a0)), temp)
                   );
    }
  };
} }
#endif
