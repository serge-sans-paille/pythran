//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TRIGONOMETRIC_FUNCTIONS_FAST_COSPI_HPP_INCLUDED
#define NT2_TRIGONOMETRIC_FUNCTIONS_FAST_COSPI_HPP_INCLUDED
#include <nt2/include/functor.hpp>


namespace nt2 { namespace tag
  {
   /*!
     @brief fast_cospi generic tag

     Represents the fast_cospi function in generic contexts.

     @par Models:
        Hierarchy
   **/
    struct fast_cospi_ : ext::elementwise_<fast_cospi_>
    {
      /// @brief Parent hierarchy
      typedef ext::elementwise_<fast_cospi_> parent;
    };
  }
  /*!
    cosine of the angle in pi multiples, in the interval
    \f$[-1/4, 1/4]\f$, nan outside.

    @par Semantic:

    For every parameter of floating type T0

    @code
    T0 r = fast_cospi();
    @endcode

    is similar to:

    @code
    T0 r = cospi(x);
    @endcode

    provided that x belongs to \f$[-1/4, 1/4]\f$

    @see @funcref{fast_cos}, @funcref{sincospi}, @funcref{cos}, @funcref{cosd}
    @param a0

    @return a value of the same type as the parameter
  **/
  NT2_FUNCTION_IMPLEMENTATION(tag::fast_cospi_, fast_cospi, 1)
}

#endif


