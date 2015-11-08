//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_ELLIPTIC_FUNCTIONS_ELLIK_HPP_INCLUDED
#define NT2_ELLIPTIC_FUNCTIONS_ELLIK_HPP_INCLUDED
#include <nt2/include/functor.hpp>


namespace nt2 { namespace tag
  {
   /*!
     @brief ellik generic tag

     Represents the ellik function in generic contexts.

     @par Models:
        Hierarchy
   **/
    struct ellik_ : ext::elementwise_<ellik_>
    {
      /// @brief Parent hierarchy
      typedef ext::elementwise_<ellik_> parent;
    };
  }
  /*!
    Returns the incomplete elliptic integral of the first kind

    @par Semantic:

    For every parameters of floating types respectively T0, T1:

    @code
    T0 r = ellik(a0,a1);
    @endcode

    computes: \f$ F(a_0, a_1) =\displaystyle \int_0^{a0} \frac1{\sqrt{1-a_1\sin^2 t}} dt\f$


    @see @funcref{ellie}
    @param a0

    @param a1

    @return a value of the same type as the parameter
  **/
  NT2_FUNCTION_IMPLEMENTATION(tag::ellik_, ellik, 2)
}

#endif

