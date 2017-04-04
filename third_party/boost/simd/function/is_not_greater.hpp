//==================================================================================================
/*!
  @file

    @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_IS_NOT_GREATER_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_IS_NOT_GREATER_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{

  /*!
    @ingroup group-predicates

    This function object returns @ref True if x is not greater than y else returns @ref False.


    @par Header <boost/simd/function/is_not_greater.hpp>

    @par Note

     Using `is_not_greater(x,y)` is similar to: `!(x > y)`

    @par Example:

      @snippet is_not_greater.cpp is_not_greater

    @par Possible output:

      @snippet is_not_greater.txt is_not_greater

  **/
  as_logical_t<Value> is_not_greater(Value const& x, Value const& y);
} }
#endif

#include <boost/simd/function/scalar/is_not_greater.hpp>
#include <boost/simd/function/simd/is_not_greater.hpp>

#endif
