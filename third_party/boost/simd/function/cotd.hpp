//==================================================================================================
/*!
  @file

    @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_COTD_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_COTD_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{

  /*!
    @ingroup group-trigonometric
    This function object returns the cotangent of input in degree:
    \f$\cos(\pi x/180)/\sin(\pi x/180)\f$.


    @par Header <boost/simd/function/cotd.hpp>

    @par Note

      As most other trigonometric function cotd can be called
      with a second optional parameter  which is a tag on speed
      and accuracy (see @ref cos for further details)

    @see cos, sin, tan, cot, cotpi


    @par Example:

      @snippet cotd.cpp cotd

    @par Possible output:

      @snippet cotd.txt cotd

  **/
  IEEEValue cotd(IEEEValue const& x);
} }
#endif

#include <boost/simd/function/scalar/cotd.hpp>
#include <boost/simd/function/simd/cotd.hpp>

#endif
