//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_FUZZY_FUNCTIONS_SCALAR_KNUTH_EQUAL_HPP_INCLUDED
#define NT2_FUZZY_FUNCTIONS_SCALAR_KNUTH_EQUAL_HPP_INCLUDED

#include <nt2/fuzzy/functions/knuth_equal.hpp>
#include <nt2/include/functions/scalar/fast_ldexp.hpp>
#include <nt2/include/functions/scalar/exponent.hpp>
#include <nt2/include/functions/scalar/maxnummag.hpp>
#include <nt2/include/functions/scalar/abs.hpp>
#include <nt2/sdk/meta/as_logical.hpp>


/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is floating_
/////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::knuth_equal_, tag::cpu_
                            , (A0)
                            , (scalar_< floating_<A0> >)(scalar_< floating_<A0> >)(scalar_< floating_<A0> >)
                            )
  {
    typedef typename meta::as_logical<A0>::type result_type;
    NT2_FUNCTOR_CALL_REPEAT(3)
    {
      return result_type(nt2::abs(a0-a1) <= fast_ldexp(a2, exponent(maxnummag(a0, a1))));
    }
  };
} }


#endif
