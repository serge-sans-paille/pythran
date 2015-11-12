//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TRIGONOMETRIC_FUNCTIONS_TANPI_HPP_INCLUDED
#define NT2_TRIGONOMETRIC_FUNCTIONS_TANPI_HPP_INCLUDED
#include <nt2/include/functor.hpp>


namespace nt2 { namespace tag
  {
   /*!
     @brief tanpi generic tag

     Represents the tanpi function in generic contexts.

     @par Models:
        Hierarchy
   **/
    struct tanpi_ : ext::elementwise_<tanpi_>
    {
      /// @brief Parent hierarchy
      typedef ext::elementwise_<tanpi_> parent;
    };
  }
  /*!
    tangent of angle in \f$\pi\f$ multiples.

    @par Semantic:

    For every parameter of floating type T0

    @code
    T0 r = tanpi(a0);
    @endcode

    is similar to:

    @code
    T0 r =  sinpi(x)/cospi(x);;
    @endcode

    @see @funcref{fast_tanpi}, @funcref{tangent}, @funcref{tan}, @funcref{tand}
    @param a0

    @return a value of the same type as the parameter
  **/
  NT2_FUNCTION_IMPLEMENTATION(tag::tanpi_, tanpi, 1)
}

#endif


