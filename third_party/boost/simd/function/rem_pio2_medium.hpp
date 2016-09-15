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
    Function object implementing rem_pio2_medium capabilities

    Computes the remainder modulo \f$\pi/2\f$ with medium algorithm,
    and the angle quadrant between 0 and 3.

    @par Semantic:

    For every parameter of floating type T

    @code
    T r;
    as_integer<T> n;
    std::tie(n, r) = rem_pio2_medium(x);
    @endcode

    is similar to:

    @code
    as_integer<T> n = div(inearbyint, x, Pio_2<T>());
    T r =  remainder(x, Pio_2<T>());
    @endcode

    @par Note:

    @c rem_pio2_medium compute the remainder modulo \f$\pi/2\f$ with medium algorithm,
    and the angle quadrant between 0 and 3.
    This is a medium_ version version accurate if the input is in:
     \f$[-2^6\pi,2^6\pi]\f$ for float,
     \f$[-2^{18}\pi,2^{18}\pi]\f$ for double.
    \par
    The reduction of the argument modulo \f$\pi/2\f$ is generally
    the most difficult part of trigonometric evaluations.
    The accurate algorithm is over costly and implies the knowledge
    of a few hundred \f$\pi\f$ decimals
    some simpler algorithms as this one
    can be used, but the precision is only insured on smaller intervals.

    @see rem_pio2, rem_pio2_straight,rem_2pi,  rem_pio2_cephes,

  **/
  std::pair<IntegerValue, Value> rem_pio2_medium(Value const & v0);
} }
#endif

#include <boost/simd/function/scalar/rem_pio2_medium.hpp>
#include <boost/simd/function/simd/rem_pio2_medium.hpp>

#endif
