//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_HYPERBOLIC_FUNCTIONS_SCALAR_ACOSH_HPP_INCLUDED
#define NT2_HYPERBOLIC_FUNCTIONS_SCALAR_ACOSH_HPP_INCLUDED
#include <nt2/hyperbolic/functions/acosh.hpp>
#include <nt2/include/constants/log_2.hpp>
#include <nt2/include/constants/oneotwoeps.hpp>
#include <nt2/include/functions/scalar/log.hpp>
#include <nt2/include/functions/scalar/log1p.hpp>
#include <nt2/include/functions/scalar/minusone.hpp>
#include <nt2/include/functions/scalar/sqr.hpp>
#include <nt2/include/functions/scalar/sqrt.hpp>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::acosh_
                            , tag::cpu_
                            , (A0)
                            , (scalar_< floating_<A0> > )
                            )
  {
    typedef A0 result_type;

    NT2_FUNCTOR_CALL(1)
    {
      A0 t = minusone(a0);
      if(BOOST_LIKELY(t <= Oneotwoeps<A0>()))
        return log1p(t+nt2::sqrt(t+t+sqr(t)));
      else
        return log(t)+Log_2<A0>();
    }
  };
} }
#endif
