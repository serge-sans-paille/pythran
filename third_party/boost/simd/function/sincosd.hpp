//==================================================================================================
/*!
  @file

    @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_SINCOSD_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_SINCOSD_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{

  /*!
    @ingroup group-trigonometric
    This function object computes simultaneously and
    at lower cost the sind and cosd of the input

    @par Header <boost/simd/function/sincosd.hpp>

    @see sincos, sincospi

    @par Example:

      @snippet sincosd.cpp sincosd

    @par Possible output:

      @snippet sincosd.txt sincosd

  **/
  std::pair<IEEEValue, IEEEValue> sincosd(IEEEValue const& x);
} }
#endif

#include <boost/simd/function/scalar/sincosd.hpp>
#include <boost/simd/function/simd/sincosd.hpp>

#endif
