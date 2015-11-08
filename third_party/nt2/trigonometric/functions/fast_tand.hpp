//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TRIGONOMETRIC_FUNCTIONS_FAST_TAND_HPP_INCLUDED
#define NT2_TRIGONOMETRIC_FUNCTIONS_FAST_TAND_HPP_INCLUDED
#include <nt2/include/functor.hpp>


namespace nt2 { namespace tag
  {
   /*!
     @brief fast_tand generic tag

     Represents the fast_tand function in generic contexts.

     @par Models:
        Hierarchy
   **/
    struct fast_tand_ : ext::elementwise_<fast_tand_>
    {
      /// @brief Parent hierarchy
       typedef ext::elementwise_<fast_tand_> parent;
    };
  }
  /*!
    tangent of the angle in degree, in the interval \f$[-45, 45]\f$, nan outside.

    @par Semantic:

    For every parameter of floating type T0

    @code
    T0 r = fast_tand(x);
    @endcode

    is similar to:

    @code
    T0 r = tand(x);
    @endcode

    @see  @funcref{tand}, @funcref{tan}
    @param a0

    @return a value of the same type as the parameter
  **/
  NT2_FUNCTION_IMPLEMENTATION(tag::fast_tand_, fast_tand, 1)
}

#endif


