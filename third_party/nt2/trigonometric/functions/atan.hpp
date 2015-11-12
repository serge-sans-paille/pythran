//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TRIGONOMETRIC_FUNCTIONS_ATAN_HPP_INCLUDED
#define NT2_TRIGONOMETRIC_FUNCTIONS_ATAN_HPP_INCLUDED
#include <nt2/include/functor.hpp>


namespace nt2 { namespace tag
  {
   /*!
     @brief atan generic tag

     Represents the atan function in generic contexts.

     @par Models:
        Hierarchy
   **/
    struct atan_ : ext::elementwise_<atan_>
    {
      /// @brief Parent hierarchy
      typedef ext::elementwise_<atan_> parent;
    };
  }
  /*!
    inverse tangent.

    @par Semantic:

    For every parameter of floating type T0

    @code
    T0 r = atan(a0);
    @endcode

    Returns the arc @c r in the interval
    \f$[-\pi/2, \pi/2[\f$ such that <tt>tan(r) == x</tt>.
    If @c x is outside \f$[-1, 1[\f$ the result is Nan.

    @see @funcref{atan2}, @funcref{atand}, @funcref{atanpi}, @funcref{nbd_atan2}
    @param a0

    @return a value of the same type as the parameter
  **/
  NT2_FUNCTION_IMPLEMENTATION(tag::atan_, atan, 1)
}

#endif


