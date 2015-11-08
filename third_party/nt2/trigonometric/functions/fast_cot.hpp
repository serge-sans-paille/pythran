//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TRIGONOMETRIC_FUNCTIONS_FAST_COT_HPP_INCLUDED
#define NT2_TRIGONOMETRIC_FUNCTIONS_FAST_COT_HPP_INCLUDED
#include <nt2/include/functor.hpp>


namespace nt2 { namespace tag
  {
   /*!
     @brief fast_cot generic tag

     Represents the fast_cot function in generic contexts.

     @par Models:
        Hierarchy
   **/
    struct fast_cot_ : ext::elementwise_<fast_cot_>
    {
      /// @brief Parent hierarchy
      typedef ext::elementwise_<fast_cot_> parent;
    };
  }
  /*!
    cotangent in the interval \f$[-\pi/4, \pi/4]\f$, nan outside.

    @par Semantic:

    For every parameter of floating type T0

    @code
    T0 r = fast_cot(x);
    @endcode

    is similar to:

    @code
    T0 r = cot(x);
    @endcode

    provided that x belongs to \f$[-\pi/4, \pi/4]\f$

    @see @funcref{cotangent}, @funcref{cot}, @funcref{cotd}, @funcref{cotpi}
    @param a0

    @return a value of the same type as the parameter
  **/
  NT2_FUNCTION_IMPLEMENTATION(tag::fast_cot_, fast_cot, 1)
}

#endif


