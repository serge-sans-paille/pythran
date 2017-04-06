//==================================================================================================
/*!
  @file

    @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_IS_NOT_EQUAL_WITH_EQUAL_NANS_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_IS_NOT_EQUAL_WITH_EQUAL_NANS_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{

  /*!
    @ingroup group-predicates

    This function object returns @ref True if x and y are not equal else @ref False,
    nans being considered equal


    @par Header <boost/simd/function/is_not_equal_with_equal_nans.hpp>

    @par Note

     Using `is_not_equal_with_equal_nans(x,y)` is similar to: `(x != y) || ((x!= x) && (y!= y))`

    @par Example:

      @snippet is_not_equal_with_equal_nans.cpp is_not_equal_with_equal_nans

    @par Possible output:

      @snippet is_not_equal_with_equal_nans.txt is_not_equal_with_equal_nans

  **/
  as_logical_t<Value> is_not_equal_with_equal_nans(Value const& x, Value const& y);
} }
#endif

#include <boost/simd/function/scalar/is_not_equal_with_equal_nans.hpp>
#include <boost/simd/function/simd/is_not_equal_with_equal_nans.hpp>

#endif
