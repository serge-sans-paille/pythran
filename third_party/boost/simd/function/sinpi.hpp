//==================================================================================================
/*!
  @file

    @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_SINPI_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_SINPI_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{

  /*!
    @ingroup group-trigonometric
    This function object returns the sine of the parameter in \f$\pi\f$ multiples:
    \f$\sin(\pi x)\f$.

    @par Header <boost/simd/function/sinpi.hpp>

    @see sine, sincospi, sin, sind

    @par Example:

      @snippet sinpi.cpp sinpi

    @par Possible output:

      @snippet sinpi.txt sinpi

  **/
  IEEEValue sinpi(IEEEValue const& x);
} }
#endif

#include <boost/simd/function/scalar/sinpi.hpp>
#include <boost/simd/function/simd/sinpi.hpp>

#endif
