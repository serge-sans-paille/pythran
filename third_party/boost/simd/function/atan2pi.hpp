//==================================================================================================
/*!
  @file

    @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_ATAN2PI_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_ATAN2PI_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{

  /*!
    @ingroup group-trigonometric
    This function object returns the atan2pi function : atan2 in pi multiples.


    @par Header <boost/simd/function/atan2pi.hpp>

    @par Note

      For every parameters of same floating type `atan2pi(y, x)`
      is similar  to: `atan2(y, x)/Pi`


    @see atan2,  atan2pi

    @par Example:

      @snippet atan2pi.cpp atan2pi

    @par Possible output:

      @snippet atan2pi.txt atan2pi

  **/
  IEEEValue atan2pi(IEEEValue const& y, const IEEEValue& x);
} }
#endif

#include <boost/simd/function/scalar/atan2pi.hpp>
#include <boost/simd/function/simd/atan2pi.hpp>

#endif
