//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_COMBINATORIAL_FUNCTIONS_FACTORIAL_HPP_INCLUDED
#define NT2_COMBINATORIAL_FUNCTIONS_FACTORIAL_HPP_INCLUDED
#include <nt2/include/functor.hpp>


namespace nt2 { namespace tag
  {
   /*!
     @brief factorial generic tag

     Represents the factorial function in generic contexts.

     @par Models:
        Hierarchy
   **/
    struct factorial_ : ext::elementwise_<factorial_>
    {
      /// @brief Parent hierarchy
      typedef ext::elementwise_<factorial_> parent;
    };
  }
  /*!
    Computes saturated factorial in the input type

    be aware that the result is never exact if n>12
    and that the result is saturated in the input type!

    @par Semantic:

    For every table expression of elements of type T0

    @code
    auto r = factorial(n);
    @endcode

    is similar to:

    @code
    auto r = saturate<T0>(prod(_(1, n));
    @endcode

    @see @funcref{saturate}
    @param a0

    @return an expression which eventually will evaluate to the result
  **/
  NT2_FUNCTION_IMPLEMENTATION(tag::factorial_,factorial, 1)
}

#endif

