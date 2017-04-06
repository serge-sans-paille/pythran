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
    This function object categorizes floating point value into the following categories:
    zero, subnormal, normal, infinite, nan, or implementation-defined.


    @par Header <boost/simd/function/fpclassify.hpp>

    @par Notes

    - fpclassify returns a value of integral type that matches one of the classification
    macro constants, depending on the value of @c x :
    value description:
      - @c FP_INFINITE Positive or negative infinity
      - @c FP_NAN  Not-A-Number
      - @c FP_ZERO Value of zero
      - @c FP_SUBNORMAL  Sub-normal value
      - @c FP_NORMAL Normal value (none of the above)

      These macro constants of type int are defined in header @c cmath

    - Note that each value pertains to a single category: for fpclassify, zero is not a
    normal value.

    - the return type is not @c int : it is the integral signed type
       associated to the floating entry type.


    @par Decorators

      - std_ for floating entries call std::fpclassify and returns @c int

    @see is_eqz, is_denormal, is_normal, is_inf, is_nan


    @par Example:

      @snippet fpclassify.cpp fpclassify

    @par Possible output:

      @snippet fpclassify.txt fpclassify

  **/
  as_integer_t<IEEEValue> fpclassify(IEEEValue const& x);
} }
#endif

#include <boost/simd/function/scalar/fpclassify.hpp>
#include <boost/simd/function/simd/fpclassify.hpp>

#endif
