//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_BESSEL_FUNCTIONS_J0_HPP_INCLUDED
#define NT2_BESSEL_FUNCTIONS_J0_HPP_INCLUDED
#include <nt2/include/functor.hpp>


namespace nt2 { namespace tag
  {
   /*!
     @brief j0 generic tag

     Represents the j0 function in generic contexts.

     @par Models:
        Hierarchy
   **/
    struct j0_ : ext::elementwise_<j0_>
    {
      /// @brief Parent hierarchy
      typedef ext::elementwise_<j0_> parent;
    };
  }
  /*!
    Bessel function of the first kind of order 0.

    @par Semantic:

    For every parameter of floating type T0

    @code
    T0 r = j0(x);
    @endcode

    Computes \f$\displaystyle \frac1{\pi} \int_0^\pi \cos(x \sin t)\mbox{d}t\f$

    @param a0

    @return a value of the same type as the parameter
  **/
  NT2_FUNCTION_IMPLEMENTATION(tag::j0_, j0, 1)
}

#endif

