//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2011 - 2012   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_NANASUM2_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_NANASUM2_HPP_INCLUDED

#include <nt2/include/functor.hpp>

namespace nt2
{
  namespace tag
  {
    /*!
      @brief Tag for the nanasum2 functor
    **/
    struct nanasum2_ : boost::dispatch::tag::formal_
    {
      /// @brief Parent hierarchy
      typedef boost::dispatch::tag::formal_ parent;
    };
  }
  /*!
    @brief sum of square absolute value of a table expression,  suppressing Nans

    Computes the sum of square absolute value of the non nan elements of a table expression
    along a given dimension.

    @par Semantic

    For any table  expression @c t and any integer @c n:

    @code
    auto r = nanasum2(t,n);
    @endcode

    is equivalent to:

    @code
    auto r = asum2(if_zero_else(isnan(t), t),n);
    @endcode

    @par Note:
    n default to firstnonsingleton(t)

    @see @funcref{firstnonsingleton}, @funcref{asum2}, @funcref{if_zero_else}
    @param a0 Table expression to process
    @param a1 Dimension along which to process a0

    @return An expression eventually evaluated to the result
   */
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::nanasum2_       , nanasum2, 2)
  /// @overload
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::nanasum2_       , nanasum2, 1)
}

#endif
