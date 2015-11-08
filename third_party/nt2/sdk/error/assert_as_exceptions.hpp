//==============================================================================
//         Copyright 2003 - 2012 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_SDK_ERROR_ASSERT_AS_EXCEPTIONS_HPP_INCLUDED
#define NT2_SDK_ERROR_ASSERT_AS_EXCEPTIONS_HPP_INCLUDED

/*!
 * \file
 * \brief Defines macros and functions controlling runtime assertions
 */

#if defined(NT2_ASSERTS_AS_EXCEPTIONS) && !defined(BOOST_ENABLE_ASSERT_HANDLER)
#error BOOST_ENABLE_ASSERT_HANDLER must be defined to use NT2_ASSERTS_AS_EXCEPTIONS
#endif

#include <boost/config.hpp>
#if defined(NT2_ASSERTS_AS_EXCEPTIONS) && defined(BOOST_NO_EXCEPTIONS)
#error Exceptions must be enabled to use NT2_ASSERTS_AS_EXCEPTIONS
#endif

#if defined(NT2_ASSERTS_AS_EXCEPTIONS)
#include <nt2/sdk/error/assert_exception.hpp>
#include <boost/assert.hpp>

namespace boost
{
  // INTERNAL ONLY
  // Define a BOOST_ASSERT handler for the NT2_ASSERTS_AS_EXCEPTIONS mode.
  extern inline
  void assertion_failed ( char const* expr, char const* fn
                        , char const* f, long l
                        )
  {
    nt2::except_assertion_failed(expr, fn, f, l);
  }

  // INTERNAL ONLY
  // Define a BOOST_ASSERT_MSG handler for the NT2_ASSERTS_AS_EXCEPTIONS mode.
  extern inline
  void assertion_failed_msg ( char const* expr, char const* msg
                            , char const* fn, char const* f, long l
                            )
  {
    nt2::except_assertion_failed_msg(expr, msg, fn, f, l);
  }
}

#endif

#endif
