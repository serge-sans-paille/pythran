//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_STATISTICS_FUNCTIONS_UNIFPDF_HPP_INCLUDED
#define NT2_STATISTICS_FUNCTIONS_UNIFPDF_HPP_INCLUDED
#include <nt2/include/functor.hpp>


namespace nt2 { namespace tag
  {
   /*!
     @brief unifpdf generic tag

     Represents the unifpdf function in generic contexts.

     @par Models:
        Hierarchy
   **/
    struct unifpdf_ : ext::elementwise_<unifpdf_>
    {
      typedef ext::elementwise_<unifpdf_> parent;
    };
  }
  /*!
    uniform  distribution

    @par Semantic:

    For every table expression

    @code
    auto r = unifpdf(a0, a, b);
    @endcode

    is similar to:

    @code
    auto r = (a0<a || a0 >= b) ? 0 : 1/(b-a);
    @endcode

    @param a0
    @param a1
    @param a2

    @return an expression which eventually will evaluate to the result
  **/
  NT2_FUNCTION_IMPLEMENTATION(tag::unifpdf_, unifpdf, 3)
  /// @overload
  NT2_FUNCTION_IMPLEMENTATION(tag::unifpdf_, unifpdf, 1)
  /// @overload
  NT2_FUNCTION_IMPLEMENTATION(tag::unifpdf_, unifpdf, 2)
}

#endif
