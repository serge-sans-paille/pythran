//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_FPCLASSIFY_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_FPCLASSIFY_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{

 /*!
    @ingroup group-ieee
    Function object implementing fpclassify capabilities

    Categorizes floating point value arg into the following categories:
    zero, subnormal, normal, infinite, NAN, or implementation-defined category.

    @code
    auto r = fpclassify(x);
    @endcode

    This function is similar to std::fpclassify,  but the return type
    is the integral signed type associated to the floating input type.

    If you want the standard behaviour which return an int in scalar mode you
    can use the std_ decorator.

    fpclassify returns a value of integral type that matches one of the classification
    macro constants, depending on the value of x:

    value description:

    - FP_INFINITE Positive or negative infinity
    - FP_NAN  Not-A-Number
    - FP_ZERO Value of zero
    - FP_SUBNORMAL  Sub-normal value
    - FP_NORMAL Normal value (none of the above)

    Note that each value pertains to a single category: for fpclassify zero is not a
    normal value.

    These macro constants of type int are defined in header cmath

    @par Decorators

    std_ for floating entries

    @see is_eqz, is_denormal, is_normal, is_inf, is_nan

  **/
  as_integer_t<Value> fpclassify(Value const & v0);
} }
#endif

#include <boost/simd/function/scalar/fpclassify.hpp>
#include <boost/simd/function/simd/fpclassify.hpp>

#endif
