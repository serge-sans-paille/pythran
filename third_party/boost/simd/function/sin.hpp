//==================================================================================================
/*!
  @file

    @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_SIN_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_SIN_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{

  /*!
    @ingroup group-trigonometric
    This function object returns the sine of the input in radians.


    @par Header <boost/simd/function/sin.hpp>

    @par Note

      As most other trigonometric function @c sin may be called with a second
      optional parameter  which is a tag on speed and accuracy
      (see @ref cos for further details)

    @see sincos, sind, sinpi


    @par Example:

      @snippet sin.cpp sin

    @par Possible output:

      @snippet sin.txt sin

  **/
  IEEEValue sin(IEEEValue const& x);
} }
#endif

#include <boost/simd/function/scalar/sin.hpp>
#include <boost/simd/function/simd/sin.hpp>

#endif
