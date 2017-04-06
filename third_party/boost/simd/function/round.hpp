//==================================================================================================
/*!
  @file

    @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_ROUND_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_ROUND_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{

  /*!

    @ingroup group-arithmetic
    This function object computes the rounding away from zero of its parameter.


    @par Header <boost/simd/function/round.hpp>

    @par Notes:

    - With a second integral parameter  `round(x,n)` rounds aways from 0 to n digits:
    this is similar to  `round(x*exp10(n))*exp10(-n)`

      - n default to 0,
      - n > 0: round to n digits to the right of the decimal point.
      - n = 0: round to the nearest integer.
      - n < 0: round to n digits to the left of the decimal point.

    - aways from 0 means that half integer values are rounded to the nearest
    integer of greatest absolute value

    The current rounding mode has no effect.

    - If x is \f$\pm\infty\f$ or \f$\pm0\f$, it is returned, unmodified
    - If x is a NaN, a NaN is returned

    @par Example:

      @snippet round.cpp round

    @par Possible output:

      @snippet round.txt round
  **/
  IEEEValue round(IEEEValue const& x, IntegerValue const& n = 0);
} }
#endif

#include <boost/simd/function/scalar/round.hpp>
#include <boost/simd/function/simd/round.hpp>

#endif
