//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_COMBINATORIAL_FUNCTIONS_SCALAR_LCM_HPP_INCLUDED
#define NT2_COMBINATORIAL_FUNCTIONS_SCALAR_LCM_HPP_INCLUDED

#include <nt2/combinatorial/functions/lcm.hpp>
#include <nt2/include/constants/nan.hpp>
#include <nt2/include/functions/scalar/abs.hpp>
#include <nt2/include/functions/scalar/gcd.hpp>
#include <nt2/include/functions/scalar/is_invalid.hpp>
#include <nt2/include/functions/scalar/trunc.hpp>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::lcm_, tag::cpu_
                            , (A0)
                            , (scalar_< integer_<A0> >)
                              (scalar_< integer_<A0> >)
                            )
  {
    typedef A0 result_type;
    NT2_FUNCTOR_CALL_REPEAT(2)
    {
     return nt2::abs(a0 * (a1 / gcd(a0, a1 ? a1 : A0(1))));
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::lcm_, tag::cpu_
                            , (A0)(A1)
                            , (scalar_< floating_<A0> >)
                              (scalar_< floating_<A1> >)
                            )
  {

    typedef typename boost::common_type<A0,A1>::type result_type;

    NT2_FUNCTOR_CALL(2)
    {
      typedef result_type type;
      if (is_invalid(a0+a1)) return Nan<type>();
      return nt2::abs(trunc(a0)*(a1/gcd(a0,a1)));
    }
  };
} }

#endif
