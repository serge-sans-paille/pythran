//==============================================================================
//         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_TRIL_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_TRIL_HPP_INCLUDED

#include <nt2/include/functor.hpp>

namespace nt2
{
  namespace tag
  {
    /*!
      @brief tril generic tag

      Represents the tril function in generic contexts.

      @par Models:
      Hierarchy
    **/
    struct tril_ : ext::elementwise_<tril_>
    {
      /// @brief Parent hierarchy
      typedef ext::elementwise_<tril_> parent;
    };
  }

  /*!
    @brief Apply a lower-triangular masking to an expression

    returns the elements on and below the diagonal of @c a0
    and 0 elsewhere.

    @param a0 Expression to mask.
  **/
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::tril_, tril, 1)


  /*!
    @brief Apply an offset lower-triangular masking to an expression

    returns the elements on and below the @c a1-th diagonal of  @c a0,  0 elsewhere.
      - @c a1 = 0 is the main diagonal,
      - @c a1 > 0 is above the main diagonal,
      - @c a1 < 0 is below the main diagonal.

    @see funcref{triu}, funcref{tri1u}, funcref{tri1l}
    @param a0 Expression to mask.
    @param a1 Diagonal offset to the mask.
  **/
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::tril_, tril, 2)
}

#endif
