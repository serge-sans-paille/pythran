//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_ATAND_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_ATAND_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{

 /*!

    @ingroup group-trigonometric
    Function object implementing atand capabilities

    inverse tangent in degree.

    @par Semantic:

    For every parameter of floating type

    @code
    auto r = atand(x);
    @endcode

    Returns the arc @c r in the interval
    \f$[-90, 90[\f$ such that <tt>tand(r) == x</tt>.

    @see atan2d, atan2, atan, atanpi, tand

  **/
  Value atand(Value const & v0);
} }
#endif

#include <boost/simd/function/scalar/atand.hpp>
#include <boost/simd/function/simd/atand.hpp>

#endif
