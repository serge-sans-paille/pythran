//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_HYPERBOLIC_FUNCTIONS_ACOSH_HPP_INCLUDED
#define NT2_HYPERBOLIC_FUNCTIONS_ACOSH_HPP_INCLUDED
#include <nt2/include/functor.hpp>


namespace nt2 { namespace tag
  {
   /*!
     @brief acosh generic tag

     Represents the acosh function in generic contexts.

     @par Models:
        Hierarchy
   **/
    struct acosh_ : ext::elementwise_<acosh_>
    {
      /// @brief Parent hierarchy
      typedef ext::elementwise_<acosh_> parent;
    };
  }
  /*!
    Returns the hyperbolic cosine argument: \f$\log(a_0+\sqrt{a_0^2-1})\f$.

    @par Semantic:

    For every parameter of floating type T0

    @code
    T0 r = acosh(x);
    @endcode

    is similar to:

    @code
    T0 r = log(x+sqrt{x*x-one});
    @endcode

    @see @funcref{log}, @funcref{sqrt}, @funcref{cosh}
    @param a0

    @return a value of the same type as the parameter
  **/
  NT2_FUNCTION_IMPLEMENTATION(tag::acosh_, acosh, 1)
}

#endif

