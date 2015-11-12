//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_COMBINATORIAL_FUNCTIONS_SCALAR_FACTORIAL_HPP_INCLUDED
#define NT2_COMBINATORIAL_FUNCTIONS_SCALAR_FACTORIAL_HPP_INCLUDED
#include <nt2/combinatorial/functions/factorial.hpp>
#include <nt2/include/constants/inf.hpp>
#include <nt2/include/constants/one.hpp>
#include <nt2/include/constants/valmax.hpp>
#include <nt2/include/functions/scalar/abss.hpp>
#include <nt2/include/functions/scalar/gamma.hpp>
#include <nt2/include/functions/scalar/round2even.hpp>
#include <nt2/include/functions/scalar/trunc.hpp>
#include <nt2/sdk/meta/as_floating.hpp>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION(nt2::tag::factorial_, tag::cpu_,
                      (A0),
                      (scalar_ < arithmetic_<A0> > )
                      )
  {
    typedef A0  result_type;
    NT2_FUNCTOR_CALL(1)
    {
      typedef typename boost::dispatch::meta::as_floating<A0>::type ftype;
      typedef typename meta::upgrade<ftype>::type uftype;
      const ftype r = static_cast<ftype>(nt2::gamma(nt2::trunc(nt2::abss(static_cast<uftype>(a0)))+One<uftype>()));
      return r > Valmax<A0>() ? Inf<A0>() : static_cast<A0>(nt2::round2even(r));
    }
  };
} }
#endif
