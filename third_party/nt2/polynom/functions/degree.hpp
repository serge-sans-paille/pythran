//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_POLYNOM_FUNCTIONS_DEGREE_HPP_INCLUDED
#define NT2_POLYNOM_FUNCTIONS_DEGREE_HPP_INCLUDED
#include <nt2/include/functor.hpp>

namespace nt2 { namespace tag
  {
   /*!
     @brief degree generic tag

     Represents the degree function in generic contexts.

     @par Models:
        Hierarchy
   **/
    struct degree_ : ext::elementwise_<degree_>
    {
      /// @brief Parent hierarchy
      typedef ext::elementwise_<degree_> parent;
    };
  }
  /*!
    returns the degree of the input polynomial expression.

    @par Semantic:

    For every expression representing a polynomial:

    @code
    ptrdiff_t r = degree(p);
    @endcode

    The degree is the greatest exponent associated to a non null coefficient.
    null polynomial has degree -1
    non null constant polynomial has degree 0


    @param a0

    @return an integral value
  **/
  NT2_FUNCTION_IMPLEMENTATION(tag::degree_,degree, 1)
}
#endif
