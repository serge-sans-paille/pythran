//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_EXPONENTIAL_FUNCTIONS_SCALAR_NTHROOT_HPP_INCLUDED
#define NT2_EXPONENTIAL_FUNCTIONS_SCALAR_NTHROOT_HPP_INCLUDED
#include <nt2/exponential/functions/nthroot.hpp>
#include <boost/simd/sdk/config.hpp>
#include <nt2/include/constants/nan.hpp>
#include <nt2/include/constants/one.hpp>
#include <nt2/include/constants/zero.hpp>
#include <nt2/include/functions/scalar/abs.hpp>
#include <nt2/include/functions/scalar/is_ltz.hpp>
#include <nt2/include/functions/scalar/is_odd.hpp>
#include <nt2/include/functions/scalar/minusone.hpp>
#include <nt2/include/functions/scalar/pow.hpp>
#include <nt2/include/functions/scalar/rec.hpp>
#include <nt2/include/functions/scalar/sign.hpp>

#ifndef BOOST_SIMD_NO_INFINITIES
#include <nt2/include/functions/scalar/is_inf.hpp>
#endif
#include <iostream>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::nthroot_, tag::cpu_
                            , (A0)(A1)
                            , (scalar_< floating_<A0> >)(scalar_< integer_<A1> >)
                            )
  {

    typedef A0 result_type;

    NT2_FUNCTOR_CALL(2)
    {
      bool is_ltza0 = is_ltz(a0);
      bool is_odda1 = is_odd(a1);
      if (is_ltza0 && !is_odda1) return Nan<A0>();
      A0 x = nt2::abs(a0);
      if (x == One<A0>())  return a0;
      if (!a1) return (x < One<A0>()) ? Zero<A0>() : sign(a0)*Inf<A0>();
      if (!a0) return Zero<A0>();
      #ifndef BOOST_SIMD_NO_INFINITIES
      if (is_inf(a0)) return (a1) ? a0 : One<A0>();
      #endif
      A0 aa1 = static_cast<A0>(a1);
      A0 y = nt2::pow(x,rec(aa1));
      // Correct numerical errors (since, e.g., 64^(1/3) is not exactly 4)
      // by one iteration of Newton's method
      if (y) y -= (nt2::pow(y, a1) - x) / (aa1* nt2::pow(y,minusone(a1)));
      return (is_ltza0 && is_odda1)? -y : y;
    }
  };
} }

#endif
