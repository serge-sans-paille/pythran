//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_POLYNOM_FUNCTIONS_COMPAN_HPP_INCLUDED
#define NT2_POLYNOM_FUNCTIONS_COMPAN_HPP_INCLUDED
#include <nt2/include/functor.hpp>

namespace nt2 { namespace tag
  {
   /*!
     @brief compan generic tag

     Represents the compan function in generic contexts.

     @par Models:
        Hierarchy
   **/
    struct compan_ : ext::elementwise_<compan_>
    {
      /// @brief Parent hierarchy
      typedef ext::elementwise_<compan_> parent;
    };
  }
  /*!
    returns the companion matrix of the input polynomial.

    @par Semantic:

    For every expression representing a polynomial

    @code
    auto r = compan(p);
    @endcode

    @par Note:

    The eigenvalues of @c compan(p) are the roots of the polynomial.

    The first row of r is -p(_(2, n))/p(1).

    null polynomial has compan -1 and
    non null constant polynomial has compan 0

    @see @funcref{colon}

    @param a0

    @return a value of the same type as the parameter
  **/
  NT2_FUNCTION_IMPLEMENTATION(tag::compan_,compan, 1)
}
#endif
