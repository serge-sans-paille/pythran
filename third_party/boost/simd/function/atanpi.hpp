//==================================================================================================
/*!
  @file

    @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_ATANPI_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_ATANPI_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{

  /*!
    @ingroup group-trigonometric
    This function object returns the inverse tangent in \f$\pi\f$ multiples.


    @par Header <boost/simd/function/atanpi.hpp>

    @par Note

      For every parameter of floating type `atanpi(x)`
      returns the arc @c r in the interval  \f$[-0.5, 0.5[\f$
      such that <tt>tanpi(r) == x</tt>.

    @see atan2, atan2d, atand, atan, tanpi


    @par Example:

      @snippet atanpi.cpp atanpi

    @par Possible output:

      @snippet atanpi.txt atanpi

  **/
  IEEEValue atanpi(IEEEValue const& x);
} }
#endif

#include <boost/simd/function/scalar/atanpi.hpp>
#include <boost/simd/function/simd/atanpi.hpp>

#endif
