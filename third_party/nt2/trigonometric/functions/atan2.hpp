//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TRIGONOMETRIC_FUNCTIONS_ATAN2_HPP_INCLUDED
#define NT2_TRIGONOMETRIC_FUNCTIONS_ATAN2_HPP_INCLUDED
#include <nt2/include/functor.hpp>


namespace nt2 { namespace tag
  {
   /*!
     @brief atan2 generic tag

     Represents the atan2 function in generic contexts.

     @par Models:
        Hierarchy
   **/
    struct atan2_ : ext::elementwise_<atan2_>
    {
      /// @brief Parent hierarchy
      typedef ext::elementwise_<atan2_> parent;
    };
  }
  /*!
    atan2 function.

    @par Semantic:

    For every parameters of floating types respectively T0, T1:

    @code
    T0 r = atan2(x, y);
    @endcode

    is similar but not fully equivalent to:

    @code
    T0 r =  atan(y/x);;
    @endcode

    as it is quadrant aware.

    For any real arguments @c x and @c y not both equal to zero, <tt>atan2(x, y)</tt>
    is the angle in radians between the positive x-axis of a plane and the point
    given by the coordinates  <tt>(y, x)</tt>.

    It is also the angle in \f$[-\pi,\pi[\f$ such that
    \f$x/\sqrt{x^2+y^2}\f$ and \f$y/\sqrt{x^2+y^2}\f$
    are respectively the sine and the cosine.

    @see @funcref{nbd_atan2}, @funcref{atan}
    @param a0

    @param a1

    @return a value of the same type as the parameters
  **/
  NT2_FUNCTION_IMPLEMENTATION(tag::atan2_, atan2, 2)
}

#endif

