//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_TAN_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_TAN_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{

 /*!

    @ingroup group-trigonometric
    Function object implementing tan capabilities

    tangent of the input in radians: \f$\sin(x)/\cos(x)\f$.

    @par Semantic:

    For every parameter of floating type

    @code
    auto r = tan(x);
    @endcode

    As most other trigonometric function tan can be called with a second optional parameter
    which is a tag on speed and accuracy (see @ref cos for further details)

    @see tand, tanpi

  **/
  Value tan(Value const & v0);
} }
#endif

#include <boost/simd/function/scalar/tan.hpp>
#include <boost/simd/function/simd/tan.hpp>

#endif
