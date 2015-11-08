//==============================================================================
//         Copyright 2003 - 2012 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012        MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_SDK_UNIT_DETAILS_SUITE_HPP_INCLUDED
#define NT2_SDK_UNIT_DETAILS_SUITE_HPP_INCLUDED

#include <nt2/sdk/unit/config.hpp>
#include <nt2/sdk/unit/details/unit_test.hpp>

namespace nt2 { namespace details
{
  struct BOOST_SYMBOL_VISIBLE test_suite
  {
    NT2_TEST_UNIT_DECL test_suite(unit_test const* t_);

    NT2_TEST_UNIT_DECL virtual ~test_suite();
    NT2_TEST_UNIT_DECL virtual void report() const;
    NT2_TEST_UNIT_DECL virtual void process() const;
    NT2_TEST_UNIT_DECL unit_test const* link(unit_test const* n) const;

    mutable unit_test const*  tests;
  };

  unit_test const dummy;
  test_suite const unit_tests(&dummy);
} }

#endif
