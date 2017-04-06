//==================================================================================================
/*!
  @file

    @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_REM_PIO2_CEPHES_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_REM_PIO2_CEPHES_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{

  /*!
    @ingroup group-trigonometric
    This function object returns the Computes the remainder modulo \f$\pi/2\f$ with cephes algorithm,
     and the angle quadrant between 0 and 3.

     This is a quick version accurate if the input is in \f$[-20\pi,20\pi]\f$.


    @par Header <boost/simd/function/rem_pio2_cephes.hpp>

    @par Note

      Using `std::tie(n, r) = rem_pio2_cephes(x)` is similar to
      `n = div(inearbyint, x, Pio_2<T>())` and `r = remainder(x, Pio_2<T>())`


    @par Example:

      @snippet rem_pio2_cephes.cpp rem_pio2_cephes

    @par Possible output:

      @snippet rem_pio2_cephes.txt rem_pio2_cephes

  **/
  std::pair<IEEEValue, IEEEValue> rem_pio2_cephes(IEEEValue const& x);
} }
#endif

#include <boost/simd/function/scalar/rem_pio2_cephes.hpp>
#include <boost/simd/function/simd/rem_pio2_cephes.hpp>

#endif
