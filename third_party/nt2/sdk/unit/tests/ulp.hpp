//==============================================================================
//         Copyright 2003 - 2012 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012        MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_SDK_UNIT_TESTS_ULP_HPP_INCLUDED
#define NT2_SDK_UNIT_TESTS_ULP_HPP_INCLUDED

#include <nt2/sdk/unit/io.hpp>
#include <nt2/sdk/unit/stats.hpp>
#include <nt2/sdk/unit/details/ulp.hpp>
#include <boost/dispatch/preprocessor/once.hpp>
#include <boost/current_function.hpp>

/*!
  @brief Check for absolute precision using a provided distance function

  For two given values @c A and @c B, consider the test successful if and only
  if the distance between @c A and @b is less or equal to @c N.

  @usage{test_ulp.cpp}
**/
#define NT2_TEST_ULP_EQUAL_FN(A, B, N, FN)                                     \
do                                                                             \
{                                                                              \
  nt2::unit::test_count()++;                                                   \
                                                                               \
  nt2::details::test_ulp_equal( #A " == " #B                                   \
                              , BOOST_CURRENT_FUNCTION, __LINE__               \
                              , A, B, N, FN                                    \
                              );                                               \
} BOOST_DISPATCH_ONCE                                                          \
/**/

/*!
  @brief Check for absolute precision

  For two given values @c A and @c B, consider the test successful if and only
  if the ULP distance between @c A and @b is less or equal to @c N.

  @usage{test_ulp.cpp}
**/
#define NT2_TEST_ULP_EQUAL(A, B, N)                                            \
NT2_TEST_ULP_EQUAL_FN(A, B, N, nt2::details::max_ulps_caller())                \
/**/

#endif
