//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_ACOSPI_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_ACOSPI_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{

 /*!

    @ingroup group-trigonometric
    Function object implementing acospi capabilities

    inverse cosine in \f$\pi\f$ multiples.

    @par Semantic:

    For every parameter of floating type

    @code
    auto r = acospi(x);
    @endcode

    Returns the arc @c r in the interval
    \f$[0, 1[\f$ such that <tt>cospi(r) == x</tt>.
    If @c x is outside \f$[-1, 1[\f$ the result is Nan.

    @see acosd, acos, cospi

  **/
  Value acospi(Value const & v0);
} }
#endif

#include <boost/simd/function/scalar/acospi.hpp>
#include <boost/simd/function/simd/acospi.hpp>

#endif
