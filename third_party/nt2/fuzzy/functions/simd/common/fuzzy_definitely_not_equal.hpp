//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_FUZZY_FUNCTIONS_SIMD_COMMON_FUZZY_DEFINITELY_NOT_EQUAL_HPP_INCLUDED
#define NT2_FUZZY_FUNCTIONS_SIMD_COMMON_FUZZY_DEFINITELY_NOT_EQUAL_HPP_INCLUDED

#include <nt2/fuzzy/functions/fuzzy_definitely_not_equal.hpp>
#include <nt2/include/functions/simd/multiplies.hpp>
#include <nt2/include/functions/simd/is_greater.hpp>
#include <nt2/include/functions/simd/max.hpp>
#include <nt2/include/functions/simd/abs.hpp>
#include <nt2/include/functions/simd/dist.hpp>

/////////////////////////////////////////////////////////////////////////////
// Implementation when type  is arithmetic_
/////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION(nt2::tag::fuzzy_definitely_not_equal_, tag::cpu_,
                                             (A0)(X),
                                             ((simd_<arithmetic_<A0>,X>))
                                             ((simd_<arithmetic_<A0>,X>))
                                             ((simd_<arithmetic_<A0>,X>))
                                            )
  {
    typedef typename meta::as_logical<A0>::type result_type;
    NT2_FUNCTOR_CALL_REPEAT(3)
    {
       return gt(dist(a0, a1), max(abs(a0),abs(a1))*a2);
    }
  };
} }
#endif
