//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_POPCNT_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_POPCNT_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{

 /*!

    @ingroup group-bitwise
    Function object implementing popcnt capabilities

    Returns the number of bit sets in the input.

    @par semantic:
    For any given value @c x of type @c T:

    @code
    as_integer_t<T, unsigned> r = popcnt(x);
    @endcode

    @see  clz, ctz
  **/
  IntegerValue popcnt(Value const & v0);
} }
#endif

#include <boost/simd/function/scalar/popcnt.hpp>
#include <boost/simd/function/simd/popcnt.hpp>

#endif
