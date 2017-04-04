//==================================================================================================
/*!
  @file

    @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_MAXMAG_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_MAXMAG_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{

  /*!
    @ingroup group-ieee
    This function object returns the value with the greatest absolute value among
    its arguments.


    @par Header <boost/simd/function/maxmag.hpp>

    @par Example:

      @snippet maxmag.cpp maxmag

    @par Possible output:

      @snippet maxmag.txt maxmag

  **/
  Value maxmag(Value const& x, Value const& y);
} }
#endif

#include <boost/simd/function/scalar/maxmag.hpp>
#include <boost/simd/function/simd/maxmag.hpp>

#endif
