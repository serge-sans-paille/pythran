//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_ATANPI_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_ATANPI_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{

 /*!

    @ingroup group-trigonometric
    Function object implementing atanpi capabilities

    inverse tangent in \f$\pi\f$ multiples.

    @par Semantic:

    For every parameter of floating type

    @code
    auto r = atanpi(x);
    @endcode

    Returns the arc @c r in the interval
    \f$[-0.5, 0.5[\f$ such that <tt>tanpi(r) == x</tt>.

    @see atan2, atan2d, atand, atan, tanpi

  **/
  Value atanpi(Value const & v0);
} }
#endif

#include <boost/simd/function/scalar/atanpi.hpp>
#include <boost/simd/function/simd/atanpi.hpp>

#endif
