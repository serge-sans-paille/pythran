//==============================================================================
//         Copyright 2003 - 2012 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012        MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_SDK_UNIT_TESTS_EXCEPTIONS_HPP_INCLUDED
#define NT2_SDK_UNIT_TESTS_EXCEPTIONS_HPP_INCLUDED

/*!
  @file
  @brief Exceptions and assertions related testing macros
**/

#include <nt2/sdk/unit/stats.hpp>
#include <nt2/sdk/error/assert_exception.hpp>
#include <boost/dispatch/preprocessor/strip.hpp>
#include <boost/dispatch/preprocessor/once.hpp>
#include <boost/dispatch/meta/ignore_unused.hpp>
#include <iostream>

#ifdef __GNUC__
// INTERNAL ONLY
#define NT2_UNUSED_EXPR (void)
#else
// INTERNAL ONLY
#define NT2_UNUSED_EXPR
#endif

/*!
  @brief Check exception being thrown

  For any given expression @c X, consider the test successful if and only if
  @c X throws an exception of type to @c E.

  @usage{test_throw.cpp}
**/
#define NT2_TEST_THROW(X,E)                                                    \
do {                                                                           \
  ::nt2::unit::test_count()++;                                                 \
  bool caught = false;                                                         \
  try { NT2_UNUSED_EXPR (BOOST_DISPATCH_PP_STRIP(X)); }                        \
  catch( E& ex )                                                               \
  {                                                                            \
    ::boost::dispatch::ignore_unused(ex);                                      \
    ::nt2::unit::pass(#X " throws " #E);                                       \
    caught = true;                                                             \
  }                                                                            \
  catch(...)      {}                                                           \
  if(!caught) ::nt2::unit::fail( #X " throws " #E                              \
                                  , __LINE__, BOOST_CURRENT_FUNCTION);         \
} BOOST_DISPATCH_ONCE                                                          \
/**/

#define NT2_TEST_WARNING_NOFATAL_BEGIN()                                       \
{                                                                              \
  nt2::log_mode_t old_warning_mode = nt2::warning_mode;                        \
  nt2::warning_mode = nt2::log_mode_t(                                         \
      (nt2::warning_mode & ~nt2::LOG_EXCEPT & ~nt2::LOG_ABORT)                 \
  );                                                                           \
/**/

#define NT2_TEST_WARNING_NOFATAL_END()                                         \
  nt2::warning_mode = old_warning_mode;                                        \
}                                                                              \
/**/

#define NT2_TEST_WARNING_EXCEPT_BEGIN()                                        \
{                                                                              \
  nt2::log_mode_t old_warning_mode = nt2::warning_mode;                        \
  nt2::warning_mode = nt2::log_mode_t(                                         \
      (nt2::warning_mode & ~nt2::LOG_ABORT) | nt2::LOG_EXCEPT                  \
  );                                                                           \
/**/

#define NT2_TEST_WARNING_EXCEPT_END()                                          \
  nt2::warning_mode = old_warning_mode;                                        \
}
/**/

/*!
  @brief Check runtime assertion failing

  For any given expression @c X, consider the test successful if and only if
  @c X triggered a run-time assertion.

  @usage{test_assert.cpp}
**/
#define NT2_TEST_ASSERT(X)                                                     \
do {                                                                           \
  nt2::log_mode_t old_assert_mode = nt2::assert_mode;                          \
  nt2::assert_mode = nt2::log_mode_t(                                          \
    (nt2::assert_mode & ~nt2::LOG_ABORT) | nt2::LOG_EXCEPT                     \
  );                                                                           \
  ::nt2::unit::test_count()++;                                                 \
  bool caught = false;                                                         \
  try { NT2_UNUSED_EXPR (BOOST_DISPATCH_PP_STRIP(X)); }                        \
  catch( nt2::assert_exception& ex )  {                                        \
    ::nt2::unit::pass(#X " asserts ");                                         \
    std::cout << "with message:\n\t'" << ex.what() << "'\n";                   \
    caught = true;                                                             \
  }                                                                            \
  catch(...)      {}                                                           \
  if(!caught)                                                                  \
  {                                                                            \
    ::nt2::unit::fail( #X " asserts "                                          \
                        , __LINE__, BOOST_CURRENT_FUNCTION);                   \
  }                                                                            \
  nt2::assert_mode = old_assert_mode;                                          \
} BOOST_DISPATCH_ONCE                                                          \
/**/

/*!
  @brief Check exception not being thrown

  For any given expression @c X, consider the test successful if and only if
  @c X does not throw any exception.

  @usage{test_no_throw.cpp}
**/
#define NT2_TEST_NO_THROW(X)                                                   \
do {                                                                           \
  bool nt2_test_no_throw = true;                                               \
  ::nt2::unit::test_count()++;                                                 \
  try { NT2_UNUSED_EXPR (BOOST_DISPATCH_PP_STRIP(X)); }                        \
  catch(...)                                                                   \
  {                                                                            \
    ::nt2::unit::fail( #X " should not throw"                                  \
                        , __LINE__, BOOST_CURRENT_FUNCTION                     \
                        );                                                     \
    nt2_test_no_throw = false;                                                 \
  }                                                                            \
  if(nt2_test_no_throw) ::nt2::unit::pass(#X " does not throw");               \
} BOOST_DISPATCH_ONCE                                                          \
/**/


/*!
  @brief Check runtime assertion not failing

  For any given expression @c X, consider the test successful if and only if
  @c X does not trigger any runtime assertion.

  @usage{test_no_assert.cpp}
**/
#define NT2_TEST_NO_ASSERT(X)                                                  \
do {                                                                           \
  nt2::log_mode_t old_assert_mode = nt2::assert_mode;                          \
  nt2::assert_mode = nt2::log_mode_t(                                          \
    (nt2::assert_mode & ~nt2::LOG_ABORT) | nt2::LOG_EXCEPT                     \
  );                                                                           \
  bool nt2_test_no_throw = true;                                               \
  ::nt2::unit::test_count()++;                                                 \
  try { NT2_UNUSED_EXPR (BOOST_DISPATCH_PP_STRIP(X)); }                        \
  catch(nt2::assert_exception& ex)                                             \
  {                                                                            \
    ::nt2::unit::fail( #X " should not assert "                                \
                        , __LINE__, BOOST_CURRENT_FUNCTION                     \
                        );                                                     \
    std::cout << "with message:\n\t'" << ex.what() << "'\n";                   \
    nt2_test_no_throw = false;                                                 \
  }                                                                            \
  catch(...) {}                                                                \
  if(nt2_test_no_throw)                                                        \
    ::nt2::unit::pass(#X " does not assert " );                                \
  nt2::assert_mode = old_assert_mode;                                          \
} BOOST_DISPATCH_ONCE                                                          \
/**/

#endif
