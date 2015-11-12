//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2011 - 2012   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_MEANAD_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_MEANAD_HPP_INCLUDED

#include <nt2/include/functor.hpp>

namespace nt2
{
  namespace tag
  {
   /*!
      @brief Tag for the meanad functor
    **/
     struct meanad_ : boost::dispatch::tag::formal_
    {
      typedef boost::dispatch::tag::formal_ parent;
    };
  }
  /*!
    @brief mean of the absolute deviation to the mean of an expression

    Computes the mean of the of the absolute deviation to the mean of
    non nan elements of a table expression along a given dimension.

    @par Semantic

    For any table  expression @c t and any integer @c n:

    @code
    auto r = meanad(t,n);
    @endcode

    is equivalent to:

    @code
    auto r = mean(abs(a-expand_to(mean(a,n), size(a))), n);
    @endcode

    @par Note:
    n default to firstnonsingleton(t)

    @see @funcref{firstnonsingleton}, @funcref{mean},
    @funcref{abs}, @funcref{size}, @funcref{expand_to}

    @param a0 Table to process @param a1 Dimension along which to
    process a0

    @return An expression eventually evaluated to the result
   */
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::meanad_       , meanad, 2)
  ///@overload
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::meanad_       , meanad, 1)

}

#endif
