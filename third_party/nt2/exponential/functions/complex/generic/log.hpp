//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_EXPONENTIAL_FUNCTIONS_COMPLEX_GENERIC_LOG_HPP_INCLUDED
#define NT2_EXPONENTIAL_FUNCTIONS_COMPLEX_GENERIC_LOG_HPP_INCLUDED
#include <nt2/exponential/functions/log.hpp>
#include <nt2/include/functions/log.hpp>
#include <nt2/include/functions/arg.hpp>
#include <nt2/include/functions/abs.hpp>
#include <nt2/include/functions/if_zero_else.hpp>
#include <nt2/include/functions/is_real.hpp>
#include <nt2/include/functions/is_nan.hpp>
#include <nt2/include/constants/zero.hpp>
#include <boost/dispatch/meta/as_floating.hpp>
#include <nt2/sdk/complex/meta/as_complex.hpp>
#include <nt2/sdk/complex/meta/as_real.hpp>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::log_, tag::cpu_
                            , (A0)
                            , (generic_< complex_<floating_<A0> > >)
                            )
  {
    typedef typename meta::as_complex<A0>::type result_type;
    NT2_FUNCTOR_CALL(1)
    {
      typedef typename meta::as_real<A0>::type rtype;
      rtype a = if_zero_else(logical_and(nt2::is_real(a0), nt2::is_nan(a0)), nt2::arg(a0)) ;
      return result_type(nt2::log(nt2::abs(a0)), a);
    }
  };

} }


#endif
