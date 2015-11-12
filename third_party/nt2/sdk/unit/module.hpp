//==============================================================================
//         Copyright 2003 - 2012 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012        MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_SDK_UNIT_MODULE_HPP_INCLUDED
#define NT2_SDK_UNIT_MODULE_HPP_INCLUDED

/*!
  @file
  @brief Main Unit test module header
**/

#if defined(NT2_USE_HPX)
#include <hpx/hpx_init.hpp>
#endif

#if defined(DNT2_USE_MAGMA)
#include <magma.h>
#endif

#include <nt2/sdk/config/types.hpp>
#include <nt2/sdk/unit/io.hpp>
#include <nt2/sdk/unit/test_case.hpp>
#include <nt2/sdk/unit/details/suite.hpp>
#include <nt2/sdk/unit/details/unit_test.hpp>
#include <nt2/sdk/unit/details/main.hpp>
#include <nt2/sdk/error/throw_exception.hpp>
#include <nt2/sdk/error/assert_as_flexible.hpp>
#include <nt2/sdk/error/warning_as_flexible.hpp>
#include <nt2/sdk/functor/site.hpp>
#include <nt2/sdk/meta/type_id.hpp>
#include <boost/preprocessor/cat.hpp>
#include <iostream>
#include <string>

#if !defined(NT2_UNIT_MAIN_SUITE)
/// INTERNAL ONLY
#define NT2_UNIT_MAIN_SUITE nt2::details::unit_tests

namespace nt2 { namespace details
{
  inline void unit_test_prologue() {}
} }

#else

namespace nt2 { namespace details
{
  inline void unit_test_prologue()
  {
    std::cout << "CTEST_FULL_OUTPUT" << std::endl;
  }
} }

#endif

#if defined(NT2_USE_HPX)
struct hpx_initializer
{
  hpx_initializer(int argc_, char** argv_) : argc(argc_), argv(argv_) {}

  int operator()(boost::program_options::variables_map&) const
  {
    int res = nt2::details::unit_main(argc,argv,NT2_UNIT_MAIN_SUITE);
    hpx::finalize();
    return res;
  }

private:
  int argc;
  char** argv;
};
#endif

/*!
  @brief Embedded main for testing purposes.

  This function is used as an entry point for the current test.
  In normal mode, it's basically a @c main(). In driver mode, it is a unique
  symbol callable from the driver @c main().
**/

NT2_UNIT_MAIN_SPEC int NT2_UNIT_MAIN(int argc, char* argv[])
{
  ::nt2::details::unit_test_prologue();
  std::cout << "Architecture: " << BOOST_SIMD_STRING << "\n";
  std::cout << "Site: " << nt2::type_id<boost::dispatch::default_site<int>::type>() << "\n",
  std::cout <<  std::string(80,'-') << std::endl;

#if defined(NT2_USE_MAGMA)
  magma_init();
#endif

#if defined(NT2_USE_HPX)
  std::vector<std::string> cfg;
  cfg.push_back("hpx.parcel.port=0");

  using boost::program_options::options_description;
  options_description desc_commandline("Usage: " HPX_APPLICATION_STRING " [options]");
  char *dummy_argv[1] = { const_cast<char*>(HPX_APPLICATION_STRING) };

  return hpx::init(hpx_initializer(argc, argv), boost::program_options::options_description(), 1, dummy_argv, cfg);
#else
  return nt2::details::unit_main(argc,argv,NT2_UNIT_MAIN_SUITE);
#endif
}

#endif
