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
    Function object implementing average

    Computes the arithmetic mean of its parameters.

    @par semantic:
    For any given value @c x,  @c y of type @c T:

    @code
    T r = average(x, y);
    @endcode

    For floating point values the code is equivalent to:

    @code
    T r = (x+y)/T(2);
    @endcode

    for integer types, it returns a rounded value at a distance guaranteed
    to be less than or equal to 0.5 of the average floating value, but may differ
    by unity from the truncation given by (x1+x2)/T(2).

    @par Note:
      This function does not overflow.

    @see meanof

  **/
  Value average(Value const & v0);
} }
#endif

#include <boost/simd/function/scalar/average.hpp>
#include <boost/simd/function/simd/average.hpp>

#endif
