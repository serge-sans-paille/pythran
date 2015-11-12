//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TRIGONOMETRIC_FUNCTIONS_COMPLEX_GENERIC_SINCOS_HPP_INCLUDED
#define NT2_TRIGONOMETRIC_FUNCTIONS_COMPLEX_GENERIC_SINCOS_HPP_INCLUDED
#include <nt2/trigonometric/functions/sincos.hpp>
#include <nt2/include/functions/sincos.hpp>
#include <nt2/include/functions/sinhcosh.hpp>
#include <nt2/include/functions/real.hpp>
#include <nt2/include/functions/imag.hpp>
#include <nt2/include/functions/is_imag.hpp>
#include <nt2/include/functions/is_real.hpp>
#include <nt2/include/functions/logical_and.hpp>
#include <nt2/include/functions/is_invalid.hpp>
#include <nt2/include/functions/is_inf.hpp>
#include <nt2/sdk/complex/meta/as_complex.hpp>
#include <nt2/sdk/complex/meta/as_real.hpp>
#include <nt2/sdk/meta/as_logical.hpp>
#include <nt2/include/functions/logical_or.hpp>
#include <nt2/include/functions/if_zero_else.hpp>
#include <nt2/include/functions/if_else.hpp>
#include <nt2/include/functions/any.hpp>
#include <nt2/include/constants/inf.hpp>
#include <nt2/include/constants/nan.hpp>
#include <boost/fusion/include/std_pair.hpp>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION(nt2::tag::sincos_, tag::cpu_,
                             (A0),
                             (generic_ < complex_<floating_ < A0> > > )
                             (generic_ < complex_<floating_ < A0> > > )
                             (generic_ < complex_<floating_ < A0> > > )
                            )
  {
    typedef void result_type;
    inline void operator()(A0 const& a0,A0 & a1,A0 & a2) const
    {
      typedef typename meta::as_real<A0>::type rtype;
      typedef typename meta::as_logical<A0>::type ltype;
      rtype c, s, ch, sh;
      sincos(nt2::real(a0), s, c);
      sinhcosh(nt2::imag(a0), sh, ch);
      rtype r1 = if_zero_else(is_imag(a0), s*ch);
      rtype i1 = if_zero_else(is_real(a0), c*sh);
      rtype r2 = c*ch;
      rtype i2 = if_zero_else(logical_or(is_imag(a0), is_real(a0)), -s*sh);
      a1 =  A0(r1, i1);
      a2 =  A0(r2, i2);
#ifndef BOOST_SIMD_NO_INVALIDS
      ltype t = logical_and(is_invalid(real(a0)), is_inf(imag(a0)));
      if (any(t))
      {
        A0 zs = A0(Nan<rtype>(),imag(a0));
        A0 zc = A0(Inf<rtype>(),Nan<rtype>());
        a1 = if_else(t, zs, a1);
        a2 = if_else(t, zc, a2);
      }
#endif

    }
  };

  NT2_FUNCTOR_IMPLEMENTATION(nt2::tag::sincos_, tag::cpu_,
                             (A0),
                             (generic_ < dry_<floating_ < A0> > > )
                             (generic_ < dry_<floating_ < A0> > > )
                             (generic_ < dry_<floating_ < A0> > > )
                            )
  {
    typedef void result_type;
    inline void operator()(A0 const& a0,A0 & a1,A0 & a2) const
    {
      typedef typename meta::as_real<A0>::type rtype;
      rtype c, s;
      sincos(nt2::real(a0), s, c);
      a1 =  bitwise_cast<A0>(c);
      a2 =  bitwise_cast<A0>(s);
    }
  };


  NT2_FUNCTOR_IMPLEMENTATION(nt2::tag::sincos_, tag::cpu_,
                             (A0),
                             (generic_ < complex_<floating_ < A0> > > )
                             (generic_ < complex_<floating_ < A0> > > )
                            )
  {
    typedef A0 result_type;
    inline A0 operator()(A0 const& a0,A0 & a2) const
    {
      result_type a1;
      sincos(a0, a1, a2);
      return a1;
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION(nt2::tag::sincos_, tag::cpu_,
                             (A0),
                             (generic_ < complex_<floating_<A0> > > )
                            )
  {
    typedef std::pair<A0, A0>           result_type;
    NT2_FUNCTOR_CALL(1)
    {
      A0 first, second;
      sincos(a0, first, second);
      return result_type(first, second);
    }
  };
} }


#endif
