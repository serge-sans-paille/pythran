//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TRIGONOMETRIC_FUNCTIONS_TAN_HPP_INCLUDED
#define NT2_TRIGONOMETRIC_FUNCTIONS_TAN_HPP_INCLUDED
#include <nt2/include/functor.hpp>


namespace nt2 { namespace tag
  {
   /*!
     @brief tan generic tag

     Represents the tan function in generic contexts.

     @par Models:
        Hierarchy
   **/
    struct tan_ : ext::elementwise_<tan_>
    {
      /// @brief Parent hierarchy
      typedef ext::elementwise_<tan_> parent;
    };
  }
  /*!
    tangent of the input in radians.

    @par Semantic:

    For every parameter of floating type T0

    @code
    T0 r = tan(x);
    @endcode

    is similar to:

    @code
    T0 r = sin(x)/cos(x);
    @endcode

    @see @funcref{tangent}, @funcref{tan}, @funcref{tand}, @funcref{tanpi}
    @param a0

    @return a value of the same type as the parameter
  **/
  NT2_FUNCTION_IMPLEMENTATION(tag::tan_, tan, 1)
}

#endif

