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
    Function object implementing rem_pio2_cephes capabilities

    Computes the remainder modulo \f$\pi/2\f$ with cephes algorithm,
    and the angle quadrant between 0 and 3.
    This is a quick version accurate if the input is in \f$[-20\pi,20\pi]\f$.

    @par Semantic:

    For every parameters of floating type T:

    @code
    T r;
    as_integer<T> n;
    std::tie(n, r) = rem_pio2_cephes(x);
    @endcode

    is similar to:

    @code
    as_integer<T> n = div(inearbyint, x, Pio_2<T>());
    T r =  remainder(x, Pio_2<T>());
    @endcode

    The reduction of the argument modulo \f$\pi/2\f$ is generally
    the most difficult part of trigonometric evaluations.
    The accurate algorithm over the whole floating point range
    is over costly and implies the knowledge
    of a few hundred \f$\pi\f$ decimals
    some simpler algorithms as this one
    can be used, but the precision is only insured on specific intervals.

    @see rem_pio2, rem_pio2_straight,rem_2pi, rem_pio2_medium,

  **/
  std::pair<IntegerValue, Value> rem_pio2_cephes(Value const & v0);
} }
#endif

#include <boost/simd/function/scalar/rem_pio2_cephes.hpp>
#include <boost/simd/function/simd/rem_pio2_cephes.hpp>

#endif
