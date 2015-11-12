//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TRIGONOMETRIC_FUNCTIONS_CSC_HPP_INCLUDED
#define NT2_TRIGONOMETRIC_FUNCTIONS_CSC_HPP_INCLUDED
#include <nt2/include/functor.hpp>


namespace nt2 { namespace tag
  {
   /*!
     @brief csc generic tag

     Represents the csc function in generic contexts.

     @par Models:
        Hierarchy
   **/
    struct csc_ : ext::elementwise_<csc_>
    {
      /// @brief Parent hierarchy
      typedef ext::elementwise_<csc_> parent;
    };
  }
  /*!
    cosecante of the input in radian.

    @par Semantic:

    For every parameter of floating type T0

    @code
    T0 r = csc(x);
    @endcode

    is similar to:

    @code
    T0 r = rec(sin(x));
    @endcode

    @see @funcref{cscd}, @funcref{cosecant}, @funcref{cscpi},
    @param a0

    @return a value of the same type as the parameter
  **/
  NT2_FUNCTION_IMPLEMENTATION(tag::csc_, csc, 1)
}

#endif

