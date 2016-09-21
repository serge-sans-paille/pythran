//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_CTZ_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_CTZ_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{

 /*!

    @ingroup group-bitwise
    Function object implementing ctz capabilities

    Returns the bit count of trailing zeroes

    Finds the first bit set in x, and returns the index of that bit, 0 being
    the least significant bit index.
    @c ctz asserts is the entry is 0

    @par semantic:
    For any given value @c x of type @c T:

    @code
    as_integer_t<T> r = ctz(x);
    @endcode

    @see  clz, popcnt
  **/
  as_integer_t<Value> ctz(Value const & v0);
} }
#endif

#include <boost/simd/function/scalar/ctz.hpp>
#include <boost/simd/function/simd/ctz.hpp>

#endif
