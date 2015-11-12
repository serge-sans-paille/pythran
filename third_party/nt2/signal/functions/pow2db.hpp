//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================

#ifndef NT2_SIGNAL_FUNCTIONS_POW2DB_HPP_INCLUDED
#define NT2_SIGNAL_FUNCTIONS_POW2DB_HPP_INCLUDED
#include <nt2/include/functor.hpp>
namespace nt2 { namespace tag
  {
    /*!
      @brief Tag for the pow2db functor
    **/
    struct pow2db_ : ext::elementwise_<pow2db_>
    {
      /// @brief Parent hierarchy
      typedef ext::elementwise_<pow2db_> parent;
    };
  }
  /*!
    @brief Converts magnitudeenergy to decibels

    Computes the decibels from energy a0 (> 0).

    @par Semantic

    For any table expression,  and mode:

    @code
    auto d = db(t);
    @endcode

    is equivalent to:

    @code
    auto d = 10*log10(t);
    @endcode

    @see @funcref{log10}, @funcref{sqr}, @funcref{db},
    @funcref{mag2db}, @funcref{db2pow}, @funcref{db2mag}
    @param a0
    Table expression to process

    @return An expression eventually evaluated to the result
  **/
  NT2_FUNCTION_IMPLEMENTATION(tag::pow2db_, pow2db, 1)
}



#endif
