//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_ARITHMETIC_FUNCTIONS_COMPLEX_GENERIC_SQR_HPP_INCLUDED
#define NT2_ARITHMETIC_FUNCTIONS_COMPLEX_GENERIC_SQR_HPP_INCLUDED

#include <nt2/arithmetic/functions/sqr.hpp>
#include <nt2/include/functions/real.hpp>
#include <nt2/include/functions/imag.hpp>
#include <nt2/include/functions/if_else.hpp>
#include <nt2/include/functions/is_real.hpp>
#include <nt2/include/functions/is_imag.hpp>
#include <nt2/include/functions/simd/sqr.hpp>
#include <nt2/include/functions/simd/any.hpp>
#include <nt2/include/functions/simd/is_invalid.hpp>
#include <nt2/include/functions/simd/minus.hpp>
#include <nt2/include/functions/simd/unary_minus.hpp>
#include <nt2/include/functions/simd/logical_or.hpp>
#include <nt2/include/functions/simd/logical_andnot.hpp>
#include <nt2/include/functions/simd/multiplies.hpp>
#include <nt2/include/functions/bitwise_cast.hpp>
#include <nt2/include/constants/two.hpp>
#include <nt2/sdk/complex/hierarchy.hpp>
#include <nt2/sdk/complex/meta/as_complex.hpp>
#include <nt2/sdk/complex/meta/as_real.hpp>
#include <nt2/sdk/complex/meta/as_dry.hpp>
#include <nt2/sdk/meta/as_logical.hpp>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::sqr_, tag::cpu_, (A0)
                            , (generic_< complex_< arithmetic_<A0> > >)
                            )
  {
    typedef A0 result_type;
    NT2_FUNCTOR_CALL(1)
    {
      typedef typename meta::as_real<A0>::type rA0;
      typedef typename meta::as_logical<rA0>::type lA0;
      rA0 x = sqr(nt2::real(a0)) - sqr(nt2::imag(a0));
      rA0 y = Two<rA0>()*nt2::real(a0)*nt2::imag(a0);
      result_type r = result_type(x, y);
      if (nt2::any(logical_or(is_invalid(x), is_invalid(y))))
      {
        lA0 test = is_real(a0);
        r = if_else(test, result_type(sqr(nt2::real(a0))), r);
        test = logical_andnot(is_imag(a0), test);
        r = if_else(test, result_type(-sqr(nt2::imag(a0))), r);
      }
      return r;
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::sqr_, tag::cpu_, (A0)
                            , (generic_< dry_< arithmetic_<A0> > >)
                            )
  {
    typedef A0 result_type;
    NT2_FUNCTOR_CALL(1)
    {
      return bitwise_cast<result_type>(nt2::sqr(nt2::real(a0)));
    }
  };
} }

#endif
