//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_HYPERBOLIC_FUNCTIONS_CSCH_HPP_INCLUDED
#define NT2_HYPERBOLIC_FUNCTIONS_CSCH_HPP_INCLUDED
#include <nt2/include/functor.hpp>


namespace nt2 { namespace tag
  {
   /*!
     @brief csch generic tag

     Represents the csch function in generic contexts.

     @par Models:
        Hierarchy
   **/
    struct csch_ : ext::elementwise_<csch_>
    {
      /// @brief Parent hierarchy
      typedef ext::elementwise_<csch_> parent;
    };
  }
  /*!
    hyperbolic cosecant: \f$\frac1{\sinh(a_0)}\f$.

    @par Semantic:

    For every parameter of floating type T0

    @code
    T0 r = csch(x);
    @endcode

    is similar to:

    @code
    T0 r = rec(sinh(x));
    @endcode

    @see @funcref{rec}, @funcref{sinh}
    @param a0

    @return a value of the same type as the parameter
  **/
  NT2_FUNCTION_IMPLEMENTATION(tag::csch_, csch, 1)
}

#endif

