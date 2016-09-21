//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_ACOSD_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_ACOSD_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{

 /*!

    @ingroup group-trigonometric
    Function object implementing acosd capabilities

    inverse cosine in degree.

    @par Semantic:

    For every parameter of floating type

    @code
    auto r = acosd(x);
    @endcode

    Returns the arc @c r in the interval
    \f$[0, 180[\f$ such that <tt>cosd(r) == x</tt>.
    If @c x is outside \f$[-1, 1[\f$ the result is @ref Nan.

    @see acos, acospi, cosd

  **/
  Value acosd(Value const & v0);
} }
#endif

#include <boost/simd/function/scalar/acosd.hpp>
#include <boost/simd/function/simd/acosd.hpp>

#endif
