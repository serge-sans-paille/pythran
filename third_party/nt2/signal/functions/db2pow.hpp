//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_SIGNAL_FUNCTIONS_DB2POW_HPP_INCLUDED
#define NT2_SIGNAL_FUNCTIONS_DB2POW_HPP_INCLUDED
#include <nt2/include/functor.hpp>

namespace nt2
{
  namespace tag
  {
    /*!
      @brief Tag for the db2pow functor
    **/
    struct db2pow_ : ext::elementwise_<db2pow_>
    {
      /// @brief Parent hierarchy
      typedef ext::elementwise_<db2pow_> parent;
    };
  }
  /*!
    @brief Convert decibels (dB) to magnitude.

    Computes the decibels to magnitude across a resistance of a1 (default 1).

    @par Semantic

    For any table expression:

    @code
    auto m = db2pow(d, r);
    @endcode

    is equivalent to:

    @code
    auto m = sqrt(r)*exp10(d/2);
    @endcode

    @see @funcref{exp10}, @funcref{db},
    @funcref{pow2db}, @funcref{db2pow}, @funcref{db2mag}
    @param a0 Table expression to process
    @param a1 optional resistance (default 1)


    @return An expression eventually evaluated to the result
  **/

  NT2_FUNCTION_IMPLEMENTATION(tag::db2pow_, db2pow, 2)
  /// @overload
  NT2_FUNCTION_IMPLEMENTATION(tag::db2pow_, db2pow, 1)
}

#endif
