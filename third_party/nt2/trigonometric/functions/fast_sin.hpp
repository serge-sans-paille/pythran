//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TRIGONOMETRIC_FUNCTIONS_FAST_SIN_HPP_INCLUDED
#define NT2_TRIGONOMETRIC_FUNCTIONS_FAST_SIN_HPP_INCLUDED
#include <nt2/include/functor.hpp>


namespace nt2 { namespace tag
  {
   /*!
     @brief fast_sin generic tag

     Represents the fast_sin function in generic contexts.

     @par Models:
        Hierarchy
   **/
    struct fast_sin_ : ext::elementwise_<fast_sin_>
    {
      /// @brief Parent hierarchy
      typedef ext::elementwise_<fast_sin_> parent;
    };
  }
  /*!
    sine in the interval \f$[-\pi/4, \pi/4]\f$, nan outside.

    @par Semantic:

    For every parameter of floating type T0

    @code
    T0 r = fast_sin(x);
    @endcode

    is similar to:

    @code
    T0 r = sin(x) ;
    @endcode

    provided that x belongs to \f$[-\pi/4, \pi/4]\f$

    @see @funcref{sine}, @funcref{sin}, @funcref{sincos}, @funcref{sind}, @funcref{sinpi}
    @param a0

    @return a value of the same type as the parameter
  **/
  NT2_FUNCTION_IMPLEMENTATION(tag::fast_sin_, fast_sin, 1)
}

#endif



