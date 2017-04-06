//==================================================================================================
/*!
  @file

    @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_REM_PIO2_MEDIUM_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_REM_PIO2_MEDIUM_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{

  /*!
    @ingroup group-trigonometric
    This function object computes the remainder modulo
    \f$\pi/2\f$ with medium algorithm, and the angle quadrant between 0 and 3.


    @par Header <boost/simd/function/rem_pio2_medium.hpp>

    @par Note:


    - This is a medium version accurate if the input is in:
     \f$[-2^6\pi,2^6\pi]\f$ for float,
     \f$[-2^{18}\pi,2^{18}\pi]\f$ for double.
    \par

    The reduction of the argument modulo \f$\pi/2\f$ is generally
    the most difficult part of trigonometric evaluations.
    The accurate algorithm @ref rem_pio2 is over costly and implies the knowledge
    of a few hundred \f$\pi\f$ decimals
    some simpler algorithms as this one
    can be used, but the precision is only insured on smaller intervals.

    @see rem_pio2, rem_pio2_straight,rem_2pi,  rem_pio2_cephes,


    @par Example:

      @snippet rem_pio2_medium.cpp rem_pio2_medium

    @par Possible output:

      @snippet rem_pio2_medium.txt rem_pio2_medium

  **/
  std::pair<IEEEValue, IEEEValue> rem_pio2_medium(IEEEValue const& x);
} }
#endif

#include <boost/simd/function/scalar/rem_pio2_medium.hpp>
#include <boost/simd/function/simd/rem_pio2_medium.hpp>

#endif
