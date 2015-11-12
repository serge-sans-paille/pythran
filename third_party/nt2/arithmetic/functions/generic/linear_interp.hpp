//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2014   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2014   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_ARITHMETIC_FUNCTIONS_GENERIC_LINEAR_INTERP_HPP_INCLUDED
#define NT2_ARITHMETIC_FUNCTIONS_GENERIC_LINEAR_INTERP_HPP_INCLUDED

#include <nt2/arithmetic/functions/linear_interp.hpp>
#include <nt2/include/functions/oneminus.hpp>
#include <nt2/include/functions/fma.hpp>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::linear_interp_, tag::cpu_,
                              (A0)(A1)(A2),
                              (generic_<floating_<A0> >)
                              (generic_<floating_<A1> >)
                              (generic_<floating_<A2> >)
                            )
  {
    typedef A0 result_type;

    BOOST_FORCEINLINE
    result_type operator()(A0 const& dx, A1 const& a, A2 const& b ) const
    {
      return nt2::fma(dx, a, nt2::oneminus(dx)*b);
    }
  };
} }

#endif
