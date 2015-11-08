//==============================================================================
//         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_VAR_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_VAR_HPP_INCLUDED

#include <nt2/include/functor.hpp>

namespace nt2
{
  namespace tag
  {
    /*!
      @brief Tag for the var functor
    **/
    struct var_ : boost::dispatch::tag::formal_
    {
      /// @brief Parent hierarchy
       typedef boost::dispatch::tag::formal_ parent;
    };
  }
  /*!
    @brief variance of a table along a given dimension

    Returns the variance of a table along a given dimension

    @par Semantic

    For any table expression of T @c t integer or weights w   and any integer @c n:

    @code
    auto r = var(t, w, n);
    @endcode

    is equivalent to:

    if w is an integer

    @code
    size_t h = size(a, n);
    auto r = asum2(a-mean(a, n))/(w || (h == 1))? h : h-1);
    @endcode

    if w is an expression table of positive weights

    @code
    auto r = asum2(a-mean(a, w, n))/sum(w);
    @endcode

    @par Note:
    n default to firstnonsingleton(t)

    @see @funcref{firstnonsingleton}, @funcref{mean}, @funcref{asum2}
    @param a0 Table expression to process
    @param a1 normalization hint or table expression of weights
    @param a2 Dimension along which to process a0

    @return An expression eventually evaluated to the result
  **/
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::var_       , var, 3)
  /// @overload
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::var_       , var, 2)
  /// @overload
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::var_       , var, 1)
}


#endif
