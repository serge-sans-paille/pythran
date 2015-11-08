//==============================================================================
//         Copyright 2003 - 2012 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012        MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_SDK_UNIT_STATS_HPP_INCLUDED
#define NT2_SDK_UNIT_STATS_HPP_INCLUDED

#include <nt2/sdk/unit/config.hpp>

/*!
  @file
  @brief Basic building blocks for test macros
**/

namespace nt2 { namespace unit
{
  /*!
    @brief Global error counter accessor

    Give a mutable access to the current test error counter.

    @return a non-const reference to the current error counter
  **/
  NT2_TEST_UNIT_DECL int& error_count();

  /*!
    @brief Global test counter accessor

    Give a mutable access to the current test counter.

    @return a non-const reference to the current test counter
  **/
  NT2_TEST_UNIT_DECL int& test_count();

  /*!
    @brief Report a passed test

    Report a test as a success and display a message about this success.

    @param msg Message to display when test passes
  **/
  NT2_TEST_UNIT_DECL void pass(char const* msg);

  /*!
    @brief Report a failed test

    Report a test as a failure and display a message about this failure.

    @param msg  Message to display when test fails
    @param ln   Line number at which test failed
    @param fn   Name of the function in which the test failed
  **/
  NT2_TEST_UNIT_DECL void fail(char const* msg, int ln, char const* fn);

  /*!
    @brief Report a forced failure

    Report a test as a forced failure and display a message about this failure.

    @param msg  Message to display when test fails
    @param ln   Line number at which test failed
    @param fn   Name of the function in which the test failed
  **/
  NT2_TEST_UNIT_DECL void error(char const* msg, int ln, char const* fn);
} }

#endif
