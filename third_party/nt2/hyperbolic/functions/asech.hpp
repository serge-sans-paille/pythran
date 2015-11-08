//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_HYPERBOLIC_FUNCTIONS_ASECH_HPP_INCLUDED
#define NT2_HYPERBOLIC_FUNCTIONS_ASECH_HPP_INCLUDED
#include <nt2/include/functor.hpp>


namespace nt2 { namespace tag
  {
   /*!
     @brief asech generic tag

     Represents the asech function in generic contexts.

     @par Models:
        Hierarchy
   **/
    struct asech_ : ext::elementwise_<asech_>
    {
      /// @brief Parent hierarchy
      typedef ext::elementwise_<asech_> parent;
    };
  }
  /*!
    Returns the hyperbolic secant argument \f$\mathop{\textrm{acosh}}(1/a_0)\f$

    @par Semantic:

    For every parameter of floating type T0

    @code
    T0 r = asech(x);
    @endcode

    is similar to:

    @code
    T0 r = acosh(rec(x));
    @endcode

    @see @funcref{acosh}, @funcref{cosh}, @funcref{rec}
    @param a0

    @return a value of the same type as the parameter
  **/
  NT2_FUNCTION_IMPLEMENTATION(tag::asech_, asech, 1)
}

#endif

