//==================================================================================================
/*!
  @file

    @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_IS_EQUAL_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_IS_EQUAL_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{

  /*!

    @ingroup group-operator
    This function object returns @ref True or @ref False
    according x and y are equal or not.

    Infix notation can be used with operator '=='


    @par Header <boost/simd/function/is_equal.hpp>

    @par Note

      Using `is_equal(x,y)` is equivalent to `x == y`

    @see  is_not_equal, is_eqz, is_equal_with_equal_nans

    @par Example:

      @snippet is_equal.cpp is_equal

    @par Possible output:

      @snippet is_equal.txt is_equal

  **/
  as_logical_t<Value> is_equal(Value const& x, Value const& y);
} }
#endif

#include <boost/simd/function/scalar/is_equal.hpp>
#include <boost/simd/function/simd/is_equal.hpp>

#endif
