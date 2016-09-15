//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_REM_2PI_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_REM_2PI_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{

 /*!

    @ingroup group-trigonometric
    Function object implementing rem_2pi capabilities

    compute the remainder modulo \f$2\pi\f$.

    the result is in \f$[-\pi, \pi]\f$. If the input
    is near \f$\pi\f$ the output can be \f$\pi\f$ or \f$-\pi\f$
    depending
    on register disponibility if extended arithmetic is used.

    @par Semantic:

    For every parameter of floating type T

    @code
    T r = rem_2pi(x);
    @endcode

    is similar to:

    @code
    T r = remainder(x, Twopi<T>());
    @endcode

    @see rem_pio2, rem_pio2_straight, rem_pio2_cephes,  rem_pio2_medium,

  **/
  Value rem_2pi(Value const & v0);
} }
#endif

#include <boost/simd/function/scalar/rem_2pi.hpp>
#include <boost/simd/function/simd/rem_2pi.hpp>

#endif
