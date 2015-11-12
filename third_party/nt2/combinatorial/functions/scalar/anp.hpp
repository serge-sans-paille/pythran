//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_COMBINATORIAL_FUNCTIONS_SCALAR_ANP_HPP_INCLUDED
#define NT2_COMBINATORIAL_FUNCTIONS_SCALAR_ANP_HPP_INCLUDED
#include <nt2/combinatorial/functions/anp.hpp>
#include <nt2/include/constants/nan.hpp>
#include <nt2/include/constants/zero.hpp>
#include <nt2/include/functions/scalar/exp.hpp>
#include <nt2/include/functions/scalar/gammaln.hpp>
#include <nt2/include/functions/scalar/is_less.hpp>
#include <nt2/include/functions/scalar/is_ngez.hpp>
#include <nt2/include/functions/scalar/oneplus.hpp>
#include <nt2/include/functions/scalar/round2even.hpp>
#include <nt2/sdk/meta/as_floating.hpp>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::anp_, tag::cpu_
                            , (A0)
                            , (scalar_< arithmetic_<A0> >)
                              (scalar_< arithmetic_<A0> >)
                            )
  {

    typedef A0 result_type;

    NT2_FUNCTOR_CALL_REPEAT(2)
    {
      typedef typename boost::dispatch::meta::as_floating<A0>::type type;
      typedef result_type rtype;
      if (is_ngez(a0)||is_ngez(a1)) return (rtype)Nan<type>();
      if (lt(a0,a1)) return (rtype)Zero<type>();
      const type n = type(oneplus(round2even(a0)));
      const type p = type(round2even(a1));
      return (rtype)round2even(nt2::exp(gammaln(n)-gammaln(n-p)));
    }
  };
} }

#endif
