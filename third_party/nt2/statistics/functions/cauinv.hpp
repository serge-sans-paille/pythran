//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_STATISTICS_FUNCTIONS_CAUINV_HPP_INCLUDED
#define NT2_STATISTICS_FUNCTIONS_CAUINV_HPP_INCLUDED
#include <nt2/include/functor.hpp>


namespace nt2 { namespace tag
  {
   /*!
     @brief cauinv generic tag

     Represents the cauinv function in generic contexts.

     @par Models:
        Hierarchy
   **/
    struct cauinv_ : ext::elementwise_<cauinv_>
    {
      /// @brief Parent hierarchy
      typedef ext::elementwise_<cauinv_> parent;
    };
  }
  /*!
    inverse of Cauchy cumulative distribution

    @par Semantic:

    For every table expression a0 and optional scalars m and s

    @code
    auto r = cauinv(a0{, m, s});
    @endcode

    is similar to:

    @code
    auto r = tanpi(a0-Half<A0>()*s+m;
    @endcode

    @see @funcref{tanpi},  @funcref{proper_tanpi}
    @param a0 points of evaluation
    @param a1 optional median default to 0
    @param a2 optional scale default to 1

    @return an expression which eventually will evaluate to the result
  **/
  NT2_FUNCTION_IMPLEMENTATION(tag::cauinv_, cauinv, 3)
  /// @overload
  NT2_FUNCTION_IMPLEMENTATION(tag::cauinv_, cauinv, 1)
  /// @overload
  NT2_FUNCTION_IMPLEMENTATION(tag::cauinv_, cauinv, 2)
}

#endif
