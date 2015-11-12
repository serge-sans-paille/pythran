//==============================================================================
//         Copyright 2003 - 2012 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012        MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_SDK_UNIT_DETAILS_UNIT_TEST_HPP_INCLUDED
#define NT2_SDK_UNIT_DETAILS_UNIT_TEST_HPP_INCLUDED

#include <nt2/sdk/unit/config.hpp>

namespace nt2 { namespace details
{
  struct test_suite;

  struct BOOST_SYMBOL_VISIBLE unit_test
  {
    typedef void (*ptr_fun_t)();

    NT2_TEST_UNIT_DECL
    unit_test (test_suite const* s = 0, ptr_fun_t c = 0, const char* n = 0);

    virtual NT2_TEST_UNIT_DECL ~unit_test();

    NT2_TEST_UNIT_DECL virtual   void    process() const;
    NT2_TEST_UNIT_DECL unit_test const*  link(unit_test const* n)  const;
    NT2_TEST_UNIT_DECL void              advance() const;

            ptr_fun_t         call;
            const char*       name;
    mutable unit_test const*  next;
  };
} }

#endif
