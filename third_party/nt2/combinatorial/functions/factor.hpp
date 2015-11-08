//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_COMBINATORIAL_FUNCTIONS_FACTOR_HPP_INCLUDED
#define NT2_COMBINATORIAL_FUNCTIONS_FACTOR_HPP_INCLUDED
#include <nt2/include/functor.hpp>


namespace nt2 { namespace tag
  {
   /*!
     @brief factor generic tag

     Represents the factor function in generic contexts.

     @par Models:
        Hierarchy
   **/
    struct factor_ : ext::elementwise_<factor_>
    {
      /// @brief Parent hierarchy
      typedef ext::elementwise_<factor_> parent;
    };
  }
  /*!
    returns the  table of prime numbers in non decreasing order
    the product of which is equal to the input

    @par Semantic:

    For every table expression

    @code
    auto r = factor(a0);
    @endcode

    @param a0

    @return a table containing the result
  **/
  NT2_FUNCTION_IMPLEMENTATION(tag::factor_,factor, 1)
}

#endif

