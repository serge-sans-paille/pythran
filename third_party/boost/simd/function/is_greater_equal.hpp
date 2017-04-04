//==================================================================================================
/*!
  @file

    @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_IS_GREATER_EQUAL_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_IS_GREATER_EQUAL_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{

  /*!

    @ingroup group-predicates
    This function object returns @ref True or @ref False
    according x is greater or equal to y or not.

    Infix notation can be used with operator '>='.


    @par Header <boost/simd/function/is_greater_equal.hpp>

    @par Note

      Using `is_greater_equal(x,y)` is equivalent to `x >= y`

    @see  is_greater, is_gtz

    @par Example:

      @snippet is_greater_equal.cpp is_greater_equal

    @par Possible output:

      @snippet is_greater_equal.txt is_greater_equal

  **/
  as_logical_t<Value> is_greater_equal(Value const& x, Value const& y);
} }
#endif

#include <boost/simd/function/scalar/is_greater_equal.hpp>
#include <boost/simd/function/simd/is_greater_equal.hpp>

#endif
