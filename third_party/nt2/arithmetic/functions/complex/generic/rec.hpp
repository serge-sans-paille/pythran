//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_ARITHMETIC_FUNCTIONS_COMPLEX_GENERIC_REC_HPP_INCLUDED
#define NT2_ARITHMETIC_FUNCTIONS_COMPLEX_GENERIC_REC_HPP_INCLUDED

#include <nt2/arithmetic/functions/rec.hpp>
#include <nt2/include/functions/simd/abs.hpp>
#include <nt2/include/functions/real.hpp>
#include <nt2/include/functions/imag.hpp>
#include <nt2/include/functions/sqr_abs.hpp>
#include <nt2/include/functions/conj.hpp>
#include <nt2/include/functions/if_else.hpp>
#include <nt2/include/functions/is_real.hpp>
#include <nt2/include/functions/is_imag.hpp>
#include <nt2/include/functions/is_inf.hpp>
#include <nt2/include/functions/is_finite.hpp>
#include <nt2/include/functions/divides.hpp>
#include <nt2/include/functions/ldexp.hpp>
#include <nt2/include/functions/simd/minus.hpp>
#include <nt2/include/functions/simd/is_eqz.hpp>
#include <nt2/include/functions/simd/unary_minus.hpp>
#include <nt2/include/functions/simd/plus.hpp>
#include <nt2/include/functions/simd/rec.hpp>
#include <nt2/include/functions/simd/exponent.hpp>
#include <nt2/include/functions/simd/copysign.hpp>
#include <nt2/include/functions/simd/all.hpp>
#include <nt2/include/functions/simd/is_less.hpp>
#include <nt2/include/constants/inf.hpp>
#include <nt2/sdk/complex/hierarchy.hpp>
#include <nt2/sdk/complex/meta/as_real.hpp>
#include <nt2/sdk/meta/as_integer.hpp>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::rec_, tag::cpu_, (A0)
                            , (generic_< complex_< arithmetic_<A0> > >)
                            )
  {
    typedef A0 result_type;
    NT2_FUNCTOR_CALL(1)
    {
      typedef typename meta::as_real<result_type>::type rtype;
      typedef typename meta::as_integer<rtype>::type itype;
      rtype rr =  nt2::abs(nt2::real(a0));
      rtype ii =  nt2::abs(nt2::imag(a0));
      itype e =  -if_else(lt(rr, ii), exponent(ii), exponent(rr));
      A0 aa0 =  nt2::ldexp(a0, e);
      rtype denom =  sqr_abs(aa0);
      A0 num = conj(aa0);
      A0 r =  ldexp(num/denom, e);
      r = if_else(is_eqz(denom), result_type(copysign(Inf<rtype>(), nt2::real(a0)), Zero<rtype>()), r);
      if (nt2::all(is_finite(a0))) return r;
      r = if_else(is_inf(a0),  result_type(rec(copysign(denom, nt2::real(a0))), Zero<rtype>()), r);
      r = if_else(is_imag(a0), result_type(Zero<rtype>(), nt2::imag(r)), r);
      r = if_else(is_real(a0), result_type(nt2::real(r)), r);
      return r;
    }
  };


  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::rec_, tag::cpu_, (A0)
                            , (generic_< dry_< arithmetic_<A0> > >)
                            )
  {
    typedef A0 result_type;
    NT2_FUNCTOR_CALL(1)
    {
      return bitwise_cast<result_type>(nt2::rec(nt2::real(a0)));
    }
  };

} }

#endif
