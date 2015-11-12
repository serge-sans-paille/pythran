//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_EULER_FUNCTIONS_SCALAR_BETA_HPP_INCLUDED
#define NT2_EULER_FUNCTIONS_SCALAR_BETA_HPP_INCLUDED

#include <nt2/euler/functions/beta.hpp>
#include <nt2/include/functions/scalar/exp.hpp>
#include <nt2/include/functions/scalar/gammaln.hpp>
#include <nt2/include/functions/scalar/signgam.hpp>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::beta_, tag::cpu_
                            , (A0)
                            , (scalar_< floating_<A0> >)
                              (scalar_< floating_<A0> >)
                            )
  {

    typedef A0 result_type;

    NT2_FUNCTOR_CALL_REPEAT(2)
    {
      const A0 y = a0+a1;
      const A0 sign = signgam(a0)*signgam(a1)*signgam(y);
      return sign*exp(gammaln(a0)+gammaln(a1)-gammaln(y));
    }
  };
} }

#endif
