//==============================================================================
//         Copyright 2003 - 2012 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012        MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_SDK_BENCH_DETAILS_BENCH_HPP_INCLUDED
#define NT2_SDK_BENCH_DETAILS_BENCH_HPP_INCLUDED

#include <nt2/sdk/bench/config.hpp>
#include <nt2/sdk/unit/details/unit_test.hpp>

namespace nt2 { namespace details
{
  struct test_suite;

  struct BOOST_SYMBOL_VISIBLE bench : public unit_test
  {
    typedef void (*ptr_fun_t)();

    NT2_TEST_BENCHMARK_DECL
    bench (test_suite const* s = 0, ptr_fun_t c = 0, const char* n = 0);

    virtual NT2_TEST_BENCHMARK_DECL ~bench();
    NT2_TEST_BENCHMARK_DECL virtual   void    process() const;
  };
} }

#endif
