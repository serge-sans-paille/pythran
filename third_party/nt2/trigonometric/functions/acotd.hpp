//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TRIGONOMETRIC_FUNCTIONS_ACOTD_HPP_INCLUDED
#define NT2_TRIGONOMETRIC_FUNCTIONS_ACOTD_HPP_INCLUDED
#include <nt2/include/functor.hpp>


namespace nt2 { namespace tag
  {
   /*!
     @brief acotd generic tag

     Represents the acotd function in generic contexts.

     @par Models:
        Hierarchy
   **/
    struct acotd_ : ext::elementwise_<acotd_>
    {
      /// @brief Parent hierarchy
      typedef ext::elementwise_<acotd_> parent;
    };
  }
  /*!
    inverse cotangent in degree.

    @par Semantic:

    For every parameter of floating type T0

    @code
    T0 r = acotd(x);
    @endcode

    Returns the arc @c r in the interval
    \f$[0, 180[\f$ such that <tt>cotd(r) == x</tt>.

    @see @funcref{acot}
    @param a0

    @return a value of the same type as the parameter
  **/
  NT2_FUNCTION_IMPLEMENTATION(tag::acotd_, acotd, 1)
}

#endif


