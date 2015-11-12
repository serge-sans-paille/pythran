//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_HYPERBOLIC_FUNCTIONS_SECH_HPP_INCLUDED
#define NT2_HYPERBOLIC_FUNCTIONS_SECH_HPP_INCLUDED
#include <nt2/include/functor.hpp>


namespace nt2 { namespace tag
  {
   /*!
     @brief sech generic tag

     Represents the sech function in generic contexts.

     @par Models:
        Hierarchy
   **/
    struct sech_ : ext::elementwise_<sech_>
    {
      /// @brief Parent hierarchy
      typedef ext::elementwise_<sech_> parent;
    };
  }
  /*!
    Returns the hyperbolic secant: \f$\frac1{\cosh(a_0)}\f$.

    @par Semantic:

    For every parameter of floating type T0

    @code
    T0 r = sech(x);
    @endcode

    is similar to:

    @code
    T0 r = rec(cosh(x));
    @endcode

    @see @funcref{rec}, @funcref{cosh}
    @param a0

    @return a value of the same type as the parameter
  **/
  NT2_FUNCTION_IMPLEMENTATION(tag::sech_, sech, 1)
}

#endif

