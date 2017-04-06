//==================================================================================================
/*!
  @file

    @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_MINMAG_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_MINMAG_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{

  /*!
    @ingroup group-ieee
    This function object returns the input value which have the least absolute value.


    @par Header <boost/simd/function/minmag.hpp>

    @par Example:

      @snippet minmag.cpp minmag

    @par Possible output:

      @snippet minmag.txt minmag

  **/
  Value minmag(Value const& x, Value const& y);
} }
#endif

#include <boost/simd/function/scalar/minmag.hpp>
#include <boost/simd/function/simd/minmag.hpp>

#endif
