//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_EXPONENTIAL_FUNCTIONS_COMPLEX_GENERIC_EXP10_HPP_INCLUDED
#define NT2_EXPONENTIAL_FUNCTIONS_COMPLEX_GENERIC_EXP10_HPP_INCLUDED

#include <nt2/exponential/functions/exp10.hpp>
#include <nt2/include/functions/real.hpp>
#include <nt2/include/functions/imag.hpp>
#include <nt2/include/functions/is_real.hpp>
#include <nt2/include/functions/if_else.hpp>
#include <nt2/include/functions/multiplies.hpp>
#include <nt2/include/functions/bitwise_cast.hpp>
#include <nt2/include/functions/simd/sincos.hpp>
#include <nt2/include/functions/simd/is_equal.hpp>
#include <nt2/include/functions/simd/logical_or.hpp>
#include <nt2/include/constants/log_10.hpp>
#include <nt2/include/constants/minf.hpp>
#include <nt2/sdk/complex/meta/as_complex.hpp>
#include <nt2/sdk/complex/meta/as_real.hpp>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::exp10_, tag::cpu_
                            , (A0)
                            , (generic_< complex_<floating_<A0> > >)
                            )
  {
    typedef A0 result_type;
    NT2_FUNCTOR_CALL(1)
    {
      typedef typename meta::as_real<A0>::type rtype;
      rtype c, s;
      sincos(nt2::imag(a0)*Log_10<rtype>(), s, c);
      rtype rho = exp10(nt2::real(a0));
      return if_else(logical_or(is_real(a0), eq(nt2::real(a0), Minf<rtype>())),
                     result_type(rho, Zero<rtype>()),
                     rho*result_type(c, s));
    }
  };


  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::exp10_, tag::cpu_
                            , (A0)
                            , (generic_< dry_<floating_<A0> > >)
                            )
  {
    typedef A0 result_type;
    NT2_FUNCTOR_CALL(1)
    {
      return bitwise_cast<result_type>(nt2::exp10(nt2::real(a0)));
    }
  };
} }


#endif
