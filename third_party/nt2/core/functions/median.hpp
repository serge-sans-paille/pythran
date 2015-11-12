//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2011 - 2012   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_MEDIAN_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_MEDIAN_HPP_INCLUDED

namespace nt2
{
  namespace tag
  {
    /*!
      @brief Tag for the asum1 functor
    **/
    struct median_ : boost::dispatch::tag::formal_
    {
      /// @brief Parent hierarchy
      typedef boost::dispatch::tag::formal_ parent;
    };
  }
 /*!
    @brief median of a table expression along a dimension

    Compute the median of all the elements of a
    table expression along a given dimension.

    @par Semantic

    For any table  expression @c t and any integer @c n:

    @code
    auto r = median(t,n);
    @endcode

    is similar to:

    @code
    auto s = sort(t,n);
    h =  size(t, n)/2;
    auto r = s(_, ..., h, ...; _);
    @endcode

    where h is the nth slot of s

    @par Note:
    n default to firstnonsingleton(t)


    @see @funcref{firstnonsingleton}, @funcref{sort}
    @param a0 Table to process
    @param a1 Dimension along which to process a0

    @return An expression eventually evaluated to the result
  **/

  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::median_       , median, 1)
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::median_       , median, 2)
}

#endif
