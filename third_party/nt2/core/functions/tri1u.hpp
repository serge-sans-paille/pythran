//==============================================================================
//         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_TRI1U_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_TRI1U_HPP_INCLUDED

#include <nt2/include/functor.hpp>

namespace nt2
{
  namespace tag
  {
    /*!
      @brief tri1u generic tag

      Represents the tri1u function in generic contexts.

      @par Models:
      Hierarchy
    **/
    struct tri1u_ : ext::elementwise_<tri1u_>
    {
      /// @brief Parent hierarchy
      typedef ext::elementwise_<tri1u_> parent;
    };
  }

  /*!
    @brief Apply a 1-upper-triangular masking to an expression

    returns the elements  above the @c a1 diagonal of @c a0,  1 on the kth diagonal
    and 0 elsewhere.
      - @c a1 = 0 is the main diagonal,
      - @c a1 > 0 is above the main diagonal,
      - @c a1 < 0 is below the main diagonal.

    @see funcref{triu}, funcref{tril}, funcref{tri1l}

    @param a0 Expression to mask.
  **/
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::tri1u_, tri1u, 1)


  /*!
    @brief Apply an offset 1-upper-triangular masking to an expression

    Apply a mask on an expression that evaluates to 0 everywhere except on the
    upper triangular part of @c a0 and @c a1 subdiagonal and 1 on the diagonal.

    @param a0 Expression to mask.
    @param a1 Diagonal offset to the mask.
  **/
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::tri1u_, tri1u, 2)
}

#endif
