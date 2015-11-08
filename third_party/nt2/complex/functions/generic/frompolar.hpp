//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_COMPLEX_FUNCTIONS_GENERIC_FROMPOLAR_HPP_INCLUDED
#define NT2_COMPLEX_FUNCTIONS_GENERIC_FROMPOLAR_HPP_INCLUDED
#include <nt2/complex/functions/frompolar.hpp>
#include <nt2/sdk/complex/complex.hpp>
#include <nt2/sdk/complex/meta/as_complex.hpp>
#include <nt2/include/functions/sincos.hpp>
#include <nt2/include/functions/multiplies.hpp>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::frompolar_, tag::cpu_, (A0)
                            , (generic_< arithmetic_<A0> >)
                              (generic_< arithmetic_<A0> >)
                            )
  {
    typedef typename meta::as_complex<A0>::type  result_type;
    BOOST_FORCEINLINE result_type operator()(A0 const& a0, A0 const& a1) const
    {
      A0 s, c;
      nt2::sincos(a1, s, c);
      return multiplies(a0, result_type(c, s));
    }
  };

} }

#endif
