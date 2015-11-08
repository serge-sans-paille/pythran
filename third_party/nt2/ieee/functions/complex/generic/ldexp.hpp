//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_IEEE_FUNCTIONS_COMPLEX_GENERIC_LDEXP_HPP_INCLUDED
#define NT2_IEEE_FUNCTIONS_COMPLEX_GENERIC_LDEXP_HPP_INCLUDED
#include <nt2/ieee/functions/ldexp.hpp>
#include <nt2/include/functions/imag.hpp>
#include <nt2/include/functions/real.hpp>
#include <nt2/sdk/complex/meta/as_dry.hpp>
#include <nt2/sdk/complex/meta/as_complex.hpp>
#include <nt2/sdk/complex/meta/as_real.hpp>

namespace nt2  { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::ldexp_, tag::cpu_, (A0)(A1)
                            , (generic_< complex_ < floating_<A0> > >)
                              (generic_< integer_<A1> >)
                            )
  {
    typedef A0 result_type;
    BOOST_SIMD_FUNCTOR_CALL(2)
    {
      return result_type(nt2::ldexp(nt2::real(a0), a1),nt2::ldexp(nt2::imag(a0), a1));
    }
  };

   NT2_FUNCTOR_IMPLEMENTATION( boost::simd::tag::ldexp_, tag::cpu_, (A0)(A1)
                            , (generic_< dry_ < floating_<A0> > >)
                              (generic_< integer_<A1> >)
                            )
  {
    typedef A0 result_type;
    BOOST_SIMD_FUNCTOR_CALL(2)
    {
      return result_type(nt2::ldexp(nt2::real(a0), a1));
    }
  };
} }

#endif
