//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_HYPERBOLIC_FUNCTIONS_COMPLEX_GENERIC_SINH_HPP_INCLUDED
#define NT2_HYPERBOLIC_FUNCTIONS_COMPLEX_GENERIC_SINH_HPP_INCLUDED
#include <nt2/hyperbolic/functions/sinh.hpp>
#include <nt2/include/functions/simd/sincos.hpp>
#include <nt2/include/functions/simd/sinhcosh.hpp>
#include <nt2/include/functions/simd/is_nan.hpp>
#include <nt2/include/functions/is_invalid.hpp>
#include <nt2/include/functions/simd/logical_and.hpp>
#include <nt2/include/functions/simd/if_else.hpp>
#include <nt2/include/functions/simd/if_zero_else.hpp>
#include <nt2/include/functions/simd/none.hpp>
#include <nt2/include/functions/real.hpp>
#include <nt2/include/functions/imag.hpp>
#include <nt2/include/functions/is_real.hpp>
#include <nt2/include/functions/is_imag.hpp>
#include <nt2/include/functions/is_eqz.hpp>
#include <nt2/include/functions/bitwise_cast.hpp>
#include <nt2/include/constants/nan.hpp>
#include <nt2/include/functions/is_inf.hpp>


//sinh(x+iy)=sinh(x)cos(y)+i.cosh(x)sin(y).
namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::sinh_, tag::cpu_, (A0)
                            , (generic_< complex_< floating_<A0> > >)
                            )
  {
    typedef A0 result_type;
    NT2_FUNCTOR_CALL(1)
    {
      typedef typename meta::as_real<A0>::type rtype;
      rtype c, s, ch, sh;
      sincos(nt2::imag(a0), s, c);
      sinhcosh(nt2::real(a0), sh, ch);
      rtype r = c*sh;
      rtype i = s*ch;

      if (none(is_invalid(a0))) return result_type(r, i);
      r = if_else(logical_and(is_inf(nt2::real(a0)), is_invalid(nt2::imag(a0))), nt2::real(a0), r);
      i = if_else(logical_and(is_inf(nt2::real(a0)), is_nan(nt2::imag(a0))), nt2::Nan<rtype>(), i);
      r = if_else(is_nan(nt2::real(a0)), nt2::real(a0), r);
      i = if_else(is_nan(nt2::real(a0)), nt2::real(a0), i);
      i = if_zero_else(is_real(a0), i);
      r = if_zero_else(is_imag(a0), r);
      result_type res =  result_type(r, i);
      return res;
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::sinh_, tag::cpu_, (A0)
                            , (generic_< dry_< floating_<A0> > >)
                            )
  {
    typedef A0 result_type;
    NT2_FUNCTOR_CALL(1)
    {
      return bitwise_cast<result_type>(nt2::sinh(nt2::real(a0)));
    }
  };
} }

#endif
