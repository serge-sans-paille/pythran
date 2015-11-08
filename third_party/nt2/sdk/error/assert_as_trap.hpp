//==============================================================================
//         Copyright 2003 - 2012 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_SDK_ERROR_ASSERT_AS_TRAP_HPP_INCLUDED
#define NT2_SDK_ERROR_ASSERT_AS_TRAP_HPP_INCLUDED

/*!
 * \file
 * \brief Turn assertions into bug trap
 */

#if defined(NT2_ASSERTS_AS_TRAP) && !defined(BOOST_ENABLE_ASSERT_HANDLER)
#error BOOST_ENABLE_ASSERT_HANDLER must be defined to use NT2_ASSERTS_AS_TRAP
#endif

#if defined(NT2_ASSERTS_AS_TRAP) && defined(BOOST_ENABLE_ASSERT_HANDLER)
#include <cstdio>
#include <boost/assert.hpp>
#include <nt2/sdk/error/trap.hpp>

namespace boost
{
  // INTERNAL ONLY
  // Define a BOOST_ASSERT handler for the NT2_ASSERTS_AS_TRAP mode.
  extern inline
  void assertion_failed ( char const* expr
                        , char const* fn, char const* f, long l
                        )
  {
    fprintf(stderr,"%s:%ld: %s: Assertion %s failed.\n",f,l,fn,expr);
    ::nt2::trap();
  }

  // INTERNAL ONLY
  // Define a BOOST_ASSERT_MSG handler for the NT2_ASSERTS_AS_EXCEPTIONS mode.
  extern inline
  void assertion_failed_msg ( char const* expr, char const* msg
                            , char const* fn, char const* f, long l
                            )
  {
    fprintf(stderr,"%s:%ld: %s: Assertion %s failed.\n\t%s",f,l,fn,expr,msg);
    ::nt2::trap();
  }
}

#endif

#endif
