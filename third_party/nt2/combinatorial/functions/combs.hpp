//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_COMBINATORIAL_FUNCTIONS_COMBS_HPP_INCLUDED
#define NT2_COMBINATORIAL_FUNCTIONS_COMBS_HPP_INCLUDED
#include <nt2/include/functor.hpp>


namespace nt2 { namespace tag
  {
   /*!
     @brief combs generic tag

     Represents the combs function in generic contexts.

     @par Models:
        Hierarchy
   **/
    struct combs_ : ext::elementwise_<combs_>
    {
      /// @brief Parent hierarchy
      typedef ext::elementwise_<combs_> parent;
    };
  }
  /*!
    Computes combination number of combined subvectors.

    @par Semantic:

    @code
    auto r = combs(a0, k);
    @endcode

      - when a0 (n) and k are non-negative integers the number of
      combinations of k elements among n. If n or k are large a
      warning will be produced indicating possible inexact results. in
      such cases, the result is only accurate to 15 digits for
      double-precision inputs, or 8 digits for single-precision
      inputs.

      - when a0 is a vector of length n, and k is an integer
      produces a matrix with n!/k!(n-k)! rows and k columns. each row
      of the result has k of the elements in the vector v. this syntax
      is only practical for situations where n is less than about 15.

    @see @funcref{cnp}
    @param a0
    @param a1

    @return an expression which eventually will evaluate to the result
  **/
  NT2_FUNCTION_IMPLEMENTATION(tag::combs_, combs, 2)
}

#endif

