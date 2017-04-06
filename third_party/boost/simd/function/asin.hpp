//==================================================================================================
/*!
  @file

    @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_ASIN_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_ASIN_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{

  /*!
    @ingroup group-trigonometric
    This function object returns the inverse sine.


    @par Header <boost/simd/function/asin.hpp>

    @par Note

      For every parameter of floating type `asin(x)`
      returns the arc @c r in the interval  \f$[-\pi/2, \pi/2]\f$ such that
      <tt>sin(r) == x</tt>.  If @c x is outside \f$[-1, 1]\f$ the result is Nan.

    @par Decorators

      - std_ for floating entries provides access to std::asin

    @see asind, asinpi, sin


    @par Example:

      @snippet asin.cpp asin

    @par Possible output:

      @snippet asin.txt asin

  **/
  IEEEValue asin(IEEEValue const & x);
} }
#endif

#include <boost/simd/function/scalar/asin.hpp>
#include <boost/simd/function/simd/asin.hpp>

#endif
