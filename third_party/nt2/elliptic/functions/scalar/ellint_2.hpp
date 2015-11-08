//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_ELLIPTIC_FUNCTIONS_SCALAR_ELLINT_2_HPP_INCLUDED
#define NT2_ELLIPTIC_FUNCTIONS_SCALAR_ELLINT_2_HPP_INCLUDED
#include <nt2/elliptic/functions/ellint_2.hpp>
#include <boost/math/special_functions/ellint_2.hpp>
#include <nt2/include/constants/nan.hpp>
#include <nt2/include/constants/one.hpp>
#include <nt2/include/functions/scalar/abs.hpp>
#include <nt2/sdk/error/policies.hpp>

namespace nt2 { namespace ext
{

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::ellint_2_, tag::cpu_
                            , (A0)
                            , (scalar_< floating_<A0> >)
                            )
  {

    typedef A0 result_type;

    NT2_FUNCTOR_CALL(1)
    {
      result_type x = nt2::abs(a0);
      if (x>nt2::One<A0>())    return nt2::Nan<A0>();
      if (x == nt2::One<A0>()) return x;
      return boost::math::ellint_2(a0, nt2_policy());
    }
  };
} }

#endif
