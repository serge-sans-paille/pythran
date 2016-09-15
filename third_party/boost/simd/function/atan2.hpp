//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_ATAN2_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_ATAN2_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{

 /*!

    @ingroup group-trigonometric
    Function object implementing atan2 capabilities

    quadrant aware atan2 function.

    @par Semantic:

    For every parameters @c x and @c y of same floating type

    @code
    auto r = atan2(y, x);
    @endcode

    @par Notes

    - For any real arguments @c x and @c y not both equal to zero, <tt>atan2(y, x)</tt>
    is the angle in radians between the positive x-axis of a plane and the point
    given by the coordinates  <tt>(x, y)</tt>.

    - It is also the angle in \f$[-\pi,\pi[\f$ for which
    \f$x/\sqrt{x^2+y^2}\f$ and \f$y/\sqrt{x^2+y^2}\f$
    are respectively the sine and the cosine.

    - Following IEEE norms
     -  If y is \f$\pm0\f$ and x is negative or -0,\f$\pm\pi\f$ is returned
     -  If y is \f$\pm0\f$ and x is positive or +0, \f$\pm0\f$ is returned
     -  If y is \f$\pm\infty\f$ and x is finite, \f$\pm\pi/2\f$ is returned
     -  If y is \f$\pm\infty\f$ and x is \f$-\infty\f$,\f$\pm3\pi/4\f$ is returned
     -  If y is \f$\pm\infty\f$ and x is \f$+\infty\f$, \f$\pm\pi/4\f$ is returned
     -  If x is \f$\pm0\f$ and y is negative, \f$-\pi/2\f$ is returned
     -  If x is \f$\pm0\f$ and y is positive, \f$+\pi/2\f$  is returned
     -  If x is \f$-\infty\f$ and y is finite and positive, \f$+\pi\f$ is returned
     -  If x is \f$-\infty\f$ and y is finite and negative, \f$-\pi\f$ is returned
     -  If x is \f$+\infty\f$ and y is finite and positive, +0 is returned
     -  If x is \f$+\infty\f$ and y is finite and negative, -0 is returned
     -  If either x is Nan or y is Nan, Nan is returned

    - The fast_ decorator may be used when speed is of essence. In this case, if
      x and y are both either null or infinite, this function will return a Nan result which in fact
      is not more absurd than the IEEE choices. It will be conforming in all other cases.

    @par Decorators

    std_ for floating entries provides access to std::atan2

    fast_ is speedier but as indicated is not fully conformant to the standard

  @see atan, atand, atanpi

  **/
  Value atan2(Value const &y, Value const &x);
} }
#endif

#include <boost/simd/function/scalar/atan2.hpp>
#include <boost/simd/function/simd/atan2.hpp>

#endif
