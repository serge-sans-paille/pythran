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
    This function object returns the bit count of trailing zeroes.

   @par Header <boost/simd/function/ctz.hpp>

   @par Notes

    - It finds the first bit set in x, and returns the index of that bit, 0 being
    the least significant bit index.

    - @c ctz asserts is the entry is 0

    @see  clz, popcnt



    @par Header <boost/simd/function/ctz.hpp>

    @par Example:

      @snippet ctz.cpp ctz

    @par Possible output:

      @snippet ctz.txt ctz

  **/
  as_integer_t<Value> ctz(Value const& x);
} }
#endif

#include <boost/simd/function/scalar/ctz.hpp>
#include <boost/simd/function/simd/ctz.hpp>

#endif
