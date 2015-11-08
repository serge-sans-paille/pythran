//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_EULER_FUNCTIONS_STIRLING_HPP_INCLUDED
#define NT2_EULER_FUNCTIONS_STIRLING_HPP_INCLUDED
#include <nt2/include/functor.hpp>


namespace nt2 { namespace tag
  {
   /*!
     @brief stirling generic tag

     Represents the stirling function in generic contexts.

     @par Models:
        Hierarchy
   **/
    struct stirling_ : ext::elementwise_<stirling_>
    {
      /// @brief Parent hierarchy
      typedef ext::elementwise_<stirling_> parent;
    };
  }
  /*!
    Computes stirling formula for the gamma function

    @par Semantic:

    For every parameter of floating type T0

    @code
    T0 r = stirling(a0);
    @endcode

    Computes \f$\Gamma(a_0) \approx \sqrt{2 \pi} a_0^{a_0-\frac12} e^{-a_0} ( 1 + \frac1{a_0} P(\frac1{a_0}))\f$,
    where \f$P\f$ is a polynomial.

    The formula implementation is usable for a0 between 33 and 172, according cephes

    @see @funcref{gamma}
    @param a0

    @return a value of the same type as the parameter
  **/
  NT2_FUNCTION_IMPLEMENTATION(tag::stirling_, stirling, 1)
}

#endif

