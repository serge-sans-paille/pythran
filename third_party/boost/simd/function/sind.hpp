//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_SIND_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_SIND_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{

 /*!

    @ingroup group-trigonometric
    Function object implementing sind capabilities

    sine of the angle in degree: \f$\sin(\pi x/180)\f$.

    @par Semantic:

    For every parameter of floating type T

    @code
    T r = sind(x);
    @endcode

    @see sincosd, sin, sinpi

    As most other trigonometric function sind can be called with a second optional parameter
    which is a tag on speed and accuracy (see @ref cos for further details)

  **/
  Value sind(Value const & v0);
} }
#endif

#include <boost/simd/function/scalar/sind.hpp>
#include <boost/simd/function/simd/sind.hpp>

#endif
