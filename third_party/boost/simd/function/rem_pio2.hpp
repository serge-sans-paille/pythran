//==================================================================================================
/*!
  @file

    @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_REM_PIO2_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_REM_PIO2_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{

  /*!
    @ingroup group-trigonometric

    This function object computes the remainder modulo \f$\pi/2\f$,
     and the angle quadrant between 0 and 3.

     This is a rather slow version,  but accurate in the full floating range.


    @par Header <boost/simd/function/rem_pio2.hpp>

    @par Notes

     - This algorithm is accurate over  the full floating range,  but also is over
      costly and implies the knowledge  of a few hundred \f$\pi\f$ decimals

     - Some simpler algorithms  @ref rem_pio2_medium, @ref rem_pio2_cephes or @ref rem_pio2_straight
      can often be used, but the precision is only insured on smaller intervals.

      - Using  `std::tie(n, r) = rem_pio2(x);` is similar to ` n = div(inearbyint, x, Pio_2<T>())`
      and `r =  remainder(x, Pio_2<T>())`

    @see rem_pio2_medium, rem_pio2_straight, rem_2pi,  rem_pio2_cephes,

    @par Example:

      @snippet rem_pio2.cpp rem_pio2

    @par Possible output:

      @snippet rem_pio2.txt rem_pio2

  **/
  std::pair<IEEEValue, IEEEValue> rem_pio2(IEEEValue const & x);
} }
#endif

#include <boost/simd/function/scalar/rem_pio2.hpp>
#include <boost/simd/function/simd/rem_pio2.hpp>

#endif
