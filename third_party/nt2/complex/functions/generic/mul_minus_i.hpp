//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_COMPLEX_FUNCTIONS_GENERIC_MUL_MINUS_I_HPP_INCLUDED
#define NT2_COMPLEX_FUNCTIONS_GENERIC_MUL_MINUS_I_HPP_INCLUDED

#include <nt2/complex/functions/mul_minus_i.hpp>
#include <nt2/include/functions/real.hpp>
#include <nt2/include/functions/imag.hpp>
#include <nt2/include/functions/simd/unary_minus.hpp>
#include <nt2/sdk/complex/hierarchy.hpp>
#include <nt2/sdk/complex/meta/as_real.hpp>
#include <nt2/sdk/complex/meta/as_complex.hpp>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::mul_minus_i_, tag::cpu_, (A0)
                            , (generic_< complex_ < arithmetic_<A0> > >)
                            )
  {
    typedef typename meta::as_complex<A0>::type result_type;
    BOOST_FORCEINLINE result_type operator()(A0 const& a0) const
    {
      return result_type(nt2::imag(a0), -nt2::real(a0));
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::mul_minus_i_, tag::cpu_, (A0)
                            , (generic_< arithmetic_<A0> >)
                            )
  {
    typedef typename meta::as_complex<A0>::type result_type;
    BOOST_FORCEINLINE result_type operator()(A0 const& a0) const
    {
      return result_type(Zero<A0>(), -a0);
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::mul_minus_i_, tag::cpu_, (A0)
                            , (generic_< dry_< arithmetic_<A0> > > )
                            )
  {
    typedef typename meta::as_complex<A0>::type result_type;
    BOOST_FORCEINLINE result_type operator()(A0 const& a0) const
    {
      typedef typename meta::as_real<A0>::type rtype;
      return result_type(Zero<rtype>(), -nt2::real(a0));
    }
  };
} }

#endif
