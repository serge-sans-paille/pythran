//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_EULER_FUNCTIONS_ERFC_HPP_INCLUDED
#define NT2_EULER_FUNCTIONS_ERFC_HPP_INCLUDED
#include <nt2/include/functor.hpp>


namespace nt2 { namespace tag
  {
   /*!
     @brief erfc generic tag

     Represents the erfc function in generic contexts.

     @par Models:
        Hierarchy
   **/
    struct erfc_ : ext::elementwise_<erfc_>
    {
      /// @brief Parent hierarchy
      typedef ext::elementwise_<erfc_> parent;
    };
  }
  /*!
    Computes the complementary eroor function

    @par Semantic:

    For every parameter of floating type T0

    @code
    T0 r = erfc(a0);
    @endcode

    is similar to:

    @code
    T0 r = one-erf(x);
    @endcode

  @see @funcref{erf}, @funcref{erfinv}, @funcref{erfcinv}
  @param a0

    @return a value of the same type as the parameter
  **/
  NT2_FUNCTION_IMPLEMENTATION(tag::erfc_, erfc, 1)
}

#endif

