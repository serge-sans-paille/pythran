//==============================================================================
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2014 NUMSCALE SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_EXPONENTIAL_FUNCTIONS_GENERIC_POW_ABS_HPP_INCLUDED
#define NT2_EXPONENTIAL_FUNCTIONS_GENERIC_POW_ABS_HPP_INCLUDED

#include <nt2/exponential/functions/pow_abs.hpp>
#include <nt2/include/functions/simd/pow.hpp>
#include <nt2/include/functions/simd/abs.hpp>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::pow_abs_, tag::cpu_
                            , (A0)(A1)
                            , (generic_<arithmetic_<A0> >)
                              (generic_<integer_<A1> >)
                            )
  {
    typedef A0 result_type;

    BOOST_FORCEINLINE NT2_FUNCTOR_CALL(2)
    {
      return pow(abs(a0), a1);
    }
  };
} }

#endif
