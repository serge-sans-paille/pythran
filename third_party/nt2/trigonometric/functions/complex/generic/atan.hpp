//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TRIGONOMETRIC_FUNCTIONS_COMPLEX_GENERIC_ATAN_HPP_INCLUDED
#define NT2_TRIGONOMETRIC_FUNCTIONS_COMPLEX_GENERIC_ATAN_HPP_INCLUDED
#include <nt2/trigonometric/functions/atan.hpp>
#include <nt2/include/functions/log.hpp>
#include <nt2/include/functions/sqrt.hpp>
#include <nt2/include/functions/oneplus.hpp>
#include <nt2/include/functions/is_real.hpp>
#include <nt2/include/functions/if_zero_else.hpp>
#include <nt2/include/functions/if_allbits_else.hpp>
#include <nt2/sdk/complex/meta/as_complex.hpp>
#include <nt2/sdk/complex/meta/as_real.hpp>
#include <nt2/sdk/complex/meta/as_dry.hpp>
#include <nt2/include/functions/is_ltz.hpp>
#include <nt2/include/functions/abs.hpp>
#include <nt2/include/functions/real.hpp>
#include <nt2/include/functions/imag.hpp>
#include <nt2/include/functions/atan.hpp>
#include <nt2/include/functions/logical_or.hpp>
#include <nt2/include/functions/logical_and.hpp>
#include <nt2/include/functions/logical_andnot.hpp>
#include <nt2/include/functions/is_real.hpp>
#include <nt2/include/functions/is_less_equal.hpp>
#include <nt2/include/functions/is_greater_equal.hpp>
#include <nt2/include/functions/is_less.hpp>
#include <nt2/include/functions/is_greater.hpp>
#include <nt2/include/functions/is_inf.hpp>
#include <nt2/include/functions/is_nan.hpp>
#include <nt2/include/functions/is_not_nan.hpp>
#include <nt2/include/functions/is_invalid.hpp>
#include <nt2/include/functions/oneplus.hpp>
#include <nt2/include/functions/minusone.hpp>
#include <nt2/include/functions/sqrt.hpp>
#include <nt2/include/functions/sqr.hpp>
#include <nt2/include/functions/atan.hpp>
#include <nt2/include/functions/log.hpp>
#include <nt2/include/functions/log1p.hpp>
#include <nt2/include/functions/any.hpp>
#include <nt2/include/functions/splat.hpp>
#include <nt2/include/functions/negif.hpp>
#include <nt2/include/functions/mul_minus_i.hpp>
#include <nt2/include/functions/mul_i.hpp>
#include <nt2/include/functions/atanh.hpp>


#include <nt2/include/constants/one.hpp>
#include <nt2/include/constants/four.hpp>
#include <nt2/include/constants/eight.hpp>
#include <nt2/include/constants/valmax.hpp>
#include <nt2/include/constants/smallestposval.hpp>
#include <nt2/include/constants/eps.hpp>
#include <nt2/include/constants/log_2.hpp>
#include <nt2/include/constants/pi.hpp>
#include <nt2/include/constants/pio_2.hpp>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::atan_, tag::cpu_, (A0)
                            , (generic_< complex_< floating_<A0> > >)
                            )
  {
    typedef A0 result_type;
    NT2_FUNCTOR_CALL(1)
    {
      // C99 definition here; atan(z) = -i atanh(iz):
      return mul_minus_i(nt2::atanh(mul_i(a0)));
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::atan_, tag::cpu_, (A0)
                            , (generic_< dry_< arithmetic_<A0> > >)
                            )
  {
    typedef A0 result_type;
    NT2_FUNCTOR_CALL(1)
    {
      return bitwise_cast<result_type>(nt2::atan(nt2::real(a0)));
    }
  };

} }

#endif
