//==================================================================================================
/*!
  @file

    @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_REM_PIO2_STRAIGHT_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_REM_PIO2_STRAIGHT_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{

  /*!
    @ingroup group-trigonometric
    This function object returns the Computes the remainder modulo \f$\pi/2\f$.



    @par Header <boost/simd/function/rem_pio2_straight.hpp>

    @par Notes

    - @c rem_pio2_straight computes the remainder modulo \f$\pi/2\f$ with "straight" algorithm,
    and returns an angle quadrant which is always 1.
    This is a very quick version only correct if the input
    is in \f$[\pi/4,\pi/2]\f$.

    - In fact it only substracts \f$\pi/2\f$ to the input
    so it can be viewed as a specially accurate minuspio_2 function outside
    the interval in which it can be used as a substitute to @ref rem_pio2.

    - The reduction of the argument modulo \f$\pi/2\f$ is generally
    the most difficult part of trigonometric evaluations.
    The accurate algorithm over the whole floating point range
    is over costly and implies the knowledge
    of a few hundred \f$\pi\f$ decimals
    some simpler algorithms as this one
    can be used, but the precision is only insured on specific intervals.

    @see rem_pio2, rem_pio2_medium,rem_2pi, rem_pio2_cephes,


    @par Example:

      @snippet rem_pio2_straight.cpp rem_pio2_straight

    @par Possible output:

      @snippet rem_pio2_straight.txt rem_pio2_straight

  **/
  std::pair<IEEEValue, IEEEValue> rem_pio2_straight(IEEEValue const& x);
} }
#endif

#include <boost/simd/function/scalar/rem_pio2_straight.hpp>
#include <boost/simd/function/simd/rem_pio2_straight.hpp>

#endif
