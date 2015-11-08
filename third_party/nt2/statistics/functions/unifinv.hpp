//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_STATISTICS_FUNCTIONS_UNIFINV_HPP_INCLUDED
#define NT2_STATISTICS_FUNCTIONS_UNIFINV_HPP_INCLUDED
#include <nt2/include/functor.hpp>


namespace nt2 { namespace tag
  {
   /*!
     @brief unifinv generic tag

     Represents the unifinv function in generic contexts.

     @par Models:
        Hierarchy
   **/
    struct unifinv_ : ext::elementwise_<unifinv_>
    {
      /// @brief Parent hierarchy
      typedef ext::elementwise_<unifinv_> parent;
    };
  }
  /*!
    uniform inverse cumulative distribution

    @par Semantic:

    For every table expression and interval bounds a and b

    @code
    auto r = unifinv(a0, a, b);
    @endcode

    is similar to:

    @code
    auto r = (a0 < a || a0 >=  b)? Nan : a0*(b-a)+a;
    @endcode

    @param a0
    @param a1 lower interval bound
    @param a2 upper interval bound

    @return an expression which eventually will evaluate to the result
  **/
  NT2_FUNCTION_IMPLEMENTATION(tag::unifinv_, unifinv, 3)
  /// @overload
  NT2_FUNCTION_IMPLEMENTATION(tag::unifinv_, unifinv, 2)
  /// @overload
  NT2_FUNCTION_IMPLEMENTATION(tag::unifinv_, unifinv, 1)
}

#endif
