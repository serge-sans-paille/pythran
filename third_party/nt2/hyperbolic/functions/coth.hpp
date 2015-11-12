//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_HYPERBOLIC_FUNCTIONS_COTH_HPP_INCLUDED
#define NT2_HYPERBOLIC_FUNCTIONS_COTH_HPP_INCLUDED
#include <nt2/include/functor.hpp>


namespace nt2 { namespace tag
  {
   /*!
     @brief coth generic tag

     Represents the coth function in generic contexts.

     @par Models:
        Hierarchy
   **/
    struct coth_ : ext::elementwise_<coth_>
    {
      /// @brief Parent hierarchy
      typedef ext::elementwise_<coth_> parent;
    };
  }
  /*!
    Returns the hyperbolic cotangent

    @par Semantic:

    For every parameter of floating type T0

    @code
    T0 r = coth(x);
    @endcode

    is similar to:

    @code
    T0 r = cosh(x)/sinh(x);
    @endcode

    @see @funcref{sinh}, @funcref{cosh}
    @param a0

    @return a value of the same type as the parameter
  **/
  NT2_FUNCTION_IMPLEMENTATION(tag::coth_, coth, 1)
}

#endif

