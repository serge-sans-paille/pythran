//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_EXPONENTIAL_FUNCTIONS_SIMD_COMMON_POW_HPP_INCLUDED
#define NT2_EXPONENTIAL_FUNCTIONS_SIMD_COMMON_POW_HPP_INCLUDED

#include <nt2/exponential/functions/pow.hpp>
#include <nt2/include/functions/simd/if_else.hpp>
#include <nt2/include/functions/simd/is_flint.hpp>
#include <nt2/include/functions/simd/is_ltz.hpp>
#include <nt2/include/functions/simd/is_odd.hpp>
#include <nt2/include/functions/simd/logical_and.hpp>
#include <nt2/include/functions/simd/logical_andnot.hpp>
#include <nt2/include/functions/simd/negif.hpp>
#include <nt2/include/functions/simd/pow_abs.hpp>
#include <nt2/include/functions/simd/any.hpp>
#include <nt2/include/functions/simd/sqr.hpp>
#include <nt2/include/functions/simd/shift_right.hpp>
#include <nt2/include/functions/simd/multiplies.hpp>
#include <nt2/include/constants/one.hpp>
#include <nt2/include/constants/nan.hpp>
#include <nt2/sdk/meta/as_logical.hpp>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::pow_, tag::cpu_
                            , (A0)(X)
                            , ((simd_< floating_<A0>,X>))
                              ((simd_< floating_<A0>,X>))
                            )
  {
    typedef A0 result_type;

    NT2_FUNCTOR_CALL_REPEAT(2)
    {
      typedef typename meta::as_logical<A0>::type bA0;
      bA0 ltza0 = is_ltz(a0);
      A0 z = pow_abs(a0, a1);
      z =  negif(l_and(is_odd(a1), ltza0), z);
      bA0 invalid =  l_andnot(ltza0, is_flint(a1));
      return if_else(invalid, Nan<result_type>(), z);
    }
  };


  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::pow_, tag::cpu_
                            , (A0)(A1)(X)
                            , ((simd_<arithmetic_<A0>,X>))
                              ((simd_<uint_<A1>,X>))
                            )
  {
    typedef A0 result_type;
    NT2_FUNCTOR_CALL(2)
    {
      A0 base = a0;
      A1 exp = a1;

      result_type result = One<result_type>();
      while(nt2::any(exp))
      {
        result *= if_else(is_odd(exp), base, One<result_type>());
        exp >>= 1;
        base = sqr(base);
      }

      return result;
     }
  };
} }

#endif
