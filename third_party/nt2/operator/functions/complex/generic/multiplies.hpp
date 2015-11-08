//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_OPERATOR_FUNCTIONS_COMPLEX_GENERIC_MULTIPLIES_HPP_INCLUDED
#define NT2_OPERATOR_FUNCTIONS_COMPLEX_GENERIC_MULTIPLIES_HPP_INCLUDED

#include <nt2/operator/functions/multiplies.hpp>
#include <nt2/include/functions/real.hpp>
#include <nt2/include/functions/imag.hpp>
#include <nt2/include/functions/pure.hpp>
#include <nt2/include/functions/simd/minus.hpp>
#include <nt2/include/functions/simd/unary_minus.hpp>
#include <nt2/include/functions/simd/any.hpp>
#include <nt2/include/functions/fma.hpp>
#include <nt2/include/functions/simd/all.hpp>
#include <nt2/include/functions/simd/is_nez.hpp>
#include <nt2/include/functions/simd/is_invalid.hpp>
#include <nt2/include/functions/logical_or.hpp>
#include <nt2/include/functions/logical_and.hpp>
#include <nt2/include/functions/logical_andnot.hpp>
#include <nt2/include/functions/if_else.hpp>
#include <nt2/include/functions/if_zero_else.hpp>
#include <nt2/include/functions/if_else_zero.hpp>
#include <nt2/include/functions/is_finite.hpp>
#include <nt2/include/functions/is_eqz.hpp>
#include <nt2/include/functions/is_real.hpp>
#include <nt2/include/functions/is_imag.hpp>
#include <nt2/include/functions/simd/mul_i.hpp>
#include <nt2/include/functions/bitwise_cast.hpp>
#include <nt2/include/constants/zero.hpp>
#include <nt2/include/constants/nan.hpp>
#include <nt2/sdk/complex/hierarchy.hpp>
#include <nt2/sdk/complex/meta/as_real.hpp>
#include <nt2/sdk/complex/meta/as_dry.hpp>
#include <nt2/sdk/meta/as_logical.hpp>
#include <boost/simd/sdk/config.hpp>

namespace nt2 { namespace ext
{
  // complex/complex
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::multiplies_, tag::cpu_, (A0)
                            , ((generic_< complex_< arithmetic_<A0> > >))
                              ((generic_< complex_< arithmetic_<A0> > >))
                            )
  {
    typedef A0 result_type;
    NT2_FUNCTOR_CALL_REPEAT(2)
    {
      typedef typename meta::as_real<A0>::type r_type;
      const r_type a = nt2::real(a0);
      const r_type b = nt2::imag(a0);
      const r_type c = nt2::real(a1);
      const r_type d = nt2::imag(a1);
      result_type r(fma(a,c,-b*d), fma(a,d,b*c));
#ifndef BOOST_SIMD_NO_INVALIDS
      typedef typename meta::as_logical<r_type>::type l_type;
      l_type test = is_finite(r);
      if (nt2::all(test)) return r;
      l_type cur  = nt2::logical_andnot(is_real(a0), test);
      if (nt2::any(cur))
      {
        r = if_else(cur, nt2::multiplies(a, a1), r);
        test = logical_or(test, cur);
        if (nt2::all(test)) return r;
      }
      cur = nt2::logical_andnot(is_imag(a0), test);
      if (nt2::any(cur))
      {
        r = if_else(cur, nt2::mul_i(nt2::multiplies(b, a1)), r);
        test = logical_or(test, cur);
        if (nt2::all(test)) return r;
      }
      cur = nt2::logical_andnot(is_real(a1), test);
      if (nt2::any(cur))
      {
        r = if_else(cur, nt2::multiplies(c, a0), r);
        test = logical_or(test, cur);
        if (nt2::all(test)) return r;
      }
      cur = nt2::logical_andnot(is_imag(a1), test);
      if (nt2::any(cur))
      {
        r = if_else(cur, nt2::mul_i(nt2::multiplies(d, a0)), r);
        test = logical_or(test, cur);
        if (nt2::all(test)) return r;
      }
 #endif
      return r;
    }
  };

  // complex/real
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::multiplies_, tag::cpu_, (A0)(A1)
                            , ((generic_< arithmetic_<A0> >))
                              ((generic_< complex_< arithmetic_<A1> > >))
                            )
  {
    typedef A1 result_type;
    typedef A0 r_type;
    NT2_FUNCTOR_CALL(2)
    {
      r_type r = a0*real(a1);
      r_type i = a0*imag(a1);
#ifndef BOOST_SIMD_NO_INVALIDS
      typename meta::as_logical<A1>::type is_real_a1 = is_real(a1);
      r = if_zero_else(logical_andnot(is_imag(a1), is_real_a1), r);
      i = if_zero_else(is_real_a1, i);
#endif
      return result_type(r, i);
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::multiplies_, tag::cpu_, (A0)(A1)
                            , ((generic_< complex_< arithmetic_<A0> > >))
                              ((generic_< arithmetic_<A1> >))
                            )
  {
    typedef A0 result_type;
    NT2_FUNCTOR_CALL(2)
    {
      return nt2::multiplies(a1, a0);
    }
  };
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::multiplies_, tag::cpu_, (A0)(A1)
                            , ((generic_< dry_ < arithmetic_<A0> > >))
                              ((generic_< complex_< arithmetic_<A1> > >))
                            )
  {
    typedef A1 result_type;
    NT2_FUNCTOR_CALL(2)
    {
      return nt2::multiplies(nt2::real(a0), a1);
    }
  };
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::multiplies_, tag::cpu_, (A0)(A1)
                            , ((generic_< complex_< arithmetic_<A0> > >))
                              ((generic_< dry_ < arithmetic_<A1> > >))
                            )
  {
    typedef A0 result_type;
    NT2_FUNCTOR_CALL(2)
    {
      return nt2::multiplies(a0, nt2::real(a1));
    }
  };

  // dry/dry
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::multiplies_, tag::cpu_, (A0)(A1)
                            , ((generic_< dry_< arithmetic_<A0> > >))
                              ((generic_< dry_< arithmetic_<A1> > >))
                            )
  {
    typedef typename meta::as_dry<A0>::type result_type;
    NT2_FUNCTOR_CALL(2)
    {
      return bitwise_cast<result_type>(nt2::real(a0)*nt2::real(a1));
    }
  };

} }

#endif
