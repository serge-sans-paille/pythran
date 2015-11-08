//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_COMBINATORIAL_FUNCTIONS_IS_PRIME_HPP_INCLUDED
#define NT2_COMBINATORIAL_FUNCTIONS_IS_PRIME_HPP_INCLUDED
#include <nt2/include/functor.hpp>


namespace nt2 { namespace tag
  {
   /*!
     @brief is_prime generic tag

     Represents the is_prime function in generic contexts.

     @par Models:
        Hierarchy
   **/
    //    struct is_prime_ : ext::elementwise_<is_prime_> { typedef ext::elementwise_<is_prime_> parent; };
    struct is_prime_ : tag::formal_
    {
      /// @brief Parent hierarchy
      typedef tag::formal_ parent;
    };
  }
  /*!
    computes if each element of the table is prime or not in an expression table of logical.

    @par Semantic:

    For every table expression

    @code
    auto r = is_prime(a0);
    @endcode

    an integer is prime if it is positive and has exactly 2 distinct exact divisors.

    @see @funcref{primes},  @funcref{factor}
    @param a0

    @return an expression which eventually will evaluate to the result
  **/
  NT2_FUNCTION_IMPLEMENTATION(tag::is_prime_,is_prime, 1)
  NT2_FUNCTION_IMPLEMENTATION(tag::is_prime_,is_prime, 2)
}

#endif

