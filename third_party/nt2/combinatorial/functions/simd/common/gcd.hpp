//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_COMBINATORIAL_FUNCTIONS_SIMD_COMMON_GCD_HPP_INCLUDED
#define NT2_COMBINATORIAL_FUNCTIONS_SIMD_COMMON_GCD_HPP_INCLUDED

#include <nt2/combinatorial/functions/gcd.hpp>
#include <nt2/include/functions/simd/any.hpp>
#include <nt2/include/functions/simd/if_else.hpp>
#include <nt2/include/functions/simd/if_else_allbits.hpp>
#include <nt2/include/functions/simd/if_else_zero.hpp>
#include <nt2/include/functions/simd/is_flint.hpp>
#include <nt2/include/functions/simd/is_nez.hpp>
#include <nt2/include/functions/simd/logical_and.hpp>
#include <nt2/include/functions/simd/rem.hpp>
#include <nt2/sdk/meta/as_logical.hpp>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::gcd_, tag::cpu_
                            , (A0)(X)
                            , ((simd_<integer_<A0>,X>))
                              ((simd_<integer_<A0>,X>))
                            )
  {
    typedef A0 result_type;
    NT2_FUNCTOR_CALL_REPEAT(2)
    {
      typedef typename meta::as_logical<A0>::type bA0;
      A0 a = a0, b = a1;
      bA0 t= nt2::is_nez(b);
      while (nt2::any(t))
      {
        A0 r = nt2::if_else_zero(t, rem(a, b));
        a = nt2::if_else(t, b, a);
        b = r;
        t =  nt2::is_nez(b);
      }
      return a;
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::gcd_, tag::cpu_
                            , (A0)(X)
                            , ((simd_<floating_<A0>,X>))
                              ((simd_<floating_<A0>,X>))
                            )
  {
    typedef A0 result_type;
    NT2_FUNCTOR_CALL_REPEAT(2)
    {
      typedef typename meta::as_logical<A0>::type    bA0;
      bA0 ints = nt2::logical_and(is_flint(a1), is_flint(a0));
      A0 a =  nt2::if_else_zero(ints, a0);
      A0 b =  nt2::if_else_zero(ints, a1);
      bA0 t= nt2::is_nez(b);
      while (bool(nt2::any(t)))
      {
        A0 r = nt2::if_else_zero(t, rem(a, b));
        a = nt2::if_else(t, b, a);
        b = r;
        t = nt2::is_nez(b);
      }
      return nt2::if_else_nan(ints, a);
    }
  };
} }

#endif
