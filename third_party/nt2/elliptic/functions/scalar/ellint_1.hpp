//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_ELLIPTIC_FUNCTIONS_SCALAR_ELLINT_1_HPP_INCLUDED
#define NT2_ELLIPTIC_FUNCTIONS_SCALAR_ELLINT_1_HPP_INCLUDED

#include <nt2/elliptic/functions/ellint_1.hpp>
#include <nt2/include/constants/eps.hpp>
#include <nt2/include/constants/inf.hpp>
#include <nt2/include/constants/nan.hpp>
#include <nt2/include/constants/one.hpp>
#include <nt2/include/constants/pio_2.hpp>
#include <nt2/include/functions/scalar/abs.hpp>
#include <nt2/include/functions/scalar/average.hpp>
#include <nt2/include/functions/scalar/oneminus.hpp>
#include <nt2/include/functions/scalar/sqr.hpp>
#include <nt2/include/functions/scalar/sqrt.hpp>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::ellint_1_, tag::cpu_
                            , (A0)
                            , (scalar_< floating_<A0> >)
                            )
  {
    typedef A0 result_type;
    NT2_FUNCTOR_CALL(1)
    {
      result_type x = a0;
      if (abs(x) > nt2::One<result_type>()) return nt2::Nan<result_type>();
      if (x == nt2::One<result_type>())  return nt2::Inf<result_type>();
      result_type a = One<result_type>();
      result_type b = nt2::sqrt(oneminus(sqr(a0)));
      result_type c = a0;
      while (abs(c) > Eps<result_type>())
      {
        result_type an=average(a, b);
        result_type bn=nt2::sqrt(a*b);
        c=average(a, -b);
        a=an;
        b=bn;
      }
      return  Pio_2<result_type>()/a;
    }
  };
} }

#endif
