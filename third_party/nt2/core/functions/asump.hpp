//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2011 - 2012   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_ASUMP_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_ASUMP_HPP_INCLUDED
#include <nt2/include/functor.hpp>

namespace nt2
{
  namespace tag
  {
    /*!
      @brief Tag for the asump functor
    **/
    struct asump_ : boost::dispatch::tag::formal_
    {
      /// @brief Parent hierarchy
      typedef boost::dispatch::tag::formal_ parent;
    };
  }

  /*!
    @brief Sum of the power of absolute values of a table  expression along a dimension

    Computes the sum of the pth power of the absolute value of all the elements
    of a table along a given dimension.

    @par Semantic

    For any table  expression and any arithmetic value @c
    p and integer n  :

    @code
    auto r = asump(t,p n);
    @endcode

    is equivalent to:

    @code
    auto r = sum(pow_abs(t,p),n);
    @endcode

    @par Note:
    n default to firstnonsingleton(t)

    @see @funcref{firstnonsingleton}, @funcref{pow_abs}
    @param a0 Table to process
    @param a1 Power at which absolute values are raised
    @param a2 Dimension along which to process a0

    @return An expression eventually evaluated to the result

  **/

  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::asump_, asump, 3)
  /// @overload
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::asump_, asump, 2)

}

#endif
