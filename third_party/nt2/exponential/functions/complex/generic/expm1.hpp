//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_EXPONENTIAL_FUNCTIONS_COMPLEX_GENERIC_EXPM1_HPP_INCLUDED
#define NT2_EXPONENTIAL_FUNCTIONS_COMPLEX_GENERIC_EXPM1_HPP_INCLUDED
#include <nt2/exponential/functions/expm1.hpp>
#include <nt2/sdk/meta/as_logical.hpp>
#include <nt2/include/constants/mtwo.hpp>
#include <nt2/include/constants/one.hpp>
#include <nt2/include/constants/half.hpp>
#include <nt2/include/functions/exp.hpp>
#include <nt2/include/functions/log.hpp>
#include <nt2/include/functions/log1p.hpp>
#include <nt2/include/functions/minusone.hpp>
#include <nt2/include/functions/sin.hpp>
#include <nt2/include/functions/logical_notand.hpp>
#include <nt2/include/functions/logical_or.hpp>
#include <nt2/include/functions/is_not_equal.hpp>
#include <nt2/include/functions/is_eqz.hpp>
#include <nt2/include/functions/is_invalid.hpp>
#include <nt2/include/functions/is_inf.hpp>
#include <nt2/include/functions/is_nlt.hpp>
#include <nt2/include/functions/if_else.hpp>
#include <nt2/include/functions/multiplies.hpp>
#include <nt2/include/functions/divides.hpp>
#include <nt2/include/functions/real.hpp>
#include <nt2/include/functions/imag.hpp>
#include <nt2/sdk/complex/meta/as_complex.hpp>
#include <nt2/sdk/complex/meta/as_real.hpp>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::expm1_, tag::cpu_
                            , (A0)
                            , ((generic_<complex_<floating_<A0> > >))
                            )
  {
    typedef A0 result_type;
    NT2_FUNCTOR_CALL(1)
    {
      typedef typename meta::as_real<result_type>::type rtype;
      typedef typename meta::as_logical<rtype>::type ltype;
      const A0 u =  nt2::exp(a0);
      const A0 w =  minusone(u);
      const rtype ru =  nt2::real(u);
      const ltype exceptionnal =
        logical_or(is_eqz(ru),
                   logical_or(is_invalid(u),
                              logical_or(is_eqz(a0),
                                         is_nlt(nt2::abs(nt2::imag(a0)), Pio_2<rtype>())
                                         )
                              )
                   );
      const A0 correct = nt2::divides(a0, nt2::log1p(w));
      A0 res =  if_else(exceptionnal, w, nt2::multiplies(w, correct));
      return res;
    }
  };

   NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::expm1_, tag::cpu_
                            , (A0)
                            , (generic_< dry_<floating_<A0> > >)
                            )
  {
    typedef A0 result_type;
    NT2_FUNCTOR_CALL(1)
    {
      return bitwise_cast<result_type>(nt2::expm1(nt2::real(a0)));
    }
  };
} }

#endif
