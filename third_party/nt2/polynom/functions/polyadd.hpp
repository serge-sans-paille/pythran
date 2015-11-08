//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_POLYNOM_FUNCTIONS_POLYADD_HPP_INCLUDED
#define NT2_POLYNOM_FUNCTIONS_POLYADD_HPP_INCLUDED
#include <nt2/include/functor.hpp>
#include <nt2/sdk/meta/size_as.hpp>
#include <nt2/sdk/meta/value_as.hpp>
#include <nt2/core/container/dsl/size.hpp>
#include <nt2/sdk/meta/tieable_hierarchy.hpp>
#include <nt2/core/container/dsl/value_type.hpp>

namespace nt2 { namespace tag
  {
   /*!
     @brief polyadd generic tag

     Represents the polyadd function in generic contexts.

     @par Models:
        Hierarchy
   **/
    struct polyadd_ : ext::elementwise_<polyadd_>
    {
      /// @brief Parent hierarchy
      typedef ext::elementwise_<polyadd_> parent;
    };
  }
  /*!
    Computes the sum of two polynomials.
    The polynomials are supposed to be given by an expression representing a vector
    of coefficients in decreasing degrees order

    @par Semantic:

    For every expressions representing polynomials a, b:

    @code
    auto r = polyadd(a, b);
    @endcode

    is such that if a represents \f$\displaystyle \sum_0^n a_i x^i\f$ and b represents
    \f$\displaystyle \sum_0^n b_ix^i\f$ then r represents
    \f$\displaystyle \sum_0^n(a_i+b_i)x^i\f$


    @param a0

    @param a1

    @return an expression
  **/
  NT2_FUNCTION_IMPLEMENTATION(tag::polyadd_, polyadd, 2)
}

#endif
