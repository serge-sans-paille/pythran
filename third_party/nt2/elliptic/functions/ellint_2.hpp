//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_ELLIPTIC_FUNCTIONS_ELLINT_2_HPP_INCLUDED
#define NT2_ELLIPTIC_FUNCTIONS_ELLINT_2_HPP_INCLUDED
#include <nt2/include/functor.hpp>


namespace nt2 { namespace tag
  {
   /*!
     @brief ellint_2 generic tag

     Represents the ellint_2 function in generic contexts.

     @par Models:
        Hierarchy
   **/
    struct ellint_2_ : ext::elementwise_<ellint_2_>
    {
      /// @brief Parent hierarchy
      typedef ext::elementwise_<ellint_2_> parent;
    };
  }
  /*!
    Compute the complete elliptic integral of the second kind

    @par Semantic:

    For every parameter of floating type T0

    @code
    T0 r = ellint_2(a0);
    @endcode

    computes: \f$\displaystyle E(a_0) = \int_0^{\pi/2} \sqrt{1-a_0^2\sin^2 t} dt\f$

    @see @funcref{ellint_1}
    @param a0

    @return a value of the same type as the parameter
  **/
  NT2_FUNCTION_IMPLEMENTATION(tag::ellint_2_, ellint_2, 1)
}

#endif

