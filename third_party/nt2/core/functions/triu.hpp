//==============================================================================
//         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_TRIU_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_TRIU_HPP_INCLUDED

#include <nt2/include/functor.hpp>

namespace nt2
{
  namespace tag
  {
    /*!
      @brief triu generic tag

      Represents the triu function in generic contexts.

      @par Models:
      Hierarchy
    **/
    struct triu_ : ext::elementwise_<triu_>
    {
      /// @brief Parent hierarchy
      typedef ext::elementwise_<triu_> parent;
    };
  }

  /*!
    @brief Apply a upper-triangular masking to an expression

    returns the elements on and above the @c a1-th diagonal of  @c a0, 0 elsewhere.
      - @c a1 = 0 is the main diagonal,
      - @c a1 > 0 is above the main diagonal,
      - @c a1 < 0 is below the main diagonal.

    Apply a mask on an expression that evaluates to 0 everywhere except on the
    upper triangular part of @c a0.

    @see funcref{tri1u}, funcref{tril}, funcref{tri1l}
    @param a0 Expression to mask.
  **/
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::triu_, triu, 1)


  /*!
    @brief Apply an offset upper-triangular masking to an expression

    Apply a mask on an expression that evaluates to 0 everywhere except on the
    upper triangular part of @c a0 and @c a1 subdiagonal.

    @param a0 Expression to mask.
    @param a1 Diagonal offset to the mask.
  **/
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::triu_, triu, 2)
}

#endif
