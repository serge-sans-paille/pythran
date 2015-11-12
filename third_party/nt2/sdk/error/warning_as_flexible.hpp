//==============================================================================
//         Copyright 2003 - 2012 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_SDK_ERROR_WARNING_AS_FLEXIBLE_HPP_INCLUDED
#define NT2_SDK_ERROR_WARNING_AS_FLEXIBLE_HPP_INCLUDED

/*!
 * \file
 * \brief Defines macros and functions controlling runtime warningions
 */

#include <nt2/sdk/error/log_mode.hpp>
#include <boost/config.hpp>

namespace nt2
{

#ifdef NT2_WARNINGS_AS_FLEXIBLE_SOURCE
  extern BOOST_SYMBOL_EXPORT log_mode_t warning_mode;
#else
  extern BOOST_SYMBOL_IMPORT log_mode_t warning_mode;
#endif
}

#if defined(NT2_WARNINGS_AS_FLEXIBLE_SOURCE) && defined(BOOST_NO_EXCEPTIONS)
#error Exceptions must be enabled to use NT2_WARNINGS_AS_FLEXIBLE
#endif

#ifdef NT2_WARNINGS_AS_FLEXIBLE_SOURCE
#include <nt2/sdk/error/assert_exception.hpp>
#include <nt2/sdk/error/trap.hpp>
#include <nt2/sdk/error/backtrace.hpp>
#include <iostream>

namespace nt2
{
  // INTERNAL ONLY
  // Define a warning handler for NT2 unit tests
  BOOST_SYMBOL_EXPORT
  void warning_handler( char const* expr, char const* msg
                      , char const* fn, char const* f, long l
                      )
  {
    if(nt2::warning_mode & nt2::LOG_PRINT)
      std::cerr << f << ":" << l << ": " << fn << ": warning: " << expr << "\n\t" << msg << std::endl;

    if(nt2::warning_mode & nt2::LOG_STACKDUMP)
      nt2::backtrace(std::cerr);

    if(nt2::warning_mode & nt2::LOG_TRAP)
      nt2::trap();

    if(nt2::warning_mode & nt2::LOG_EXCEPT)
      nt2::except_assertion_failed_msg(expr, msg, fn, f, l);

    if(nt2::warning_mode & nt2::LOG_ABORT)
      std::abort();
  }
}

#endif
#endif
