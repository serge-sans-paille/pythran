//==============================================================================
//         Copyright 2003 - 2012 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012        MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_SDK_UNIT_TESTS_BASIC_HPP_INCLUDED
#define NT2_SDK_UNIT_TESTS_BASIC_HPP_INCLUDED

#include <nt2/sdk/unit/stats.hpp>

/*!
  @brief Check a boolean predicate

  For any given expression @c X, consider the test successful if and only if
  @c X evaluates to @c true.

  @usage{test.cpp}
**/
#define NT2_TEST(X)                                             \
( ::nt2::unit::test_count()++                                   \
, (X) ? ::nt2::unit::pass(#X)                                   \
      : ::nt2::unit::fail(#X, __LINE__, BOOST_CURRENT_FUNCTION) \
)                                                               \
/**/

/*!
  @brief Force a test failure

  Force the test to fail and output @c X as a custom message.

  @usage{test_error.cpp}
**/
#define NT2_TEST_ERROR(X)                                   \
( ::nt2::unit::test_count()++                               \
, ::nt2::unit::error(#X, __LINE__, BOOST_CURRENT_FUNCTION)  \
)                                                           \
/**/


/*!
  @brief Signify test suite completion

  Register the test suite as complete.

  @usage{test_completion.cpp}
**/
#define NT2_TEST_COMPLETE(X)  \
( ::nt2::unit::test_count()++ \
, ::nt2::unit::pass(#X)       \
)                             \
/**/

#endif
