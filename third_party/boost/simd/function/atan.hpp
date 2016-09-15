//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_ATAN_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_ATAN_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{

 /*!

    @ingroup group-trigonometric
    Function object implementing atan capabilities

    inverse tangent.

    @par Semantic:

    For every parameter of floating type

    @code
    auto r = atan(x);
    @endcode

    Returns the arc @c r in the interval
    \f$[-\pi/2, \pi/2[\f$ such that <tt>tan(r) == x</tt>.

    @par Decorators

    std_ for floating entries  provides access to std::atan

    @see atan2, atand, atanpi, tan

  **/
  Value atan(Value const & v0);
} }
#endif

#include <boost/simd/function/scalar/atan.hpp>
#include <boost/simd/function/simd/atan.hpp>

#endif
