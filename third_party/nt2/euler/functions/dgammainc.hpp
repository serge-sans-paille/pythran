//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_EULER_FUNCTIONS_DGAMMAINC_HPP_INCLUDED
#define NT2_EULER_FUNCTIONS_DGAMMAINC_HPP_INCLUDED
#include <nt2/include/functor.hpp>


namespace nt2 { namespace tag
  {
   /*!
     @brief dgammainc generic tag

     Represents the dgammainc function in generic contexts.

     @par Models:
        Hierarchy
   **/
    struct dgammainc_ : ext::elementwise_<dgammainc_>
    {
      /// @brief Parent hierarchy
      typedef ext::elementwise_<dgammainc_> parent;
    };
  }
  /*!
    Computes the derivative of incomplete Gamma function relative to the first parameter

    @par Semantic:

    For every parameters of floating type respectively T0:

    @code
    T0 r = dgammainc(x, a);
    @endcode

    Computes:  \f$ \mathop{\mbox{dgammainc}}(x, a)=\frac{x^{a-1}e^{-x}}{\Gamma(x)}\f$

    @param a0

    @param a1

    @return a value of the same type as the parameter
  **/
  NT2_FUNCTION_IMPLEMENTATION(tag::dgammainc_, dgammainc, 2)
}

#endif

