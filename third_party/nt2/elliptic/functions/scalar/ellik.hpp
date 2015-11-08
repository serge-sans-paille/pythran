//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_ELLIPTIC_FUNCTIONS_SCALAR_ELLIK_HPP_INCLUDED
#define NT2_ELLIPTIC_FUNCTIONS_SCALAR_ELLIK_HPP_INCLUDED
#include <nt2/elliptic/functions/ellik.hpp>
#include <boost/math/special_functions/ellint_1.hpp>
#include <nt2/include/constants/eps.hpp>
#include <nt2/include/constants/nan.hpp>
#include <nt2/include/constants/one.hpp>
#include <nt2/include/constants/pi.hpp>
#include <nt2/include/constants/pio_2.hpp>
#include <nt2/include/functions/scalar/abs.hpp>
#include <nt2/include/functions/scalar/atan.hpp>
#include <nt2/include/functions/scalar/average.hpp>
#include <nt2/include/functions/scalar/ellint_1.hpp>
#include <nt2/include/functions/scalar/is_eqz.hpp>
#include <nt2/include/functions/scalar/is_ltz.hpp>
#include <nt2/include/functions/scalar/log.hpp>
#include <nt2/include/functions/scalar/oneminus.hpp>
#include <nt2/include/functions/scalar/oneplus.hpp>
#include <nt2/include/functions/scalar/sqrt.hpp>
#include <nt2/include/functions/scalar/tan.hpp>
#include <nt2/include/functions/scalar/toint.hpp>
#include <nt2/sdk/error/policies.hpp>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::ellik_, tag::cpu_
                            , (A0)
                            , (scalar_< double_<A0> >)
                              (scalar_< double_<A0> >)
                            )
  {
    typedef A0 result_type;
    NT2_FUNCTOR_CALL_REPEAT(2)
    {
      if (a1>nt2::One<A0>()||(nt2::is_ltz(a1))) return nt2::Nan<A0>();
      if (nt2::is_eqz(a1))  return A0(a0);
      return boost::math::ellint_1(nt2::sqrt(a1), a0, nt2_policy());
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::ellik_, tag::cpu_
                            , (A0)
                            , (scalar_< single_<A0> >)(scalar_< single_<A0> >)
                            )
  {
    typedef A0 result_type;
    NT2_FUNCTOR_CALL_REPEAT(2)
    {
      if (a1>nt2::One<A0>()||(nt2::is_ltz(a1))) return nt2::Nan<A0>();
      if (nt2::is_eqz(a1))  return a0;
      A0 phi = nt2::abs(a0);
      A0 m = a1;
      A0 a = nt2::One<A0>();
      A0 b = nt2::oneminus(m);
      if( nt2::is_eqz(b) )   return nt2::log(nt2::tan(nt2::average(Pio_2<A0>(),phi)));
      b = nt2::sqrt(b);
      A0 c = nt2::sqrt(m);
      A0 d = nt2::One<A0>();
      A0 t = nt2::tan(phi);
      int mod = nt2::toint((phi+nt2::Pio_2<A0>())/nt2::Pi<A0>());
      while( nt2::abs(c) > nt2::abs(a)*nt2::Eps<A0>() )
      {
        A0 temp = b/a;
        phi += nt2::atan(t*temp) + mod*nt2::Pi<A0>();
        mod = nt2::toint((phi+nt2::Pio_2<A0>())/nt2::Pi<A0>());
        t = t*nt2::oneplus(temp)/( nt2::oneminus(temp*t*t));
        c = nt2::average(a,-b);
        temp = nt2::sqrt(a*b);
        a = nt2::average(a,b);
        b = temp;
        d += d;
      }
      A0 temp = (nt2::atan(t) + mod * nt2::Pi<A0>())/(d * a);
      if( nt2::is_ltz(a0) )  temp = -temp;
      return temp;
    }
  };
} }

#endif
