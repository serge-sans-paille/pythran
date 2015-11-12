//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TRIGONOMETRIC_FUNCTIONS_REM_2PI_HPP_INCLUDED
#define NT2_TRIGONOMETRIC_FUNCTIONS_REM_2PI_HPP_INCLUDED
#include <nt2/include/functor.hpp>


namespace nt2 { namespace tag
  {
   /*!
     @brief rem_2pi generic tag

     Represents the rem_2pi function in generic contexts.

     @par Models:
        Hierarchy
   **/
    struct rem_2pi_ : ext::elementwise_<rem_2pi_> { typedef ext::elementwise_<rem_2pi_> parent; };
  }
  /*!
    compute the remainder modulo \f$2\pi\f$.

    the result is in \f$[-\pi, \pi]\f$. If the input
    is near \f$\pi\f$ the output can be \f$\pi\f$ or \f$-\pi\f$
    depending
    on register disponibility if extended arithmetic is used.

    @par Semantic:

    For every parameter of floating type T0

    @code
    T0 r = rem_2pi(x);
    @endcode

    is similar to:

    @code
    T0 r = remainder(x, _2_pi<T0>();
    @endcode

    @see @funcref{rem_pio2}, @funcref{rem_pio2_straight},@funcref{rem_pio2_cephes},  @funcref{rem_pio2_medium},
    @param a0

    @return a value of the same type as the parameter
  **/
  NT2_FUNCTION_IMPLEMENTATION(tag::rem_2pi_, rem_2pi,1)
  NT2_FUNCTION_IMPLEMENTATION(tag::rem_2pi_, rem_2pi,2)
}

#endif



