//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TRIGONOMETRIC_FUNCTIONS_PROPER_TANPI_HPP_INCLUDED
#define NT2_TRIGONOMETRIC_FUNCTIONS_PROPER_TANPI_HPP_INCLUDED
#include <nt2/include/functor.hpp>


namespace nt2 { namespace tag
  {
   /*!
     @brief proper_tanpi generic tag

     Represents the proper_tanpi function in generic contexts.

     @par Models:
        Hierarchy
   **/
    struct proper_tanpi_ : ext::elementwise_<proper_tanpi_>
    {
      /// @brief Parent hierarchy
      typedef ext::elementwise_<proper_tanpi_> parent;
    };
  }
  /*!
    tangent of angle in \f$\pi\f$ multiples,
    restricted between -0.5 and +0.5.
    This function is the inverse of @c atanpi and so is
    such that @c proper_tanpi(0.5) is inf
    and @c proper_tanpi(-0.5) is -inf

    @par Semantic:

    For every parameter of floating type T0

    @code
    T0 r = proper_tanpi(x);
    @endcode

    is similar to:

    @code
    T0 r = tanpi(x);
    @endcode

    provided input is in \f$]-0.5,  0.5[\f$

    @see @funcref{tanpi}, @funcref{fast_tanpi}
    @param a0

    @return a value of the same type as the parameter
  **/
  NT2_FUNCTION_IMPLEMENTATION(tag::proper_tanpi_, proper_tanpi, 1)
}

#endif

// modified by jt the 25/12/2010


