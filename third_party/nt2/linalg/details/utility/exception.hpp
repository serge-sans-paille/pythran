//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_LINALG_DETAILS_UTILITY_EXCEPTION_HPP_INCLUDED
#define NT2_LINALG_DETAILS_UTILITY_EXCEPTION_HPP_INCLUDED

#if !defined(BOOST_NO_EXCEPTIONS)
#include <nt2/sdk/error/exception.hpp>
#include <boost/exception/info.hpp>
#endif

namespace nt2
{
  /**
    @brief Low level LAPACK exception

    lapack_exception is thrown when a runtime error is triggered from a
    direct call to a LAPACK kernel.

  **/
  struct BOOST_SYMBOL_VISIBLE lapack_exception : nt2::exception
  {
    /**
    * Builds an assert_exception from the actual runtime assertion message
    **/
    lapack_exception(std::string const& msg) : nt2::exception(msg) {}
  };

  /// @brief Defines LAPACK error information holder
  typedef boost::error_info<struct tag_lapack_error,int> lapack_error;
}

#endif
