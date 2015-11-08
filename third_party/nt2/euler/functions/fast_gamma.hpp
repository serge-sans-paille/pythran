//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_EULER_FUNCTIONS_FAST_GAMMA_HPP_INCLUDED
#define NT2_EULER_FUNCTIONS_FAST_GAMMA_HPP_INCLUDED
#include <nt2/include/functor.hpp>


namespace nt2 { namespace tag
  {
   /*!
     @brief fast_gamma generic tag

     Represents the fast_gamma function in generic contexts.

     @par Models:
        Hierarchy
   **/
    struct fast_gamma_ : ext::elementwise_<fast_gamma_>
    {
      /// @brief Parent hierarchy
      typedef ext::elementwise_<fast_gamma_> parent;
    };
  }
  /*!
    Computes Gamma function.

    The fast prefix indicates less accuracy than gamma
    function itself and nonguaranted limiting values for the sake of speed.

    @par Semantic:

    For every parameter of floating type T0

    @code
    T0 r = fast_gamma(a0);
    @endcode

    Computes \f$ \displaystyle \Gamma(a_0)=\int_0^\infty t^{a_0-1}e^{-t}dt\f$

    @see @funcref{gamma}

    @param a0

    @return a value of the same type as the parameter
  **/
  NT2_FUNCTION_IMPLEMENTATION(tag::fast_gamma_, fast_gamma, 1)
}

#endif

