//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_POLYNOM_FUNCTIONS_VALUATION_HPP_INCLUDED
#define NT2_POLYNOM_FUNCTIONS_VALUATION_HPP_INCLUDED
#include <nt2/include/functor.hpp>

namespace nt2 { namespace tag
  {
   /*!
     @brief valuation generic tag

     Represents the valuation function in generic contexts.

     @par Models:
        Hierarchy
   **/
    struct valuation_ : ext::elementwise_<valuation_>
    {
      /// @brief Parent hierarchy
      typedef ext::elementwise_<valuation_> parent;
    };
  }
  /*!
    returns the valuation of the input polynomial.
    null polynomial has valuation -1.
    non null constant polynomial has valuation 0.

    @par Semantic:

    For every polynomial p

    @code
    ptrdiff_t r = valuation(p);
    @endcode

    The valuation is the least exponent associated to a non null coefficient.
    null polynomial has valuation -1.
    non null constant polynomial has valuation 0.

    @param a0

    @return a ptrdiff_t value
  **/
  NT2_FUNCTION_IMPLEMENTATION(tag::valuation_,valuation, 1)
}
#endif
