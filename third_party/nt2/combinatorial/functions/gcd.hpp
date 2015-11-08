//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_COMBINATORIAL_FUNCTIONS_GCD_HPP_INCLUDED
#define NT2_COMBINATORIAL_FUNCTIONS_GCD_HPP_INCLUDED
#include <nt2/include/functor.hpp>


namespace nt2 { namespace tag
  {
   /*!
     @brief gcd generic tag

     Represents the gcd function in generic contexts.

     @par Models:
        Hierarchy
   **/
    struct gcd_ : ext::elementwise_<gcd_>
    {
      /// @brief Parent hierarchy
      typedef ext::elementwise_<gcd_> parent;
    };
  }
  /*!
    Computes the greatest common divisor

    @par Semantic:

    For every table expressions

    @code
    auto r = gcd(a0,a1);
    @endcode

    is the greater positive integer which exactly divides a0 and a1

      - If any input is zero 0 is returned
      - If parameters are floating point and not flint,
      nan is returned.

    @see @funcref{lcm}, @funcref{is_flint}
    @param a0
    @param a1

    @return an expression which eventually will evaluate to the result
  **/
  NT2_FUNCTION_IMPLEMENTATION(tag::gcd_, gcd, 2)
}

#endif

