//==================================================================================================
/*!
  @file

    @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_SQR_ABS_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_SQR_ABS_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{

  /*!
    @ingroup group-arithmetic
    This function computes the square of the absolute value of its parameter.
    For real entries it coincides with @ref sqr.

    @par Header <boost/simd/function/sqr.hpp>

    @par Decorators

    - saturated_ for integer entries ensure that sqr_abs(x) is never strictly less than x

    @see sqrt, sqr

    @par Example:

      @snippet sqr_abs.cpp sqr_abs

    @par Possible output:

      @snippet sqr_abs.txt sqr_abs

  **/
  Value sqr_abs(Value const& x);
} }
#endif

#include <boost/simd/function/scalar/sqr_abs.hpp>
#include <boost/simd/function/simd/sqr_abs.hpp>

#endif
