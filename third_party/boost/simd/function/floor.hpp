//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_FLOOR_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_FLOOR_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{

 /*!

    @ingroup group-arithmetic
    Function object implementing floor capabilities

    Computes the floor of its parameter.

    @par semantic:
    For any given value @c x of type @c T:

    @code
    T r = floor(x);
    @endcode

    is the greatest integral value of type @c T less or equal to @c x.

    @see  ceil, round, nearbyint, trunc, ifloor

  **/
  Value floor(Value const & v0);
} }
#endif

#include <boost/simd/function/scalar/floor.hpp>
#include <boost/simd/function/simd/floor.hpp>

#endif
