//==================================================================================================
/*!
  @file

    @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_SINCPI_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_SINCPI_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{

  /*!
    @ingroup group-trigonometric
    This function object returns the Computes the sinpi cardinal
    value of its parameter, i.e. \f$sin(\pi x)/(\pi x) \f$.

    @par Header <boost/simd/function/sincpi.hpp>

    @see sin, sinc, sinhc

    @par Example:

      @snippet sincpi.cpp sincpi

    @par Possible output:

      @snippet sincpi.txt sincpi

  **/
  IEEEValue sincpi(IEEEValue const& x);
} }
#endif

#include <boost/simd/function/scalar/sincpi.hpp>
#include <boost/simd/function/simd/sincpi.hpp>

#endif
