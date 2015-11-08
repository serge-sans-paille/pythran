//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TRIGONOMETRIC_FUNCTIONS_COTPI_HPP_INCLUDED
#define NT2_TRIGONOMETRIC_FUNCTIONS_COTPI_HPP_INCLUDED
#include <nt2/include/functor.hpp>


namespace nt2 { namespace tag
  {
   /*!
     @brief cotpi generic tag

     Represents the cotpi function in generic contexts.

     @par Models:
        Hierarchy
   **/
    struct cotpi_ : ext::elementwise_<cotpi_>
    {
      /// @brief Parent hierarchy
      typedef ext::elementwise_<cotpi_> parent;
    };
  }
  /*!
    cotangent of input in \f$\pi\f$ multiples.

    @par Semantic:

    For every parameter of floating type T0

    @code
    T0 r = cotpi(x);
    @endcode

    is similar to:

    @code
    T0 r = cot(Pi<T0>()*x);
    @endcode

    @see @funcref{cot}, @funcref{cotangent}, @funcref{fast_cotpi},
    @param a0

    @return a value of the same type as the parameter
  **/
  NT2_FUNCTION_IMPLEMENTATION(tag::cotpi_, cotpi, 1)
}

#endif


