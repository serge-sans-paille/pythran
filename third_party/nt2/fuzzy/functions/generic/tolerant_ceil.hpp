//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_FUZZY_FUNCTIONS_GENERIC_TOLERANT_CEIL_HPP_INCLUDED
#define NT2_FUZZY_FUNCTIONS_GENERIC_TOLERANT_CEIL_HPP_INCLUDED
#include <nt2/fuzzy/functions/tolerant_ceil.hpp>
#include <nt2/include/functions/simd/tolerant_floor.hpp>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::tolerant_ceil_, tag::cpu_
                            , (A0)
                            , (generic_< floating_<A0> >)
                            )
  {
    typedef A0 result_type;
    inline result_type operator()(const A0& a0)
    {
      return -tolerant_floor(-a0);
    }
  };
} }


#endif
