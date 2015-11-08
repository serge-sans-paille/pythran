//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_STATISTICS_FUNCTIONS_GAMPDF_HPP_INCLUDED
#define NT2_STATISTICS_FUNCTIONS_GAMPDF_HPP_INCLUDED
#include <nt2/include/functor.hpp>


namespace nt2 { namespace tag
  {
   /*!
     @brief gampdf generic tag

     Represents the gampdf function in generic contexts.

     @par Models:
        Hierarchy
   **/
    struct gampdf_ : ext::elementwise_<gampdf_>
    {
      /// @brief Parent hierarchy
      typedef ext::elementwise_<gampdf_> parent;
    };
  }
  /*!
    gamma distribution

    @par Semantic:

    For every table expressions

    @code
    auto r = gampdf(a0, shape, scale);
    @endcode

    is similar to:

    @code
    auto r = (exp((1-shape)*log(a0/scale)-a0-gammaln(shape))/scale;
    @endcode

    @see @funcref{exp}, @funcref{log}, @funcref{gammaln},
    @param a0
    @param a1 shape
    @param a2 optional scale (default to 1)

    @return an expression which eventually will evaluate to the result
  **/
  NT2_FUNCTION_IMPLEMENTATION(tag::gampdf_, gampdf, 3)
  /// @overload
  NT2_FUNCTION_IMPLEMENTATION(tag::gampdf_, gampdf, 2)
}

#endif
