//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_HYPERBOLIC_FUNCTIONS_COMPLEX_GENERIC_ASINH_HPP_INCLUDED
#define NT2_HYPERBOLIC_FUNCTIONS_COMPLEX_GENERIC_ASINH_HPP_INCLUDED
#include <nt2/hyperbolic/functions/asinh.hpp>
#include <nt2/include/functions/asin.hpp>
#include <nt2/include/functions/log.hpp>
#include <nt2/include/functions/sqrt.hpp>
#include <nt2/include/functions/oneplus.hpp>
#include <nt2/include/functions/is_real.hpp>
#include <nt2/include/functions/bitwise_cast.hpp>
#include <nt2/include/functions/if_zero_else.hpp>
#include <nt2/include/functions/mul_i.hpp>
#include <nt2/include/functions/mul_minus_i.hpp>
#include <nt2/sdk/complex/meta/as_complex.hpp>
#include <nt2/sdk/complex/meta/as_real.hpp>
#include <nt2/sdk/complex/meta/as_dry.hpp>
#include <nt2/include/functions/mul_minus_i.hpp>
#include <nt2/include/functions/mul_i.hpp>
#include <nt2/include/functions/asin.hpp>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::asinh_, tag::cpu_, (A0)
                            , (generic_< complex_< arithmetic_<A0> > >)
                            )
  {
    typedef A0 result_type;
    NT2_FUNCTOR_CALL(1)
    {
      // We use asinh(z) = i asin(-i z);
      // Note that C99 defines this the other way around (which is
      // to say asin is specified in terms of asinh), this is consistent
      // with C99 though:
      result_type res =  mul_i(nt2::asin(mul_minus_i(a0)));
      return res;
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::asinh_, tag::cpu_, (A0)
                            , (generic_< dry_< arithmetic_<A0> > >)
                            )
  {
    typedef A0 result_type;
    NT2_FUNCTOR_CALL(1)
    {
      //asinh is bijective on the real axis and its computation
      // involves no proper complex value
      return bitwise_cast<result_type>(nt2::asinh(nt2::real(a0)));
    }
  };

} }

#endif
