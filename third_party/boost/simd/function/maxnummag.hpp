//==================================================================================================
/*!
  @file

    @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_MAXNUMMAG_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_MAXNUMMAG_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{

  /*!
    @ingroup group-ieee
    This function object returns between two floating point arguments,
    the one  having the greatest absolute value, treating NaNs
    as missing data (between a NaN and a numeric value, the numeric value is chosen).


    @par Header <boost/simd/function/maxnummag.hpp>

    @par Example:

      @snippet maxnummag.cpp maxnummag

    @par Possible output:

      @snippet maxnummag.txt maxnummag

  **/
  Value maxnummag(Value const& x, Value const& y);
} }
#endif

#include <boost/simd/function/scalar/maxnummag.hpp>
#include <boost/simd/function/simd/maxnummag.hpp>

#endif
