//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_EULER_FUNCTIONS_ERFINV_HPP_INCLUDED
#define NT2_EULER_FUNCTIONS_ERFINV_HPP_INCLUDED
#include <nt2/include/functor.hpp>


namespace nt2 { namespace tag
  {
   /*!
     @brief erfinv generic tag

     Represents the erfinv function in generic contexts.

     @par Models:
        Hierarchy
   **/
    struct erfinv_ : ext::elementwise_<erfinv_>
    {
      /// @brief Parent hierarchy
      typedef ext::elementwise_<erfinv_> parent;
    };
  }
  /*!
    Computes the inverse of the error function

    @par Semantic:

    For every parameter of floating type T0

    @code
    T0 r = erfinv(x);
    @endcode

    satisfies  @c x==erf(r)

    @see @funcref{erf}, @funcref{erfc}, @funcref{erfcinv}
    @param a0

    @return a value of the same type as the parameter
  **/
  NT2_FUNCTION_IMPLEMENTATION(tag::erfinv_, erfinv, 1)
}

#endif

