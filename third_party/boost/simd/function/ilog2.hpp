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
    Function object implementing ilog2 capabilities

    Returns the integer part of the base 2
    logarithm of the input.

    @par semantic:
    For any given value @c x of type @c T:

    @code
    as_integer_t<T> r = ilog2(x);
    @endcode

    The code is similar to

    @code
    as_integer_t<T> r = toint_s(log2(x));
    @endcode

    @par Note
    This function asserts for negative or null values.

    @see  twopower, exponent

  **/
  as_integer_t<Value> ilog2(Value const& x);
} }
#endif

#include <boost/simd/function/scalar/ilog2.hpp>
#include <boost/simd/function/simd/ilog2.hpp>

#endif
