//==============================================================================
//         Copyright 2003 - 2012 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012        MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_SDK_UNIT_TESTS_COVER_HPP_INCLUDED
#define NT2_SDK_UNIT_TESTS_COVER_HPP_INCLUDED

#include <nt2/sdk/unit/io.hpp>
#include <nt2/sdk/unit/stats.hpp>
#include <nt2/sdk/unit/details/cover.hpp>
#include <nt2/sdk/unit/details/prng.hpp>
#include <nt2/include/functor.hpp>
#include <boost/simd/memory/allocator.hpp>
#include <boost/dispatch/preprocessor/once.hpp>
#include <vector>
#include <string>

/// INTERNAL ONLY
#if !defined(NT2_NB_RANDOM_TEST)
#define NT2_NB_RANDOM_TEST 128
#endif

/// INTERNAL ONLY TO REMOVE LATER
#define NT2_CREATE_BUF(Name,Type,Size,Min,Max)                                 \
std::vector<Type,boost::simd::allocator<Type> > Name(Size);                    \
nt2::roll( Name, Min, Max )                                                    \
/**/

/// INTERNAL ONLY TO REMOVE LATER
#define NT2_CREATE_LOGICAL_BUF(Name,Type,Size)                                 \
std::vector<Type,boost::simd::allocator<Type> > Name(Size);                    \
do                                                                             \
{                                                                              \
  for(std::size_t i=0;i<Name.size();++i) Name[i] = Type(rand() % 2);           \
} BOOST_DISPATCH_ONCE                                                          \
/**/


/*!
  @brief Perform precision coverage test on arbitrary function

  For a given function @c FUNC, checks if the application of @c FUNC on the
  set of data @c INPUTS is within a given ULP tolerance relatively to a set
  of reference value @c REF

  @param FUNC   Polymorphic function to test
  @param INPUTS Preprocessor sequence of tuples containing references data and
                the types to use to perform the computation.
  @param REF    Reference data to check against
  @param N      Maximum ULP tolerance
**/
#define NT2_COVER_FN_ULP_EQUAL(FUNC, INPUTS, REF, N)                           \
do                                                                             \
{                                                                              \
  std::string desc = NT2_COVER_TEST_NAME(FUNC,INPUTS);                         \
  nt2::unit::test_count()++;                                                   \
  ::nt2::details::test_cover_ulp( desc.c_str()                                 \
                                ,__FILE__,__LINE__                             \
                                , FUNC, (REF)                                  \
                                , NT2_COVER_TYPES_LIST(INPUTS)()               \
                                , N                                            \
                                , NT2_COVER_VALUES_LIST(INPUTS)                \
                                );                                             \
} BOOST_DISPATCH_ONCE                                                          \
/**/

/*!
  @brief Perform precision coverage test on an NT2 functor

  For a given fucntor tag @c TAG, checks if the application of the associated
  function on the set of data @c INPUTS is within a given ULP tolerance
  relatively to a set of reference value @c REF

  @param TAG    Tag for the function to test.
  @param INPUTS Preprocessor sequence of tuples containing references data and
                the types to use to perform the computation.
  @param REF    Reference data to check against
  @param N      Maximum ULP tolerance
**/
#define NT2_COVER_ULP_EQUAL(TAG, INPUTS, REF, N)                               \
NT2_COVER_FN_ULP_EQUAL(nt2::functor<TAG>(), INPUTS, REF, N)                    \
/**/
#endif
