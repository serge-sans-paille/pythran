//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2011 - 2012   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_MEDIANAD_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_MEDIANAD_HPP_INCLUDED

namespace nt2
{
  namespace tag
  {
    /*!
      @brief Tag for the medianad functor
    **/
    struct medianad_ : boost::dispatch::tag::formal_
    {
      /// @brief Parent hierarchy
      typedef boost::dispatch::tag::formal_ parent;
    };
  }
  /*!
    @brief median of the absolute deviation to the median of a table

    Computes the meian of the of the absolute deviation to the median of
    non nan elements of a table expression along a given dimension.

    @par Semantic

    For any table  expression @c t and any integer @c n:

    @code
    auto r = medianad(t,n);
    @endcode

    is equivalent to:

    @code
    auto r = median(abs(a-expand_to(median(a,n), size(a))), n);
    @endcode

    @par Note:
    n default to firstnonsingleton(t)

    @see @funcref{firstnonsingleton}, @funcref{median},
    @funcref{abs}, @funcref{size}, @funcref{expand_to}

    @param a0 Table to process @param a1 Dimension along which to
    process a0

    @return An expression eventually evaluated to the result
   */
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::medianad_       , medianad, 1)
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::medianad_       , medianad, 2)
}

#endif
