//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TRIGONOMETRIC_FUNCTIONS_SIN_HPP_INCLUDED
#define NT2_TRIGONOMETRIC_FUNCTIONS_SIN_HPP_INCLUDED

#include <nt2/include/functor.hpp>

namespace nt2
{
  namespace tag
  {
   /*!
     @brief sin generic tag

     Represents the sin function in generic contexts.

     @par Models:
        Hierarchy
   **/
    struct sin_ : ext::elementwise_<sin_>
    {
      /// @brief Parent hierarchy
      typedef ext::elementwise_<sin_> parent;
    };
  }
  /*!
    sine of the input in radians.

    @par Semantic:

    For every parameter of floating type T0

    @code
    T0 r = sin(x);
    @endcode


    @see @funcref{sine}, @funcref{fast_sin}, @funcref{sincos}, @funcref{sind}, @funcref{sinpi}
    @param a0

    @return a value of the same type as the parameter
  **/
  NT2_FUNCTION_IMPLEMENTATION(tag::sin_, sin, 1)
}

#endif



