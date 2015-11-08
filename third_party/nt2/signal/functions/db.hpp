//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================

#ifndef NT2_SIGNAL_FUNCTIONS_DB_HPP_INCLUDED
#define NT2_SIGNAL_FUNCTIONS_DB_HPP_INCLUDED

#include <nt2/include/functor.hpp>

namespace nt2
{
  namespace tag
  {
    /*!
      @brief Tag for the db functor
    **/
    struct db_ : ext::elementwise_<db_>
    {
      /// @brief Parent hierarchy
      typedef ext::elementwise_<db_> parent;
    };
  }

  namespace details
  {
  /// INTERNAL ONLY
    struct voltage_;
  /// INTERNAL ONLY
    struct power_;

  /// INTERNAL ONLY
    typedef meta::as_<voltage_>   voltage_t;
  /// INTERNAL ONLY
    typedef meta::as_<power_>     power_t;
  }

  details::voltage_t  const voltage_  = {};
  details::power_t    const power_    = {};
  /*!
    @brief Converts energy or power to decibels.

    Computes the decibels from energy or power; The elements of a0 are
    voltage measurements across a resistance of a2 (default 1) ohm.

    @par Semantic

    For any table expression,  and mode:

    @code
    auto r = db(t, voltage_, n = 1);
    @endcode

    or

    @code
    auto r = db(t, n = 1);
    @endcode

    is equivalent to:

    @code
      auto d = mag2db(t, r);
    @endcode

    else if mode is power_
    @code
    auto d = db(t, power_);
    @endcode

    or

    @code
    auto d = db(t);
    @endcode

    is equivalent to:

    @code
    auto d = pow2db(e);
    @endcode

    @see @funcref{pow2db}, @funcref{mag2db}
    @param a0 Table to process
    @param a1 mode: can be power_ or voltage_ (default to voltage_)
    @param a2 optional resistance (only in voltage_ case)


    @return An expression eventually evaluated to the result
  **/

  NT2_FUNCTION_IMPLEMENTATION(tag::db_, db, 3)
  ///  @overload
  NT2_FUNCTION_IMPLEMENTATION(tag::db_, db, 2)
  ///  @overload
  NT2_FUNCTION_IMPLEMENTATION(tag::db_, db, 1)

}

#endif
