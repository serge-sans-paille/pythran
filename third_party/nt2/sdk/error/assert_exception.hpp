//==============================================================================
//         Copyright 2012 - 2013 MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_SDK_ERROR_ASSERT_EXCEPTION_HPP_INCLUDED
#define NT2_SDK_ERROR_ASSERT_EXCEPTION_HPP_INCLUDED

#include <nt2/sdk/error/exception.hpp>
#include <boost/throw_exception.hpp>
#include <boost/exception/all.hpp>
#include <iosfwd>
#include <sstream>

namespace nt2
{
  /**
  * @brief Runtime assertion exception
  *
  * assert_exception is thrown when a runtime assertion triggers while the
  * preprocessor symbol NT2_ASSERTS_AS_EXCEPTIONS is defined.
  *
  * @usage
  * @include assert_exception.cpp
  **/
  struct BOOST_SYMBOL_VISIBLE assert_exception : nt2::exception
  {
    /**
    * Builds an assert_exception from the actual runtime assertion message
    **/
    assert_exception(std::string const& msg) : nt2::exception(msg) {}
  };

  // INTERNAL ONLY
  // Define a BOOST_ASSERT handler for the NT2_ASSERTS_AS_EXCEPTIONS mode.
  extern inline
  void except_assertion_failed( char const* expr, char const* fn
                              , char const* f, long l
                              )
  {
    std::ostringstream ss;
    ss << f << ':' << l << ": " << fn << ": Assertion " << expr << " failed.";

    #ifndef BOOST_EXCEPTION_DISABLE
    ::boost::throw_exception
    ( ::boost::enable_error_info( ::nt2::assert_exception(ss.str()) )
      << ::boost::throw_function(fn)
      << ::boost::throw_file(f)
      << ::boost::throw_line(int(l))
    );
    #else
    ::boost::throw_exception( ::nt2::assert_exception(ss.str()) );
    #endif
  }

  // INTERNAL ONLY
  // Define a BOOST_ASSERT_MSG handler for the NT2_ASSERTS_AS_EXCEPTIONS mode.
  extern inline
  void except_assertion_failed_msg( char const* expr, char const* msg
                                  , char const* fn, char const* f, long l
                                  )
  {
    std::ostringstream ss;
    ss  << f << ':' << l << ": " << fn << ": Assertion "
        << expr << " failed.\n\t" << msg;

    #ifndef BOOST_EXCEPTION_DISABLE
    ::boost::throw_exception( ::boost::enable_error_info( ::nt2::assert_exception(ss.str()) ) <<
        ::boost::throw_function(fn) <<
        ::boost::throw_file(f) <<
        ::boost::throw_line(int(l))
    );
    #else
    ::boost::throw_exception( ::nt2::assert_exception(ss.str()) );
    #endif
  }
}

#endif
