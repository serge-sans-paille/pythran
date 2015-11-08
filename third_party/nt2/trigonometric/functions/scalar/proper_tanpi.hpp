//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TRIGONOMETRIC_FUNCTIONS_SCALAR_PROPER_TANPI_HPP_INCLUDED
#define NT2_TRIGONOMETRIC_FUNCTIONS_SCALAR_PROPER_TANPI_HPP_INCLUDED

#include <nt2/trigonometric/functions/proper_tanpi.hpp>
#include <nt2/trigonometric/functions/scalar/impl/trigo.hpp>
#include <nt2/include/functions/scalar/is_ltz.hpp>
#include <nt2/include/functions/scalar/negif.hpp>
#include <nt2/include/functions/scalar/rec.hpp>
#include <nt2/include/functions/scalar/is_nan.hpp>
#include <nt2/include/constants/zero.hpp>
#include <nt2/include/constants/nan.hpp>
#include <nt2/include/constants/half.hpp>
#include <nt2/include/constants/quarter.hpp>

// compute atan (pi*x)  for -1/2 <= x << 1/2 else return nan
namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::proper_tanpi_, tag::cpu_
                            , (A0)
                            , (scalar_< floating_<A0> >)
                            )
  {

    typedef A0 result_type;

    NT2_FUNCTOR_CALL(1)
    {
      if (is_nan(a0)) return a0;
      A0 absa0 = nt2::abs(a0);
      if (absa0 > nt2::Half<A0>()) return nt2::Nan<A0>();
      bool test = (absa0 <= nt2::Quarter<A0>());
      absa0 = test ? absa0 : nt2::Half<A0>()-absa0;
      A0 that = details::trig_base<A0,pi_tag,tag::not_simd_type, clipped_pio4_>::tana(absa0);
      that = nt2::negif(nt2::is_ltz(a0), that);
      return test ? that : nt2::rec(that);
    }
  };
} }


#endif
