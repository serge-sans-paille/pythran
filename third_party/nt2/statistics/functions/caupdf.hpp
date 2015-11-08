//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_STATISTICS_FUNCTIONS_CAUPDF_HPP_INCLUDED
#define NT2_STATISTICS_FUNCTIONS_CAUPDF_HPP_INCLUDED
#include <nt2/include/functor.hpp>


namespace nt2 { namespace tag
  {
   /*!
     @brief caupdf generic tag

     Represents the caupdf function in generic contexts.

     @par Models:
        Hierarchy
   **/
    struct caupdf_ : ext::elementwise_<caupdf_>
    {
      /// @brief Parent hierarchy
      typedef ext::elementwise_<caupdf_> parent;
    };
  }
  /*!
    cauchy  distribution

    @par Semantic:

    For every table expression a0 and optional scalars m and s

    @code
    auto r = caupdf(a0, m, s);
    @endcode

    is similar to:

    @code
    auto r =  (s*Invpi)/(sqr(s)+sqr(a0-m));
    @endcode

    @see @funcref{tanpi},  @funcref{proper_tanpi}
    @param a0 points of evaluation
    @param a1 optional median default to 0
    @param a2 optional scale default to 1

    @return an expression which eventually will evaluate to the result
  **/
  NT2_FUNCTION_IMPLEMENTATION(tag::caupdf_, caupdf, 3)
  /// @overload
  NT2_FUNCTION_IMPLEMENTATION(tag::caupdf_, caupdf, 1)
  /// @overload
  NT2_FUNCTION_IMPLEMENTATION(tag::caupdf_, caupdf, 2)
}

#endif
