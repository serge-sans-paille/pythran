//==================================================================================================
/*!
  @file

    @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_IS_GREATER_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_IS_GREATER_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{

  /*!

    @ingroup group-predicates
    This function object returns @ref True or @ref False according
    x is greater than y or not.

    Infix notation can be used with operator '>'.



    @par Header <boost/simd/function/is_greater.hpp>

    @par Note

    Using `is_greater(x,y)` is equivalent to `x > y`

    @see  is_greater_equal, is_gtz, is_not_less_equal, is_not_less

    @par Example:

      @snippet is_greater.cpp is_greater

    @par Possible output:

      @snippet is_greater.txt is_greater

  **/
  as_logical_t<Value> is_greater(Value const& x, Value const& y);
} }
#endif

#include <boost/simd/function/scalar/is_greater.hpp>
#include <boost/simd/function/simd/is_greater.hpp>

#endif
