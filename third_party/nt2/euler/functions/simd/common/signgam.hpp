//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_EULER_FUNCTIONS_SIMD_COMMON_SIGNGAM_HPP_INCLUDED
#define NT2_EULER_FUNCTIONS_SIMD_COMMON_SIGNGAM_HPP_INCLUDED

#include <nt2/euler/functions/signgam.hpp>
#include <nt2/include/functions/simd/is_lez.hpp>
#include <nt2/include/functions/simd/is_flint.hpp>
#include <nt2/include/functions/simd/selsub.hpp>
#include <nt2/include/functions/simd/floor.hpp>
#include <nt2/include/functions/simd/is_odd.hpp>
#include <nt2/include/functions/simd/if_allbits_else.hpp>
#include <nt2/include/functions/simd/if_else_zero.hpp>
#include <nt2/include/functions/simd/logical_or.hpp>
#include <nt2/include/functions/simd/logical_and.hpp>
#include <nt2/include/functions/simd/is_nan.hpp>
#include <nt2/include/functions/simd/is_equal.hpp>
#include <nt2/sdk/meta/as_logical.hpp>
#include <nt2/include/constants/minf.hpp>
#include <nt2/include/constants/mtwo.hpp>
#include <nt2/include/constants/one.hpp>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION(nt2::tag::signgam_, tag::cpu_,
                    (A0)(X),
                    ((simd_<arithmetic_<A0>,X>))
                    )
  {
    typedef A0 result_type;
    NT2_FUNCTOR_CALL(1)
    {
      typedef typename meta::as_logical<A0>::type bA0;
      bA0 leza0 = nt2::is_lez(a0);
      return nt2::if_nan_else(
        nt2::logical_or( nt2::logical_or(is_nan(a0), nt2::eq(a0,Minf<A0>()))
                       , nt2::logical_and(leza0, nt2::is_flint(a0))
                       ),
        nt2::selsub(leza0,
                    nt2::One<A0>(),
                    nt2::if_else_zero(nt2::is_odd(floor(a0)), nt2::Mtwo<A0>())
                   )
      );
    }

  };
} }

#endif
