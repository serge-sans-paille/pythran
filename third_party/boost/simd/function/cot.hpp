//==================================================================================================
/*!
  @file

    @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_COT_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_COT_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{

  /*!
    @ingroup group-trigonometric
    This function object returns the cotangent of the input in radian: \f$\cos(x)/\sin(x)\f$.


    @par Header <boost/simd/function/cot.hpp>

    @par Note

      As most other trigonometric function cot can be called
      with a second optional parameter  which is a tag on speed and accuracy
      (see @ref cos for further details)

    @see cos, sin, tan, cotd, cotpi


    @par Example:

      @snippet cot.cpp cot

    @par Possible output:

      @snippet cot.txt cot

  **/
  IEEEValue cot(IEEEValue const& x);
} }
#endif

#include <boost/simd/function/scalar/cot.hpp>
#include <boost/simd/function/simd/cot.hpp>

#endif
