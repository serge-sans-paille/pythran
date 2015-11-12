//==============================================================================
//         Copyright 2009 - 2013 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2013 MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_SDK_BENCH_BENCHMARK_HPP_INCLUDED
#define NT2_SDK_BENCH_BENCHMARK_HPP_INCLUDED

#include <nt2/sdk/config/type_lists.hpp>
#include <nt2/sdk/bench/config.hpp>
#include <nt2/sdk/bench/suite.hpp>
#include <nt2/sdk/bench/args.hpp>
#include <nt2/sdk/bench/details/bench.hpp>

#define NT2_UNIT_MAIN_SUITE nt2::details::benchmarks

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/details/base_case.hpp>
#include <boost/preprocessor/seq/for_each.hpp>

/*
  Note: We use the factorized TEST_BASE_* macro but without any suffix so the
  display and the speedup identification works without any changes
*/

/*!
  @brief Single benchmark registration

  Create and register a function as a benchmark by creating all the needed
  boilerplate code around the body of the benchmark function itself.

  @param Name Experiment type used in this benchmark
**/
#define NT2_REGISTER_BENCHMARK(Name)                                           \
NT2_TEST_BASE_CASE(Name,nt2::details::bench,nt2::details::benchmarks,)         \
/**/

/*!
  @brief Template benchmarks registration

  Create and register a template function as benchmarks by creating all the
  needed boilerplate code around the body of the benchmark function itself so
  that every instantiation of said function for a type inside the preprocessor
  sequence TYPES is run independently.

  @param Name   Experiment type used in this benchmark
  @param Types  Preprocessor sequence of type to pass to the benchmark function
**/
#define NT2_REGISTER_BENCHMARK_TPL(Name, Types)                                \
NT2_TEST_BASE_CASE_TPL( Name, Types                                            \
                      , nt2::details::bench                                    \
                      , nt2::details::benchmarks                               \
                      ,                                                        \
                      )                                                        \
/**/

#endif
