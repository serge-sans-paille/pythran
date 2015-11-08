//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TRIGONOMETRIC_FUNCTIONS_SINCPI_HPP_INCLUDED
#define NT2_TRIGONOMETRIC_FUNCTIONS_SINCPI_HPP_INCLUDED
#include <nt2/include/functor.hpp>


namespace nt2 { namespace tag
  {
   /*!
     @brief sincpi generic tag

     Represents the sincpi function in generic contexts.

     @par Models:
        Hierarchy
   **/
    struct sincpi_ : ext::elementwise_<sincpi_>
    {
      /// @brief Parent hierarchy
      typedef ext::elementwise_<sincpi_> parent;
    };
  }
  /*!
    sinus cardinal second form

    @par Semantic:

    For every parameter of floating type T0

    @code
    T0 r = sincpi(x);
    @endcode

    is similar to:

    @code
    T0 r = sin(pi*x)/(pi*x);
    @endcode

    @see @funcref{sinc}
    @param a0

    @return a value of the same type as the parameter
  **/
  NT2_FUNCTION_IMPLEMENTATION(tag::sincpi_, sincpi, 1)
}

#endif


