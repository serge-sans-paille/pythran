//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_ACOT_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_ACOT_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{

 /*!

    @ingroup group-trigonometric
    Function object implementing acot capabilities

    inverse cotangent.

    @par Semantic:

    For every parameter of floating type

    @code
    T r = acot(x);
    @endcode

    Returns the arc @c r in the interval
    \f$[0, \pi[\f$ such that <tt>cot(r) == x</tt>.

    @see acotd, acotpi, cot

  **/
  Value acot(Value const & v0);
} }
#endif

#include <boost/simd/function/scalar/acot.hpp>
#include <boost/simd/function/simd/acot.hpp>

#endif
