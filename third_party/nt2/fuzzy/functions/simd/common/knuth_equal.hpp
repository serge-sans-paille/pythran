//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_FUZZY_FUNCTIONS_SIMD_COMMON_KNUTH_EQUAL_HPP_INCLUDED
#define NT2_FUZZY_FUNCTIONS_SIMD_COMMON_KNUTH_EQUAL_HPP_INCLUDED
#include <nt2/fuzzy/functions/knuth_equal.hpp>
#include <nt2/include/functions/simd/logical_or.hpp>
#include <nt2/fuzzy/functions/knuth_equal.hpp>
#include <nt2/include/functions/simd/bitwise_or.hpp>
#include <nt2/include/functions/simd/is_equal.hpp>
#include <nt2/include/functions/simd/is_less_equal.hpp>
#include <nt2/include/functions/simd/maxnummag.hpp>
#include <nt2/include/functions/simd/dist.hpp>
#include <nt2/include/functions/simd/exponent.hpp>
#include <nt2/include/functions/simd/ldexp.hpp>

/////////////////////////////////////////////////////////////////////////////
// Implementation when type  is arithmetic_
/////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION(nt2::tag::knuth_equal_, tag::cpu_,
                              (A0)(X),
                              ((simd_<floating_<A0>,X>))
                              ((simd_<floating_<A0>,X>))
                              ((simd_<floating_<A0>,X>))
                             )
  {
    typedef typename meta::as_logical<A0>::type result_type;
    NT2_FUNCTOR_CALL_REPEAT(3)
    {
      return l_or( eq(a0, a1)
                   , le( dist(a0, a1)
                     , ldexp(a2,
                           exponent(maxnummag(a0, a1))
                           )
                     )
                   );
    }
  };
} }
#endif
