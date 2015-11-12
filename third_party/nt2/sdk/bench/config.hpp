//==============================================================================
//         Copyright 2009 - 2013 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2013 MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_SDK_BENCH_CONFIG_HPP_INCLUDED
#define NT2_SDK_BENCH_CONFIG_HPP_INCLUDED

#include <boost/config.hpp>

#ifdef NT2_TEST_BENCHMARK_DYN_LINK
#  ifdef NT2_TEST_BENCHMARK_SOURCE
#    define NT2_TEST_BENCHMARK_DECL BOOST_SYMBOL_EXPORT
#  else
#    define NT2_TEST_BENCHMARK_DECL BOOST_SYMBOL_IMPORT
#  endif
#else

/// @brief Macro for exporting benchmark public interface
#define NT2_TEST_BENCHMARK_DECL

#endif

#endif
