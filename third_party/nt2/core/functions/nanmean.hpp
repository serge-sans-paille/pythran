//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2011 - 2012   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_NANMEAN_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_NANMEAN_HPP_INCLUDED

#include <nt2/include/functor.hpp>


namespace nt2
{
  namespace tag
  {
    /*!
      @brief Tag for the nanmean functor
    **/
    struct nanmean_ : boost::dispatch::tag::formal_
    {
      /// @brief Parent hierarchy
      typedef boost::dispatch::tag::formal_ parent;
    };
  }
  /*!
   @brief mean of a table expression,  suppressing Nans

    Compute the mean of the non nan elements of a table expression
    along a given dimension.

    @par Semantic

    For any table  expression @c t and any integer @c n:

    @code
    auto r = nanmean(t,n);
    @endcode

    is equivalent to:

    @code
    auto d = nt2::max(nt2::nbtrue(nt2::is_not_nan(t), n), 1);
    auto r = sum(if_else_zero(is_not_nan(t), t),n)/d;
    @endcode


    @par Note:
    n default to firstnonsingleton(t)

    @see @funcref{firstnonsingleton}, @funcref{sum}, @funcref{max}, @funcref{if_else_zero}, @funcref{is_not_nan}
    @param a0 Table expression to process
    @param a1 Dimension along which to process a0

    @return An expression eventually evaluated to the result
   */
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::nanmean_       , nanmean, 2)
  /// @overload
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::nanmean_       , nanmean, 1)
}

#endif
