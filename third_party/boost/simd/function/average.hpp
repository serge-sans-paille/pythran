//==================================================================================================
/*!
  @file

    @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_AVERAGE_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_AVERAGE_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
                  {

  /*!
    @ingroup group-arithmetic
    This function object computes the arithmetic mean of its parameters.

    @par Header <boost/simd/abs.hpp>

    @par Notes

    Using `average(x, y)` for floating entries is similar to  `(x+y)/2`

    for integer types, it returns a rounded value at a distance guaranteed
    to be less than or equal to 0.5 of the average floating value, but may differ
    by unity from the truncation given by `(x+y)/2`.

    @par Note:
      This function does not overflow.

    @see meanof

    @par Example:

      @snippet average.cpp average

    @par Possible output:

      @snippet average.txt average


  **/
  Value average(Value const& x, Value const& y);
} }
#endif

#include <boost/simd/function/scalar/average.hpp>
#include <boost/simd/function/simd/average.hpp>

#endif
