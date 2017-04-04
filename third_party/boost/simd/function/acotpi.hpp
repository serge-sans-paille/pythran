//==================================================================================================
/*!
  @file

    @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_ACOTPI_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_ACOTPI_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{

  /*!
    @ingroup group-trigonometric
    This function object returns the inverse cotangent in pi multiples.


    @par Header <boost/simd/function/acotpi.hpp>

    @par Note

      For every parameter of floating type `acotpi(x)`
      returns the arc @c r in the interval  \f$[0, 1[\f$ such
      that <tt>cotpi(r) == x</tt>.

    @see acot, acotd, cotpi


    @par Example:

      @snippet acotpi.cpp acotpi

    @par Possible output:

      @snippet acotpi.txt acotpi

  **/
  IEEEValue acotpi(IEEEValue const & x);
} }
#endif

#include <boost/simd/function/scalar/acotpi.hpp>
#include <boost/simd/function/simd/acotpi.hpp>

#endif
