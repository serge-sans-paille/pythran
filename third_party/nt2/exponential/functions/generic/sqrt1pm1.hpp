//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_EXPONENTIAL_FUNCTIONS_GENERIC_SQRT1PM1_HPP_INCLUDED
#define NT2_EXPONENTIAL_FUNCTIONS_GENERIC_SQRT1PM1_HPP_INCLUDED

#include <nt2/exponential/functions/sqrt1pm1.hpp>
#include <nt2/include/constants/half.hpp>
#include <nt2/include/functions/simd/abs.hpp>
#include <nt2/include/functions/simd/if_else.hpp>
#include <nt2/include/functions/simd/is_less.hpp>
#include <nt2/include/functions/simd/minusone.hpp>
#include <nt2/include/functions/simd/oneplus.hpp>
#include <nt2/include/functions/simd/sqrt.hpp>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::sqrt1pm1_, tag::cpu_
                            , (A0)
                            , (generic_< floating_<A0> >)
                            )
  {
    typedef A0 result_type;
    NT2_FUNCTOR_CALL(1)
    {
      A0 tmp =  nt2::sqrt(oneplus(a0));
      return  nt2::if_else(lt(nt2::abs(a0),  nt2::Half<A0>()),
                           a0/nt2::oneplus(tmp),
                           nt2::minusone(tmp));
    }
  };
} }

#endif
