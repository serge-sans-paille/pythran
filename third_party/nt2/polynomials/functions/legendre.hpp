//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_POLYNOMIALS_FUNCTIONS_LEGENDRE_HPP_INCLUDED
#define NT2_POLYNOMIALS_FUNCTIONS_LEGENDRE_HPP_INCLUDED
#include <nt2/include/functor.hpp>

namespace nt2 { namespace tag
  {
    struct legendre_ : ext::elementwise_<legendre_> { typedef ext::elementwise_<legendre_> parent; };
  }
  NT2_FUNCTION_IMPLEMENTATION(tag::legendre_, legendre, 2)
}


#endif

// modified by jt the 25/12/2010
