//==================================================================================================
/*!
  @file

    @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_SQR_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_SQR_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{

  /*!

    @ingroup group-arithmetic
    This function computes the square of its parameter.

    @par Header <boost/simd/function/sqr.hpp>

    @par Decorators

    - saturated_ for integer entries ensure that sqr(x) is never strictly less than x

    @see sqrt, sqr_abs

    @par Example:

      @snippet sqr.cpp sqr

    @par Possible output:

      @snippet sqr.txt sqr


  **/
  Value sqr(Value const& x);
} }
#endif

#include <boost/simd/function/scalar/sqr.hpp>
#include <boost/simd/function/simd/sqr.hpp>

#endif
