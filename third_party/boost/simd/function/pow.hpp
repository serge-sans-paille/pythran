//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_POW_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_POW_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{

 /*!

    @ingroup group-exponential
    Function object implementing pow capabilities

    Computes \f$x^y\f$

    @par Semantic:

    For every parameters of floating types respectively T, U:

    @code
    T r = pow(x,y);
    @endcode

    is similar to:

    @code
    T r = exp(y*log(x));
    @endcode

    The pow function is conformant to std:pow considering the limits behaviours
    defined by the standard:

         - pow(+0, y), where y is a negative odd integer, returns +Inf
         - pow(-0, y), where y is a negative odd integer, returns -Inf
         - pow(+/-0, y), where y is negative, finite, and is an even integer or a non-integer, returns +Inf
         - pow(+/-0, -Inf) returns +inf
         - pow(+0, y), where y is a positive odd integer, returns +0
         - pow(-0, y), where y is a positive odd integer, returns -0
         - pow(+/-0, y), where y is positive non-integer or a positive even integer, returns +0
         - pow(-1, +/-Inf) returns 1
         - pow(+1, y) returns 1 for any y, even when y is Nan
         - pow(x, +/-0) returns 1 for any x, even when x is Nan
         - pow(x, y) returns Nan if x is finite and negative and y is finite and non-integer.
         - pow(x, -Inf) returns +Inf for any |x|<1
         - pow(x, -Inf) returns +0 for any |x|>1
         - pow(x, +Inf) returns +0 for any |x|<1
         - pow(x, +Inf) returns +Inf for any |x|>1
         - pow(-Inf, y) returns -0 if y is a negative odd integer
         - pow(-Inf, y) returns +0 if y is a negative non-integer or even integer
         - pow(-Inf, y) returns -Inf if y is a positive odd integer
         - pow(-Inf, y) returns +Inf if y is a positive non-integer or even integer
         - pow(+Inf, y) returns +0 for any negative y
         - pow(+Inf, y) returns +Inf for any positive y

      But return a value of the same type as the first parameter, which is necessary for good SIMD behaviour.

      @par Decorators

        -std_ decorator provides access to std:pow

        -fast_ decorator almost nearly uses the naive formula and so doesnot really care for limits and leads to lower

  **/
  Value pow(Value const & v0, Value const& y);
} }
#endif

#include <boost/simd/function/scalar/pow.hpp>
#include <boost/simd/function/simd/pow.hpp>

#endif
