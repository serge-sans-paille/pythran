//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TRIGONOMETRIC_FUNCTIONS_ATANPI_HPP_INCLUDED
#define NT2_TRIGONOMETRIC_FUNCTIONS_ATANPI_HPP_INCLUDED
#include <nt2/include/functor.hpp>


namespace nt2 {
  namespace tag
  {
   /*!
     @brief atanpi generic tag

     Represents the atanpi function in generic contexts.

     @par Models:
        Hierarchy
   **/
    struct atanpi_ : ext::elementwise_<atanpi_>
    {
      /// @brief Parent hierarchy
      typedef ext::elementwise_<atanpi_> parent;
    };
  }
  /*!
    inverse tangent in \f$\pi\f$ multiples.

    @par Semantic:

    For every parameter of floating type T0

    @code
    T0 r = atanpi(a0);
    @endcode

    Returns the arc @c r in the interval
    \f$[-0.5, 0.5[\f$ such that <tt>tanpi(r) == x</tt>.

    @see @funcref{atan2}, @funcref{atand}, @funcref{atan}, @funcref{nbd_atan2}
    @param a0

    @return a value of the same type as the parameter
  **/
  NT2_FUNCTION_IMPLEMENTATION(tag::atanpi_, atanpi, 1)
}

#endif


