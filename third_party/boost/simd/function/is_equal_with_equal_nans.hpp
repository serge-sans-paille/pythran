//==================================================================================================
/*!
  @file

    @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_IS_EQUAL_WITH_EQUAL_NANS_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_IS_EQUAL_WITH_EQUAL_NANS_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{

  /*!

    @ingroup group-predicates
    This unction object returns @ref True or @ref False according x and y are equal or not.
    Nans are considered equal


    @par Header <boost/simd/function/is_equal_with_equal_nans.hpp>

    @par Note

    Using `is_equal_with_equal_nans(x,y)` is similar to `(x == y) || ((x!= x) && (y!= y))`

    @see Nan

    @par Example:

      @snippet is_equal_with_equal_nans.cpp is_equal_with_equal_nans

    @par Possible output:

      @snippet is_equal_with_equal_nans.txt is_equal_with_equal_nans

  **/
  as_logical_t<Value> is_equal_with_equal_nans(Value const& x, Value const& y);
} }
#endif

#include <boost/simd/function/scalar/is_equal_with_equal_nans.hpp>
#include <boost/simd/function/simd/is_equal_with_equal_nans.hpp>

#endif
