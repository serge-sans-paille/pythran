//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_HYPERBOLIC_FUNCTIONS_SCALAR_COTH_HPP_INCLUDED
#define NT2_HYPERBOLIC_FUNCTIONS_SCALAR_COTH_HPP_INCLUDED

#include <nt2/hyperbolic/functions/coth.hpp>
#include <nt2/hyperbolic/functions/details/tanh_kernel.hpp>
#include <nt2/include/constants/fiveo_8.hpp>
#include <nt2/include/constants/one.hpp>
#include <nt2/include/constants/two.hpp>
#include <nt2/include/functions/scalar/abs.hpp>
#include <nt2/include/functions/scalar/bitofsign.hpp>
#include <nt2/include/functions/scalar/bitwise_xor.hpp>
#include <nt2/include/functions/scalar/coth.hpp>
#include <nt2/include/functions/scalar/exp.hpp>
#include <nt2/include/functions/scalar/fma.hpp>
#include <nt2/include/functions/scalar/minusone.hpp>
#include <nt2/include/functions/scalar/rec.hpp>
#include <nt2/include/functions/scalar/sqr.hpp>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::coth_, tag::cpu_
                            , (A0)
                            , (scalar_< floating_<A0> >)
                            )
  {
    typedef A0 result_type;
    NT2_FUNCTOR_CALL(1)
    {
      //////////////////////////////////////////////////////////////////////////////
      // if x = abs(a0) is less than 5/8 sinh is computed using a polynomial(float)
      // (respectively rational(double)) approx inspirated from cephes.
      // else
      // coth(a0) is  sign(a0)*(1 + 2/(exp(2*x)-1))
      //////////////////////////////////////////////////////////////////////////////
      result_type x = nt2::abs(a0);
      A0 r;
      if( x < Fiveo_8<A0>())
      {
        r = details::tanh_kernel<A0>::coth(x, sqr(x));
      }
      else
      {
        r = fma(Two<A0>(), rec(minusone(exp(x+x))), One<A0>());
      }
      return b_xor(r, bitofsign(a0));
    }
  };
} }
#endif
