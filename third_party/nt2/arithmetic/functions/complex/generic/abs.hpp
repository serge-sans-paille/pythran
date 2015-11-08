//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_ARITHMETIC_FUNCTIONS_COMPLEX_GENERIC_ABS_HPP_INCLUDED
#define NT2_ARITHMETIC_FUNCTIONS_COMPLEX_GENERIC_ABS_HPP_INCLUDED
#include <nt2/arithmetic/functions/abs.hpp>
#include <nt2/include/functions/simd/real.hpp>
#include <nt2/include/functions/simd/imag.hpp>
#include <nt2/include/functions/simd/hypot.hpp>
#include <nt2/include/functions/simd/abs.hpp>
#include <nt2/sdk/complex/meta/as_real.hpp>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::abs_, tag::cpu_, (A0)
                            , (generic_< complex_< floating_<A0> > >)
                            )
  {
    typedef typename meta::as_real<A0>::type       result_type;
    NT2_FUNCTOR_CALL(1)
    {
      return hypot(nt2::real(a0),nt2::imag(a0));
    }
  };


  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::abs_, tag::cpu_, (A0)
                            , (generic_< dry_< floating_<A0> > >)
                            )
  {
    typedef typename meta::as_real<A0>::type result_type;
    NT2_FUNCTOR_CALL(1)
    {
      return nt2::abs(nt2::real(a0));
    }
  };
} }

#endif
