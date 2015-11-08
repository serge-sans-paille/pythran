//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TRIGONOMETRIC_FUNCTIONS_SCALAR_ASEC_HPP_INCLUDED
#define NT2_TRIGONOMETRIC_FUNCTIONS_SCALAR_ASEC_HPP_INCLUDED
#include <nt2/trigonometric/functions/asec.hpp>
#include <nt2/include/constants/zero.hpp>
#include <nt2/include/constants/pio_2.hpp>
#include <nt2/include/constants/pi.hpp>
#include <nt2/include/constants/nan.hpp>
#include <nt2/include/functions/scalar/acsc.hpp>
#include <nt2/include/functions/scalar/is_eqz.hpp>
#include <nt2/include/functions/scalar/is_ltz.hpp>
#include <nt2/include/functions/scalar/abs.hpp>
#include <nt2/include/functions/scalar/sqrt.hpp>
#include <nt2/include/functions/scalar/is_equal.hpp>
#include <nt2/include/functions/scalar/minusone.hpp>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::asec_, tag::cpu_
                            , (A0)
                            , (scalar_< double_<A0> >)
                            )
  {
    typedef A0 result_type;
    NT2_FUNCTOR_CALL(1)
    {
      if (nt2::is_equal(a0, nt2::One<A0>())) return nt2::Zero<A0>();
      A0 tmp =  (nt2::Pio_2<A0>()-nt2::acsc(a0))+  double_constant<A0, 0x3c91a62633145c07ll>();
      return tmp;
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::asec_, tag::cpu_
                            , (A0)
                            , (scalar_< single_<A0> >)
                            )
  {

    typedef A0 result_type;

    NT2_FUNCTOR_CALL(1)
    {
      A0 ax =  nt2::abs(a0);
      if (ax <  nt2::One<A0>()) return nt2::Nan<A0>();
      A0 ax1 =  nt2::minusone(ax);

      if (ax1 < 0.001f)
      {
        A0 tmp = nt2::sqrt(2*(ax1))*(1-ax1*((5/12.0f)
                                      +ax1*((43/160.0f)
                                      -ax1*((177/896.0f)
                                      +ax1*(2867/18432.0f))))
                          );

        return (nt2::is_ltz(a0)) ? nt2::Pi<A0>()-tmp : tmp;
      }

      if (is_equal(a0, One<A0>())) return Zero<A0>();
      A0 tmp =  (nt2::Pio_2<A0>()-nt2::acsc(a0));
      return tmp;
    }
  };
} }

#endif
