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
    Function object implementing cot capabilities

    cotangent of the input in radian: \f$\cos(x)/\sin(x)\f$.

    @par Semantic:

    For every parameter of floating type

    @code
    auto r = cot(x);
    @endcode


    As most other trigonometric function cot can be called with a second optional parameter
    which is a tag on speed and accuracy (see @ref cos for further details)

    @see cos, sin, tan, cotd, cotpi

  **/
  Value cot(Value const & v0);
} }
#endif

#include <boost/simd/function/scalar/cot.hpp>
#include <boost/simd/function/simd/cot.hpp>

#endif
