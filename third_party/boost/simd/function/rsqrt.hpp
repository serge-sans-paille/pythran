//==================================================================================================
/*!
  @file

    @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_RSQRT_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_RSQRT_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{

  /*!

    @ingroup group-arithmetic
    This function object returns the inverse of the square root of the input.

    @par Header <boost/simd/function/rsqrt.hpp>

    Using `rsqrt(x)` is similar to `One(as(x))/sqrt(x)`

    @par Decorators

    - raw_  if full accuracy is not needed gives access on some architectures to faster
    but less accurate version of the function.

    @see sqrt

    @par Example:

      @snippet rsqrt.cpp rsqrt

    @par Possible output:

      @snippet rsqrt.txt rsqrt


  **/
  IEEEValue rsqrt(IEEEValue const& x);
} }
#endif

#include <boost/simd/function/scalar/rsqrt.hpp>
#include <boost/simd/function/scalar/rsqrt.hpp>
#include <boost/simd/function/simd/rsqrt.hpp>

#endif
