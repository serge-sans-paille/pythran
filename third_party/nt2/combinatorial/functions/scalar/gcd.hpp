//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_COMBINATORIAL_FUNCTIONS_SCALAR_GCD_HPP_INCLUDED
#define NT2_COMBINATORIAL_FUNCTIONS_SCALAR_GCD_HPP_INCLUDED

#include <nt2/combinatorial/functions/gcd.hpp>
#include <nt2/include/constants/nan.hpp>
#include <nt2/include/functions/scalar/is_flint.hpp>
#include <nt2/include/functions/scalar/rem.hpp>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::gcd_, tag::cpu_
                            , (A0)
                            , (scalar_< integer_<A0> >)
                              (scalar_< integer_<A0> >)
                            )
  {
    typedef A0 result_type;
    NT2_FUNCTOR_CALL_REPEAT(2)
    {
      result_type a(a0);
      result_type b(a1);
      while (b) {
        const result_type  r = a % b;
        a = b;
        b = r;
      }
      return a;
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::gcd_, tag::cpu_
                            , (A0)
                            , (scalar_< floating_<A0> >)
                              (scalar_< floating_<A0> >)
                            )
  {
    typedef A0 result_type;
    NT2_FUNCTOR_CALL_REPEAT(2)
    {
      result_type a(a0);
      result_type b(a1);
      if (!b) return a;
      if (!is_flint(a)||!is_flint(b)) return Nan<result_type>();
      while (b) {
        result_type  r  = rem(a, b);
        a = b;
        b = r;
      }
      return a;
    }
  };
} }

#endif
