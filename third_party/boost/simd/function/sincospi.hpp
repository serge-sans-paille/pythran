//==================================================================================================
/*!
  @file

    @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_SINCOSPI_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_SINCOSPI_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{

  /*!
    @ingroup group-trigonometric
    This function object computes simultaneously and
    at lower cost the sine and cosine of the input in \f$\pi\f$ multiples.

    @par Header <boost/simd/function/sincospi.hpp>

    @see sincosd, sincos

    @par Example:

      @snippet sincospi.cpp sincospi

    @par Possible output:

      @snippet sincospi.txt sincospi

  **/
  std::pair<IEEEValue, IEEEValue> sincospi(IEEEValue const& x);
} }
#endif

#include <boost/simd/function/scalar/sincospi.hpp>
#include <boost/simd/function/simd/sincospi.hpp>

#endif
