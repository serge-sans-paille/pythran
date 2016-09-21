//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_COTPI_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_COTPI_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{

 /*!

    @ingroup group-trigonometric
    Function object implementing cotpi capabilities

    cotangent of input in \f$\pi\f$ multiples: \f$\cos(\pi x)/sin(\pi x)\f$.

    @par Semantic:

    For every parameter of floating type

    @code
    auto r = cotpi(x);
    @endcode

    As most other trigonometric function cotd can be called with a second optional parameter
    which is a tag on speed and accuracy (see @ref cos for further details)

    @see cos, sin, tan, cot, cotpi

  **/
  Value cotpi(Value const & v0);
} }
#endif

#include <boost/simd/function/scalar/cotpi.hpp>
#include <boost/simd/function/simd/cotpi.hpp>

#endif
