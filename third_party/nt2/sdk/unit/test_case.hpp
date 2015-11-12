//==============================================================================
//         Copyright 2003 - 2012 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012        MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_SDK_UNIT_TEST_CASE_HPP_INCLUDED
#define NT2_SDK_UNIT_TEST_CASE_HPP_INCLUDED

#include <cstdio>
#include <nt2/sdk/unit/stats.hpp>
#include <nt2/sdk/config/types.hpp>
#include <nt2/sdk/meta/type_id.hpp>
#include <nt2/sdk/config/type_lists.hpp>
#include <nt2/sdk/error/assert_as_exceptions.hpp>

#include <boost/preprocessor/stringize.hpp>
#include <boost/preprocessor/seq/for_each.hpp>
#include <boost/preprocessor/seq/enum.hpp>
#include <boost/dispatch/preprocessor/strip.hpp>
#include <nt2/sdk/unit/details/base_case.hpp>

#include <boost/mpl/for_each.hpp>
#include <boost/mpl/not.hpp>
#include <boost/mpl/and.hpp>
#include <boost/mpl/size.hpp>
#include <boost/mpl/or.hpp>
#include <boost/mpl/vector.hpp>
#include <boost/mpl/filter_view.hpp>

/*!
  @brief MPL list generation macro.

  This macro generates a MPL list of types from a preprocessor sequence
  and an MPL meta-function. It returns the MPL sequence with the elements
  of the preprocessor sequence that satisfy the given predicate.
**/
#define NT2_TEST_SEQ_MPL_FILTER(seq, cond)                                     \
(boost::mpl::filter_view< boost::mpl::vector<BOOST_PP_SEQ_ENUM(seq)>           \
            , BOOST_DISPATCH_PP_STRIP(cond)                                    \
            >::type                                                            \
)                                                                              \
/**/

/*!
  @brief Test case registration macro.

  This macro declares a new test case function containing user-defined tests
  sequences. Each test case has a unique name passed as a parameter that
  identifies the set of tests inside the whole test suite.

  @usage{test_case.cpp}
**/
#define NT2_TEST_CASE(Name)                                                     \
NT2_TEST_BASE_CASE(Name,nt2::details::unit_test,nt2::details::unit_tests,_test) \
/**/

/*!
  @brief Type-dependant test case registration macro

  This macro declares a new set of test cases functions containing user
  defined tests sequences parametrized by a list of types. The test function
  is then instantiated for each type in the preprocessor sequence. Each test
  case has a unique name passed as a parameter that identifies the set of tests
  inside the whole test suite.

  @usage{test_case_tpl.cpp}
**/
#define NT2_TEST_CASE_TPL(Name, Types)                                         \
NT2_TEST_BASE_CASE_TPL( Name, Types                                            \
                      , nt2::details::unit_test                                \
                      , nt2::details::unit_tests                               \
                      , _test                                                  \
                      )                                                        \
/**/

/*!
  @brief Type-dependant test case registration macro, with MPL type list

  This macro declares a new set of test cases functions containing user
  defined tests sequences parametrized by a MPL list of types. The test function
  is then instantiated for each type in the MPL sequence. Each test
  case has a unique name passed as a parameter that identifies the set of tests
  inside the whole test suite.
**/
#define NT2_TEST_CASE_TPL_MPL(Name, TypeList)                                  \
NT2_TEST_BASE_CASE_TPL_MPL( Name, TypeList                                     \
                          , nt2::details::unit_test                            \
                          , nt2::details::unit_tests                           \
                          , _test                                              \
                          )                                                    \
/**/

#endif
