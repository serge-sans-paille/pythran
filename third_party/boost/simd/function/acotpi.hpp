//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_ACOTPI_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_ACOTPI_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{

 /*!

    @ingroup group-trigonometric
    Function object implementing acotpi capabilities

    inverse cotangent in pi multiples.

    @par Semantic:

    For every parameter of floating type

    @code
    auto r = acotpi(x);
    @endcode

    Returns the arc @c r in the interval
    \f$[0, 1[\f$ such that <tt>cotpi(r) == x</tt>.

    @see acot, acotd, cotpi

  **/
  Value acotpi(Value const & v0);
} }
#endif

#include <boost/simd/function/scalar/acotpi.hpp>
#include <boost/simd/function/simd/acotpi.hpp>

#endif
