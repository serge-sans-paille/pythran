//==================================================================================================
/*!
  @file

    @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_SECD_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_SECD_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{

  /*!
    @ingroup group-trigonometric
    This function object returns the secant of the angle in degree:
    \f$1/\cos(\pi x/180)\f$.

    @see cosd, sec, secpi



    @par Header <boost/simd/function/secd.hpp>

    @par Example:

      @snippet secd.cpp secd

    @par Possible output:

      @snippet secd.txt secd

  **/
  IEEEValue secd(IEEEValue const& x);
} }
#endif

#include <boost/simd/function/scalar/secd.hpp>
#include <boost/simd/function/simd/secd.hpp>

#endif
