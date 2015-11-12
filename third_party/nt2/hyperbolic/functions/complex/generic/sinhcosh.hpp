//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_HYPERBOLIC_FUNCTIONS_COMPLEX_GENERIC_SINHCOSH_HPP_INCLUDED
#define NT2_HYPERBOLIC_FUNCTIONS_COMPLEX_GENERIC_SINHCOSH_HPP_INCLUDED
#include <nt2/hyperbolic/functions/sinhcosh.hpp>
#include <nt2/include/functions/sincos.hpp>
#include <nt2/include/functions/sinhcosh.hpp>
#include <nt2/include/functions/real.hpp>
#include <nt2/include/functions/imag.hpp>
#include <nt2/sdk/complex/meta/as_complex.hpp>
#include <nt2/sdk/complex/meta/as_real.hpp>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::sinhcosh_, tag::cpu_
                            , (A0)
                            , (generic_ < complex_<floating_ < A0> > > )
                              (generic_ < complex_<floating_ < A0> > > )
                              (generic_ < complex_<floating_ < A0> > > )
                            )
  {
    typedef void result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& a0,A0 & a1,A0 & a2) const
    {
      typedef typename meta::as_real<A0>::type rtype;
      rtype c, s, ch, sh;

      sincos(nt2::imag(a0), s, c);
      sinhcosh(nt2::real(a0), sh, ch);

      a1 = A0(sh*c, ch*s);
      a2 = A0(c*ch, s*sh);
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::sinhcosh_, tag::cpu_
                            , (A0)
                            , (generic_ < dry_<floating_ < A0> > > )
                              (generic_ < dry_<floating_ < A0> > > )
                              (generic_ < dry_<floating_ < A0> > > )
                            )
  {
    typedef void result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& a0,A0 & a1,A0 & a2) const
    {
      typedef typename meta::as_real<A0>::type rtype;
      rtype ch, sh;
      sinhcosh(nt2::real(a0), sh, ch);
      a1 =  bitwise_cast<A0>(sh);
      a2 =  bitwise_cast<A0>(ch);
    }
  };


  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::sinhcosh_, tag::cpu_
                            , (A0)
                            , (generic_ < complex_<floating_ < A0> > > )
                              (generic_ < complex_<floating_ < A0> > > )
                            )
  {
    typedef A0 result_type;
    BOOST_FORCEINLINE A0 operator()(A0 const& a0,A0 & a2) const
    {
      result_type a1;
      sinhcosh(a0, a1, a2);
      return a1;
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION(nt2::tag::sinhcosh_, tag::cpu_,
                             (A0),
                             (generic_ < complex_<floating_<A0> > > )
                             )
  {
    typedef std::pair<A0, A0> result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& a0) const
    {
      A0 first, second;
      sinhcosh(a0, first, second);
      return result_type(first, second);
    }
  };
} }

#endif
