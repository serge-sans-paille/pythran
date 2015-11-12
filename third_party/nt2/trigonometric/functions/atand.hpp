//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TRIGONOMETRIC_FUNCTIONS_ATAND_HPP_INCLUDED
#define NT2_TRIGONOMETRIC_FUNCTIONS_ATAND_HPP_INCLUDED
#include <nt2/include/functor.hpp>


namespace nt2 { namespace tag
  {
   /*!
     @brief atand generic tag

     Represents the atand function in generic contexts.

     @par Models:
        Hierarchy
   **/
    struct atand_ : ext::elementwise_<atand_>
    {
      /// @brief Parent hierarchy
      typedef ext::elementwise_<atand_> parent;
    };
  }
  /*!
    inverse tangent in degree.

    @par Semantic:

    For every parameter of floating type T0

    @code
    T0 r = atand(a0);
    @endcode

    Returns the arc @c r in the interval
    \f$[-90, 90[\f$ such that <tt>tand(r) == x</tt>.

    @see @funcref{atan2}, @funcref{atan}, @funcref{atanpi}, @funcref{nbd_atan2}
    @param a0

    @return a value of the same type as the parameter
  **/
  NT2_FUNCTION_IMPLEMENTATION(tag::atand_, atand, 1)
}

#endif


