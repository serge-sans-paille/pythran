//==================================================================================================
/*!
  @file

    @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_ACOS_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_ACOS_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{

  /*!
    @ingroup group-trigonometric
    This function object returns the inverse cosine in radian.


    @par Header <boost/simd/function/acos.hpp>

    @par Call

    For every parameter of floating type

    @code
    auto r = acos(x);
    @endcode

    Returns the arc @c r in the interval
    \f$[0, \pi[\f$ such that <tt>cos(r) == x</tt>.
    If @c x is outside \f$[-1, 1[\f$ the result is @ref Nan.

    @par Decorators

    - std_           entries provides access to std::acos

    - pedantic_      is accurate on the full \f$[-1, 1[\f$ range

    - the regular version (no decorator) is less accurate around for x < 0.9
      (up to circa 256 ulp), but is faster by a factor 2 than the pedantic version.

    @see acosd, acospi, cos


    @par Example:

      @snippet acos.cpp acos

    @par Possible output:

      @snippet acos.txt acos

  **/
  IEEEValue acos(IEEEValue const & x);
} }
#endif

#include <boost/simd/function/scalar/acos.hpp>
#include <boost/simd/function/simd/acos.hpp>

#endif
