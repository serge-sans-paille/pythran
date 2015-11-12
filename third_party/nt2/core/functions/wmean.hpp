//==============================================================================
//         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_WMEAN_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_WMEAN_HPP_INCLUDED

#include <nt2/include/functor.hpp>


namespace nt2
{
  namespace tag
  {
    /*!
      @brief Tag for the wmean functor
    **/
     struct wmean_ : boost::dispatch::tag::formal_
    {
      /// @brief Parent hierarchy
       typedef boost::dispatch::tag::formal_ parent;
    };
  }
  /*!
    @brief weigthed mean of a table along a given dimension

    Returns the weigthed mean of a table along a given dimension

    @par Semantic

    For any table expression of T @c t,  weights w   and any integer @c n:

    @code
    auto r = wmean(t, w, n);
    @endcode

    is equivalent to:

    @code
    auto r = dot(a, expand_to(a, w), n)/sum(w);
    @endcode

    @par Note:
    n default to firstnonsingleton(t)

    @see @funcref{firstnonsingleton}, @funcref{mean}, @funcref{asum2}
    @param a0 Table expression to process
    @param a1 normalization hint or table of weights
    @param a2 Dimension along which to process a0

    @return An expression eventually evaluated to the result
  **/
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::wmean_       , wmean, 3)
  /// @overload
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::wmean_       , wmean, 2)
}

#endif
