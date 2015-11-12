//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_EULER_FUNCTIONS_ERFCINV_HPP_INCLUDED
#define NT2_EULER_FUNCTIONS_ERFCINV_HPP_INCLUDED
#include <nt2/include/functor.hpp>


namespace nt2 { namespace tag
  {
   /*!
     @brief erfcinv generic tag

     Represents the erfcinv function in generic contexts.

     @par Models:
        Hierarchy
   **/
    struct erfcinv_ : ext::elementwise_<erfcinv_>
    {
      /// @brief Parent hierarchy
      typedef ext::elementwise_<erfcinv_> parent;
    };
  }
  /*!
    Computes the inverse of the complementary error function


    @par Semantic:

    For every parameter of floating type T0

    @code
    T0 r = erfcinv(a0);
    @endcode

    satisfies  @c x==erfc(r)

    @see @funcref{erfc}, @funcref{erf}, @funcref{erfinv}
    @param a0

    @return a value of the same type as the parameter
  **/
  NT2_FUNCTION_IMPLEMENTATION(tag::erfcinv_, erfcinv, 1)
}

#endif

