//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_ARITHMETIC_FUNCTIONS_COMPLEX_GENERIC_RSQRT_HPP_INCLUDED
#define NT2_ARITHMETIC_FUNCTIONS_COMPLEX_GENERIC_RSQRT_HPP_INCLUDED
#include <nt2/arithmetic/functions/rsqrt.hpp>
#include <nt2/include/functions/real.hpp>
#include <nt2/include/functions/imag.hpp>
#include <nt2/include/functions/if_else.hpp>
#include <nt2/include/functions/simd/is_nltz.hpp>
#include <nt2/include/functions/abs.hpp>
#include <nt2/include/functions/sqrt.hpp>
#include <nt2/include/functions/rec.hpp>
#include <nt2/sdk/complex/meta/as_complex.hpp>
#include <nt2/sdk/complex/meta/as_real.hpp>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::rsqrt_, tag::cpu_, (A0)
                            , (generic_< complex_< arithmetic_<A0> > >)
                            )
  {
    typedef A0 result_type;
    NT2_FUNCTOR_CALL(1)
    {
      return rec(sqrt(a0));
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::rsqrt_, tag::cpu_, (A0)
                            , (generic_< dry_< arithmetic_<A0> > >)
                            )
  {
    typedef typename meta::as_real<A0>::type rA0;
    typedef typename meta::as_complex<A0>::type result_type;
    NT2_FUNCTOR_CALL(1)
    {
      const rA0 root = rsqrt(nt2::abs(a0));
      return if_else( is_nltz( nt2::real(a0))
                    , result_type(root)
                    , result_type(Zero<rA0>(), -root)
                    );
    }
  };

} }

#endif
