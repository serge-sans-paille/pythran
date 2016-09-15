//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_ATAN2PI_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_ATAN2PI_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{

 /*!

    @ingroup group-trigonometric
    Function object implementing atan2pi capabilities

    atan2pi function : atan2 in pi multiples.

    @par Semantic:

    For every parameters of same floating type

    @code
    auto r = atan2pi(y, x);
    @endcode

    is similar  to:

    @code
    auto r =  atan2(y, x)/Pi;
    @endcode

    as it is quadrant aware.

    For any real arguments @c x and @c y not both equal to zero, <tt>atan2pi(y, x)</tt>
    is the angle in degrees between the positive x-axis of a plane and the point
    given by the coordinates  <tt>(x, y)</tt>.

    It is also the angle in \f$[-1, 1[\f$ for which
    \f$x/\sqrt{x^2+y^2}\f$ and \f$y/\sqrt{x^2+y^2}\f$
    are respectively the sine and the cosine.

    @see atand, atan2, atan2d, atan

  **/
  Value atan2pi(Value const& x, const Value &y);
} }
#endif

#include <boost/simd/function/scalar/atan2pi.hpp>
#include <boost/simd/function/simd/atan2pi.hpp>

#endif
