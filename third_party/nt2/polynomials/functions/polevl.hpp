//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_POLYNOMIALS_FUNCTIONS_POLEVL_HPP_INCLUDED
#define NT2_POLYNOMIALS_FUNCTIONS_POLEVL_HPP_INCLUDED
#include <nt2/include/functor.hpp>
// polevl(x, p)
// This compute the valuation of a polynomial p of degree N at x
// The polynomial is supposed to be given by an array of N+1 elements
// in decreasing degrees order

namespace nt2 { namespace tag
  {
    struct polevl_ : ext::elementwise_<polevl_> { typedef ext::elementwise_<polevl_> parent; };
  }
  NT2_FUNCTION_IMPLEMENTATION(tag::polevl_, polevl, 2)
}


#endif

// modified by jt the 25/12/2010
