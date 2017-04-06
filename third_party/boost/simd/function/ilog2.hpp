//==================================================================================================
/*!
  @file

    @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_ILOG2_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_ILOG2_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{

  /*!
    @ingroup group-bitwise
    This function object returns the integer part of the base 2
    logarithm of the input.


    @par Header <boost/simd/function/ilog2.hpp>

    @par Note
    This function asserts for negative or null values.

    @see  twopower, exponent


    @par Example:

      @snippet ilog2.cpp ilog2

    @par Possible output:

      @snippet ilog2.txt ilog2

  **/
  as_integer_t<Value> ilog2(Value const& x);
} }
#endif

#include <boost/simd/function/scalar/ilog2.hpp>
#include <boost/simd/function/simd/ilog2.hpp>

#endif
