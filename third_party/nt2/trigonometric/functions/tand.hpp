//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TRIGONOMETRIC_FUNCTIONS_TAND_HPP_INCLUDED
#define NT2_TRIGONOMETRIC_FUNCTIONS_TAND_HPP_INCLUDED
#include <nt2/include/functor.hpp>


namespace nt2 { namespace tag
  {
   /*!
     @brief tand generic tag

     Represents the tand function in generic contexts.

     @par Models:
        Hierarchy
   **/
    struct tand_ : ext::elementwise_<tand_> { typedef ext::elementwise_<tand_> parent; };
  }
  /*!
    tangent of the input in degrees.

    @par Semantic:

    For every parameter of floating type T0

    @code
    T0 r = tand(a0);
    @endcode

    is similar to:

    @code
    T0 r =  sind(x)/cosd(x);
    @endcode

    @see @funcref{fast_tand}, @funcref{tangent}, @funcref{tan}, @funcref{tanpi}
    @param a0

    @return a value of the same type as the parameter
  **/
  NT2_FUNCTION_IMPLEMENTATION(tag::tand_, tand, 1)
}

#endif


