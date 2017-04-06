//==================================================================================================
/*!
  @file

    @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_SECPI_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_SECPI_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{

  /*!
    @ingroup group-trigonometric
    This function object returns the secant of the angle in pi multiples:
    \f$1/\cos(\pi x)\f$.

    @see secd, sec, cospi, cos



    @par Header <boost/simd/function/secpi.hpp>

    @par Example:

      @snippet secpi.cpp secpi

    @par Possible output:

      @snippet secpi.txt secpi

  **/
  IEEEValue secpi(IEEEValue const& x);
} }
#endif

#include <boost/simd/function/scalar/secpi.hpp>
#include <boost/simd/function/simd/secpi.hpp>

#endif
