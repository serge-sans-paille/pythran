//==============================================================================
//         Copyright 2003 - 2012 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012        MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_SDK_UNIT_DETAILS_MAIN_HPP_INCLUDED
#define NT2_SDK_UNIT_DETAILS_MAIN_HPP_INCLUDED

#include <nt2/sdk/unit/config.hpp>
#include <nt2/sdk/unit/details/suite.hpp>

namespace nt2 { namespace details
{
  /// INTERNAL ONLY - Actual unit test main function
  NT2_TEST_UNIT_DECL int unit_main(int argc, char* argv[], test_suite const& c);
} }

/// Depending on the mode (normal or driver), the entry point of the test suite
/// is either a regular main() function  of some special symbol.
#ifndef NT2_UNIT_MAIN

/// INTERNAL ONLY
/// Define the name of the test entry point.
#define NT2_UNIT_MAIN main

/// INTERNAL ONLY
/// Define if the test case has to be exported as C or C++ symbol
/// depending on the test is compiled in normal or driver mode.
#define NT2_UNIT_MAIN_SPEC
#else
#define NT2_UNIT_MAIN_SPEC extern "C"
#endif

/// INTERNAL ONLY
/// Define a file specific prefix for test functions that works in both
/// normal and driver mode.
#define NT2_UNIT_PREFIX BOOST_PP_CAT(BOOST_PP_CAT(test_, NT2_UNIT_MAIN), _)

#endif
