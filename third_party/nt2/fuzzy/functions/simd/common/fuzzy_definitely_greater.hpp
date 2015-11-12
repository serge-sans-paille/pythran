//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_FUZZY_FUNCTIONS_SIMD_COMMON_FUZZY_DEFINITELY_GREATER_HPP_INCLUDED
#define NT2_FUZZY_FUNCTIONS_SIMD_COMMON_FUZZY_DEFINITELY_GREATER_HPP_INCLUDED
#include <nt2/fuzzy/functions/fuzzy_definitely_greater.hpp>
#include <nt2/sdk/meta/as_logical.hpp>
#include <nt2/fuzzy/functions/fuzzy_definitely_greater.hpp>
#include <nt2/include/functions/simd/multiplies.hpp>
#include <nt2/include/functions/simd/plus.hpp>
#include <nt2/include/functions/simd/is_greater.hpp>
#include <nt2/include/functions/simd/max.hpp>
#include <nt2/include/functions/simd/abs.hpp>

/////////////////////////////////////////////////////////////////////////////
// Implementation when type  is arithmetic_
/////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION(nt2::tag::fuzzy_definitely_greater_, tag::cpu_,
                                           (A0)(X),
                                           ((simd_<arithmetic_<A0>,X>))
                                           ((simd_<arithmetic_<A0>,X>))
                                           ((simd_<arithmetic_<A0>,X>))
                                          )
  {
    typedef typename meta::as_logical<A0>::type result_type;
    NT2_FUNCTOR_CALL_REPEAT(3)
    {
      return gt(a0,a1+max(abs(a0),abs(a1))*a2);
    }
  };
} }
#endif
